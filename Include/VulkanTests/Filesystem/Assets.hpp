// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_FILESYSTEM_ASSETS_HPP
#define VK_TESTS_FILESYSTEM_ASSETS_HPP

#include <VulkanTests/pch.hpp>

#include <cstdlib>
#include <sys/stat.h>

namespace VkTests::Filesystem {
    namespace Paths {
        enum Type {
            // Relative paths
            Assets,
            Shaders,
            Storage,
            Screenshots,
            Logs,

            TotalRelativePaths,

            // Special paths
            ExternalStorage,
            Temp
        };

        extern const std::unordered_map<Type, std::string> g_RelativePaths;

        /**
         * @brief Gets the absolute path of a given type or a specific file
         * @param type The type of file path
         * @param file (Optional) The filename
         * @return Path to the directory of a certain type
         */
        std::string Get(Type type, const std::string& file = "");
    }

    /**
     * @brief Helper to tell if a given path is a directory
     * @param path A path to a directory
     * @return True if the path points to a valid directory, false if not
     */
    [[nodiscard]] inline bool IsDirectory(const std::string& path);

    /**
     * @brief Checks if a file exists
     * @param filename The filename to check
     * @return True if the path points to a valid file, false if not
     */
    [[nodiscard]] inline bool IsFile(const std::string& filename);

    /**
     * @brief Create a directory
     * @param path A path to a directory
     * @return True if creating the directory was successful.
     */
    [[nodiscard]] inline bool CreateDirectory(const std::string& path);

    /**
     * @brief Recursively creates a directory
     * @param root The root directory that the path is relative to
     * @param path A path in the format 'this/is/an/example/path/'
     * @return True if creating the directory was successful.
     */
    [[nodiscard]] bool CreatePath(const std::string& root, const std::string& path);

    /**
     * @brief Helper to read an asset file into a byte-array
     *
     * @param filename The path to the file (relative to the assets directory)
     * @return A vector filled with data read from the file
     */
    [[nodiscard]] inline std::vector<UInt8> ReadAsset(const std::string& filename);

    /**
     * @brief Helper to read a shader file into a single string
     *
     * @param filename The path to the file (relative to the assets' directory)
     * @return A string of the text in the shader file
     */
    [[nodiscard]] inline std::string ReadShader(const std::string& filename);

    /**
     * @brief Helper to read a shader file into a byte-array
     *
     * @param filename The path to the file (relative to the assets' directory)
     * @return A vector filled with data read from the file
     */
    [[nodiscard]] inline std::vector<UInt8> ReadShaderBinary(const std::string& filename);

    /**
     * @brief Helper to read a temporary file into a byte-array
     *
     * @param filename The path to the file (relative to the temporary storage directory)
     * @return A vector filled with data read from the file
     */
    [[nodiscard]] inline std::vector<UInt8> ReadTemp(const std::string& filename);

    /**
     * @brief Helper to write to a file in temporary storage
     *
     * @param data A vector filled with data to write
     * @param filename The path to the file (relative to the temporary storage directory)
     * of data will be used.
     */
    inline void WriteTemp(const std::vector<UInt8>& data, const std::string& filename);

    /**
     * @brief Helper to write to a png image in permanent storage
     *
     * @param data       A vector filled with pixel data to write in (R, G, B, A) format
     * @param filename   The name of the image file without an extension
     * @param width      The width of the image
     * @param height     The height of the image
     * @param components The number of bytes per element
     * @param rowStride  The stride in bytes of a row of pixels
     */
    void WriteImage(const UInt8* data, const std::string& filename, UInt32 width, UInt32 height, UInt32 components,
                    UInt32 rowStride);

}

#include <VulkanTests/Filesystem/Assets.inl>

#endif // VK_TESTS_FILESYSTEM_ASSETS_HPP
