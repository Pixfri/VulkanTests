// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_STRINGS_HPP
#define VK_TESTS_RENDERER_STRINGS_HPP

#include <VulkanTests/pch.hpp>

#include <volk.h>

namespace VkTests {
	enum class ShaderResourceType;

	namespace SceneGraph {
		enum class AlphaMode {
			/// Alpha value is ignored
			Opaque,
			/// Either full opaque or fully transparent
			Mask,
			/// Output is combined with the background
			Blend
		};
	}

	std::vector<std::string> Split(const std::string& str, const std::string& delimiter);
	std::string Join(const std::vector<std::string>& str, const std::string& separator);

	/**
 * @brief Helper function to convert a VkFormat enum to a string
 * @param format Vulkan format to convert.
 * @return The string to return.
 */
	inline std::string ToString(VkFormat format);

	/**
	 * @brief Helper function to convert a VkPresentModeKHR to a string
	 * @param presentMode Vulkan present mode to convert.
	 * @return The string to return.
	 */
	inline std::string ToString(VkPresentModeKHR presentMode);

	/**
	 * @brief Helper function to convert a VkResult enum to a string
	 * @param result Vulkan result to convert.
	 * @return The string to return.
	 */
	inline std::string ToString(VkResult result);

	/**
	 * @brief Helper function to convert a VkPhysicalDeviceType enum to a string
	 * @param type Vulkan physical device type to convert.
	 * @return The string to return.
	 */
	inline std::string ToString(VkPhysicalDeviceType type);

	/**
	 * @brief Helper function to convert a VkSurfaceTransformFlagBitsKHR flag to a string
	 * @param transformFlag Vulkan surface transform flag bit to convert.
	 * @return The string to return.
	 */
	inline std::string ToString(VkSurfaceTransformFlagBitsKHR transformFlag);

	/**
	 * @brief Helper function to convert a VkSurfaceFormatKHR format to a string
	 * @param surfaceFormat Vulkan surface format to convert.
	 * @return The string to return.
	 */
	inline std::string ToString(VkSurfaceFormatKHR surfaceFormat);

	/**
	 * @brief Helper function to convert a VkCompositeAlphaFlagBitsKHR flag to a string
	 * @param compositeAlpha Vulkan composite alpha flag bit to convert.
	 * @return The string to return.
	 */
	inline std::string ToString(VkCompositeAlphaFlagBitsKHR compositeAlpha);

	/**
	 * @brief Helper function to convert a VkImageUsageFlagBits flag to a string
	 * @param imageUsage Vulkan image usage flag bit to convert.
	 * @return The string to return.
	 */
	inline std::string ToString(VkImageUsageFlagBits imageUsage);

	/**
	 * @brief Helper function to convert a VkExtent2D flag to a string
	 * @param format Vulkan format to convert.
	 * @return The string to return.
	 */
	inline std::string ToString(VkExtent2D format);

	/**
	 * @brief Helper function to convert VkSampleCountFlagBits to a string
	 * @param flags Vulkan sample count flags to convert
	 * @return  std::string
	 */
	inline std::string ToString(VkSampleCountFlagBits flags);

	/**
	 * @brief Helper function to convert VkImageTiling to a string
	 * @param tiling Vulkan VkImageTiling to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkImageTiling tiling);

	/**
	 * @brief Helper function to convert VkImageType to a string
	 * @param type Vulkan VkImageType to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkImageType type);

	/**
	 * @brief Helper function to convert VkBlendFactor to a string
	 * @param blend Vulkan VkBlendFactor to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkBlendFactor blend);

	/**
	 * @brief Helper function to convert VkVertexInputRate to a string
	 * @param rate Vulkan VkVertexInputRate to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkVertexInputRate rate);

	/**
	 * @brief Helper function to convert VkBool32 to a string
	 * @param state Vulkan VkBool32 to convert
	 * @return The string to return
	 */
	inline std::string ToStringVkBool(VkBool32 state);

	/**
	 * @brief Helper function to convert VkPrimitiveTopology to a string
	 * @param topology Vulkan VkPrimitiveTopology to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkPrimitiveTopology topology);

	/**
	 * @brief Helper function to convert VkFrontFace to a string
	 * @param face Vulkan VkFrontFace to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkFrontFace face);

	/**
	 * @brief Helper function to convert VkPolygonMode to a string
	 * @param mode Vulkan VkPolygonMode to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkPolygonMode mode);

	/**
	 * @brief Helper function to convert VkCompareOp to a string
	 * @param operation Vulkan VkCompareOp to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkCompareOp operation);

	/**
	 * @brief Helper function to convert VkStencilOp to a string
	 * @param operation Vulkan VkStencilOp to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkStencilOp operation);

	/**
	 * @brief Helper function to convert VkLogicOp to a string
	 * @param operation Vulkan VkLogicOp to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkLogicOp operation);

	/**
	 * @brief Helper function to convert VkBlendOp to a string
	 * @param operation Vulkan VkBlendOp to convert
	 * @return The string to return
	 */
	inline std::string ToString(VkBlendOp operation);

	/**
	 * @brief Helper function to convert AlphaMode to a string
	 * @param mode Vulkan AlphaMode to convert
	 * @return The string to return
	 */
	inline std::string ToString(SceneGraph::AlphaMode mode);

	/**
	 * @brief Helper function to convert bool to a string
	 * @param flag Vulkan bool to convert (true/false)
	 * @return The string to return
	 */
	inline std::string ToString(bool flag);

	/**
	 * @brief Helper function to convert ShaderResourceType to a string
	 * @param type Vulkan ShaderResourceType to convert
	 * @return The string to return
	 */
	inline std::string ToString(ShaderResourceType type);

	/**
	 * @brief Helper generic function to convert a bitmask to a string of its components
	 * @param bitmask The bitmask to convert
	 * @param stringMap A map of bitmask bits to the string that describe the Vulkan flag
	 * @returns A string of the enabled bits in the bitmask
	 */
	template <typename T>
	std::string ToString(uint32_t bitmask, std::map<T, const char*> stringMap);

	/**
	 * @brief Helper function to convert VkBufferUsageFlags to a string
	 * @param flags The buffer usage bitmask to convert to strings
	 * @return The converted string to return
	 */
	inline std::string BufferUsageToString(VkBufferUsageFlags flags);

	/**
	 * @brief Helper function to convert VkShaderStageFlags to a string
	 * @param flags The shader stage bitmask to convert
	 * @return The converted string to return
	 */
	inline std::string ShaderStageToString(VkShaderStageFlags flags);

	/**
	 * @brief Helper function to convert VkImageUsageFlags to a string
	 * @param flags The image usage flags to convert
	 * @return The converted string to return
	 */
	inline std::string ImageUsageToString(VkImageUsageFlags flags);

	/**
	 * @brief Helper function to convert VkImageAspectFlags to a string
	 * @param flags The image aspect bitmask to convert
	 * @return The converted string to return
	 */
	inline std::string ImageAspectToString(VkImageAspectFlags flags);

	/**
	 * @brief Helper function to convert VkCullModeFlags to a string
	 * @param flags The cull mode bitmask to convert
	 * @return The converted string to return
	 */
	inline std::string CullModeToString(VkCullModeFlags flags);

	/**
	 * @brief Helper function to convert VkColorComponentFlags to a string
	 * @param flags The color component bitmask to convert
	 * @return The converted string to return
	 */
	inline std::string ColorComponentToString(VkColorComponentFlags flags);

	/**
	 * @brief Helper function to convert VkImageCompressionFlagsEXT to a string
	 * @param flags The flags to convert
	 * @return The converted string to return
	 */
	inline std::string ImageCompressionFlagsToString(VkImageCompressionFlagsEXT flags);

	/**
	 * @brief Helper function to convert VkImageCompressionFixedRateFlagsEXT to a string
	 * @param flags The flags to convert
	 * @return The converted string to return
	 */
	inline std::string ImageCompressionFixedRateFlagsToString(VkImageCompressionFixedRateFlagsEXT flags);

	/**
	 * @brief Helper function to split a single string into a vector of strings by a delimiter
	 * @param input The input string to be split
	 * @param delimiter The character to delimit by
	 * @return The vector of tokenized strings
	 */
	std::vector<std::string> Split(const std::string& input, char delimiter);
}

#include <VulkanTests/Renderer/Strings.inl>

#endif // VK_TESTS_RENDERER_STRINGS_HPP
