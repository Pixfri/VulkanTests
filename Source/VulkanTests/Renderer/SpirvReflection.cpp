// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#include <VulkanTests/Renderer/SpirvReflection.hpp>

#include <VulkanTests/Utils/Helpers.hpp>

namespace VkTests {
    namespace {
        template <ShaderResourceType T>
        void ReadShaderResource(const spirv_cross::Compiler& compiler, const VkShaderStageFlagBits stage,
                                std::vector<ShaderResource>& resources, const ShaderVariant& variant) {
            VK_TESTS_UNUSED(compiler);
            VK_TESTS_UNUSED(stage);
            VK_TESTS_UNUSED(resources);
            VK_TESTS_UNUSED(variant);
            Log::Error("Not implemented. Read shader resource of type.");
        }

        template <spv::Decoration>
        void ReadResourceDecoration(const spirv_cross::Compiler& compiler, const spirv_cross::Resource& resource,
                                    ShaderResource& shaderResource, const ShaderVariant& variant) {
            VK_TESTS_UNUSED(compiler);
            VK_TESTS_UNUSED(resource);
            VK_TESTS_UNUSED(shaderResource);
            VK_TESTS_UNUSED(variant);
            Log::Error("Not implemented. Read resource decoration.");
        }

        template <>
        void ReadResourceDecoration<spv::DecorationLocation>(const spirv_cross::Compiler& compiler,
                                                             const spirv_cross::Resource& resource,
                                                             ShaderResource& shaderResource,
                                                             const ShaderVariant& variant) {
            VK_TESTS_UNUSED(variant);

            shaderResource.Location = compiler.get_decoration(resource.id, spv::DecorationLocation);
        }

        template <>
        void ReadResourceDecoration<spv::DecorationDescriptorSet>(const spirv_cross::Compiler& compiler,
                                                                  const spirv_cross::Resource& resource,
                                                                  ShaderResource& shaderResource,
                                                                  const ShaderVariant& variant) {
            VK_TESTS_UNUSED(variant);

            shaderResource.Set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
        }

        template <>
        void ReadResourceDecoration<spv::DecorationBinding>(const spirv_cross::Compiler& compiler,
                                                            const spirv_cross::Resource& resource,
                                                            ShaderResource& shaderResource,
                                                            const ShaderVariant& variant) {
            VK_TESTS_UNUSED(variant);

            shaderResource.Binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
        }

        template <>
        void ReadResourceDecoration<spv::DecorationInputAttachmentIndex>(const spirv_cross::Compiler& compiler,
                                                                         const spirv_cross::Resource& resource,
                                                                         ShaderResource& shaderResource,
                                                                         const ShaderVariant& variant) {
            VK_TESTS_UNUSED(variant);

            shaderResource.InputAttachmentIndex = compiler.get_decoration(resource.id,
                                                                          spv::DecorationInputAttachmentIndex);
        }

        template <>
        void ReadResourceDecoration<spv::DecorationNonWritable>(const spirv_cross::Compiler& compiler,
                                                                const spirv_cross::Resource& resource,
                                                                ShaderResource& shaderResource,
                                                                const ShaderVariant& variant) {
            VK_TESTS_UNUSED(compiler);
            VK_TESTS_UNUSED(resource);
            VK_TESTS_UNUSED(variant);

            shaderResource.Qualifiers |= ShaderResourceQualifier::NonWritable;
        }

        template <>
        void ReadResourceDecoration<spv::DecorationNonReadable>(const spirv_cross::Compiler& compiler,
                                                                const spirv_cross::Resource& resource,
                                                                ShaderResource& shaderResource,
                                                                const ShaderVariant& variant) {
            VK_TESTS_UNUSED(compiler);
            VK_TESTS_UNUSED(resource);
            VK_TESTS_UNUSED(variant);

            shaderResource.Qualifiers |= ShaderResourceQualifier::NonReadable;
        }

        void ReadResourceVecSize(const spirv_cross::Compiler& compiler, const spirv_cross::Resource& resource,
                                 ShaderResource& shaderResource, const ShaderVariant& variant) {
            VK_TESTS_UNUSED(variant);

            const auto& spirvType = compiler.get_type_from_variable(resource.id);

            shaderResource.VecSize = spirvType.vecsize;
            shaderResource.Columns = spirvType.columns;
        }

        void ReadResourceArraySize(const spirv_cross::Compiler& compiler, const spirv_cross::Resource& resource,
                                   ShaderResource& shaderResource, const ShaderVariant& variant) {
            const auto& spirvType = compiler.get_type_from_variable(resource.id);

            USize arraySize = 0;
            if (variant.GetRuntimeArraySizes().contains(resource.name)) {
                arraySize = variant.GetRuntimeArraySizes().at(resource.name);
            }

            shaderResource.ArraySize = ToUInt32(compiler.get_declared_struct_size_runtime_array(spirvType, arraySize));
        }

        void ReadResourceSize(const spirv_cross::Compiler& compiler, const spirv_cross::Resource& resource,
                              ShaderResource& shaderResource, const ShaderVariant& variant) {
            const auto& spirvType = compiler.get_type_from_variable(resource.id);

            USize arraySize{0};
            if (variant.GetRuntimeArraySizes().contains(resource.name)) {
                arraySize = variant.GetRuntimeArraySizes().at(resource.name);
            }

            shaderResource.Size = ToUInt32(compiler.get_declared_struct_size_runtime_array(spirvType, arraySize));
        }

        void ReadResourceSize(const spirv_cross::Compiler& compiler, const spirv_cross::SPIRConstant& constant,
                              ShaderResource& shaderResource, const ShaderVariant& variant) {
            VK_TESTS_UNUSED(variant);

            switch (compiler.get_type(constant.constant_type).basetype) {
            case spirv_cross::SPIRType::BaseType::Boolean:
            case spirv_cross::SPIRType::BaseType::Char:
            case spirv_cross::SPIRType::BaseType::Int:
            case spirv_cross::SPIRType::BaseType::UInt:
            case spirv_cross::SPIRType::BaseType::Float:
                shaderResource.Size = 4;
                break;
            case spirv_cross::SPIRType::BaseType::Int64:
            case spirv_cross::SPIRType::BaseType::UInt64:
            case spirv_cross::SPIRType::BaseType::Double:
                shaderResource.Size = 8;
                break;
            default:
                shaderResource.Size = 0;
                break;
            }
        }

        template <>
        void ReadShaderResource<ShaderResourceType::Input>(const spirv_cross::Compiler& compiler,
                                                           const VkShaderStageFlagBits stage,
                                                           std::vector<ShaderResource>& resources,
                                                           const ShaderVariant& variant) {
            for (auto& resource : compiler.get_shader_resources().stage_inputs) {
                ShaderResource shaderResource{};
                shaderResource.Type = ShaderResourceType::Input;
                shaderResource.Stages = stage;
                shaderResource.Name = resource.name;

                ReadResourceVecSize(compiler, resource, shaderResource, variant);
                ReadResourceArraySize(compiler, resource, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationLocation>(compiler, resource, shaderResource, variant);

                resources.push_back(shaderResource);
            }
        }

        template <>
        void ReadShaderResource<ShaderResourceType::InputAttachment>(const spirv_cross::Compiler& compiler,
                                                                     const VkShaderStageFlagBits stage,
                                                                     std::vector<ShaderResource>& resources,
                                                                     const ShaderVariant& variant) {
            VK_TESTS_UNUSED(stage);

            for (auto& subpassInput : compiler.get_shader_resources().subpass_inputs) {
                ShaderResource shaderResource{};
                shaderResource.Type = ShaderResourceType::InputAttachment;
                shaderResource.Stages = VK_SHADER_STAGE_FRAGMENT_BIT;
                shaderResource.Name = subpassInput.name;

                ReadResourceArraySize(compiler, subpassInput, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationInputAttachmentIndex>(
                    compiler, subpassInput, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationDescriptorSet>(compiler, subpassInput, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationBinding>(compiler, subpassInput, shaderResource, variant);

                resources.push_back(shaderResource);
            }
        }

        template <>
        void ReadShaderResource<ShaderResourceType::Output>(const spirv_cross::Compiler& compiler,
                                                            const VkShaderStageFlagBits stage,
                                                            std::vector<ShaderResource>& resources,
                                                            const ShaderVariant& variant) {
            for (auto& output : compiler.get_shader_resources().stage_outputs) {
                ShaderResource shaderResource{};
                shaderResource.Type = ShaderResourceType::Output;
                shaderResource.Stages = stage;
                shaderResource.Name = output.name;

                ReadResourceArraySize(compiler, output, shaderResource, variant);
                ReadResourceVecSize(compiler, output, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationLocation>(compiler, output, shaderResource, variant);

                resources.push_back(shaderResource);
            }
        }

        template <>
        void ReadShaderResource<ShaderResourceType::Image>(const spirv_cross::Compiler& compiler,
                                                           const VkShaderStageFlagBits stage,
                                                           std::vector<ShaderResource>& resources,
                                                           const ShaderVariant& variant) {
            for (auto& image : compiler.get_shader_resources().separate_images) {
                ShaderResource shaderResource{};
                shaderResource.Type = ShaderResourceType::Image;
                shaderResource.Stages = stage;
                shaderResource.Name = image.name;

                ReadResourceArraySize(compiler, image, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationDescriptorSet>(compiler, image, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationBinding>(compiler, image, shaderResource, variant);

                resources.push_back(shaderResource);
            }
        }

        template <>
        void ReadShaderResource<ShaderResourceType::ImageSampler>(const spirv_cross::Compiler& compiler,
                                                                  const VkShaderStageFlagBits stage,
                                                                  std::vector<ShaderResource>& resources,
                                                                  const ShaderVariant& variant) {
            for (auto& image : compiler.get_shader_resources().sampled_images) {
                ShaderResource shaderResource{};
                shaderResource.Type = ShaderResourceType::ImageSampler;
                shaderResource.Stages = stage;
                shaderResource.Name = image.name;

                ReadResourceArraySize(compiler, image, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationDescriptorSet>(compiler, image, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationBinding>(compiler, image, shaderResource, variant);

                resources.push_back(shaderResource);
            }
        }

        template <>
        void ReadShaderResource<ShaderResourceType::ImageStorage>(const spirv_cross::Compiler& compiler,
                                                                  const VkShaderStageFlagBits stage,
                                                                  std::vector<ShaderResource>& resources,
                                                                  const ShaderVariant& variant) {
            for (auto& image : compiler.get_shader_resources().storage_images) {
                ShaderResource shaderResource{};
                shaderResource.Type = ShaderResourceType::ImageStorage;
                shaderResource.Stages = stage;
                shaderResource.Name = image.name;

                ReadResourceArraySize(compiler, image, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationNonReadable>(compiler, image, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationNonWritable>(compiler, image, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationDescriptorSet>(compiler, image, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationBinding>(compiler, image, shaderResource, variant);

                resources.push_back(shaderResource);
            }
        }

        template <>
        void ReadShaderResource<ShaderResourceType::Sampler>(const spirv_cross::Compiler& compiler,
                                                             const VkShaderStageFlagBits stage,
                                                             std::vector<ShaderResource>& resources,
                                                             const ShaderVariant& variant) {
            for (auto& sampler : compiler.get_shader_resources().separate_samplers) {
                ShaderResource shaderResource{};
                shaderResource.Type = ShaderResourceType::Sampler;
                shaderResource.Stages = stage;
                shaderResource.Name = sampler.name;

                ReadResourceArraySize(compiler, sampler, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationDescriptorSet>(compiler, sampler, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationBinding>(compiler, sampler, shaderResource, variant);

                resources.push_back(shaderResource);
            }
        }

        template <>
        void ReadShaderResource<ShaderResourceType::BufferUniform>(const spirv_cross::Compiler& compiler,
                                                                   const VkShaderStageFlagBits stage,
                                                                   std::vector<ShaderResource>& resources,
                                                                   const ShaderVariant& variant) {
            for (auto& buffer : compiler.get_shader_resources().uniform_buffers) {
                ShaderResource shaderResource{};
                shaderResource.Type = ShaderResourceType::BufferUniform;
                shaderResource.Stages = stage;
                shaderResource.Name = buffer.name;

                ReadResourceSize(compiler, buffer, shaderResource, variant);
                ReadResourceArraySize(compiler, buffer, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationDescriptorSet>(compiler, buffer, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationBinding>(compiler, buffer, shaderResource, variant);

                resources.push_back(shaderResource);
            }
        }

        template <>
        void ReadShaderResource<ShaderResourceType::BufferStorage>(const spirv_cross::Compiler& compiler,
                                                                   const VkShaderStageFlagBits stage,
                                                                   std::vector<ShaderResource>& resources,
                                                                   const ShaderVariant& variant) {
            for (auto& buffer : compiler.get_shader_resources().storage_buffers) {
                ShaderResource shaderResource{};
                shaderResource.Type = ShaderResourceType::BufferStorage;
                shaderResource.Stages = stage;
                shaderResource.Name = buffer.name;

                ReadResourceSize(compiler, buffer, shaderResource, variant);
                ReadResourceArraySize(compiler, buffer, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationNonReadable>(compiler, buffer, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationNonWritable>(compiler, buffer, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationDescriptorSet>(compiler, buffer, shaderResource, variant);
                ReadResourceDecoration<spv::DecorationBinding>(compiler, buffer, shaderResource, variant);

                resources.push_back(shaderResource);
            }
        }
    }

    bool SpirvReflection::ReflectShaderResources(const VkShaderStageFlagBits stage, const std::vector<UInt32>& spirv,
                                                 std::vector<ShaderResource>& resources, const ShaderVariant& variant) {
        spirv_cross::CompilerGLSL compiler{spirv};

        auto opts = compiler.get_common_options();
        opts.enable_420pack_extension = true;

        compiler.set_common_options(opts);

        ParseShaderResources(compiler, stage, resources, variant);
        ParsePushConstants(compiler, stage, resources, variant);
        ParseSpecializationConstants(compiler, stage, resources, variant);

        return true;
    }

    void SpirvReflection::ParseShaderResources(const spirv_cross::Compiler& compiler, const VkShaderStageFlagBits stage,
                                               std::vector<ShaderResource>& resources, const ShaderVariant& variant) {
        ReadShaderResource<ShaderResourceType::Input>(compiler, stage, resources, variant);
        ReadShaderResource<ShaderResourceType::InputAttachment>(compiler, stage, resources, variant);
        ReadShaderResource<ShaderResourceType::Output>(compiler, stage, resources, variant);
        ReadShaderResource<ShaderResourceType::Image>(compiler, stage, resources, variant);
        ReadShaderResource<ShaderResourceType::ImageSampler>(compiler, stage, resources, variant);
        ReadShaderResource<ShaderResourceType::ImageStorage>(compiler, stage, resources, variant);
        ReadShaderResource<ShaderResourceType::Sampler>(compiler, stage, resources, variant);
        ReadShaderResource<ShaderResourceType::BufferUniform>(compiler, stage, resources, variant);
        ReadShaderResource<ShaderResourceType::BufferStorage>(compiler, stage, resources, variant);
    }

    void SpirvReflection::ParsePushConstants(const spirv_cross::Compiler& compiler, const VkShaderStageFlagBits stage,
                                             std::vector<ShaderResource>& resources, const ShaderVariant& variant) {
        for (auto& resource : compiler.get_shader_resources().push_constant_buffers) {
            const auto& spirvType = compiler.get_type_from_variable(resource.id);

            UInt32 offset = std::numeric_limits<UInt32>::max();

            for (auto i = 0U; i < spirvType.member_types.size(); ++i) {
                auto memOffset = compiler.get_member_decoration(spirvType.self, i, spv::DecorationOffset);

                offset = std::min(offset, memOffset);
            }

            ShaderResource shaderResource{};
            shaderResource.Type = ShaderResourceType::PushConstant;
            shaderResource.Stages = stage;
            shaderResource.Name = resource.name;
            shaderResource.Offset = offset;

            ReadResourceSize(compiler, resource, shaderResource, variant);

            shaderResource.Size -= shaderResource.Offset;

            resources.push_back(shaderResource);
        }
    }

    void SpirvReflection::ParseSpecializationConstants(const spirv_cross::Compiler& compiler,
                                                       const VkShaderStageFlagBits stage,
                                                       std::vector<ShaderResource>& resources,
                                                       const ShaderVariant& variant) {
        for (auto& constant : compiler.get_specialization_constants()) {
            auto& spirvValue = compiler.get_constant(constant.id);

            ShaderResource shaderResource{};
            shaderResource.Type = ShaderResourceType::SpecializationConstant;
            shaderResource.Stages = stage;
            shaderResource.Name = compiler.get_name(constant.id);
            shaderResource.Offset = 0;
            shaderResource.ConstantId = constant.constant_id;

            ReadResourceSize(compiler, spirvValue, shaderResource, variant);

            resources.push_back(shaderResource);
        }
    }

}
