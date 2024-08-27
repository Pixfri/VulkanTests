// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#define __GCC__ __GNUC__
#endif

#if defined(__clang__)
// CLANG ENABLE/DISABLE WARNING DEFINITION
#define VK_TESTS_DISABLE_WARNINGS()                                                    \
    _Pragma("clang diagnostic push")                                                   \
        _Pragma("clang diagnostic ignored \"-Wall\"")                                  \
            _Pragma("clang diagnostic ignored \"-Wextra\"")                            \
                _Pragma("clang diagnostic ignored \"-Wtautological-compare\"")         \
                    _Pragma("clang diagnostic ignored \"-Wnullability-completeness\"")

#define VK_TESTS_ENABLE_WARNINGS()  \
    _Pragma("clang diagnostic pop")
#elif defined(__GNUC__) || defined(__GNUG__)
// GCC ENABLE/DISABLE WARNING DEFINITION
#define VK_TESTS_DISABLE_WARNINGS()                                          \
    _Pragma("GCC diagnostic push")                                           \
        _Pragma("GCC diagnostic ignored \"-Wall\"")                          \
            _Pragma("GCC diagnostic ignored \"-Wextra\"")                    \
                _Pragma("GCC diagnostic ignored \"-Wtautological-compare\"")

#	define VK_TESTS_ENABLE_WARNINGS() \
_Pragma("GCC diagnostic pop")
#elif defined(_MSC_VER)
// MSVC ENABLE/DISABLE WARNING DEFINITION
#define VK_TESTS_DISABLE_WARNINGS() \
    __pragma(warning(push, 0))

#define VK_TESTS_ENABLE_WARNINGS() \
    __pragma(warning(pop))
#endif

#define VK_TESTS_PREFIX(a, prefix) prefix ## a
#define VK_TESTS_PREFIX_MACRO(a, prefix) VK_TESTS_PREFIX(a, prefix)
#define VK_TESTS_SUFFIX(a, suffix) a ## suffix
#define VK_TESTS_SUFFIX_MACRO(a, suffix) VK_TESTS_SUFFIX(a, suffix)
#define VK_TESTS_STRINGIFY(s) #s
#define VK_TESTS_STRINGIFY_MACRO(s) VK_TESTS_STRINGIFY(s)
#define VK_TESTS_UNUSED(a) (void) a
