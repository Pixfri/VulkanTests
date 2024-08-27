// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

namespace VkTests {
    inline GLFWwindow* Window::GetNativeWindow() const {
        return m_Window;
    }

    inline Int32 Window::GetWidth() const {
        return m_Data.Width;
    }

    inline Int32 Window::GetHeight() const {
        return m_Data.Height;
    }

    inline std::string_view Window::GetTitle() const {
        return m_Data.Title;
    }

    inline bool Window::IsFullscreen() const {
        return m_Data.Fullscreen;
    }
    
    inline void Window::SetEventCallback(const std::function<void(Event&)>& callback) {
        m_Data.EventCallback = callback;
    }
}
