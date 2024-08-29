// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_VKCOMMON_HPP
#define VK_TESTS_RENDERER_VKCOMMON_HPP

#include <VulkanTests/pch.hpp>

#include <vk_mem_alloc.h>
#include <volk.h>

#define VK_FLAGS_NONE 0 // For better code readability

#define VK_DEFAULT_FENCE_TIMEOUT 100000000000 // Default fence timeout in nanoseconds

template <class T>
using ShaderStageMap = std::map<VkShaderStageFlagBits, T>;

template <class T>
using BindingMap = std::map<std::uint32_t, std::map<uint32_t, T>>;

namespace VkTests {
	enum class BindingType : UInt8 {
		C,
		Cpp
	};

	/**
	 * @brief Helper function to determine if a Vulkan format is depth only format.
	 * @param format Vulkan format to check.
	 * @return True if format is a depth only one, false otherwise.
	 */
	inline bool IsDepthOnlyFormat(VkFormat format);

	/**
	 * @brief Helper function to determine if a Vulkan format is depth with stencil format.
	 * @param format Vulkan format to check.
	 * @return True if format is a depth with stencil one, false otherwise.
	 */
	inline bool IsDepthStencilFormat(VkFormat format);

	/**
	 * @brief Helper function to check if a Vulkan format is a depth format.
	 * @param format Vulkan format to check.
	 * @return True if format is a depth one, false otherwise.
	 */
	inline bool IsDepthFormat(VkFormat format);

	/**
	 * @brief Helper function to determine a suitable supported depth format based on a priority list.
	 * @param physicalDevice The physical device to check the depth formats against.
	 * @param depthOnly (Optional) Whether to include the stencil component in the format or not.
	 * @param depthFormatPriorityList (Optional) The list of depth formats to prefer over one another.
	 *         By default, we start with the highest precision packed format.
	 * @return The valid suited format.
	 */
	VkFormat GetSuitableDepthFormat(VkPhysicalDevice physicalDevice, bool depthOnly = false,
	                                const std::vector<VkFormat>& depthFormatPriorityList = {
		                                VK_FORMAT_D32_SFLOAT,
		                                VK_FORMAT_D24_UNORM_S8_UINT, VK_FORMAT_D16_UNORM
	                                });

	/**
	 * @brief Helper function to pick a blendable format from a priority ordered list.
	 * @param physicalDevice The physical device to check the formats against.
	 * @param formatPriorityList List of formats in order of priority.
	 * @return The selected format.
	 */
	VkFormat ChooseBlendableFormat(VkPhysicalDevice physicalDevice, const std::vector<VkFormat>& formatPriorityList);

	/**
	 * @brief Helper function to check support for linear filtering and adjust its parameters if required
	 * @param physicalDevice The physical device to check the format against.
	 * @param format The format to check against.
	 * @param filter The preferred filter to adjust.
	 * @param mipmapMode (Optional) The preferred mipmap mode to adjust.
	 */
	void MakeFiltersValid(VkPhysicalDevice physicalDevice, VkFormat format, VkFilter* filter,
	                      VkSamplerMipmapMode* mipmapMode = nullptr);

	/**
	* @brief Helper function to determine if a Vulkan descriptor type is a dynamic storage buffer or dynamic uniform buffer.
	* @param descriptorType Vulkan descriptor type to check.
	* @return True if type is dynamic buffer, false otherwise.
	*/
	inline bool IsDynamicDescriptorType(VkDescriptorType descriptorType);

	/**
	* @brief Helper function to determine if a Vulkan descriptor type is a buffer (either uniform or storage buffer, dynamic or not).
	* @param descriptorType Vulkan descriptor type to check.
	* @return True if type is dynamic buffer, false otherwise.
	*/
	inline bool IsBufferDescriptorType(VkDescriptorType descriptorType);

	/**
	 * @brief Helper function to get the bits per pixel of a Vulkan format.
	 * @param format Vulkan format to check.
	 * @return The bits per pixel of the given format, -1 for invalid formats.
	 */
	inline Int32 GetBitsPerPixel(VkFormat format);

	enum class ShaderSourceLanguage : UInt8 {
		Glsl,
		Hlsl,
		Spv
	};

	enum class ShadingLanguage : UInt8 {
		Glsl,
		Hlsl
	};

	/**
	 * @brief Helper function to create a VkShaderModule.
	 * @param filename The shader location
	 * @param device The logical device
	 * @param stage The shader stage
	 * @param srcLanguage The shader language
	 * @return The shader module
	 */
	VkShaderModule LoadShader(const std::string& filename, VkDevice device, VkShaderStageFlagBits stage,
	                          ShaderSourceLanguage srcLanguage = ShaderSourceLanguage::Glsl);

	/**
	 * @brief Helper function to select a VkSurfaceFormatKHR.
	 * @param physicalDevice The VkPhysicalDevice to select the format for
	 * @param surface The VkSurfaceKHR to select the format for
	 * @param preferredFormats List of preferred VkFormat to use
	 * @return The preferred VkSurfaceFormatKHR
	 */
	VkSurfaceFormatKHR SelectSurfaceFormat(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
	                                       const std::vector<VkFormat>& preferredFormats = {
		                                       VK_FORMAT_R8G8B8A8_SRGB,
		                                       VK_FORMAT_B8G8R8A8_SRGB, VK_FORMAT_A8B8G8R8_SRGB_PACK32
	                                       });

	/**
	 * @brief Image memory barrier structure used to define
	 *        memory access for an image view during command recording.
	 */
	struct ImageMemoryBarrier {
		VkPipelineStageFlags SrcStageMask = {VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT};
		VkPipelineStageFlags DstStageMask = {VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT};

		VkAccessFlags SrcAccessMask{0};
		VkAccessFlags DstAccessMask{0};

		VkImageLayout OldLayout{VK_IMAGE_LAYOUT_UNDEFINED};
		VkImageLayout NewLayout{VK_IMAGE_LAYOUT_UNDEFINED};

		UInt32 OldQueueFamilyIndex{VK_QUEUE_FAMILY_IGNORED};
		UInt32 NewQueueFamilyIndex{VK_QUEUE_FAMILY_IGNORED};
	};

	/**
	 * @brief Buffer memory barrier structure used to define
	 *        memory access for a buffer during command recording.
	 */
	struct BufferMemoryBarrier {
		VkPipelineStageFlags SrcStageMask = {VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT};
		VkPipelineStageFlags DstStageMask = {VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT};

		VkAccessFlags SrcAccessMask{0};
		VkAccessFlags DstAccessMask{0};
	};

	/**
	 * @brief Put an image memory barrier for a layout transition of an image, using explicitly given transition parameters.
	 * @param commandBuffer The VkCommandBuffer to record the barrier.
	 * @param image The VkImage to transition.
	 * @param srcStageMask The VkPipelineStageFlags to use as source.
	 * @param dstStageMask The VkPipelineStageFlags to use as destination.
	 * @param srcAccessMask The VkAccessFlags to use as source.
	 * @param dstAccessMask The VkAccessFlags to use as destination.
	 * @param oldLayout The VkImageLayout to transition from.
	 * @param newLayout The VKImageLayout to transition to.
	 * @param subresourceRange The VkImageSubresourceRange to use with the transition.
	 */
	void ImageLayoutTransition(VkCommandBuffer commandBuffer,
	                           VkImage image,
	                           VkPipelineStageFlags srcStageMask,
	                           VkPipelineStageFlags dstStageMask,
	                           VkAccessFlags srcAccessMask,
	                           VkAccessFlags dstAccessMask,
	                           VkImageLayout oldLayout,
	                           VkImageLayout newLayout,
	                           const VkImageSubresourceRange& subresourceRange);

	/**
	 * @brief Put an image memory barrier for a layout transition of an image, on a given subresource range.
	 * 
	 *     The srcStageMask, dstStageMask, srcAccessMask, and dstAccessMask used are determined from oldLayout and newLayout.
	 * 
	 * @param commandBuffer The VkCommandBuffer to record the barrier.
	 * @param image The VkImage to transition.
	 * @param oldLayout The VkImageLayout to transition from.
	 * @param newLayout The VKImageLayout to transition to.
	 * @param subresourceRange The VkImageSubresourceRange to use with the transition.
	 */
	void ImageLayoutTransition(VkCommandBuffer commandBuffer,
	                           VkImage image,
	                           VkImageLayout oldLayout,
	                           VkImageLayout newLayout,
	                           const VkImageSubresourceRange& subresourceRange);

	/**
	 * @brief Put an image memory barrier for a layout transition of an image, on fixed subresource with first mip level and layer.
	 * 
	 *     The srcStageMask, dstStageMask, srcAccessMask, and dstAccessMask used are determined from oldLayout and newLayout.
	 * 
	 * @param commandBuffer The VkCommandBuffer to record the barrier.
	 * @param image The VkImage to transition.
	 * @param oldLayout The VkImageLayout to transition from.
	 * @param newLayout The VKImageLayout to transition to.
	 */
	void ImageLayoutTransition(VkCommandBuffer commandBuffer,
	                           VkImage image,
	                           VkImageLayout oldLayout,
	                           VkImageLayout newLayout);

	/**
	 * @brief Put an image memory barrier for a layout transition of a vector of images, with a given subresource range per image.
	 *
	 * The srcStageMask, dstStageMask, srcAccessMask, and dstAccessMask used are determined from oldLayout and newLayout.
	 *
	 * @param commandBuffer The VkCommandBuffer to record the barrier.
	 * @param imageAndRanges The images to transition, with accompanying subresource ranges.
	 * @param oldLayout The VkImageLayout to transition from.
	 * @param newLayout The VkImageLayout to transition to.
	 */
	void ImageLayoutTransition(VkCommandBuffer commandBuffer,
	                           const std::vector<std::pair<VkImage, VkImageSubresourceRange>>& imageAndRanges,
	                           VkImageLayout oldLayout,
	                           VkImageLayout newLayout);

	/*
	 * Helper functions for compression control.
	 */

	/**
	 * @brief Helper function to get compression rate flag bits from flags.
	 * @param flags The flags to get the bits from.
	 * @return A vector containing the bits.
	 */
	std::vector<VkImageCompressionFixedRateFlagBitsEXT> FixedRateCompressionFlagsToVector(
		VkImageCompressionFixedRateFlagsEXT flags);

	VkImageCompressionPropertiesEXT QuerySupportedFixedRateCompression(VkPhysicalDevice physicalDevice,
	                                                                   const VkImageCreateInfo& createInfo);

	VkImageCompressionPropertiesEXT QueryAppliedCompression(VkDevice device, VkImage image);

	/**
	 * @brief Load and store info for a render pass attachment.
	 */
	struct LoadStoreInfo {
		VkAttachmentLoadOp LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		VkAttachmentStoreOp StoreOp = VK_ATTACHMENT_STORE_OP_STORE;
	};

	namespace GBuffer {
		/**
		 * @brief Load store info to load all and store only the swap chain.
		 */
		std::vector<LoadStoreInfo> GetLoadAllStoreSwapchain();

		/**
		 * @brief Load store info to clear all and store only the swap chain.
		 */
		std::vector<LoadStoreInfo> GetClearAllStoreSwapchain();

		/**
		 * @brief Load store info to clear and store all images.
		 */
		std::vector<LoadStoreInfo> GetClearStoreAll();

		/**
		 * @brief Default clear values for the G-Buffer.
		 */
		std::vector<VkClearValue> GetClearValues();
	}
}

#include <VulkanTests/Renderer/VkCommon.inl>

#endif // VK_TESTS_RENDERER_VKCOMMON_HPP
