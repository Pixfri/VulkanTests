// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Filesystem/Filesystem.hpp>
#include <VulkanTests/Filesystem/StdFilesystem.hpp>

namespace VkTests::Filesystem {
    namespace {
        FilesystemPtr g_filesystem = nullptr;
    }

    void Initialize() {
        g_filesystem = std::make_shared<StdFilesystem>();
    }

    void InitializeWithContext(const PlatformContext& context) {
        g_filesystem = std::make_shared<StdFilesystem>(context.ExternalStorageDirectory(), context.TempDirectory());
    }

    FilesystemPtr Get() {
        assert(g_filesystem && "Filesystem not initialized.");
        return g_filesystem;
    }

}
