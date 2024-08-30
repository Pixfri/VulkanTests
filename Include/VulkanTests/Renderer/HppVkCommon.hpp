// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_HPPVKCOMMON_HPP
#define VK_TESTS_RENDERER_HPPVKCOMMON_HPP

#include <VulkanTests/Renderer/VkCommon.hpp>

#include <VulkanTests/Core/Logger.hpp>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_format_traits.hpp>

namespace VkTests::Common {
    struct HppBufferMemoryBarrier {
        vk::PipelineStageFlags SrcStageMask = vk::PipelineStageFlagBits::eBottomOfPipe;
        vk::PipelineStageFlags DstStageMask = vk::PipelineStageFlagBits::eTopOfPipe;
        vk::AccessFlags SrcAccessMask = {};
        vk::AccessFlags DstAccessMask = {};
    };

    struct HppImageMemoryBarrier {
        vk::PipelineStageFlags SrcStageMask = vk::PipelineStageFlagBits::eBottomOfPipe;
        vk::PipelineStageFlags DstStageMask = vk::PipelineStageFlagBits::eTopOfPipe;
        vk::AccessFlags SrcAccessMask;
        vk::AccessFlags DstAccessMask;
        vk::ImageLayout OldLayout = vk::ImageLayout::eUndefined;
        vk::ImageLayout NewLayout = vk::ImageLayout::eUndefined;
        UInt32 SrcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        UInt32 DstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    };

    struct HppLoadStore {
        vk::AttachmentLoadOp LoadOp = vk::AttachmentLoadOp::eClear;
        vk::AttachmentStoreOp StoreOp = vk::AttachmentStoreOp::eStore;
    };

    inline Int32 GetBitsPerPixel(vk::Format format);

    inline vk::Format GetSuitableDepthFormat(vk::PhysicalDevice physicalDevice, bool depthOnly = false,
                                             const std::vector<vk::Format>& depthFormatPriorityList = {
                                                 vk::Format::eD32Sfloat, vk::Format::eD24UnormS8Uint,
                                                 vk::Format::eD16Unorm});

    inline bool IsBufferDescriptorType(vk::DescriptorType type);

    inline bool IsDepthOnlyFormat(vk::Format format);

    inline bool IsDepthStencilFormat(vk::Format format);

    inline bool IsDepthFormat(vk::Format format);

    inline bool IsDynamicDescriptorType(vk::DescriptorType type);

    inline vk::ShaderModule LoadShader(const std::string& filename, vk::Device device, vk::ShaderStageFlagBits stage,
                                       ShaderSourceLanguage srcLanguage = ShaderSourceLanguage::Glsl);

    inline void ImageLayoutTransition(vk::CommandBuffer commandBuffer,
                                      vk::Image image,
                                      vk::ImageLayout oldLayout,
                                      vk::ImageLayout newLayout);

    inline void ImageLayoutTransition(vk::CommandBuffer commandBuffer,
                                      vk::Image image,
                                      vk::ImageLayout oldLayout,
                                      vk::ImageLayout newLayout,
                                      vk::ImageSubresourceRange subresourceRange);

    inline void ImageLayoutTransition(vk::CommandBuffer commandBuffer,
                                      vk::Image image,
                                      vk::PipelineStageFlags srcStageMask,
                                      vk::PipelineStageFlags dstStageMask,
                                      vk::AccessFlags srcAccessMask,
                                      vk::AccessFlags dstAccessMask,
                                      vk::ImageLayout oldLayout,
                                      vk::ImageLayout newLayout,
                                      const vk::ImageSubresourceRange& subresourceRange);

    inline vk::SurfaceFormatKHR SelectSurfaceFormat(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface,
                                                    const std::vector<vk::SurfaceFormatKHR>& preferredFormats = {
                                                        vk::Format::eR8G8B8A8Srgb, vk::Format::eB8G8R8A8Srgb,
                                                        vk::Format::eA8B8G8R8SrgbPack32});

    inline vk::Format ChooseBlendableFormat(vk::PhysicalDevice physicalDevice,
                                            const std::vector<vk::Format>& formatPriorityList);

    inline vk::CommandBuffer AllocateCommandBuffer(vk::Device device, vk::CommandPool commandPool,
                                                   vk::CommandBufferLevel level = vk::CommandBufferLevel::ePrimary);

    inline vk::DescriptorSet AllocateDescriptorSet(vk::Device device, vk::DescriptorPool descriptorPool,
                                                   vk::DescriptorSetLayout layout);

    inline vk::Framebuffer CreateFramebuffer(vk::Device device, vk::RenderPass renderPass,
                                             const std::vector<vk::ImageView>& attachments,
                                             vk::Extent2D extent);

    inline vk::Pipeline CreateGraphicsPipeline(vk::Device device, vk::PipelineCache pipelineCache,
                                               const std::vector<vk::PipelineShaderStageCreateInfo>& shaderStages,
                                               const vk::PipelineVertexInputStateCreateInfo& vertexInputState,
                                               vk::PrimitiveTopology primitiveTopology,
                                               UInt32 patchControlPoints,
                                               vk::PolygonMode polygonMode,
                                               vk::CullModeFlags cullMode,
                                               vk::FrontFace frontFace,
                                               const std::vector<vk::PipelineColorBlendAttachmentState>&
                                               colorAttachmentStates,
                                               const vk::PipelineDepthStencilStateCreateInfo& depthStencilState,
                                               vk::PipelineLayout pipelineLayout,
                                               vk::RenderPass renderPass);

    inline vk::ImageView CreateImageView(vk::Device device,
                                         vk::Image image,
                                         vk::ImageViewType viewType,
                                         vk::Format format,
                                         vk::ImageAspectFlags aspectMask = vk::ImageAspectFlagBits::eColor,
                                         UInt32 baseMipLevel = 0,
                                         UInt32 levelCount = 1,
                                         UInt32 baseArrayLayer = 0,
                                         UInt32 layerCount = 1);

    inline vk::QueryPool CreateQueryPool(vk::Device device, vk::QueryType queryType, UInt32 queryCount,
                                         vk::QueryPipelineStatisticFlags pipelineStatistics = {});

    inline vk::Sampler CreateSampler(vk::Device device,
                                     vk::Filter magFilter,
                                     vk::Filter minFilter,
                                     vk::SamplerMipmapMode mipmapMode,
                                     vk::SamplerAddressMode samplerAddressMode,
                                     Float32 maxAnisotropy,
                                     Float32 maxLod);

    inline vk::Sampler CreateSampler(vk::PhysicalDevice physicalDevice,
                                     vk::Device device,
                                     vk::Format format,
                                     vk::Filter filter,
                                     vk::SamplerAddressMode samplerAddressMode,
                                     Float32 maxAnisotropy,
                                     Float32 maxLod);

    inline vk::ImageAspectFlags GetImageAspectFlags(vk::ImageUsageFlagBits usage, vk::Format format);

    inline void SubmitAndWait(vk::Device device, vk::Queue queue, std::vector<vk::CommandBuffer> commandBuffers,
                              std::vector<vk::Semaphore> semaphores = {});
}

#include <VulkanTests/Renderer/HppVkCommon.inl>

#endif // VK_TESTS_RENDERER_HPPVKCOMMON_HPP
