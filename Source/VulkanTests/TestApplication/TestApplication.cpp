// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#include <VulkanTests/TestApplication/TestApplication.hpp>

namespace VkTests {
    TestApplication::TestApplication(const WindowProperties& properties) : Application(properties) {
    }

    bool TestApplication::Load() {
        return true;
    }


    void TestApplication::Update() {
        Application::Update();
    }

    void TestApplication::Render() {
    }

    void TestApplication::OnEvent(Event& event) {
    }
}
