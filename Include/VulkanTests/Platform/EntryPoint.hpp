// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_PLATFORM_ENTRYPOINT_HPP
#define VK_TESTS_PLATFORM_ENTRYPOINT_HPP

#include <VulkanTests/Platform/Context.hpp>

#include <VulkanTests/Core/Logger.hpp>

// Platform specific entrypoint definitions
// Applications should use CUSTOM_MAIN to define their own main function

#if defined(VK_TESTS_PLATFORM_WINDOWS)
#include <Windows.h>
#include <VulkanTests/Libs/AntiWindows.hpp>


extern std::unique_ptr<VkTests::PlatformContext> CreatePlatformContext(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                                                                       PSTR lpCmdLine, INT nCmdShow);

#define CUSTOM_MAIN(contextName)                                                                       \
    int PlatformMain(const VkTests::PlatformContext&);                                                 \
    int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) { \
        auto context = CreatePlatformContext(hInstance, hPrevInstance, lpCmdLine, nCmdShow);           \
        VkTests::Logger::Init();                                                                       \
        return PlatformMain(*context);                                                                 \
    }                                                                                                  \
    int PlatformMain(const VkTests::PlatformContext& (contextName))

#elif defined(VK_TESTS_PLATFORM_UNIX)
extern std::unique_ptr<VkTests::PlatformContext> CreatePlatformContext(int argc, char** argv);

#define CUSTOM_MAIN(contextName)                          \
    int PlatformMain(const VkTests::PlatformContext&);    \
    int main(int argc, char* argv[]) {                    \
        auto context = CreatePlatformContext(argc, argv); \
        VkTests::Logger::Init();                          \
        return PlatformMain(*context);                    \
    }                                                     \
    int PlatformMain(const VkTests::PlatformContext& (contextName))
#else
#include <stdexcept>

#define CUSTOM_MAIN(contextName) \
    int main(int argc, char* argv[]) { \
        throw std::runtime_error{"This platform is not supported."} \
    } \
    int Unused(const VkTests::PlatformContext& (contextName))
#endif

#endif // VK_TESTS_PLATFORM_ENTRYPOINT_HPP
