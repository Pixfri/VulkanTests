// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#include <VulkanTests/TestApplication/TestApplication.hpp>

int main() {
    const VkTests::WindowProperties properties = {
        1920,
        1080,
        "Vulkan Test Application",
        false
    };
    VkTests::TestApplication testApplication{properties};

    testApplication.Run();

    return 0;
}
