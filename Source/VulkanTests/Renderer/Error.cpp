// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Renderer/Error.hpp>

namespace VkTests {
	VulkanException::VulkanException(VkResult result, const std::string& message) : std::runtime_error(message),
		Result{result} {
		m_ErrorMessage = std::string(std::runtime_error::what()) + std::string{" : "} + ToString(result);
	}
}
