// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Filesystem/StdFilesystem.hpp>

#include <VulkanTests/Core/Logger.hpp>

#ifdef VK_TESTS_PLATFORM_WINDOWS
#include <VulkanTests/Libs/AntiWindows.hpp>
#endif

namespace VkTests::Filesystem {
    FileStat StdFilesystem::StatFile(const Path& path) {
        std::error_code ec;
        const auto fsStat = std::filesystem::status(path, ec);
        if (ec) {
            Log::Error("Failed to retrieve status for path: {0}; Error: {1}", path.string(), ec.message());
            return FileStat{false, false, 0};
        }

        auto size = std::filesystem::file_size(path, ec);
        if (ec) {
            size = 0;
        }

        return FileStat{
            fsStat.type() == std::filesystem::file_type::regular,
            fsStat.type() == std::filesystem::file_type::directory,
            size
        };
    }

    bool StdFilesystem::CreateDirectory(const Path& path) {
        std::error_code ec;

        std::filesystem::create_directory(path, ec);

        if (ec) {
            Log::Error("Failed to create directory at path: {0}: Error: {1}", path.string(), ec.message());
        }

        return !ec;
    }

    std::vector<UInt8> StdFilesystem::ReadChunk(const Path& path, const USize offset, const USize count) {
        std::ifstream file{path, std::ios::binary | std::ios::ate};

        if (!file.is_open()) {
            Log::Error("Failed to open file at path: {0}", path.string());
        }

        if (const auto size = StatFile(path).Size;
            offset + count > size) {
            return {};
        }

        file.seekg(static_cast<std::istream::off_type>(offset), std::ios::beg);
        std::vector<UInt8> data(count);
        file.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(count));

        return data;
    }

    void StdFilesystem::WriteFile(const Path& path, const std::vector<UInt8>& data) {
        // Create directory if it doesn't exist
        if (const auto parent = path.parent_path();
            !std::filesystem::exists(parent)) {
            if (!CreateDirectory(path)) {
                Log::Error("Failed to create parent directory for path: {}", path.string());
            }
        }
        
        std::ofstream file{path, std::ios::binary | std::ios::trunc};

        if (!file.is_open()) {
            Log::Error("Failed to open file at path: {}", path.string());
        }

        file.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
    }

    void StdFilesystem::Remove(const Path& path) {
        std::error_code ec;

        std::filesystem::remove(path, ec);

        if (ec) {
            Log::Error("Failed to remove path: {0}; Error: {1}", path.string(), ec.message());
        }
    }

}
