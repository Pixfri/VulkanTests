// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp


#include <VulkanTests/Renderer/VulkanWrapper/ShaderModule.hpp>

#include <VulkanTests/Renderer/Strings.hpp>
#include <VulkanTests/Renderer/Error.hpp>
#include <VulkanTests/Renderer/GlslCompiler.hpp>
#include <VulkanTests/Renderer/SpirvReflection.hpp>

#include <VulkanTests/Filesystem/Assets.hpp>

namespace VkTests {
    ShaderVariant::ShaderVariant(std::string&& preamble, std::vector<std::string>&& processes)
        : m_Preamble(std::move(preamble)), m_Processes(std::move(processes)) {
        UpdateId();
    }

    void ShaderVariant::AddDefinitions(const std::vector<std::string>& definitions) {
        for (auto& definition : definitions) {
            AddDefine(definition);
        }
    }

    void ShaderVariant::AddDefine(const std::string& def) {
        m_Processes.push_back("D" + def);

        std::string tempDef = def;

        // The "=" needs to turn into a space.
        if (const USize posEqual = tempDef.find_first_of('=');
            posEqual != std::string::npos) {
            tempDef[posEqual] = ' ';
        }

        m_Preamble.append("#define " + tempDef + "\n");

        UpdateId();
    }

    void ShaderVariant::AddUndefine(const std::string& undef) {
        m_Processes.push_back("U" + undef);

        m_Preamble.append("#undef " + undef + "\n");

        UpdateId();
    }

    void ShaderVariant::AddRuntimeArraySize(const std::string& runtimeArrayName, USize size) {
        if (m_RuntimeArraySizes.contains(runtimeArrayName)) {
            m_RuntimeArraySizes.insert({runtimeArrayName, size});
            return;
        }

        m_RuntimeArraySizes[runtimeArrayName] = size;
    }

    void ShaderVariant::Clear() {
        m_Preamble.clear();
    }

    void ShaderVariant::UpdateId() {
        constexpr std::hash<std::string> hasher;
        m_Id = hasher(m_Preamble);
    }

    ShaderSource::ShaderSource(const std::string& filename) : m_Filename(filename),
                                                              m_Source(Filesystem::ReadShader(filename)) {
        constexpr std::hash<std::string> hasher{};
        m_Id = hasher(std::string{m_Source.cbegin(), m_Source.cend()});
    }

    /**
     * @brief Pre-compiles project shader files to include header code.
     * @param source The shader file in a string
     * @return An array containing the final shader.
     */
    inline std::vector<std::string> PrecompileShader(const std::string& source) {
        std::vector<std::string> finalFile;

        for (const auto lines = Split(source, '\n');
             auto& line : lines) {
            if (line.starts_with("#include \"")) {
                // Include paths are relative to the base shader directory
                std::string includePath = line.substr(10);
                const USize lastQuote = includePath.find('\"');
                if (!includePath.empty() && lastQuote != std::string::npos) {
                    includePath = includePath.substr(0, lastQuote);
                }

                auto includeFile = PrecompileShader(Filesystem::ReadShader(includePath));
                for (auto& includeFileLine : includeFile) {
                    finalFile.push_back(includeFileLine);
                }
            } else {
                finalFile.push_back(line);
            }
        }

        return finalFile;
    }

    inline std::vector<UInt8> ConvertToBytes(std::vector<std::string>& lines) {
        std::vector<UInt8> bytes;

        for (auto& line : lines) {
            line += '\n';
            std::vector<UInt8> lineBytes(line.begin(), line.end());
            bytes.insert(bytes.end(), lineBytes.begin(), lineBytes.end());
        }

        return bytes;
    }

    ShaderModule::ShaderModule(Device& device, const VkShaderStageFlagBits stage, const ShaderSource& glslSource,
                               const std::string& entryPoint, const ShaderVariant& shaderVariant)
        : m_Device(device), m_Stage(stage), m_EntryPoint(entryPoint) {
        m_DebugName = fmt::format("{} [variant: {:X}] [entrypoint {}]", glslSource.GetFilename(), shaderVariant.GetId(),
                                  entryPoint);

        // Compiling from GLSL source requires the entry point
        if (entryPoint.empty()) {
            throw VulkanException{VK_ERROR_INITIALIZATION_FAILED, "Shader entry point is empty"};
        }

        const auto& source = glslSource.GetSource();

        // Check if application is passing in GLSL source code to compile to SPIR-V
        if (source.empty()) {
            throw VulkanException{VK_ERROR_INITIALIZATION_FAILED, "Shader source is empty"};
        }

        // Precompile the shader source into the final SPIR-V bytecode

        if (auto glslFinalSource = PrecompileShader(source);
            !GlslCompiler::CompileToSpirv(stage, ConvertToBytes(glslFinalSource), entryPoint, shaderVariant, m_Spirv,
                                          m_InfoLog)) {
            Log::Error("Shader compilation failed for shader \"{}\"", glslSource.GetFilename());
            Log::Error("{}", m_InfoLog);
            throw VulkanException{VK_ERROR_INITIALIZATION_FAILED, "Shader compilation failed"};
        }

        // Reflect all shader resources
        if (SpirvReflection spirvReflection;
            !spirvReflection.ReflectShaderResources(stage, m_Spirv, m_Resources, shaderVariant)) {
            throw VulkanException{VK_ERROR_INITIALIZATION_FAILED, "Shader reflection failed"};
        }

        // Generate a unique id, determined by source and variant
        constexpr std::hash<std::string> hasher{};
        m_Id = hasher(std::string{reinterpret_cast<const char*>(m_Spirv.data()),
            reinterpret_cast<const char*>(m_Spirv.data() + m_Spirv.size())});
    }


    ShaderModule::ShaderModule(ShaderModule&& other) :
        m_Device{other.m_Device},
        m_Id{other.m_Id},
        m_Stage{other.m_Stage},
        m_EntryPoint{std::move(other.m_EntryPoint)},
        m_DebugName{std::move(other.m_DebugName)},
        m_Spirv{std::move(other.m_Spirv)},
        m_Resources{std::move(other.m_Resources)},
        m_InfoLog{std::move(other.m_InfoLog)} {
        other.m_Stage = {};
    }

    void ShaderModule::SetResourceMode(const std::string& resourceName, const ShaderResourceMode& mode) {
        const auto it = std::ranges::find_if(m_Resources, [&resourceName](const ShaderResource& resource) {
            return resource.Name == resourceName;
        });

        if (it != m_Resources.end()) {
            if (mode == ShaderResourceMode::Dynamic) {
                if (it->Type == ShaderResourceType::BufferUniform || it->Type == ShaderResourceType::BufferStorage) {
                    it->Mode = mode;
                } else {
                    Log::Warn("Resource \"{}\" does not support dynamic.", resourceName);
                }
            } else {
                it->Mode = mode;
            }
        } else {
            Log::Warn("Resource \"{}\" not found.", resourceName);
        }
    }
}
