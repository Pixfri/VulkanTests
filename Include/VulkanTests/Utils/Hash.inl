// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests {
    inline void HashCombine(USize &seed, USize hash) {
        hash += 0x9e3779B9 + (seed << 6) + (seed >> 2);
        seed ^= hash;
    }

    template <class T>
    void HashCombine(USize &seed, const T& value) {
        std::hash<T> hasher;

        HashCombine(seed, hasher(value));
    }
}
