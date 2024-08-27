// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#include <cstddef>
#include <cstdint>
#include <climits>

static_assert(CHAR_BIT == 8, "CHAR_BIT is expected to be 8.");

static_assert(sizeof(std::int8_t) == 1, "int8_t is not of the correct size.");
static_assert(sizeof(std::int16_t) == 2, "int16_t is not of the correct size.");
static_assert(sizeof(std::int32_t) == 4, "int32_t is not of the correct size.");
static_assert(sizeof(std::int64_t) == 8, "int64_t is not of the correct size.");

static_assert(sizeof(std::uint8_t) == 1, "uint8_t is not of the correct size.");
static_assert(sizeof(std::uint16_t) == 2, "uint16_t is not of the correct size.");
static_assert(sizeof(std::uint32_t) == 4, "uint32_t is not of the correct size.");
static_assert(sizeof(std::uint64_t) == 8, "uint64_t is not of the correct size.");

namespace VkTests {
    using Int8 = std::int8_t;
    using Int16 = std::int16_t;
    using Int32 = std::int32_t;
    using Int64 = std::int64_t;

    using UInt8 = std::uint8_t;
    using UInt16 = std::uint16_t;
    using UInt32 = std::uint32_t;
    using UInt64 = std::uint64_t;

    using Float32 = float;
    using Float64 = double;

    using USize = size_t;
}