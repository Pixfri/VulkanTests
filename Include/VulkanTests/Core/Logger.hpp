// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#include <VulkanTests/pch.hpp>

#include <spdlog/spdlog.h>

namespace VkTests {
	/*
	 * ErrorCode : The representation of an error code when throwing an error.
	 * The first byte in the error code represents the module identifier.
	 * The last byte in the error code represents the error number in that module.
	 */
	struct ErrorCode {
		UInt8 ModuleId;
		UInt8 ErrorNumber;

		[[nodiscard]]
		UInt16 GetFormattedErrorCode() const {
			return (ModuleId << 8) + ErrorNumber;
		}
	};

	using CustomLogCallback = std::function<void(const spdlog::level::level_enum& level, const std::string& msg)>;

	class Logger {
		static std::shared_ptr<spdlog::logger> m_Logger;

	public:
		static void Init();
		static inline spdlog::logger* GetLogger();
		static void AddCallback(const CustomLogCallback& callback);
	};


	namespace Log {
		std::string_view EvaluateErrorCode(const ErrorCode& errorCode);

		template <typename... Args>
		constexpr void Trace(Args&&... args);

		template <typename... Args>
		constexpr void Info(Args&&... args);

		template <typename... Args>
		constexpr void Warn(Args&&... args);

		template <typename... Args>
		constexpr void Error(Args&&... args);

		template <typename... Args>
		constexpr void Critical(Args&&... args);

		template <typename... Args>
		constexpr void Fatal(ErrorCode errorCode, Args&&... args);
	}

#include <VulkanTests/Core/Logger.inl>
}
