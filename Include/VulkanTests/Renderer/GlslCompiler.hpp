// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_GLSLCOMPILER_HPP
#define VK_TESTS_RENDERER_GLSLCOMPILER_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Renderer/Error.hpp>

#include <glslang/Public/ShaderLang.h>

#include <VulkanTests/Renderer/VkCommon.hpp>

namespace VkTests {
	class GlslCompiler {
		static glslang::EShTargetLanguage m_SEnvTargetLanguage;
		static glslang::EShTargetLanguageVersion m_SEnvTargetLanguageVersion;

	public:
		GlslCompiler() = default;
		~GlslCompiler() = default;

		GlslCompiler(const GlslCompiler&) = delete;
		GlslCompiler(GlslCompiler&&) = delete;

		GlslCompiler& operator=(const GlslCompiler&) = delete;
		GlslCompiler& operator=(GlslCompiler&&) = delete;

		static void SetTargetEnvironment(glslang::EShTargetLanguage targetLanguage,
		                                 glslang::EShTargetLanguageVersion targetLanguageVersion);

		static void ResetTargetEnvironment();

		bool CompileToSpirv(VkShaderStageFlagBits stage, const std::vector<UInt8>& glslSource,
		                    const std::string& entryPoint, const ShaderVariant& shaderVariant,
		                    std::vector<UInt32>& spirv, std::string& infoLog);

	private:
	};
}

#include <VulkanTests/Renderer/GlslCompiler.inl>

#endif // VK_TESTS_RENDERER_GLSLCOMPILER_HPP
