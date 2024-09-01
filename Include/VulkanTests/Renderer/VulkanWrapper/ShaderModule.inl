// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests {
    inline USize ShaderVariant::GetId() const {
        return m_Id;
    }

    inline void ShaderVariant::SetRuntimeArraySizes(const std::unordered_map<std::string, USize>& sizes) {
        m_RuntimeArraySizes = sizes;
    }

    inline const std::string& ShaderVariant::GetPreamble() const {
        return m_Preamble;
    }

    inline const std::vector<std::string>& ShaderVariant::GetProcesses() const {
        return m_Processes;
    }

    inline const std::unordered_map<std::string, USize>& ShaderVariant::GetRuntimeArraySizes() const {
        return m_RuntimeArraySizes;
    }

    inline USize ShaderSource::GetId() const {
        return m_Id;
    }

    inline const std::string& ShaderSource::GetFilename() const {
        return m_Filename;
    }

    inline void ShaderSource::SetSource(const std::string& source) {
        m_Source = source;
        constexpr std::hash<std::string> hasher{};
        m_Id = hasher(std::string{m_Source.cbegin(), m_Source.cend()});
    }

    inline const std::string& ShaderSource::GetSource() const {
        return m_Source;
    }

    [[nodiscard]] inline USize ShaderModule::GetId() const {
        return m_Id;
    }

    [[nodiscard]] inline VkShaderStageFlagBits ShaderModule::GetStage() const {
        return m_Stage;
    }

    [[nodiscard]] inline const std::string& ShaderModule::GetEntryPoint() const {
        return m_EntryPoint;
    }

    [[nodiscard]] inline const std::vector<ShaderResource>& ShaderModule::GetResources() const {
        return m_Resources;
    }

    [[nodiscard]] inline const std::string& ShaderModule::GetInfoLog() const {
        return m_InfoLog;
    }

    [[nodiscard]] inline const std::vector<UInt32>& ShaderModule::GetBinary() const {
        return m_Spirv;
    }

    [[nodiscard]] inline const std::string& ShaderModule::GetDebugName() const {
        return m_DebugName;
    }

    inline void ShaderModule::SetDebugName(const std::string& name) {
        m_DebugName = name;
    }
}
