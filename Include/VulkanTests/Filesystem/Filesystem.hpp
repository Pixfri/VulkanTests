// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_FILESYSTEM_FILESYSTEM_HPP
#define VK_TESTS_FILESYSTEM_FILESYSTEM_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Platform/Context.hpp>

namespace VkTests::Filesystem {
    struct FileStat {
        bool IsFile;
        bool IsDirectory;
        USize Size;
    };

    using Path = std::filesystem::path;
    
    class Filesystem {
    public:
        Filesystem() = default;
        virtual ~Filesystem() = default;

        Filesystem(const Filesystem&) = delete;
        Filesystem(Filesystem&&) = delete;

        Filesystem& operator=(const Filesystem&) = delete;
        Filesystem& operator=(Filesystem&&) = delete;

        [[nodiscard]] virtual FileStat           StatFile(const Path& path)                                  = 0; 
        [[nodiscard]] virtual bool               IsFile(const Path& path)                                    = 0;
        [[nodiscard]] virtual bool               IsDirectory(const Path& path)                               = 0;
        [[nodiscard]] virtual bool               Exists(const Path& path)                                    = 0;
        [[nodiscard]] virtual bool               CreateDirectory(const Path& path)                           = 0;
        [[nodiscard]] virtual std::vector<UInt8> ReadChunk(const Path& path, USize offset, USize count)      = 0;
                      virtual void               WriteFile(const Path& path, const std::vector<UInt8>& data) = 0;
                      virtual void               Remove(const Path& path)                                    = 0;

                      virtual void        SetExternalStorageDirectory(const std::string& dir)  = 0;
        [[nodiscard]] virtual const Path& ExternalStorageDirectory() const                     = 0;
        [[nodiscard]] virtual const Path& TempDirectory() const                                = 0;

        inline void WriteFile(const Path& path, const std::string& data);

        // Read the entire file into a string.
        [[nodiscard]] inline std::string ReadFileString(const Path& path);

        // Read the entire file into a vector of bytes.
        [[nodiscard]] inline std::vector<UInt8> ReadFileBinary(const Path& path);
    };

    using FilesystemPtr = std::shared_ptr<Filesystem>;

    void Initialize();

    void InitializeWithContext(const PlatformContext& context);

    // Get the filesystem instance.
    FilesystemPtr Get();
}

#include <VulkanTests/Filesystem/Filesystem.inl>

#endif // VK_TESTS_FILESYSTEM_FILESYSTEM_HPP
