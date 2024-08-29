// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_VULKANWRAPPER_SHADERMODULE_HPP
#define VK_TESTS_RENDERER_VULKANWRAPPER_SHADERMODULE_HPP

#include <VulkanTests/pch.hpp>

namespace VkTests {
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

	class ShaderModule {
	public:
		ShaderModule() = default;
		~ShaderModule() = default;

		ShaderModule(const ShaderModule&) = delete;
		ShaderModule(ShaderModule&&) = delete;

		ShaderModule& operator=(const ShaderModule&) = delete;
		ShaderModule& operator=(ShaderModule&&) = delete;

	private:
	};
}

#include <VulkanTests/Renderer/VulkanWrapper/ShaderModule.inl>

#endif // VK_TESTS_RENDERER_VULKANWRAPPER_SHADERMODULE_HPP
