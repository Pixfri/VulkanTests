// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_SPIRVREFLECTION_HPP
#define VK_TESTS_RENDERER_SPIRVREFLECTION_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Renderer/Error.hpp>
#include <VulkanTests/Renderer/VkCommon.hpp>
#include <VulkanTests/Renderer/VulkanWrapper/ShaderModule.hpp>

#include <spirv_cross/spirv_glsl.hpp>

namespace VkTests {
    /// Generate a list of shader resources based on SPIR-V reflection code, and provided ShaderVariant.
    class SpirvReflection {
    public:
        /// @brief Reflects shader resources from SPIRV code
        /// @param stage The Vulkan shader stage flag
        /// @param spirv The SPIRV code of shader
        /// @param[out] resources The list of reflected shader resources
        /// @param variant ShaderVariant used for reflection to specify the size of the runtime arrays in Storage Buffers
        /// @return True if reflection was successful, false otherwise
        bool ReflectShaderResources(VkShaderStageFlagBits stage, const std::vector<UInt32>& spirv,
                                    std::vector<ShaderResource>& resources, const ShaderVariant& variant);

    private:
        static void ParseShaderResources(const spirv_cross::Compiler& compiler, VkShaderStageFlagBits stage,
                                         std::vector<ShaderResource>& resources, const ShaderVariant& variant);

        static void ParsePushConstants(const spirv_cross::Compiler& compiler, VkShaderStageFlagBits stage,
                                       std::vector<ShaderResource>& resources, const ShaderVariant& variant);

        static void ParseSpecializationConstants(const spirv_cross::Compiler& compiler, VkShaderStageFlagBits stage,
                                                 std::vector<ShaderResource>& resources, const ShaderVariant& variant);
    };
}

#endif // VK_TESTS_RENDERER_SPIRVREFLECTION_HPP
