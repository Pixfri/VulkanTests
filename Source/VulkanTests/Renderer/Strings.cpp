// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Renderer/Strings.hpp>

namespace VkTests {
	std::vector<std::string> Split(const std::string& str, const std::string& delimiter) {
		if (str.empty()) {
			return {};
		}

		std::vector<std::string> out;

		std::string buffer = str;
		USize lastFoundPos = 0;
		USize pos;
		while ((pos = buffer.find(delimiter)) != std::string::npos) {
			out.push_back(buffer.substr(0, pos));
			buffer.erase(0, pos + delimiter.length());
			lastFoundPos = lastFoundPos + pos + delimiter.length();
		}

		if (lastFoundPos == str.size()) {
			out.emplace_back("");
		}

		return out;
	}

	std::string Join(const std::vector<std::string>& str, const std::string& separator) {
		std::stringstream out;

		for (auto it = str.begin(); it != str.end(); ++it) {
			out << *it;

			if (it != str.end() - 1) {
				out << separator;
			}
		}

		return out.str();
	}

	std::vector<std::string> Split(const std::string& input, const char delimiter) {
		std::vector<std::string> tokens;

		std::stringstream sstream(input);
		std::string token;
		while (std::getline(sstream, token, delimiter)) {
			tokens.push_back(token);
		}

		return tokens;
	}
}
