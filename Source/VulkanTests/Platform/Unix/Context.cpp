// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Platform/Unix/Context.hpp>

namespace VkTests {
    UnixPlatformContext::UnixPlatformContext(const int argc, char** argv) : PlatformContext{} {
        m_Arguments.reserve(argc);
        for (Int32 i = 1; i < argc; i++) {
            m_Arguments.emplace_back(argv[i]);
        }

        const char* envTempDir = std::getenv("TMPDIR");
        m_TempDirectory = envTempDir ? std::string(envTempDir) + "/" : "/tmp/";
        m_ExternalStorageDirectory = "";
    }

}
