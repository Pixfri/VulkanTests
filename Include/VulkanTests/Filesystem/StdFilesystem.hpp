// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_FILESYSTEM_STDFILESYSTEM_HPP
#define VK_TESTS_FILESYSTEM_STDFILESYSTEM_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Filesystem/Filesystem.hpp>

namespace VkTests::Filesystem {
    class StdFilesystem final : public Filesystem {
    public:
        explicit inline StdFilesystem(Path externalStorageDirectory = std::filesystem::current_path(),
                                      Path tempDirectory = std::filesystem::temp_directory_path());
        ~StdFilesystem() override = default;

        StdFilesystem(const StdFilesystem&) = delete;
        StdFilesystem(StdFilesystem&&) = delete;

        StdFilesystem& operator=(const StdFilesystem&) = delete;
        StdFilesystem& operator=(StdFilesystem&&) = delete;

        [[nodiscard]] FileStat           StatFile(const Path& path) override;
        [[nodiscard]] inline bool        IsFile(const Path& path) override;
        [[nodiscard]] inline bool        IsDirectory(const Path& path) override;
        [[nodiscard]] inline bool        Exists(const Path& path) override;
        [[nodiscard]] bool               CreateDirectory(const Path& path) override;
        [[nodiscard]] std::vector<UInt8> ReadChunk(const Path& path, USize offset, USize count) override;
                      void               WriteFile(const Path& path, const std::vector<UInt8>& data) override;
                      void               Remove(const Path& path) override;

                      inline void        SetExternalStorageDirectory(const std::string& dir) override;
        [[nodiscard]] inline const Path& ExternalStorageDirectory() const override;
        [[nodiscard]] inline const Path& TempDirectory() const override;

    private:
        Path m_ExternalStorageDirectory;
        Path m_TempDirectory;
    };
}

#include <VulkanTests/Filesystem/StdFilesystem.inl>

#endif // VK_TESTS_FILESYSTEM_STDFILESYSTEM_HPP
