// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests::Filesystem {
    inline void Filesystem::WriteFile(const Path& path, const std::string& data) {
        WriteFile(path, std::vector<UInt8>(data.begin(), data.end()));
    }

    inline std::string Filesystem::ReadFileString(const Path& path) {
        auto bin = ReadFileBinary(path);
        return {bin.begin(), bin.end()};
    }

    inline std::vector<UInt8> Filesystem::ReadFileBinary(const Path& path) {
        return ReadChunk(path, 0, StatFile(path).Size);
    }
}
