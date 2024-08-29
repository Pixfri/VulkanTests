// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

#include <VulkanTests/Core/Logger.hpp>

namespace VkTests {
    inline ktxTexture* LoadTexture(const std::string& filename) {
        ktxTexture* texture;
        const KTX_error_code result = ktxTexture_CreateFromNamedFile(filename.c_str(),
                                                                KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT, &texture);
        if ((result != KTX_SUCCESS) || (texture == nullptr)) {
            Log::Error("Failed to load texture: {}", filename.c_str());
            return nullptr;
        }
        
        return texture;
    }
}
