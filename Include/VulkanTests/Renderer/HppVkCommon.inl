// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests::Common {
    inline Int32 GetBitsPerPixel(vk::Format format) {
        return VkTests::GetBitsPerPixel(static_cast<VkFormat>(format));
    }

    inline vk::Format GetSuitableDepthFormat(const vk::PhysicalDevice physicalDevice, const bool depthOnly,
                                             const std::vector<vk::Format>& depthFormatPriorityList) {
        return static_cast<vk::Format>(VkTests::GetSuitableDepthFormat(physicalDevice, depthOnly,
                                                                       reinterpret_cast<const std::vector<VkFormat>&>(
                                                                           depthFormatPriorityList)));
    }

    inline bool IsBufferDescriptorType(vk::DescriptorType type) {
        return VkTests::IsBufferDescriptorType(static_cast<VkDescriptorType>(type));
    }

    inline bool IsDepthOnlyFormat(vk::Format format) {
        assert(
            VkTests::IsDepthOnlyFormat(static_cast<VkFormat>(format)) == ((vk::componentCount(format) == 1) && (std::
                string(vk::componentName(format, 0)) == "D")));
        return VkTests::IsDepthOnlyFormat(static_cast<VkFormat>(format));
    }

    inline bool IsDepthStencilFormat(vk::Format format) {
        assert(
            VkTests::IsDepthStencilFormat(static_cast<VkFormat>(format)) == ((vk::componentCount(format) == 2) && (std::
                string(vk::componentName(format, 0)) == "D") && (std::string(vk::componentName(format, 1)) == "S")));
        return VkTests::IsDepthStencilFormat(static_cast<VkFormat>(format));
    }

    inline bool IsDepthFormat(vk::Format format) {
        assert(
            VkTests::IsDepthStencilFormat(static_cast<VkFormat>(format)) == (std::string(vk::componentName(format, 0))
                == "D"));

        return VkTests::IsDepthFormat(static_cast<VkFormat>(format));
    }

    inline bool IsDynamicDescriptorType(vk::DescriptorType type) {
        return VkTests::IsDynamicDescriptorType(static_cast<VkDescriptorType>(type));
    }

    inline vk::ShaderModule LoadShader(const std::string& filename, const vk::Device device,
                                       vk::ShaderStageFlagBits stage, const ShaderSourceLanguage srcLanguage) {
        return VkTests::LoadShader(filename, device, static_cast<VkShaderStageFlagBits>(stage), srcLanguage);
    }



    inline void ImageLayoutTransition(const vk::CommandBuffer commandBuffer,
                                      const vk::Image image,
                                      vk::ImageLayout oldLayout,
                                      vk::ImageLayout newLayout) {
        VkTests::ImageLayoutTransition(commandBuffer,
                                       image,
                                       static_cast<VkImageLayout>(oldLayout),
                                       static_cast<VkImageLayout>(newLayout));
    }

    inline void ImageLayoutTransition(const vk::CommandBuffer commandBuffer,
                                      const vk::Image image,
                                      vk::ImageLayout oldLayout,
                                      vk::ImageLayout newLayout,
                                      vk::ImageSubresourceRange subresourceRange) {
        VkTests::ImageLayoutTransition(commandBuffer,
                                       image,
                                       static_cast<VkImageLayout>(oldLayout),
                                       static_cast<VkImageLayout>(newLayout),
                                       subresourceRange);
    }

    inline void ImageLayoutTransition(const vk::CommandBuffer commandBuffer,
                                      const vk::Image image,
                                      const vk::PipelineStageFlags srcStageMask,
                                      const vk::PipelineStageFlags dstStageMask,
                                      const vk::AccessFlags srcAccessMask,
                                      const vk::AccessFlags dstAccessMask,
                                      vk::ImageLayout oldLayout,
                                      vk::ImageLayout newLayout,
                                      const vk::ImageSubresourceRange& subresourceRange) {
        VkTests::ImageLayoutTransition(commandBuffer,
                                       image,
                                       static_cast<VkPipelineStageFlags>(srcStageMask),
                                       static_cast<VkPipelineStageFlags>(dstStageMask),
                                       static_cast<VkAccessFlags>(srcAccessMask),
                                       static_cast<VkAccessFlags>(dstAccessMask),
                                       static_cast<VkImageLayout>(oldLayout),
                                       static_cast<VkImageLayout>(newLayout),
                                       subresourceRange);
    }

    inline vk::SurfaceFormatKHR SelectSurfaceFormat(const vk::PhysicalDevice physicalDevice,
                                                    const vk::SurfaceKHR surface,
                                                    const std::vector<vk::SurfaceFormatKHR>& preferredFormats) {
        std::vector<vk::SurfaceFormatKHR> supportedSurfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);
        assert(!supportedSurfaceFormats.empty());

        const auto it = std::ranges::find_if(supportedSurfaceFormats,
                                             [&preferredFormats](vk::SurfaceFormatKHR surfaceFormat) {
                                                 return std::any_of(preferredFormats.begin(), preferredFormats.end(),
                                                                    [&surfaceFormat](const vk::Format format) {
                                                                        return format == surfaceFormat.format;
                                                                    });
                                             });

        return it != supportedSurfaceFormats.end() ? *it : supportedSurfaceFormats.front();
    }

    inline vk::Format ChooseBlendableFormat(const vk::PhysicalDevice physicalDevice,
                                            const std::vector<vk::Format>& formatPriorityList) {
        for (const auto& format : formatPriorityList) {
            if (const vk::FormatProperties formatProperties = physicalDevice.getFormatProperties(format);
                formatProperties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eColorAttachmentBlend) {
                return format;
            }
        }

        Log::Fatal({0x02, 0x03}, "No suitable blendable format could be determined.");
        return vk::Format::eUndefined;
    }

    inline vk::CommandBuffer AllocateCommandBuffer(const vk::Device device, const vk::CommandPool commandPool,
                                                   const vk::CommandBufferLevel level) {
        const vk::CommandBufferAllocateInfo commandBufferAllocateInfo(commandPool, level, 1);
        return device.allocateCommandBuffers(commandBufferAllocateInfo).front();
    }

    inline vk::DescriptorSet AllocateDescriptorSet(const vk::Device device, const vk::DescriptorPool descriptorPool,
                                                   vk::DescriptorSetLayout layout) {
        const vk::DescriptorSetAllocateInfo descriptorSetAllocateInfo(descriptorPool, layout);
        return device.allocateDescriptorSets(descriptorSetAllocateInfo).front();
    }

    inline vk::Framebuffer CreateFramebuffer(const vk::Device device, const vk::RenderPass renderPass,
                                             const std::vector<vk::ImageView>& attachments,
                                             const vk::Extent2D extent) {
        const vk::FramebufferCreateInfo framebufferCreateInfo({}, renderPass, attachments, extent.width, extent.height,
                                                              1);
        return device.createFramebuffer(framebufferCreateInfo);
    }

    inline vk::Pipeline CreateGraphicsPipeline(vk::Device device, vk::PipelineCache pipelineCache,
                                               const std::vector<vk::PipelineShaderStageCreateInfo>& shaderStages,
                                               const vk::PipelineVertexInputStateCreateInfo& vertexInputState,
                                               const vk::PrimitiveTopology primitiveTopology,
                                               const UInt32 patchControlPoints,
                                               const vk::PolygonMode polygonMode,
                                               const vk::CullModeFlags cullMode,
                                               const vk::FrontFace frontFace,
                                               const std::vector<vk::PipelineColorBlendAttachmentState>&
                                               colorAttachmentStates,
                                               const vk::PipelineDepthStencilStateCreateInfo& depthStencilState,
                                               vk::PipelineLayout pipelineLayout,
                                               vk::RenderPass renderPass) {
        vk::PipelineInputAssemblyStateCreateInfo inputAssemblyState({}, primitiveTopology, false);

        vk::PipelineTessellationStateCreateInfo tessellationState({}, patchControlPoints);

        vk::PipelineViewportStateCreateInfo viewportState({}, 1, nullptr, 1, nullptr);

        vk::PipelineRasterizationStateCreateInfo rasterizationState;
        rasterizationState.polygonMode = polygonMode;
        rasterizationState.cullMode = cullMode;
        rasterizationState.frontFace = frontFace;
        rasterizationState.lineWidth = 1.0f;

        vk::PipelineMultisampleStateCreateInfo multisampleState({}, vk::SampleCountFlagBits::e1);

        vk::PipelineColorBlendStateCreateInfo colorBlendState({}, false, {}, colorAttachmentStates);

        std::array<vk::DynamicState, 2> dynamicStateEnables = {vk::DynamicState::eViewport, vk::DynamicState::eScissor};
        vk::PipelineDynamicStateCreateInfo dynamicState({}, dynamicStateEnables);

        // Final fullscreen composition pipeline pass
        vk::GraphicsPipelineCreateInfo pipelineCreateInfo({},
                                                          shaderStages,
                                                          &vertexInputState,
                                                          &inputAssemblyState,
                                                          &tessellationState,
                                                          &viewportState,
                                                          &rasterizationState,
                                                          &multisampleState,
                                                          &depthStencilState,
                                                          &colorBlendState,
                                                          &dynamicState,
                                                          pipelineLayout,
                                                          renderPass,
                                                          {},
                                                          {},
                                                          -1);

        vk::Result result;
        vk::Pipeline pipeline;
        std::tie(result, pipeline) = device.createGraphicsPipeline(pipelineCache, pipelineCreateInfo);
        assert(result == vk::Result::eSuccess);
        return pipeline;
    }

    inline vk::ImageView CreateImageView(const vk::Device device,
                                         const vk::Image image,
                                         const vk::ImageViewType viewType,
                                         const vk::Format format,
                                         const vk::ImageAspectFlags aspectMask,
                                         const UInt32 baseMipLevel,
                                         const UInt32 levelCount,
                                         const UInt32 baseArrayLayer,
                                         const UInt32 layerCount) {
        vk::ImageViewCreateInfo imageViewCreateInfo;
        imageViewCreateInfo.image = image;
        imageViewCreateInfo.viewType = viewType;
        imageViewCreateInfo.format = format;
        imageViewCreateInfo.subresourceRange.aspectMask = aspectMask;
        imageViewCreateInfo.subresourceRange.baseMipLevel = baseMipLevel;
        imageViewCreateInfo.subresourceRange.levelCount = levelCount;
        imageViewCreateInfo.subresourceRange.baseArrayLayer = baseArrayLayer;
        imageViewCreateInfo.subresourceRange.layerCount = layerCount;
        return device.createImageView(imageViewCreateInfo);
    }

    inline vk::QueryPool CreateQueryPool(const vk::Device device, const vk::QueryType queryType,
                                         const UInt32 queryCount,
                                         const vk::QueryPipelineStatisticFlags pipelineStatistics) {
        vk::QueryPoolCreateInfo queryPoolCreateInfo;
        queryPoolCreateInfo.queryType = queryType;
        queryPoolCreateInfo.queryCount = queryCount;
        queryPoolCreateInfo.pipelineStatistics = pipelineStatistics;
        return device.createQueryPool(queryPoolCreateInfo);
    }

    inline vk::Sampler CreateSampler(const vk::Device device,
                                     const vk::Filter magFilter,
                                     const vk::Filter minFilter,
                                     const vk::SamplerMipmapMode mipmapMode,
                                     const vk::SamplerAddressMode samplerAddressMode,
                                     const Float32 maxAnisotropy,
                                     const Float32 maxLod) {
        const vk::SamplerCreateInfo samplerCreateInfo({},
                                                      magFilter,
                                                      minFilter,
                                                      mipmapMode,
                                                      samplerAddressMode,
                                                      samplerAddressMode,
                                                      samplerAddressMode,
                                                      0.0f,
                                                      (1.0 < maxAnisotropy),
                                                      maxAnisotropy,
                                                      false,
                                                      vk::CompareOp::eNever,
                                                      0.0f,
                                                      maxLod,
                                                      vk::BorderColor::eFloatOpaqueWhite);
        return device.createSampler(samplerCreateInfo);
    }

    inline vk::Sampler CreateSampler(const vk::PhysicalDevice physicalDevice,
                                     const vk::Device device,
                                     const vk::Format format,
                                     const vk::Filter filter,
                                     const vk::SamplerAddressMode samplerAddressMode,
                                     const Float32 maxAnisotropy,
                                     const Float32 maxLod) {
        const vk::FormatProperties formatProperties = physicalDevice.getFormatProperties(format);

        const bool hasLinearFiltering = !!(formatProperties.linearTilingFeatures &
            vk::FormatFeatureFlagBits::eSampledImageFilterLinear);

        return CreateSampler(device,
                             hasLinearFiltering ? filter : vk::Filter::eNearest,
                             hasLinearFiltering ? filter : vk::Filter::eNearest,
                             hasLinearFiltering ? vk::SamplerMipmapMode::eLinear : vk::SamplerMipmapMode::eNearest,
                             samplerAddressMode,
                             maxAnisotropy,
                             maxLod);
    }

    inline vk::ImageAspectFlags GetImageAspectFlags(const vk::ImageUsageFlagBits usage, const vk::Format format) {
        vk::ImageAspectFlags flags;

        switch (usage) {
        case vk::ImageUsageFlagBits::eColorAttachment:
            assert(!IsDepthFormat(format));
            flags = vk::ImageAspectFlagBits::eColor;
            break;
        case vk::ImageUsageFlagBits::eDepthStencilAttachment:
            assert(IsDepthFormat(format));
            flags = vk::ImageAspectFlagBits::eDepth;
            if (IsDepthStencilFormat(format)) {
                flags |= vk::ImageAspectFlagBits::eStencil;
            }
            break;
        default:
            assert(false);
            break;
        }

        return flags;
    }

    inline void SubmitAndWait(vk::Device device, vk::Queue queue, std::vector<vk::CommandBuffer> commandBuffers,
                              std::vector<vk::Semaphore> semaphores = {}) {
        // Submit command buffer
        const vk::SubmitInfo submitInfo(nullptr, {}, commandBuffers, semaphores);

        // Create fence to ensure that the command buffer has finished executing
        const vk::Fence fence = device.createFence({});

        // Submit to the queue
        queue.submit(submitInfo, fence);

        // Wait for the fence to signal that the command buffer has finished executing
        if (const vk::Result result = device.waitForFences(fence, true, VK_TESTS_DEFAULT_FENCE_TIMEOUT);
            result != vk::Result::eSuccess) {
            Log::Error("Vulkan error on waitForFences: {0}", vk::to_string(result));
            abort();
        }

        // Destroy the fence.
        device.destroyFence(fence);
    }
}
