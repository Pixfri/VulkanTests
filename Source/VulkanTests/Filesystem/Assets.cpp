// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Filesystem/Assets.hpp>

#include <VulkanTests/Filesystem/Filesystem.hpp>

#include <VulkanTests/Core/Logger.hpp>

VK_TESTS_DISABLE_WARNINGS()
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
VK_TESTS_ENABLE_WARNINGS()

#ifdef VK_TESTS_PLATFORM_WINDOWS
#include <VulkanTests/Libs/AntiWindows.hpp>
#endif

namespace VkTests::Filesystem {
    namespace Paths {
        const std::unordered_map<Type, std::string> g_RelativePaths = {
            {Type::Assets, "Assets/"},
            {Type::Shaders, "Shaders/"},
            {Type::Storage, "Output/"},
            {Type::Screenshots, "Output/Screenshots/"},
            {Type::Logs, "Output/Logs/"}
        };

        std::string Get(const Type type, const std::string& file) {
            assert(
                g_RelativePaths.size() == Type::TotalRelativePaths &&
                "Not all paths are defined in filesystem, please check that each enum value is specified.");

            // Check for special cases first
            if (type == Type::Temp) {
                return VkTests::Filesystem::Get()->TempDirectory().string();
            }

            // Check for relative paths
            const auto it = g_RelativePaths.find(type);

            if (g_RelativePaths.size() < Type::TotalRelativePaths) {
                Log::Fatal({0x03, 0x00}, "Platform hasn't initialized the paths correctly.");
            } else if (it == g_RelativePaths.end()) {
                Log::Fatal({0x03, 0x01}, "Path enum value doesn't exist, or wasn't specified in the path map.");
            } else if (it->second.empty()) {
                Log::Fatal({0x03, 0x02}, "Path was found, but it is empty.");
            }

            const auto fs = VkTests::Filesystem::Get();
            const auto path = fs->ExternalStorageDirectory() / it->second;

            if (!IsDirectory(path.string())) {
                if (!CreatePath(fs->ExternalStorageDirectory().string(), it->second)) {
                    Log::Fatal({0x03, 0x03}, "Failed to create path: {}.", path.string());
                }
            }

            const auto fullPath = path / file;
            return fullPath.string();
        }
    }

    bool CreatePath(const std::string& root, const std::string& path) {
        bool success = true;

        for (auto it = path.begin(); it != path.end(); ++it) {
            it = std::find(it, path.end(), '/');
            if (!CreateDirectory(root + std::string(path.begin(), it))) {
                success = false;
                break;
            }
        }

        return success;
    }

    void WriteImage(const UInt8* data, const std::string& filename, const UInt32 width, const UInt32 height,
                    const UInt32 components, const UInt32 rowStride) {
        stbi_write_png((Paths::Get(Paths::Type::Screenshots) + filename + ".png").c_str(), static_cast<Int32>(width),
                       static_cast<Int32>(height), static_cast<Int32>(components), data, static_cast<Int32>(rowStride));
    }
}
