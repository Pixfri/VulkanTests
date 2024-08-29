// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#include <VulkanTests/Core/Window.hpp>

#include <VulkanTests/Core/Logger.hpp>

namespace VkTests {
	Window::Window(const WindowProperties& windowProperties) {
		if (!glfwInit()) {
			Log::Fatal({0x01, 0x00}, "Failed to initialize GLFW.");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);

		const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		Log::Trace("Creating window...");
		const Int32 width = windowProperties.Fullscreen ? videoMode->width : windowProperties.Width;
		const Int32 height = windowProperties.Fullscreen ? videoMode->height : windowProperties.Height;

		// If windowProperties.Fullscreen is true, discard the width and height and use the monitor's ones instead. 
		m_Window = glfwCreateWindow(width, height, windowProperties.Title.c_str(),
		                            windowProperties.Fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

		if (m_Window == nullptr) {
			Log::Fatal({0x01, 0x01}, "Failed to create GLFW window.");
		}

		if (!windowProperties.Fullscreen) {
			const Int32 windowLeft = videoMode->width / 2 - windowProperties.Width / 2;
			const Int32 windowTop = videoMode->height / 2 - windowProperties.Height / 2;
			glfwSetWindowPos(m_Window, windowLeft, windowTop);
		}

		Log::Trace("Window created.");

		m_Data.Width = width;
		m_Data.Height = height;
		m_Data.Title = windowProperties.Title;
		m_Data.Focused = true;
		m_Data.Fullscreen = windowProperties.Fullscreen;

		glfwSetWindowUserPointer(m_Window, &m_Data);

		// ------------------------------- Window callbacks ------------------------------- //
		Log::Trace("Setting up window callbacks...");

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			data->EventCallback(event);
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, const Int32 width, const Int32 height) {
			const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->Width = width;
			data->Height = height;
			WindowResizeEvent event(width, height);
			data->EventCallback(event);
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, const Int32 x, const Int32 y) {
			const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowMovedEvent event(x, y);
			data->EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, const Int32 key, const Int32 scancode, const Int32 action,
		                                const Int32 mods) {
			VK_TESTS_UNUSED(scancode);
			VK_TESTS_UNUSED(mods);
			const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			switch (action) {
			case GLFW_PRESS:
				{
					KeyDownEvent event(key, 0);
					data->EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyUpEvent event(key);
					data->EventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyDownEvent event(key, 1);
					data->EventCallback(event);
					break;
				}
			default:
				Log::Error("Unknown GLFW key action.");
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, const UInt32 keycode) {
			const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			KeyTypedEvent event(static_cast<Int32>(keycode));
			data->EventCallback(event);
		});

		glfwSetMouseButtonCallback(
			m_Window, [](GLFWwindow* window, const Int32 button, const Int32 action, const Int32 mods) {
				VK_TESTS_UNUSED(mods);

				const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action) {
				case GLFW_PRESS:
					{
						MouseButtonDownEvent event(button);
						data->EventCallback(event);
						break;
					}
				case GLFW_RELEASE:
					{
						MouseButtonUpEvent event(button);
						data->EventCallback(event);
						break;
					}
				default:
					Log::Error("Unknown GLFW mouse button action.");
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, const Float64 xOffset, const Float64 yOffset) {
			const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseScrolledEvent event(static_cast<Float32>(xOffset), static_cast<Float32>(yOffset));
			data->EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, const Float64 xPos, const Float64 yPos) {
			const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseMovedEvent event(static_cast<Float32>(xPos), static_cast<Float32>(yPos));
			data->EventCallback(event);
		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, const Int32 focused) {
			const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowFocusedEvent event(focused);
			data->EventCallback(event);
			data->Focused = focused;
		});

		Log::Trace("Callbacks are set up successfully.");
	}

	Window::~Window() {
		if (m_Window != nullptr) {
			Log::Trace("Destroying window.");
			glfwDestroyWindow(m_Window);
		}

		glfwTerminate();
	}

	void Window::Update() {
		glfwPollEvents();
	}
}
