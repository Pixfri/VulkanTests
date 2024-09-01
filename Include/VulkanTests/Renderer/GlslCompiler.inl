// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests {
    inline void GlslCompiler::SetTargetEnvironment(const glslang::EShTargetLanguage targetLanguage,
                                                   const glslang::EShTargetLanguageVersion targetLanguageVersion) {
        m_SEnvTargetLanguage = targetLanguage;
        m_SEnvTargetLanguageVersion = targetLanguageVersion;
    }

    inline void GlslCompiler::ResetTargetEnvironment() {
        m_SEnvTargetLanguage = glslang::EShTargetLanguage::EShTargetNone;
        m_SEnvTargetLanguageVersion = static_cast<glslang::EShTargetLanguageVersion>(0);
    }
}
