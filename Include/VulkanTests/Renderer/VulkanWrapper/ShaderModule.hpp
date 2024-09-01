// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_VULKANWRAPPER_SHADERMODULE_HPP
#define VK_TESTS_RENDERER_VULKANWRAPPER_SHADERMODULE_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Renderer/VkCommon.hpp>

#include <spirv_cross/spirv_cross.hpp>

namespace VkTests {
    class Device;

    /// Types of shader resources
    enum class ShaderResourceType : UInt8 {
        Input,
        InputAttachment,
        Output,
        Image,
        ImageSampler,
        ImageStorage,
        Sampler,
        BufferUniform,
        BufferStorage,
        PushConstant,
        SpecializationConstant,
        All
    };

    enum class ShaderResourceMode : UInt8 {
        Static,
        Dynamic,
        UpdateAfterBind
    };

    struct ShaderResourceQualifier {
        enum : UInt32 {
            None = 0,
            NonReadable = 1 << 0,
            NonWritable = 1 << 1,
        };
    };

    struct ShaderResource {
        VkShaderStageFlags Stages;

        ShaderResourceType Type;
        ShaderResourceMode Mode;

        UInt32 Set;
        UInt32 Binding;
        UInt32 Location;
        UInt32 InputAttachmentIndex;
        UInt32 VecSize;
        UInt32 Columns;
        UInt32 ArraySize;
        UInt32 Offset;
        UInt32 Size;
        UInt32 ConstantId;
        UInt32 Qualifiers;

        std::string Name;
    };

    /**
     * @brief Adds support for C-style preprocessor macros to glsl shaders
     *        enabling definitions and un-definitions of certain symbols.
     */
    class ShaderVariant {
    public:
        ShaderVariant() = default;

        ShaderVariant(std::string&& preamble, std::vector<std::string>&& processes);

        [[nodiscard]] inline USize GetId() const;

        /**
         * @brief Add definitions to the shader variant.
         * @param definitions Vector of definitions to add to the shader variant.
         */
        void AddDefinitions(const std::vector<std::string>& definitions);

        /**
         * @brief Adds a define macro to the shader variant.
         * @param def String which should go to the right of a define directive.
         */
        void AddDefine(const std::string& def);

        /**
         * @brief Adds an undef macro to the shader variant.
         * @param undef String which should go to the right of an undef directive.
         */
        void AddUndefine(const std::string& undef);

        /**
         * @brief Specifies the size of a named runtime array for automatic reflection. If already specified, overrides the size.
         * @param runtimeArrayName String under which the runtime array is named in the shader
         * @param size Integer specifying the wanted size of the runtime array (in number of elements, not size in bytes), used for automatic allocation of buffers.
         * See get_declared_struct_size_runtime_array() in spirv_cross
         */
        void AddRuntimeArraySize(const std::string& runtimeArrayName, USize size);

        inline void SetRuntimeArraySizes(const std::unordered_map<std::string, USize>& sizes);

        [[nodiscard]] inline const std::string& GetPreamble() const;

        [[nodiscard]] inline const std::vector<std::string>& GetProcesses() const;

        [[nodiscard]] inline const std::unordered_map<std::string, USize>& GetRuntimeArraySizes() const;

        void Clear();

    private:
        USize m_Id;

        std::string m_Preamble;

        std::vector<std::string> m_Processes;

        std::unordered_map<std::string, USize> m_RuntimeArraySizes;

        void UpdateId();
    };

    class ShaderSource {
    public:
        ShaderSource() = default;

        explicit ShaderSource(const std::string& filename);

        [[nodiscard]] inline USize GetId() const;

        [[nodiscard]] inline const std::string& GetFilename() const;

        inline void SetSource(const std::string& source);

        [[nodiscard]] inline const std::string& GetSource() const;

    private:
        USize m_Id;

        std::string m_Filename;

        std::string m_Source;
    };

    /**
     * @brief Contains shader code, with an entry point, for a specific shader stage.
     * It is needed by a PipelineLayout to create a Pipeline.
     * ShaderModule can do auto-pairing between shader code and textures.
     * The low level code can change bindings, just keeping the name of the texture.
     * Variants for each texture are also generated, such as HAS_BASE_COLOR_TEX.
     * It works similarly for attribute locations. A current limitation is that only
     * set 0 is considered. Uniform buffers are currently hardcoded as well.
     */
    class ShaderModule {
    public:
        ShaderModule(Device& device, VkShaderStageFlagBits stage, const ShaderSource& glslSource,
                     const std::string& entryPoint, const ShaderVariant& shaderVariant);

        ShaderModule(const ShaderModule&) = delete;

        ShaderModule(ShaderModule&& other) noexcept;

        ShaderModule& operator=(const ShaderModule&) = delete;

        ShaderModule& operator=(ShaderModule&&) = delete;

        [[nodiscard]] inline USize GetId() const;

        [[nodiscard]] inline VkShaderStageFlagBits GetStage() const;

        [[nodiscard]] inline const std::string& GetEntryPoint() const;

        [[nodiscard]] inline const std::vector<ShaderResource>& GetResources() const;

        [[nodiscard]] inline const std::string& GetInfoLog() const;

        [[nodiscard]] inline const std::vector<UInt32>& GetBinary() const;

        [[nodiscard]] inline const std::string& GetDebugName() const;

        inline void SetDebugName(const std::string& name);

        /**
         * @brief Flags a resource to use a different method of being bound to the shader
         * @param resourceName The name of the shader resource
         * @param mode The mode of how the shader resource will be bound
         */
        void SetResourceMode(const std::string& resourceName, const ShaderResourceMode& mode);

    private:
        Device& m_Device;

        USize m_Id;

        VkShaderStageFlagBits m_Stage{};

        std::string m_EntryPoint;

        std::string m_DebugName;

        std::vector<UInt32> m_Spirv;

        std::vector<ShaderResource> m_Resources;

        std::string m_InfoLog;
    };
}

#include <VulkanTests/Renderer/VulkanWrapper/ShaderModule.inl>

#endif // VK_TESTS_RENDERER_VULKANWRAPPER_SHADERMODULE_HPP
