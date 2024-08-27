// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#include <VulkanTests/Framework/Core/Window.hpp>

#include <chrono>

namespace VkTests {
    class Application {
    public:
        explicit Application(const WindowProperties& properties);
        virtual ~Application() = default;

        Application(const Application&) = delete;
        Application(Application&&) = delete;

        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        void Run();
    private:
        static Application* m_SInstance;
        
        bool m_IsRunning = false;
        
        std::chrono::high_resolution_clock::time_point m_CurrentTime;

    protected:
        std::unique_ptr<Window> m_Window;
    
        [[nodiscard]] virtual bool Load() = 0;
        virtual void Render() = 0;
        virtual void Update();
        virtual void OnEvent(Event& event) = 0;
        virtual void OnWindowClose(WindowCloseEvent& event);
        virtual void OnWindowResize(WindowResizeEvent& event);
    
        Float32 m_DeltaTime = 0.016f;
    };
}