// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_RENDERER_VKINITIALIZERS_HPP
#define VK_TESTS_RENDERER_VKINITIALIZERS_HPP

#include <VulkanTests/pch.hpp>

#include <volk.h>

namespace VkTests::VkInitializers {
    inline VkMemoryAllocateInfo MemoryAllocateInfo();

    inline VkMappedMemoryRange MappedMemoryRange();

    inline VkCommandBufferAllocateInfo CommandBufferAllocateInfo(VkCommandPool commandPool, VkCommandBufferLevel level,
                                                                 UInt32 bufferCount);

    inline VkCommandPoolCreateInfo CommandPoolCreateInfo();

    inline VkCommandBufferBeginInfo CommandBufferBeginInfo();

    inline VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo();

    inline VkRenderPassBeginInfo RenderPassBeginInfo();

    inline VkRenderPassCreateInfo RenderPassCreateInfo();

    inline VkRenderingAttachmentInfo RenderingAttachmentInfo();

    inline VkRenderingInfo RenderingInfo(VkRect2D renderArea = {},
                                         UInt32 colorAttachmentCount = 0,
                                         const VkRenderingAttachmentInfo* pColorAttachments = VK_NULL_HANDLE,
                                         VkRenderingFlags flags = 0);

    inline VkImageMemoryBarrier ImageMemoryBarrier();

    inline VkBufferMemoryBarrier BufferMemoryBarrier();

    inline VkMemoryBarrier MemoryBarrier();

    inline VkImageCreateInfo ImageCreateInfo();

    inline VkSamplerCreateInfo SamplerCreateInfo();

    inline VkImageViewCreateInfo ImageViewCreateInfo();

    inline VkFramebufferCreateInfo FramebufferCreateInfo();

    inline VkSemaphoreCreateInfo SemaphoreCreateInfo();

    inline VkFenceCreateInfo FenceCreateInfo(VkFenceCreateFlags flags = 0);

    inline VkEventCreateInfo EventCreateInfo();

    inline VkSubmitInfo SubmitInfo();

    inline VkViewport Viewport(Float32 width, Float32 height, Float32 minDepth, Float32 maxDepth);

    inline VkRect2D Rect2D(Int32 width, Int32 height, Int32 offsetX, Int32 offsetY);

    inline VkBufferCreateInfo BufferCreateInfo();

    inline VkBufferCreateInfo BufferCreateInfo(VkBufferUsageFlags usage, VkDeviceSize size);

    inline VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo(UInt32 count,
                                                               const VkDescriptorPoolSize* poolSizes,
                                                               UInt32 maxSets);

    inline VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo(const std::vector<VkDescriptorPoolSize>& poolSizes,
                                                               UInt32 maxSets);

    inline VkDescriptorPoolSize DescriptorPoolSize(VkDescriptorType type, UInt32 descriptorCount);

    inline VkDescriptorSetLayoutBinding DescriptorSetLayoutBinding(VkDescriptorType type, VkShaderStageFlags stageFlags,
                                                                   UInt32 binding, UInt32 count = 1);

    inline VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo(const VkDescriptorSetLayoutBinding* pBindings,
                                                                         UInt32 bindingCount);

    inline VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo(
        const std::vector<VkDescriptorSetLayoutBinding>& bindings);

    inline VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo(const VkDescriptorSetLayout* pSetLayouts,
                                                               UInt32 setLayoutCount = 1);

    inline VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo(UInt32 setLayoutCount);

    inline VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo(VkDescriptorPool descriptorPool,
                                                                 const VkDescriptorSetLayout* pSetLayouts,
                                                                 UInt32 descriptorSetCount);

    inline VkDescriptorImageInfo DescriptorImageInfo(VkSampler sampler,
                                                     VkImageView imageView,
                                                     VkImageLayout imageLayout);

    inline VkWriteDescriptorSet WriteDescriptorSet(VkDescriptorSet dstSet, VkDescriptorType type, UInt32 binding,
                                                   const VkDescriptorBufferInfo* pBufferInfo,
                                                   UInt32 descriptorCount = 1);

    inline VkWriteDescriptorSet WriteDescriptorSet(VkDescriptorSet dstSet, VkDescriptorType type, UInt32 binding,
                                                   const VkDescriptorImageInfo* pImageInfo, UInt32 descriptorCount = 1);

    inline VkVertexInputBindingDescription VertexInputBindingDescription(UInt32 binding, UInt32 stride,
                                                                         VkVertexInputRate inputRate);

    inline VkVertexInputBindingDescription2EXT VertexInputBindingDescription2Ext(UInt32 binding, UInt32 stride,
                                                                                 VkVertexInputRate inputRate,
                                                                                 UInt32 divisor);

    inline VkVertexInputAttributeDescription VertexInputAttributeDescription(UInt32 binding, UInt32 location,
                                                                             VkFormat format, UInt32 offset);

    inline VkVertexInputAttributeDescription2EXT VertexInputAttributeDescription2Ext(UInt32 binding, UInt32 location,
                                                                                     VkFormat format, UInt32 offset);

    inline VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo();

    inline VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology topology,
                                                                                       VkPipelineInputAssemblyStateCreateFlags
                                                                                       flags,
                                                                                       VkBool32 primitiveRestartEnable);

    inline VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo(VkPolygonMode polygonMode,
                                                                                       VkCullModeFlags cullMode,
                                                                                       VkFrontFace frontFace,
                                                                                       VkPipelineRasterizationStateCreateFlags
                                                                                       flags = 0);

    inline VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentState(
        VkColorComponentFlags colorWriteMask, VkBool32 blendEnable);

    inline VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo(
        UInt32 attachmentCount, const VkPipelineColorBlendAttachmentState* pAttachments);

    inline VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateCreateInfo(
        VkBool32 depthTestEnable, VkBool32 depthWriteEnable, VkCompareOp depthCompareOp);

    inline VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo(
        UInt32 viewportCount, UInt32 scissorCount, VkPipelineViewportStateCreateFlags flags = 0);

    inline VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo(
        VkSampleCountFlagBits rasterizationSamples, VkPipelineMultisampleStateCreateFlags flags = 0);

    inline VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo(
        const VkDynamicState* pDynamicStates, UInt32 dynamicStateCount,
        VkPipelineDynamicStateCreateFlags flags = 0);

    inline VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo(
        const std::vector<VkDynamicState>& dynamicStates,
        VkPipelineDynamicStateCreateFlags flags = 0);

    inline VkPipelineTessellationStateCreateInfo PipelineTessellationStateCreateInfo(UInt32 patchControlPoints);

    inline VkGraphicsPipelineCreateInfo PipelineCreateInfo(VkPipelineLayout layout, VkRenderPass renderPass,
                                                           VkPipelineCreateFlags flags = 0);

    inline VkGraphicsPipelineCreateInfo PipelineCreateInfo();

    inline VkComputePipelineCreateInfo ComputePipelineCreateInfo(VkPipelineLayout layout,
                                                                 VkPipelineCreateFlags flags = 0);

    inline VkPushConstantRange PushConstantRange(VkShaderStageFlags stageFlags, UInt32 size, UInt32 offset);

    inline VkBindSparseInfo BindSparseInfo();

    inline VkSpecializationMapEntry SpecializationMapEntry(UInt32 constantId, UInt32 offset, USize size);

    inline VkSpecializationInfo SpecializationInfo(UInt32 mapEntryCount, const VkSpecializationMapEntry* pMapEntries,
                                                   USize dataSize, const void* pData);
}

#include <VulkanTests/Renderer/VkInitializers.inl>

#endif // VK_TESTS_RENDERER_VKINITIALIZERS_HPP
