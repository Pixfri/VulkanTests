// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#define VK_TESTS_PREFIX(a, prefix) prefix ## a
#define VK_TESTS_PREFIX_MACRO(a, prefix) VK_TESTS_PREFIX(a, prefix)
#define VK_TESTS_SUFFIX(a, suffix) a ## suffix
#define VK_TESTS_SUFFIX_MACRO(a, suffix) VK_TESTS_SUFFIX(a, suffix)
#define VK_TESTS_STRINGIFY(s) #s
#define VK_TESTS_STRINGIFY_MACRO(s) VK_TESTS_STRINGIFY(s)
#define VK_TESTS_UNUSED(a) (void) a