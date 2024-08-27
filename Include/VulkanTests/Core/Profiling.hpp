// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_CORE_PROFILING_HPP
#define VK_TESTS_CORE_PROFILING_HPP

#include <unordered_map>

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

#ifdef TRACY_ENABLE
// malloc and free are used by Tracy to provide memory profiling
void* operator new(size_t count);
void operator delete(void* ptr) noexcept;

// Trace a scope
#define PROFILE_SCOPE(name) ZoneScopedN(name)

// Trace a function
#define PROFILE_FUNCTION() ZoneScoped
#else

#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()

#endif // TRACY_ENABLE

enum class PlotType : VkTests::UInt8 {
    Number,
    Percentage,
    Memory
};

#ifdef TRACY_ENABLE
namespace {
    tracy::PlotFormatType ToTracyPlotFormat(PlotType plotType);
}

#define TO_TRACY_PLOT_FORMAT(plotType) ToTracyPlotFormat(plotType)
#else
#define TO_TRACY_PLOT_FORMAT(name)
#endif // TRACY_ENABLE

// Create plots
template <typename T, PlotType Pt = PlotType::Number>
class Plot {
public:
    static void AddPlot(const char* name, T* value);
    static void Increment(const char* name, T amount);
    static void Decrement(const char* name, T amount);
    static void Reset(const char* name);

private:
    static void UpdatePlot(const char* name, T* value);

    static Plot* GetInstance();

    std::unordered_map<const char*, T> m_Plots;
};

#include <VulkanTests/Core/Profiling.inl>

#endif // VK_TESTS_CORE_PROFILING_HPP
