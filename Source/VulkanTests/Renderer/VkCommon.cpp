// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Renderer/VkCommon.hpp>

#include <VulkanTests/Renderer/Strings.hpp>

#include <VulkanTests/Core/Logger.hpp>

#include <VulkanTests/Filesystem/Assets.hpp>

std::ostream& operator<<(std::ostream& os, const VkResult result) {
#define WRITE_VK_ENUM(r) \
    case VK_##r:  \
        os << #r; \
        break

	switch (result) {
	WRITE_VK_ENUM(NOT_READY);
	WRITE_VK_ENUM(TIMEOUT);
	WRITE_VK_ENUM(EVENT_SET);
	WRITE_VK_ENUM(EVENT_RESET);
	WRITE_VK_ENUM(INCOMPLETE);
	WRITE_VK_ENUM(ERROR_OUT_OF_HOST_MEMORY);
	WRITE_VK_ENUM(ERROR_OUT_OF_DEVICE_MEMORY);
	WRITE_VK_ENUM(ERROR_INITIALIZATION_FAILED);
	WRITE_VK_ENUM(ERROR_DEVICE_LOST);
	WRITE_VK_ENUM(ERROR_MEMORY_MAP_FAILED);
	WRITE_VK_ENUM(ERROR_LAYER_NOT_PRESENT);
	WRITE_VK_ENUM(ERROR_EXTENSION_NOT_PRESENT);
	WRITE_VK_ENUM(ERROR_FEATURE_NOT_PRESENT);
	WRITE_VK_ENUM(ERROR_INCOMPATIBLE_DRIVER);
	WRITE_VK_ENUM(ERROR_TOO_MANY_OBJECTS);
	WRITE_VK_ENUM(ERROR_FORMAT_NOT_SUPPORTED);
	WRITE_VK_ENUM(ERROR_SURFACE_LOST_KHR);
	WRITE_VK_ENUM(ERROR_NATIVE_WINDOW_IN_USE_KHR);
	WRITE_VK_ENUM(SUBOPTIMAL_KHR);
	WRITE_VK_ENUM(ERROR_OUT_OF_DATE_KHR);
	WRITE_VK_ENUM(ERROR_INCOMPATIBLE_DISPLAY_KHR);
	WRITE_VK_ENUM(ERROR_VALIDATION_FAILED_EXT);
	WRITE_VK_ENUM(ERROR_INVALID_SHADER_NV);
	default:
		os << "UNKNOWN_ERROR";
	}

#undef WRITE_VK_ENUM

	return os;
}

namespace VkTests {
	namespace {
		VkShaderStageFlagBits FindShaderStage(const std::string& ext) {
			switch (ext) {
			case "vert":
				return VK_SHADER_STAGE_VERTEX_BIT;
			case "frag":
				return VK_SHADER_STAGE_FRAGMENT_BIT;
			case "comp":
				return VK_SHADER_STAGE_COMPUTE_BIT;
			case "geom":
				return VK_SHADER_STAGE_GEOMETRY_BIT;
			case "tesc":
				return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
			case "tese":
				return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
			case "rgen":
				return VK_SHADER_STAGE_RAYGEN_BIT_KHR;
			case "rahit":
				return VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
			case "rchit":
				return VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
			case "rmiss":
				return VK_SHADER_STAGE_MISS_BIT_KHR;
			case "rint":
				return VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
			case "rcall":
				return VK_SHADER_STAGE_CALLABLE_BIT_KHR;
			case "mesh":
				return VK_SHADER_STAGE_MESH_BIT_EXT;
			case "task":
				return VK_SHADER_STAGE_TASK_BIT_EXT;
			default:
				Log::Fatal({0x02, 0x00}, "File extensions {} does not have a Vulkan shader stage flag.");
				return VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
			}
		}
	}

	VkFormat GetSuitableDepthFormat(const VkPhysicalDevice physicalDevice, const bool depthOnly,
	                                const std::vector<VkFormat>& depthFormatPriorityList) {
		VkFormat depthFormat{VK_FORMAT_UNDEFINED};

		for (auto& format : depthFormatPriorityList) {
			if (depthOnly && !IsDepthOnlyFormat(format)) {
				continue;
			}

			VkFormatProperties properties;
			vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &properties);

			// Format must support depth stencil attachment for optimal tiling
			if (properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
				depthFormat = format;
				break;
			}
		}

		if (depthFormat != VK_FORMAT_UNDEFINED) {
			Log::Info("Depth format selected: {}", ToString(depthFormat));
			return depthFormat;
		}

		Log::Fatal({0x02, 0x01}, "No suitable depth format could be determined.");
		return VK_FORMAT_MAX_ENUM;
	}

	VkFormat ChooseBlendableFormat(const VkPhysicalDevice physicalDevice,
	                               const std::vector<VkFormat>& formatPriorityList) {
		for (const auto& format : formatPriorityList) {
			VkFormatProperties properties;
			vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &properties);

			if (properties.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) {
				return format;
			}
		}

		Log::Fatal({0x02, 0x02}, "No suitable blendable format could be determined");
		return VK_FORMAT_MAX_ENUM;
	}

	void MakeFiltersValid(const VkPhysicalDevice physicalDevice, const VkFormat format, VkFilter* filter,
	                      VkSamplerMipmapMode* mipmapMode) {
		// Not all formats support linear filtering, so we need to adjust them if they don't.
		if (*filter == VK_FILTER_NEAREST && (mipmapMode == nullptr || *mipmapMode == VK_SAMPLER_MIPMAP_MODE_NEAREST)) {
			return;
		}

		VkFormatProperties properties;
		vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &properties);

		if (!(properties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) {
			*filter = VK_FILTER_NEAREST;
			if (mipmapMode) {
				*mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
			}
		}
	}


	VkShaderModule LoadShader(const std::string& filename, VkDevice device, VkShaderStageFlagBits stage,
	                          ShaderSourceLanguage srcLanguage) {
	}

	VkAccessFlags GetAccessFlags(const VkImageLayout layout) {
		switch (layout) {
		case VK_IMAGE_LAYOUT_UNDEFINED:
		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			return 0;
		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			return VK_ACCESS_HOST_WRITE_BIT;
		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			return VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		case VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL:
			return VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		case VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR:
			return VK_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR;
		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			return VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			return VK_ACCESS_TRANSFER_READ_BIT;
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			return VK_ACCESS_TRANSFER_WRITE_BIT;
		case VK_IMAGE_LAYOUT_GENERAL:
			assert(
				false && "Don't know how to get a meaningful VkAccessFlags for VK_IMAGE_LAYOUT_GENERAL! Don't use it!");
			return 0;
		default:
			assert(false);
			return 0;
		}
	}

	VkPipelineStageFlags GetPipelineStageFlags(const VkImageLayout layout) {
		switch (layout) {
		case VK_IMAGE_LAYOUT_UNDEFINED:
			return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			return VK_PIPELINE_STAGE_HOST_BIT;
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			return VK_PIPELINE_STAGE_TRANSFER_BIT;
		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		case VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL:
			return VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
		case VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR:
			return VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR;
		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			return VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			return VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		case VK_IMAGE_LAYOUT_GENERAL:
			assert(
				false &&
				"Don't know how to get a meaningful VkPipelineStageFlags for VK_IMAGE_LAYOUT_GENERAL! Don't use it!");
			return 0;
		default:
			assert(false);
			return 0;
		}
	}

	void ImageLayoutTransition(const VkCommandBuffer commandBuffer,
	                           const VkImage image,
	                           const VkPipelineStageFlags srcStageMask,
	                           const VkPipelineStageFlags dstStageMask,
	                           const VkAccessFlags srcAccessMask,
	                           const VkAccessFlags dstAccessMask,
	                           const VkImageLayout oldLayout,
	                           const VkImageLayout newLayout,
	                           const VkImageSubresourceRange& subresourceRange) {
		VkImageMemoryBarrier imageMemoryBarrier{};
		imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		imageMemoryBarrier.srcAccessMask = srcAccessMask;
		imageMemoryBarrier.dstAccessMask = dstAccessMask;
		imageMemoryBarrier.oldLayout = oldLayout;
		imageMemoryBarrier.newLayout = newLayout;
		imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.image = image;
		imageMemoryBarrier.subresourceRange = subresourceRange;

		vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, 0, 0, nullptr, 0, nullptr, 1,
		                     &imageMemoryBarrier);
	}

	void ImageLayoutTransition(const VkCommandBuffer commandBuffer,
	                           const VkImage image,
	                           const VkImageLayout oldLayout,
	                           const VkImageLayout newLayout,
	                           const VkImageSubresourceRange& subresourceRange) {
		const VkPipelineStageFlags srcStageMask = GetPipelineStageFlags(oldLayout);
		const VkPipelineStageFlags dstStageMask = GetPipelineStageFlags(newLayout);
		const VkAccessFlags srcAccessMask = GetAccessFlags(oldLayout);
		const VkAccessFlags dstAccessMask = GetAccessFlags(newLayout);

		ImageLayoutTransition(commandBuffer, image, srcStageMask, dstStageMask, srcAccessMask, dstAccessMask, oldLayout,
		                      newLayout, subresourceRange);
	}

	// Fixed subresource range on first mip level and layer
	void ImageLayoutTransition(const VkCommandBuffer commandBuffer,
	                           const VkImage image,
	                           const VkImageLayout oldLayout,
	                           const VkImageLayout newLayout) {
		VkImageSubresourceRange subresourceRange{};
		subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		subresourceRange.baseMipLevel = 0;
		subresourceRange.levelCount = 1;
		subresourceRange.baseArrayLayer = 0;
		subresourceRange.layerCount = 1;
		ImageLayoutTransition(commandBuffer, image, oldLayout, newLayout, subresourceRange);
	}

	void ImageLayoutTransition(const VkCommandBuffer commandBuffer,
	                           const std::vector<std::pair<VkImage, VkImageSubresourceRange>>& imageAndRanges,
	                           const VkImageLayout oldLayout,
	                           const VkImageLayout newLayout) {
		const VkPipelineStageFlags srcStageMask = GetPipelineStageFlags(oldLayout);
		const VkPipelineStageFlags dstStageMask = GetPipelineStageFlags(newLayout);
		const VkAccessFlags srcAccessMask = GetAccessFlags(oldLayout);
		const VkAccessFlags dstAccessMask = GetAccessFlags(newLayout);

		// Create image barrier objects.
		std::vector<VkImageMemoryBarrier> imageMemoryBarriers;
		imageMemoryBarriers.reserve(imageAndRanges.size());
		for (USize i = 0; i < imageAndRanges.size(); i++) {
			imageMemoryBarriers.emplace_back(VkImageMemoryBarrier{
				VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
				nullptr,
				srcAccessMask,
				dstAccessMask,
				oldLayout,
				newLayout,
				VK_QUEUE_FAMILY_IGNORED,
				VK_QUEUE_FAMILY_IGNORED,
				imageAndRanges[i].first,
				imageAndRanges[i].second
			});
		}

		vkCmdPipelineBarrier(
			commandBuffer,
			srcStageMask,
			dstStageMask,
			0,
			0,
			nullptr,
			0,
			nullptr,
			static_cast<UInt32>(imageMemoryBarriers.size()),
			imageMemoryBarriers.data());
	}

	std::vector<VkImageCompressionFixedRateFlagBitsEXT> FixedRateCompressionFlagsToVector(
		VkImageCompressionFixedRateFlagsEXT flags) {
		constexpr std::array<VkImageCompressionFixedRateFlagBitsEXT, 24> allFlags = {
			VK_IMAGE_COMPRESSION_FIXED_RATE_1BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_2BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_3BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_4BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_5BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_6BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_7BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_8BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_9BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_10BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_11BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_12BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_13BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_14BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_15BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_16BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_17BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_18BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_19BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_20BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_21BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_22BPC_BIT_EXT,
			VK_IMAGE_COMPRESSION_FIXED_RATE_23BPC_BIT_EXT, VK_IMAGE_COMPRESSION_FIXED_RATE_24BPC_BIT_EXT
		};

		std::vector<VkImageCompressionFixedRateFlagBitsEXT> flagsVector;

		for (auto bit : allFlags) {
			if (bit & flags) {
				flagsVector.push_back(bit);
			}
		}

		return flagsVector;
	}

	VkImageCompressionPropertiesEXT QuerySupportedFixedRateCompression(const VkPhysicalDevice physicalDevice,
	                                                                   const VkImageCreateInfo& createInfo) {
		VkImageCompressionPropertiesEXT supportedCompressionProperties{};
		supportedCompressionProperties.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT;

		VkImageCompressionControlEXT compressionControl{};
		compressionControl.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
		compressionControl.flags = VK_IMAGE_COMPRESSION_FIXED_RATE_DEFAULT_EXT;

		VkPhysicalDeviceImageFormatInfo2 imageFormatInfo{};
		imageFormatInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
		imageFormatInfo.format = createInfo.format;
		imageFormatInfo.type = createInfo.imageType;
		imageFormatInfo.tiling = createInfo.tiling;
		imageFormatInfo.usage = createInfo.usage;
		imageFormatInfo.pNext = &compressionControl;

		VkImageFormatProperties2 imageFormatProperties{};
		imageFormatProperties.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;
		imageFormatProperties.pNext = &supportedCompressionProperties;

		vkGetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, &imageFormatInfo, &imageFormatProperties);

		return supportedCompressionProperties;
	}

	VkImageCompressionPropertiesEXT QueryAppliedCompression(const VkDevice device, const VkImage image) {
		VkImageSubresource2EXT imageSubresource{};
		imageSubresource.sType = VK_STRUCTURE_TYPE_IMAGE_SUBRESOURCE_2_EXT;
		imageSubresource.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageSubresource.imageSubresource.mipLevel = 0;
		imageSubresource.imageSubresource.arrayLayer = 0;

		VkImageCompressionPropertiesEXT compressionProperties{};
		compressionProperties.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT;

		VkSubresourceLayout2EXT subresourceLayout{};
		subresourceLayout.sType = VK_STRUCTURE_TYPE_SUBRESOURCE_LAYOUT_2_EXT;
		subresourceLayout.pNext = &compressionProperties;

		vkGetImageSubresourceLayout2EXT(device, image, &imageSubresource, &subresourceLayout);

		return compressionProperties;
	}

	VkSurfaceFormatKHR SelectSurfaceFormat(const VkPhysicalDevice physicalDevice, const VkSurfaceKHR surface,
	                                       const std::vector<VkFormat>& preferredFormats) {
		UInt32 surfaceFormatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, nullptr);
		assert(surfaceFormatCount > 0);
		std::vector<VkSurfaceFormatKHR> supportedSurfaceFormats(surfaceFormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount,
		                                     supportedSurfaceFormats.data());

		auto it = std::ranges::find_if(supportedSurfaceFormats,
		                               [&preferredFormats](VkSurfaceFormatKHR surfaceFormat) {
			                               return std::ranges::any_of(preferredFormats,
			                                                          [&surfaceFormat](VkFormat format) {
				                                                          return format == surfaceFormat.format;
			                                                          });
		                               });

		return it != supportedSurfaceFormats.end() ? *it : supportedSurfaceFormats[0];
	}

	namespace GBuffer {
		std::vector<LoadStoreInfo> GetLoadAllStoreSwapchain() {
			// Load every attachment and store only the swapchain.
			std::vector<LoadStoreInfo> loadStore{4};

			// Swapchain
			loadStore[0].LoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			loadStore[0].StoreOp = VK_ATTACHMENT_STORE_OP_STORE;

			// Depth
			loadStore[1].LoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
			loadStore[1].StoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			// Albedo
			loadStore[2].LoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
			loadStore[2].StoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			// Normal
			loadStore[3].LoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
			loadStore[3].StoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			return loadStore;
		}

		std::vector<LoadStoreInfo> GetClearAllStoreSwapchain() {
			// Load every attachment and store only the swapchain.
			std::vector<LoadStoreInfo> loadStore{4};

			// Swapchain
			loadStore[0].LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			loadStore[0].StoreOp = VK_ATTACHMENT_STORE_OP_STORE;

			// Depth
			loadStore[1].LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			loadStore[1].StoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			// Albedo
			loadStore[2].LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			loadStore[2].StoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			// Normal
			loadStore[3].LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			loadStore[3].StoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			return loadStore;
		}

		std::vector<LoadStoreInfo> GetClearStoreAll() {
			// Load every attachment and store only the swapchain.
			std::vector<LoadStoreInfo> loadStore{4};

			// Swapchain
			loadStore[0].LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			loadStore[0].StoreOp = VK_ATTACHMENT_STORE_OP_STORE;

			// Depth
			loadStore[1].LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			loadStore[1].StoreOp = VK_ATTACHMENT_STORE_OP_STORE;

			// Albedo
			loadStore[2].LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			loadStore[2].StoreOp = VK_ATTACHMENT_STORE_OP_STORE;

			// Normal
			loadStore[3].LoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			loadStore[3].StoreOp = VK_ATTACHMENT_STORE_OP_STORE;

			return loadStore;
		}

		std::vector<VkClearValue> GetClearValues() {
			std::vector<VkClearValue> clearValues{4};
			clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
			clearValues[1].depthStencil = {1.0f, ~0U};
			clearValues[2].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
			clearValues[3].color = {{0.0f, 0.0f, 0.0f, 1.0f}};

			return clearValues;
		}
	}
}
