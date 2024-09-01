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

		/**
		 * @brief Set the glslang target environment to translate to when generating code.
		 * @param targetLanguage The language to translate to.
		 * @param targetLanguageVersion The version of the target language.
		 */
		static void SetTargetEnvironment(glslang::EShTargetLanguage targetLanguage,
		                                 glslang::EShTargetLanguageVersion targetLanguageVersion);

		/**
		 * @brief Reset the glslang target environment to the default values.
		 */
		static void ResetTargetEnvironment();

		/**
		 * @brief Compiles GLSL to SPIR-V bytecode.
		 * @param stage The Vulkan shader stage flag.
		 * @param glslSource The GLSL source code to be compiled.
		 * @param entryPoint The entry point name of the shader.
		 * @param shaderVariant The shader variant.
		 * @param[out] spirv The generated SPIR-V code.
		 * @param[out] infoLog Stores any log messages during the compilation process. 
		 * @return True if the compilation was successful, false otherwise.
		 */
		static bool CompileToSpirv(VkShaderStageFlagBits stage, const std::vector<UInt8>& glslSource,
		                           const std::string& entryPoint, const ShaderVariant& shaderVariant,
		                           std::vector<UInt32>& spirv, std::string& infoLog);
	};
}

#include <VulkanTests/Renderer/GlslCompiler.inl>

#endif // VK_TESTS_RENDERER_GLSLCOMPILER_HPP
