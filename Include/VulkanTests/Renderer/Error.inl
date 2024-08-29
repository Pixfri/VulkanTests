// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests {
	inline const char* VulkanException::what() const noexcept {
		return m_ErrorMessage.c_str();
	}
}
