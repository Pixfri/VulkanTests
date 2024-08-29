// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests {
	template <typename T>
	void Read(std::istringstream& is, T& value) {
		is.read(reinterpret_cast<char*>(&value), sizeof(T));
	}

	template <typename T>
	void Read(std::istringstream& is, std::string& value) {
		std::size_t size;
		Read(is, size);
		value.resize(size);
		is.read(const_cast<char*>(value.data()), static_cast<std::streamsize>(size));
	}

	template <class T>
	void Read(std::istringstream& is, std::set<T>& value) {
		std::size_t size;
		Read(is, size);
		for (uint32_t i = 0; i < size; i++) {
			T item;
			is.read(reinterpret_cast<char*>(&item), sizeof(T));
			value.insert(std::move(item));
		}
	}

	template <class T>
	void Read(std::istringstream& is, std::vector<T>& value) {
		std::size_t size;
		Read(is, size);
		value.resize(size);
		is.read(reinterpret_cast<char*>(value.data()), value.size() * sizeof(T));
	}

	template <class T, class S>
	void Read(std::istringstream& is, std::map<T, S>& value) {
		std::size_t size;
		Read(is, size);

		for (uint32_t i = 0; i < size; i++) {
			std::pair<T, S> item;
			read(is, item.first);
			read(is, item.second);

			value.insert(std::move(item));
		}
	}

	template <class T, UInt32 N>
	void Read(std::istringstream& is, std::array<T, N>& value) {
		is.read(reinterpret_cast<char*>(value.data()), N * sizeof(T));
	}

	template <typename T, typename... Args>
	void Read(std::istringstream& is, T& firstArg, Args&... args) {
		Read(is, firstArg);

		Read(is, args...);
	}

	template <typename T>
	void Write(std::ostringstream& os, const T& value) {
		os.write(reinterpret_cast<const char*>(&value), sizeof(T));
	}

	inline void Write(std::ostringstream& os, const std::string& value) {
		Write(os, value.size());
		os.write(value.data(), static_cast<std::streamsize>(value.size()));
	}

	template <class T>
	void Write(std::ostringstream& os, const std::set<T>& value) {
		Write(os, value.size());
		for (const T& item : value) {
			os.write(reinterpret_cast<const char*>(&item), sizeof(T));
		}
	}

	template <class T>
	void Write(std::ostringstream& os, const std::vector<T>& value) {
		Write(os, value.size());
		os.write(reinterpret_cast<const char*>(value.data()), value.size() * sizeof(T));
	}

	template <class T, class S>
	void Write(std::ostringstream& os, const std::map<T, S>& value) {
		Write(os, value.size());

		for (const std::pair<T, S>& item : value) {
			Write(os, item.first);
			Write(os, item.second);
		}
	}

	template <class T, UInt32 N>
	void Write(std::ostringstream& os, const std::array<T, N>& value) {
		os.write(reinterpret_cast<const char*>(value.data()), N * sizeof(T));
	}

	template <typename T, typename... Args>
	void Write(std::ostringstream& os, const T& firstArg, const Args&... args) {
		Write(os, firstArg);

		Write(os, args...);
	}

	template <class T>
	std::string ToString(const T& value) {
		std::stringstream ss;
		ss << std::fixed << value;
		return ss.str();
	}

	template <class T>
	UInt32 ToUInt32(T value) {
		static_assert(std::is_arithmetic_v<T>, "T must be numeric");

		if (static_cast<uintmax_t>(value) > static_cast<uintmax_t>(std::numeric_limits<UInt32>::max())) {
			throw std::runtime_error("ToUInt32() failed, value is too big to be converted to UInt32");
		}

		return static_cast<UInt32>(value);
	}

	template <typename T>
	std::vector<UInt8> ToBytes(const T& value) {
		return std::vector<UInt8>{
			reinterpret_cast<const UInt8*>(&value),
			reinterpret_cast<const UInt8*>(&value) + sizeof(T)
		};
	}
}
