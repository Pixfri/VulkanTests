// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests::Filesystem {
    inline StdFilesystem::StdFilesystem(Path externalStorageDirectory, Path tempDirectory) :
        m_ExternalStorageDirectory(std::move(externalStorageDirectory)), m_TempDirectory(std::move(tempDirectory)) {
    }

    inline bool StdFilesystem::IsFile(const Path& path) {
        return StatFile(path).IsFile;
    }

    inline bool StdFilesystem::IsDirectory(const Path& path) {
        return StatFile(path).IsDirectory;
    }

    inline bool StdFilesystem::Exists(const Path& path) {
        const auto stat = StatFile(path);
        return stat.IsFile || stat.IsDirectory;
    }

    inline void StdFilesystem::SetExternalStorageDirectory(const std::string& dir) {
        m_ExternalStorageDirectory = dir;
    }

    inline const Path& StdFilesystem::ExternalStorageDirectory() const {
        return m_ExternalStorageDirectory;
    }

    inline const Path& StdFilesystem::TempDirectory() const {
        return m_TempDirectory;
    }
}
