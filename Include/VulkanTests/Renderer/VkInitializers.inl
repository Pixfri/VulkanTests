// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests::VkInitializers {
    inline VkMemoryAllocateInfo MemoryAllocateInfo() {
        VkMemoryAllocateInfo memoryAllocation{};
        memoryAllocation.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        return memoryAllocation;
    }

    inline VkMappedMemoryRange MappedMemoryRange() {
        VkMappedMemoryRange mappedMemoryRange{};
        mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        return mappedMemoryRange;
    }

    inline VkCommandBufferAllocateInfo CommandBufferAllocateInfo(const VkCommandPool commandPool,
                                                                 const VkCommandBufferLevel level,
                                                                 const UInt32 bufferCount) {
        VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.commandPool = commandPool;
        commandBufferAllocateInfo.level = level;
        commandBufferAllocateInfo.commandBufferCount = bufferCount;
        return commandBufferAllocateInfo;
    }

    inline VkCommandPoolCreateInfo CommandPoolCreateInfo() {
        VkCommandPoolCreateInfo commandPoolCreateInfo{};
        commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        return commandPoolCreateInfo;
    }

    inline VkCommandBufferBeginInfo CommandBufferBeginInfo() {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        return beginInfo;
    }

    inline VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo() {
        VkCommandBufferInheritanceInfo commandBufferInheritanceInfo{};
        commandBufferInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
        return commandBufferInheritanceInfo;
    }

    inline VkRenderPassBeginInfo RenderPassBeginInfo() {
        VkRenderPassBeginInfo renderPassBeginInfo{};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        return renderPassBeginInfo;
    }

    inline VkRenderPassCreateInfo RenderPassCreateInfo() {
        VkRenderPassCreateInfo renderPassCreateInfo{};
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        return renderPassCreateInfo;
    }

    inline VkRenderingAttachmentInfo RenderingAttachmentInfo() {
        VkRenderingAttachmentInfo renderingAttachmentInfo{};
        renderingAttachmentInfo.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
        renderingAttachmentInfo.pNext = nullptr;
        return renderingAttachmentInfo;
    }

    inline VkRenderingInfo RenderingInfo(const VkRect2D renderArea,
                                         const UInt32 colorAttachmentCount,
                                         const VkRenderingAttachmentInfo* pColorAttachments,
                                         const VkRenderingFlags flags) {
        VkRenderingInfo renderingInfo;
        renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
        renderingInfo.pNext = nullptr;
        renderingInfo.flags = flags;
        renderingInfo.renderArea = renderArea;
        renderingInfo.layerCount = 0;
        renderingInfo.viewMask = 0;
        renderingInfo.colorAttachmentCount = colorAttachmentCount;
        renderingInfo.pColorAttachments = pColorAttachments;
        renderingInfo.pDepthAttachment = VK_NULL_HANDLE;
        renderingInfo.pStencilAttachment = VK_NULL_HANDLE;
        return renderingInfo;
    }

    inline VkImageMemoryBarrier ImageMemoryBarrier() {
        VkImageMemoryBarrier imageMemoryBarrier{};
        imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        return imageMemoryBarrier;
    }

    inline VkBufferMemoryBarrier BufferMemoryBarrier() {
        VkBufferMemoryBarrier bufferMemoryBarrier{};
        bufferMemoryBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
        bufferMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        bufferMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        return bufferMemoryBarrier;
    }

    inline VkMemoryBarrier MemoryBarrier() {
        VkMemoryBarrier memoryBarrier{};
        memoryBarrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
        return memoryBarrier;
    }

    inline VkImageCreateInfo ImageCreateInfo() {
        VkImageCreateInfo imageCreateInfo{};
        imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        return imageCreateInfo;
    }

    inline VkSamplerCreateInfo SamplerCreateInfo() {
        VkSamplerCreateInfo samplerCreateInfo{};
        samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerCreateInfo.maxAnisotropy = 1.0f;
        return samplerCreateInfo;
    }

    inline VkImageViewCreateInfo ImageViewCreateInfo() {
        VkImageViewCreateInfo imageViewCreateInfo{};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        return imageViewCreateInfo;
    }

    inline VkFramebufferCreateInfo FramebufferCreateInfo() {
        VkFramebufferCreateInfo framebufferCreateInfo{};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        return framebufferCreateInfo;
    }

    inline VkSemaphoreCreateInfo SemaphoreCreateInfo() {
        VkSemaphoreCreateInfo semaphoreCreateInfo{};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        return semaphoreCreateInfo;
    }

    inline VkFenceCreateInfo FenceCreateInfo(const VkFenceCreateFlags flags) {
        VkFenceCreateInfo fenceCreateInfo{};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceCreateInfo.flags = flags;
        return fenceCreateInfo;
    }

    inline VkEventCreateInfo EventCreateInfo() {
        VkEventCreateInfo eventCreateInfo{};
        eventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
        return eventCreateInfo;
    }

    inline VkSubmitInfo SubmitInfo() {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        return submitInfo;
    }

    inline VkViewport Viewport(const Float32 width,
                               const Float32 height,
                               const Float32 minDepth,
                               const Float32 maxDepth) {
        VkViewport viewport{};
        viewport.width = width;
        viewport.height = height;
        viewport.minDepth = minDepth;
        viewport.maxDepth = maxDepth;
        return viewport;
    }

    inline VkRect2D Rect2D(const Int32 width, const Int32 height, const Int32 offsetX, const Int32 offsetY) {
        VkRect2D rect2D;
        rect2D.extent.width = width;
        rect2D.extent.height = height;
        rect2D.offset.x = offsetX;
        rect2D.offset.y = offsetY;
        return rect2D;
    }

    inline VkBufferCreateInfo BufferCreateInfo() {
        VkBufferCreateInfo bufferCreateInfo{};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        return bufferCreateInfo;
    }

    inline VkBufferCreateInfo BufferCreateInfo(const VkBufferUsageFlags usage, const VkDeviceSize size) {
        VkBufferCreateInfo bufferCreateInfo{};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.usage = usage;
        bufferCreateInfo.size = size;
        return bufferCreateInfo;
    }

    inline VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo(const UInt32 count,
                                                               const VkDescriptorPoolSize* poolSizes,
                                                               const UInt32 maxSets) {
        VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{};
        descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolCreateInfo.poolSizeCount = count;
        descriptorPoolCreateInfo.pPoolSizes = poolSizes;
        descriptorPoolCreateInfo.maxSets = maxSets;
        return descriptorPoolCreateInfo;
    }

    inline VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo(const std::vector<VkDescriptorPoolSize>& poolSizes,
                                                               const UInt32 maxSets) {
        VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{};
        descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolCreateInfo.poolSizeCount = static_cast<UInt32>(poolSizes.size());
        descriptorPoolCreateInfo.pPoolSizes = poolSizes.data();
        descriptorPoolCreateInfo.maxSets = maxSets;
        return descriptorPoolCreateInfo;
    }

    inline VkDescriptorPoolSize DescriptorPoolSize(const VkDescriptorType type, const UInt32 descriptorCount) {
        VkDescriptorPoolSize descriptorPoolSize;
        descriptorPoolSize.type = type;
        descriptorPoolSize.descriptorCount = descriptorCount;
        return descriptorPoolSize;
    }

    inline VkDescriptorSetLayoutBinding DescriptorSetLayoutBinding(const VkDescriptorType type,
                                                                   const VkShaderStageFlags stageFlags,
                                                                   const UInt32 binding,
                                                                   const UInt32 count) {
        VkDescriptorSetLayoutBinding setLayoutBinding{};
        setLayoutBinding.descriptorType = type;
        setLayoutBinding.stageFlags = stageFlags;
        setLayoutBinding.binding = binding;
        setLayoutBinding.descriptorCount = count;
        return setLayoutBinding;
    }

    inline VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo(const VkDescriptorSetLayoutBinding* pBindings,
                                                                         const UInt32 bindingCount) {
        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
        descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutCreateInfo.pBindings = pBindings;
        descriptorSetLayoutCreateInfo.bindingCount = bindingCount;
        return descriptorSetLayoutCreateInfo;
    }

    inline VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo(
        const std::vector<VkDescriptorSetLayoutBinding>& bindings) {
        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
        descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutCreateInfo.pBindings = bindings.data();
        descriptorSetLayoutCreateInfo.bindingCount = static_cast<UInt32>(bindings.size());
        return descriptorSetLayoutCreateInfo;
    }

    inline VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo(const VkDescriptorSetLayout* pSetLayouts,
                                                               const UInt32 setLayoutCount) {
        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
        pipelineLayoutCreateInfo.pSetLayouts = pSetLayouts;
        return pipelineLayoutCreateInfo;
    }

    inline VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo(const UInt32 setLayoutCount) {
        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
        return pipelineLayoutCreateInfo;
    }

    inline VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo(const VkDescriptorPool descriptorPool,
                                                                 const VkDescriptorSetLayout* pSetLayouts,
                                                                 const UInt32 descriptorSetCount) {
        VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{};
        descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        descriptorSetAllocateInfo.descriptorPool = descriptorPool;
        descriptorSetAllocateInfo.pSetLayouts = pSetLayouts;
        descriptorSetAllocateInfo.descriptorSetCount = descriptorSetCount;
        return descriptorSetAllocateInfo;
    }

    inline VkDescriptorImageInfo DescriptorImageInfo(const VkSampler sampler,
                                                     const VkImageView imageView,
                                                     const VkImageLayout imageLayout) {
        VkDescriptorImageInfo descriptorImageInfo;
        descriptorImageInfo.sampler = sampler;
        descriptorImageInfo.imageView = imageView;
        descriptorImageInfo.imageLayout = imageLayout;
        return descriptorImageInfo;
    }


    inline VkWriteDescriptorSet WriteDescriptorSet(const VkDescriptorSet dstSet, const VkDescriptorType type,
                                                   const UInt32 binding, const VkDescriptorBufferInfo* pBufferInfo,
                                                   const UInt32 descriptorCount) {
        VkWriteDescriptorSet writeDescriptorSet{};
        writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeDescriptorSet.dstSet = dstSet;
        writeDescriptorSet.descriptorType = type;
        writeDescriptorSet.dstBinding = binding;
        writeDescriptorSet.pBufferInfo = pBufferInfo;
        writeDescriptorSet.descriptorCount = descriptorCount;
        return writeDescriptorSet;
    }

    inline VkWriteDescriptorSet WriteDescriptorSet(const VkDescriptorSet dstSet, const VkDescriptorType type,
                                                   const UInt32 binding, const VkDescriptorImageInfo* pImageInfo,
                                                   const UInt32 descriptorCount) {
        VkWriteDescriptorSet writeDescriptorSet{};
        writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeDescriptorSet.dstSet = dstSet;
        writeDescriptorSet.descriptorType = type;
        writeDescriptorSet.dstBinding = binding;
        writeDescriptorSet.pImageInfo = pImageInfo;
        writeDescriptorSet.descriptorCount = descriptorCount;
        return writeDescriptorSet;
    }

    inline VkVertexInputBindingDescription VertexInputBindingDescription(const UInt32 binding, const UInt32 stride,
                                                                         const VkVertexInputRate inputRate) {
        VkVertexInputBindingDescription bindingDescription;
        bindingDescription.binding = binding;
        bindingDescription.stride = stride;
        bindingDescription.inputRate = inputRate;
        return bindingDescription;
    }

    inline VkVertexInputBindingDescription2EXT VertexInputBindingDescription2Ext(const UInt32 binding,
                                                                                 const UInt32 stride,
                                                                                 const VkVertexInputRate inputRate,
                                                                                 const UInt32 divisor) {
        VkVertexInputBindingDescription2EXT bindingDescription{};
        bindingDescription.sType = VK_STRUCTURE_TYPE_VERTEX_INPUT_BINDING_DESCRIPTION_2_EXT;
        bindingDescription.binding = binding;
        bindingDescription.stride = stride;
        bindingDescription.inputRate = inputRate;
        bindingDescription.divisor = divisor;
        return bindingDescription;
    }

    inline VkVertexInputAttributeDescription VertexInputAttributeDescription(const UInt32 binding,
                                                                             const UInt32 location,
                                                                             const VkFormat format,
                                                                             const UInt32 offset) {
        VkVertexInputAttributeDescription attributeDescription;
        attributeDescription.binding = binding;
        attributeDescription.location = location;
        attributeDescription.format = format;
        attributeDescription.offset = offset;
        return attributeDescription;
    }

    inline VkVertexInputAttributeDescription2EXT VertexInputAttributeDescription2Ext(const UInt32 binding,
                                                                                     const UInt32 location,
                                                                                     const VkFormat format,
                                                                                     const UInt32 offset) {
        VkVertexInputAttributeDescription2EXT attributeDescription{};
        attributeDescription.sType = VK_STRUCTURE_TYPE_VERTEX_INPUT_ATTRIBUTE_DESCRIPTION_2_EXT;
        attributeDescription.binding = binding;
        attributeDescription.location = location;
        attributeDescription.format = format;
        attributeDescription.offset = offset;
        return attributeDescription;
    }

    inline VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo() {
        VkPipelineVertexInputStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        return createInfo;
    }

    inline VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo(
        const VkPrimitiveTopology topology,
        const VkPipelineInputAssemblyStateCreateFlags flags,
        const VkBool32 primitiveRestartEnable) {
        VkPipelineInputAssemblyStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        createInfo.topology = topology;
        createInfo.flags = flags;
        createInfo.primitiveRestartEnable = primitiveRestartEnable;
        return createInfo;
    }

    inline VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo(const VkPolygonMode polygonMode,
                                                                                       const VkCullModeFlags cullMode,
                                                                                       const VkFrontFace frontFace,
                                                                                       const
                                                                                       VkPipelineRasterizationStateCreateFlags
                                                                                       flags) {
        VkPipelineRasterizationStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        createInfo.polygonMode = polygonMode;
        createInfo.cullMode = cullMode;
        createInfo.frontFace = frontFace;
        createInfo.flags = flags;
        createInfo.depthClampEnable = VK_FALSE;
        createInfo.lineWidth = 1.0f;
        return createInfo;
    }

    inline VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentState(
        const VkColorComponentFlags colorWriteMask,
        const VkBool32 blendEnable) {
        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = colorWriteMask;
        colorBlendAttachment.blendEnable = blendEnable;
        return colorBlendAttachment;
    }

    inline VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo(
        const UInt32 attachmentCount, const VkPipelineColorBlendAttachmentState* pAttachments) {
        VkPipelineColorBlendStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        createInfo.attachmentCount = attachmentCount;
        createInfo.pAttachments = pAttachments;
        return createInfo;
    }

    inline VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateCreateInfo(
        const VkBool32 depthTestEnable, const VkBool32 depthWriteEnable, const VkCompareOp depthCompareOp) {
        VkPipelineDepthStencilStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        createInfo.depthTestEnable = depthTestEnable;
        createInfo.depthWriteEnable = depthWriteEnable;
        createInfo.depthCompareOp = depthCompareOp;
        createInfo.front = createInfo.back;
        createInfo.back.compareOp = VK_COMPARE_OP_ALWAYS;
        return createInfo;
    }

    inline VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo(
        const UInt32 viewportCount, const UInt32 scissorCount, const VkPipelineViewportStateCreateFlags flags) {
        VkPipelineViewportStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        createInfo.viewportCount = viewportCount;
        createInfo.scissorCount = scissorCount;
        createInfo.flags = flags;
        return createInfo;
    }

    inline VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo(
        const VkSampleCountFlagBits rasterizationSamples, const VkPipelineMultisampleStateCreateFlags flags) {
        VkPipelineMultisampleStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        createInfo.rasterizationSamples = rasterizationSamples;
        createInfo.flags = flags;
        return createInfo;
    }

    inline VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo(
        const VkDynamicState* pDynamicStates, const UInt32 dynamicStateCount,
        const VkPipelineDynamicStateCreateFlags flags) {
        VkPipelineDynamicStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        createInfo.pDynamicStates = pDynamicStates;
        createInfo.dynamicStateCount = dynamicStateCount;
        createInfo.flags = flags;
        return createInfo;
    }

    inline VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo(
        const std::vector<VkDynamicState>& dynamicStates, const VkPipelineDynamicStateCreateFlags flags) {
        VkPipelineDynamicStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        createInfo.pDynamicStates = dynamicStates.data();
        createInfo.dynamicStateCount = static_cast<UInt32>(dynamicStates.size());
        createInfo.flags = flags;
        return createInfo;
    }

    inline VkPipelineTessellationStateCreateInfo PipelineTessellationStateCreateInfo(const UInt32 patchControlPoints) {
        VkPipelineTessellationStateCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
        createInfo.patchControlPoints = patchControlPoints;
        return createInfo;
    }

    inline VkGraphicsPipelineCreateInfo PipelineCreateInfo(const VkPipelineLayout layout, const VkRenderPass renderPass,
                                                           const VkPipelineCreateFlags flags) {
        VkGraphicsPipelineCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        createInfo.layout = layout;
        createInfo.renderPass = renderPass;
        createInfo.flags = flags;
        createInfo.basePipelineIndex = -1;
        createInfo.basePipelineHandle = VK_NULL_HANDLE;
        return createInfo;
    }

    inline VkGraphicsPipelineCreateInfo PipelineCreateInfo() {
        VkGraphicsPipelineCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        createInfo.basePipelineIndex = -1;
        createInfo.basePipelineHandle = VK_NULL_HANDLE;
        return createInfo;
    }

    inline VkComputePipelineCreateInfo ComputePipelineCreateInfo(const VkPipelineLayout layout,
                                                                 const VkPipelineCreateFlags flags) {
        VkComputePipelineCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        createInfo.layout = layout;
        createInfo.flags = flags;
        return createInfo;
    }

    inline VkPushConstantRange PushConstantRange(const VkShaderStageFlags stageFlags, const UInt32 size,
                                                 const UInt32 offset) {
        VkPushConstantRange pushConstantRange;
        pushConstantRange.stageFlags = stageFlags;
        pushConstantRange.size = size;
        pushConstantRange.offset = offset;
        return pushConstantRange;
    }

    inline VkBindSparseInfo BindSparseInfo() {
        VkBindSparseInfo bindSparseInfo{};
        bindSparseInfo.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
        return bindSparseInfo;
    }

    inline VkSpecializationMapEntry SpecializationMapEntry(const UInt32 constantId, const UInt32 offset,
                                                           const USize size) {
        VkSpecializationMapEntry specializationMapEntry;
        specializationMapEntry.constantID = constantId;
        specializationMapEntry.offset = offset;
        specializationMapEntry.size = size;
        return specializationMapEntry;
    }

    inline VkSpecializationInfo SpecializationInfo(const UInt32 mapEntryCount,
                                                   const VkSpecializationMapEntry* pMapEntries,
                                                   const USize dataSize, const void* pData) {
        VkSpecializationInfo specializationInfo;
        specializationInfo.mapEntryCount = mapEntryCount;
        specializationInfo.pMapEntries = pMapEntries;
        specializationInfo.dataSize = dataSize;
        specializationInfo.pData = pData;
        return specializationInfo;
    }
}
