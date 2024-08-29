// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests {
	inline const std::vector<std::string>& PlatformContext::Arguments() const {
		return m_Arguments;
	}

	inline const std::string& PlatformContext::ExternalStorageDirectory() const {
		return m_ExternalStorageDirectory;
	}

	inline const std::string& PlatformContext::TempDirectory() const {
		return m_TempDirectory;
	}
}
