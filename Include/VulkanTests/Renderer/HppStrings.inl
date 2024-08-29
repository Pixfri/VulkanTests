// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

#include <VulkanTests/Renderer/Strings.hpp>

namespace VkTests::Common {
    inline std::string ToString(const vk::Extent2D& extent) {
        return ToString(static_cast<const VkExtent2D&>(extent));
    }
}
