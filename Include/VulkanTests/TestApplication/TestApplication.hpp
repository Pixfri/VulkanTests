// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Direct3D11Renderer.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_TEST_APPLICATION_TEST_APPLICATION_HPP
#define VK_TESTS_TEST_APPLICATION_TEST_APPLICATION_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Framework/Application.hpp>

namespace VkTests {
    class TestApplication final : public Application {
    public:
        explicit TestApplication(const WindowProperties& properties);
        ~TestApplication() override = default;

        TestApplication(const TestApplication&) = delete;
        TestApplication(TestApplication&&) = delete;

        TestApplication& operator=(const TestApplication&) = delete;
        TestApplication& operator=(TestApplication&&) = delete;

        bool Load() override;
        void Update() override;
        void Render() override;
        void OnEvent(Event& event) override;
        
    private:
    };
}

#include <VulkanTests/TestApplication/TestApplication.inl>

#endif // VK_TESTS_TEST_APPLICATION_TEST_APPLICATION_HPP
