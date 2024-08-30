// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests {
    VkInstance Instance::GetHandle() const {
        return m_Handle;
    }

    const std::vector<const char*>& Instance::GetExtensions() {
        return m_EnabledExtensions;
    }
}
