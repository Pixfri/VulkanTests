// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

#include <VulkanTests/Filesystem/Filesystem.hpp>

namespace VkTests::Filesystem {
    inline bool IsDirectory(const std::string& path) {
        return VkTests::Filesystem::Get()->IsDirectory(path);
    }

    inline bool IsFile(const std::string& filename) {
        return VkTests::Filesystem::Get()->IsFile(filename);
    }

    inline bool CreateDirectory(const std::string& path) {
        return VkTests::Filesystem::Get()->CreateDirectory(path);
    }

    inline std::vector<UInt8> ReadAsset(const std::string& filename) {
        return VkTests::Filesystem::Get()->ReadFileBinary(Paths::Get(Paths::Type::Assets) + filename);
    }

    inline std::string ReadShader(const std::string& filename) {
        return VkTests::Filesystem::Get()->ReadFileString(Paths::Get(Paths::Type::Shaders) + filename);
    }

    inline std::vector<UInt8> ReadShaderBinary(const std::string& filename) {
        return VkTests::Filesystem::Get()->ReadFileBinary(Paths::Get(Paths::Type::Shaders) + filename);
    }

    inline std::vector<UInt8> ReadTemp(const std::string& filename) {
        return VkTests::Filesystem::Get()->ReadFileBinary(Paths::Get(Paths::Type::Temp) + filename);
    }

    inline void WriteTemp(const std::vector<UInt8>& data, const std::string& filename) {
        VkTests::Filesystem::Get()->WriteFile(Paths::Get(Paths::Type::Temp) + filename, data);
    }
}
