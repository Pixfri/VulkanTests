// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Platform/Win32/Context.hpp>

#include <stdexcept>

#include <shellapi.h>

namespace VkTests {
	inline std::string GetTempPathFromEnvironment() {
		std::string tempPath = "temp/";

		TCHAR tempBuffer[MAX_PATH];

		if (const DWORD tempPathRet = GetTempPath(MAX_PATH, tempBuffer);
			tempPathRet <= MAX_PATH && tempPathRet != 0) {
			tempPath = std::string(tempBuffer) + "/";
		}

		return tempPath;
	}

	inline std::string WStrToStr(const std::wstring& wStr) {
		if (wStr.empty()) {
			return {};
		}

		const auto wStrLen = static_cast<Int32>(wStr.size());
		const auto strLen = WideCharToMultiByte(CP_UTF8, 0, wStr.data(), wStrLen, nullptr, 0, nullptr, nullptr);

		std::string str(strLen, 0);
		WideCharToMultiByte(CP_UTF8, 0, wStr.data(), wStrLen, str.data(), wStrLen, nullptr, nullptr);

		return str;
	}

	inline std::vector<std::string> GetArgs() {
		Int32 argc;
		LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

		// Ignore the first argument containing the application's full path
		const std::vector<std::wstring> argStrings(argv + 1, argv + argc);
		std::vector<std::string> args;

		args.reserve(argStrings.size());
		for (auto& arg : argStrings) {
			args.push_back(WStrToStr(arg));
		}

		return args;
	}

	WindowsPlatformContext::WindowsPlatformContext(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine,
	                                               INT nCmdShow) : PlatformContext{} {
		m_ExternalStorageDirectory = "";
		m_TempDirectory = GetTempPathFromEnvironment();
		m_Arguments = GetArgs();

		// Attempt to attach to the parent process console if it exists.
		if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
			// No parent console, allocate a new one for this process
			if (!AllocConsole()) {
				throw std::runtime_error{"Failed to allocate console"};
			}
		}

		FILE* fp;
		if (!freopen_s(&fp, "conin$", "r", stdin) ||
			!freopen_s(&fp, "conout$", "w", stdout) ||
			!freopen_s(&fp, "conout$", "w", stderr)) {
			throw std::runtime_error{"Failed to open console streams"};
		}
	}
}
