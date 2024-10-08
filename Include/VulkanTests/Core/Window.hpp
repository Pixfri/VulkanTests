// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_CORE_WINDOW_HPP
#define VK_TESTS_CORE_WINDOW_HPP

#include <VulkanTests/pch.hpp>

#include <VulkanTests/Core/Event.hpp>

#include <GLFW/glfw3.h>

namespace VkTests {
	enum class Keys : UInt16 {
		Space = 32,
		Apostrophe = 39,
		Comma = 44,
		Minus = 45,
		Period = 46,
		Slash = 47,

		NumberZero = 48,
		NumberOne = 49,
		NumberTwo = 50,
		NumberThree = 51,
		NumberFour = 52,
		NumberFive = 53,
		NumberSix = 54,
		NumberSeven = 55,
		NumberEight = 56,
		NumberNine = 57,

		Semicolon = 59,
		Equal = 61,

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91, /* [ */
		Backlash = 92, /* \ */
		RightBracket = 93, /* ] */
		GraveAccent = 96, /* ` */
		NonUs1 = 161, /* non-US #1 */
		NonUs2 = 162, /* non-US #2 */

		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		KeypadZero = 320,
		KeypadOne = 321,
		KeypadTwo = 322,
		KeypadThree = 323,
		KeypadFour = 324,
		KeypadFive = 325,
		KeypadSix = 326,
		KeypadSeven = 327,
		KeypadEight = 328,
		KeypadNine = 329,
		KeyPadDecimal = 330,
		KeyPadDivide = 331,
		KeyPadMultiply = 332,
		KeyPadSubtract = 333,
		KeyPadAdd = 334,
		KeyPadEnter = 335,
		KeyPadEqual = 336,
		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348,
	};

	struct WindowProperties {
		Int32 Width, Height;
		std::string Title;
		bool Fullscreen;

		WindowProperties(const Int32 width, const Int32 height, std::string&& title, const bool fullscreen) :
			Width(width), Height(height), Title(std::move(title)), Fullscreen(fullscreen) {
		}
	};

	struct WindowData {
		Int32 Width, Height;
		std::string Title;
		bool Focused = false;
		bool Fullscreen = false;
		std::function<void(Event&)> EventCallback;
	};

	class Window {
	public:
		explicit Window(const WindowProperties& windowProperties);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;

		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		[[nodiscard]] inline GLFWwindow* GetNativeWindow() const;
		[[nodiscard]] inline Int32 GetWidth() const;
		[[nodiscard]] inline Int32 GetHeight() const;
		[[nodiscard]] inline std::string_view GetTitle() const;
		[[nodiscard]] inline bool IsFullscreen() const;

		inline void SetEventCallback(const std::function<void(Event&)>& callback);

		static void Update();

	private:
		GLFWwindow* m_Window = nullptr;
		WindowData m_Data;
	};
}

#include <VulkanTests/Core/Window.inl>

#endif // VK_TESTS_CORE_WINDOW_HPP
