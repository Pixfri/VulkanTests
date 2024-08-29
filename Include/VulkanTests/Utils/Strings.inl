// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests {
	inline std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
		USize startPos = 0;
		while ((startPos = str.find(from, startPos)) != std::string::npos) {
			str.replace(startPos, from.length(), to);
			startPos += to.length() - 1;
		}

		return str;
	}

	inline std::string TrimRight(const std::string& str, const std::string& chars) {
		std::string result = str;
		result.erase(str.find_last_not_of(chars) + 1);
		return result;
	}

	inline std::string TrimLeft(const std::string& str, const std::string& chars) {
		std::string result = str;
		result.erase(0, str.find_last_not_of(chars));
		return result;
	}
}
