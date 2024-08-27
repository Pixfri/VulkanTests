// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#include <VulkanTests/Framework/Application.hpp>

#include <VulkanTests/Framework/Core/Logger.hpp>

namespace VkTests {
    Application* Application::m_SInstance = nullptr;

    Application::Application(const WindowProperties& properties) {
        if (m_SInstance != nullptr) {
            Log::Fatal({0x00, 0x01}, "Only one instance of this application can be created.");
        }
        m_SInstance = this;

        Logger::Init();

        m_Window = std::make_unique<Window>(properties);

        m_Window->SetEventCallback([this](Event& event) -> void {
            EventDispatcher dispatcher(event);
            dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_TO_EVENT_HANDLER(Application::OnWindowClose));
            dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_TO_EVENT_HANDLER(Application::OnWindowResize));
            OnEvent(event);
        });
    }

    void Application::Run() {
        if (!Load()) {
            return;
        }

        m_IsRunning = true;

        while (m_IsRunning) {
            Update();
            Render();
        }
    }

    void Application::Update() {
        m_Window->Update();

        const auto oldTime = m_CurrentTime;
        m_CurrentTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> timeSpan = (m_CurrentTime - oldTime);

        m_DeltaTime = static_cast<float>(timeSpan.count() / 1000.0);
    }

    void Application::OnWindowClose(WindowCloseEvent& event) {
        m_IsRunning = false;
    }

    void Application::OnWindowResize(WindowResizeEvent& event) {
    }
}
