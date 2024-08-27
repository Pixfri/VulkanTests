// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_CORE_EVENT_HPP
#define VK_TESTS_CORE_EVENT_HPP

#include <VulkanTests/pch.hpp>

#include <ostream>
#include <sstream>
#include <type_traits>

namespace VkTests {
    template <typename Enumeration>
    constexpr auto IntegerFromEnum(const Enumeration value) -> std::underlying_type_t<Enumeration> requires (
        std::is_enum_v<Enumeration>) {
        return static_cast<std::underlying_type_t<Enumeration>>(value);
    }

    template <typename T>
    constexpr T BitFromNumber(T x) {
        return 1 << x;
    }

    enum class EventType : UInt8 {
        Undefined = 0,

        WindowClose, WindowResize, WindowMoved, WindowFocus,
        KeyDown, KeyUp, KeyTyped,
        MouseButtonDown, MouseButtonUp, MouseMoved, MouseScroll
    };

    enum class EventCategory : UInt8 {
        Undefined = 0,

        Application = BitFromNumber(0),
        Input = BitFromNumber(1),
        Keyboard = BitFromNumber(2),
        Mouse = BitFromNumber(3),
        MouseButton = BitFromNumber(4)
    };

    inline EventCategory operator|(const EventCategory a, const EventCategory b);

#define BIND_EVENT_TO_EVENT_HANDLER(x) [this](auto && PH1) { return (x)(PH1); }

#define EVENT_TYPE_CLASS(type)                                                  \
static EventType GetStaticType() { return type; }                           \
virtual EventType GetEventType() const override { return GetStaticType(); } \
virtual const char* GetName() const override { return #type; }


#define EVENT_CATEGORY_CLASS(category) \
virtual Int32 GetCategoryFlags() const override { return IntegerFromEnum(category); }

    class Event {
        friend class EventDispatcher;

        bool m_Handled = false;

    public:
        virtual ~Event() = default;
        [[nodiscard]] virtual EventType GetEventType() const = 0;
        [[nodiscard]] virtual const char* GetName() const = 0;
        [[nodiscard]] virtual Int32 GetCategoryFlags() const = 0;

        [[nodiscard]] virtual inline std::string ToString() const;

        [[nodiscard]] inline bool IsInCategory(EventCategory category) const;

        [[nodiscard]] inline bool IsHandled() const;

        inline void Stop();
    };

    class EventDispatcher {
        Event& m_Event;

    public:
        explicit EventDispatcher(Event& event) : m_Event(event) {
        }

        template <typename T>
        bool Dispatch(std::function<void(T&)> handler);
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& event);

#pragma region Events

#pragma region Application Events

    class WindowResizeEvent final : public Event {
        UInt32 m_Width, m_Height;

    public:
        WindowResizeEvent(const UInt32 width, const UInt32 height) : m_Width(width), m_Height(height) {
        }

        ~WindowResizeEvent() override = default;

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "Window Resized: Width=" << m_Width << ", Height=" << m_Height;
            return ss.str();
        }

        [[nodiscard]] UInt32 GetWidth() const {
            return m_Width;
        }

        [[nodiscard]] UInt32 GetHeight() const {
            return m_Height;
        }

        [[nodiscard]] std::pair<Float32, Float32> GetSize() const {
            return std::make_pair(static_cast<Float32>(m_Width), static_cast<Float32>(m_Height));
        }

        EVENT_TYPE_CLASS(EventType::WindowResize)
        EVENT_CATEGORY_CLASS(EventCategory::Application)
    };

    class WindowCloseEvent final : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_TYPE_CLASS(EventType::WindowClose)
        EVENT_CATEGORY_CLASS(EventCategory::Application)
    };

    class WindowFocusedEvent final : public Event {
        bool m_Focused;

    public:
        explicit WindowFocusedEvent(const bool focused) : m_Focused(focused) {
        }

        [[nodiscard]] bool IsFocused() const {
            return m_Focused;
        }

        EVENT_TYPE_CLASS(EventType::WindowFocus)
        EVENT_CATEGORY_CLASS(EventCategory::Application)
    };

    class WindowMovedEvent final : public Event {
        Int32 m_XPos, m_YPos;

    public:
        WindowMovedEvent(const Int32 x, const Int32 y) : m_XPos(x), m_YPos(y) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "Window moved: X=" << m_XPos << ", Y=" << m_YPos;
            return ss.str();
        }

        EVENT_TYPE_CLASS(EventType::WindowMoved)
        EVENT_CATEGORY_CLASS(EventCategory::Application)
    };

#pragma endregion Application Events

#pragma region Keys Events

    class KeyEvent : public Event {
    public:
        Int32 GetScancode() const {
            return m_Scancode;
        }

        EVENT_CATEGORY_CLASS(EventCategory::Keyboard | EventCategory::Input)

    protected:
        Int32 m_Scancode;

        explicit KeyEvent(const Int32 scancode) : m_Scancode(scancode) {
        }
    };

    class KeyDownEvent final : public KeyEvent {
        Int32 m_RepetitionCount;

    public:
        KeyDownEvent(const Int32 scancode, const Int32 repetitionCount) : KeyEvent(scancode),
                                                                          m_RepetitionCount(repetitionCount) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "Key down: Scancode=" << m_Scancode << " Repeated " << m_RepetitionCount << " times";
            return ss.str();
        }

        EVENT_TYPE_CLASS(EventType::KeyDown)
    };

    class KeyUpEvent final : public KeyEvent {
    public:
        explicit KeyUpEvent(const Int32 scancode) : KeyEvent(scancode) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "Key up: Scancode=" << m_Scancode;
            return ss.str();
        }

        EVENT_TYPE_CLASS(EventType::KeyUp)
    };

    class KeyTypedEvent final : public KeyEvent {
    public:
        KeyTypedEvent(const Int32 scancode) : KeyEvent(scancode) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "Key typed: Scancode=" << m_Scancode;
            return ss.str();
        }

        EVENT_TYPE_CLASS(EventType::KeyTyped)
    };

#pragma endregion Keys Events

#pragma region Mouse Events

    class MouseMovedEvent final : public Event {
        Float32 m_MouseX, m_MouseY;

    public:
        MouseMovedEvent(const Float32 x, const Float32 y) : m_MouseX(x), m_MouseY(y) {
        }

        [[nodiscard]] Float32 GetX() const {
            return m_MouseX;
        }

        [[nodiscard]] Float32 GetY() const {
            return m_MouseY;
        }

        [[nodiscard]] std::pair<Float32, Float32> GetPosition() const {
            return std::make_pair(m_MouseX, m_MouseY);
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse moved: X=" << m_MouseX << ", Y=" << m_MouseY;
            return ss.str();
        }

        EVENT_TYPE_CLASS(EventType::MouseMoved)
        EVENT_CATEGORY_CLASS(EventCategory::Mouse | EventCategory::Input)
    };

    class MouseScrolledEvent final : public Event {
        Float32 m_XOffset, m_YOffset;

    public:
        MouseScrolledEvent(const Float32 xOffset, const Float32 yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {
        }

        [[nodiscard]] inline Float32 GetXOffset() const {
            return m_XOffset;
        }

        [[nodiscard]] inline Float32 GetYOffset() const {
            return m_YOffset;
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse scroll: X offset=" << m_XOffset << ", Y offset=" << m_YOffset;
            return ss.str();
        }

        EVENT_TYPE_CLASS(EventType::MouseScroll)
        EVENT_CATEGORY_CLASS(EventCategory::Mouse | EventCategory::Input)
    };

    class MouseButtonEvent : public Event {
    public:
        [[nodiscard]] inline Int32 GetButton() const {
            return m_Button;
        }

        EVENT_CATEGORY_CLASS(EventCategory::Mouse | EventCategory::Input | EventCategory::MouseButton)

    protected:
        Int32 m_Button;

        explicit MouseButtonEvent(const Int32 button) : m_Button(button) {
        }
    };

    class MouseButtonDownEvent final : public MouseButtonEvent {
    public:
        explicit MouseButtonDownEvent(const Int32 button) : MouseButtonEvent(button) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse button down: button=" << m_Button;
            return ss.str();
        }

        EVENT_TYPE_CLASS(EventType::MouseButtonDown)
    };

    class MouseButtonUpEvent final : public MouseButtonEvent {
    public:
        explicit MouseButtonUpEvent(const Int32 button) : MouseButtonEvent(button) {
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse button up: button=" << m_Button;
            return ss.str();
        }

        EVENT_TYPE_CLASS(EventType::MouseButtonUp)
    };

#pragma endregion Mouse Events

#pragma endregion Events

}

#include <VulkanTests/Core/Event.inl>
#endif // VK_TESTS_CORE_EVENT_HPP 