// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests::Common {
    inline HPPVulkanException::HPPVulkanException(vk::Result result, const std::string& message)
        : VulkanException(static_cast<VkResult>(result), message) {
    }

}
