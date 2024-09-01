// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Renderer/GlslCompiler.hpp>

#include <glslang/SPIRV/GlslangToSpv.h>
#include <glslang/Public/ResourceLimits.h>
#include <glslang/StandAlone/DirStackFileIncluder.h>

namespace VkTests {
    namespace {
        EShLanguage FindShaderLanguage(const VkShaderStageFlagBits stage) {
            switch (stage) {
            case VK_SHADER_STAGE_VERTEX_BIT:
                return EShLangVertex;

            case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
                return EShLangTessControl;

            case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
                return EShLangTessEvaluation;

            case VK_SHADER_STAGE_GEOMETRY_BIT:
                return EShLangGeometry;

            case VK_SHADER_STAGE_FRAGMENT_BIT:
                return EShLangFragment;

            case VK_SHADER_STAGE_COMPUTE_BIT:
                return EShLangCompute;

            case VK_SHADER_STAGE_RAYGEN_BIT_KHR:
                return EShLangRayGen;

            case VK_SHADER_STAGE_ANY_HIT_BIT_KHR:
                return EShLangAnyHit;

            case VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR:
                return EShLangClosestHit;

            case VK_SHADER_STAGE_MISS_BIT_KHR:
                return EShLangMiss;

            case VK_SHADER_STAGE_INTERSECTION_BIT_KHR:
                return EShLangIntersect;

            case VK_SHADER_STAGE_CALLABLE_BIT_KHR:
                return EShLangCallable;

            case VK_SHADER_STAGE_MESH_BIT_EXT:
                return EShLangMesh;

            case VK_SHADER_STAGE_TASK_BIT_EXT:
                return EShLangTask;

            default:
                return EShLangVertex;
            }
        }
    }

    glslang::EShTargetLanguage GlslCompiler::m_SEnvTargetLanguage = glslang::EShTargetLanguage::EShTargetNone;
    glslang::EShTargetLanguageVersion GlslCompiler::m_SEnvTargetLanguageVersion = static_cast<
        glslang::EShTargetLanguageVersion>(0);

    bool GlslCompiler::CompileToSpirv(VkShaderStageFlagBits stage, const std::vector<UInt8>& glslSource,
                                      const std::string& entryPoint, const ShaderVariant& shaderVariant,
                                      std::vector<UInt32>& spirv, std::string& infoLog) {
        // Initialize the glslang library
        glslang::InitializeProcess();

        auto messages = static_cast<EShMessages>(EShMsgDefault | EShMsgVulkanRules | EShMsgSpvRules);

        EShLanguage language = FindShaderLanguage(stage);
        auto source = std::string(glslSource.begin(), glslSource.end());

        const char* filenameList[1] = {""};
        const char* shaderSource = source.c_str();

        glslang::TShader shader(language);
        shader.setStringsWithLengthsAndNames(&shaderSource, nullptr, filenameList, 1);
        shader.setEntryPoint(entryPoint.c_str());
        shader.setSourceEntryPoint(entryPoint.c_str());
        shader.setPreamble(shaderVariant.GetPreamble().c_str());
        shader.addProcesses(shaderVariant.GetProcesses());
        if (m_SEnvTargetLanguage != glslang::EShTargetLanguage::EShTargetNone) {
            shader.setEnvTarget(m_SEnvTargetLanguage, m_SEnvTargetLanguageVersion);
        }

        DirStackFileIncluder includeDir;
        includeDir.pushExternalLocalDirectory("shaders");

        if (!shader.parse(GetDefaultResources(), 100, false, messages, includeDir)) {
            infoLog = std::string(shader.getInfoLog()) + "\n" + std::string(shader.getInfoDebugLog());
            return false;
        }

        // Add the shader to the new program
        glslang::TProgram program;
        program.addShader(&shader);

        // Link program
        if (!program.link(messages)) {
            infoLog = std::string(program.getInfoLog()) + "\n" + std::string(program.getInfoDebugLog());
            return false;
        }

        // Save any info log that was generated
        if (shader.getInfoLog()) {
            infoLog += std::string(shader.getInfoLog()) + "\n" + std::string(shader.getInfoDebugLog()) + "\n";
        }

        if (program.getInfoLog()) {
            infoLog += std::string(program.getInfoLog()) + "\n" + std::string(program.getInfoDebugLog());
        }

        glslang::TIntermediate* intermediate = program.getIntermediate(language);

        // Translate to SPIR-V
        if (!intermediate) {
            infoLog += "Failed to get shared intermediate code.\n";
            return false;
        }

        spv::SpvBuildLogger logger;

        glslang::GlslangToSpv(*intermediate, spirv, &logger);

        infoLog += logger.getAllMessages() + "\n";

        // Shutdown glslang library.
        glslang::FinalizeProcess();

        return true;
    }
}
