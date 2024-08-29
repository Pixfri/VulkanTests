// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

#ifdef TRACY_ENABLE
namespace {
	tracy::PlotFormatType ToTracyPlotFormat(const PlotType plotType) {
		switch (plotType) {
		case PlotType::Number:
			return tracy::PlotFormatType::Number;
		case PlotType::Memory:
			return tracy::PlotFormatType::Memory;
		case PlotType::Percentage:
			return tracy::PlotFormatType::Percentage;
		}
		return tracy::PlotFormatType::Number;
	}
}

template <typename T, PlotType Pt>
void Plot<T, Pt>::AddPlot(const char* name, T* value) {
	auto* p = GetInstance();
	p->m_Plots[name] = value;
	UpdatePlot(name, value);
}

template <typename T, PlotType Pt>
void Plot<T, Pt>::Increment(const char* name, T amount) {
	auto* p = GetInstance();
	p->m_Plots[name] += amount;
	UpdatePlot(name, p->m_Plots[name]);
}

template <typename T, PlotType Pt>
void Plot<T, Pt>::Decrement(const char* name, T amount) {
	auto* p = GetInstance();
	p->m_Plots[name] -= amount;
	UpdatePlot(name, p->m_Plots[name]);
}

template <typename T, PlotType Pt>
void Plot<T, Pt>::Reset(const char* name) {
	auto* p = GetInstance();
	p->m_Plots[name] = T{};
	UpdatePlot(name, p->m_Plots[name]);
}

template <typename T, PlotType Pt>
void Plot<T, Pt>::UpdatePlot(const char* name, T* value) {
#ifdef TRACY_ENABLE
	TracyPlot(name, value);
	TracyPlotConfig(name, TO_TRACY_PLOT_FORMAT(Pt), true, true, 0);
#endif
}

template <typename T, PlotType Pt>
Plot<T, Pt>* Plot<T, Pt>::GetInstance() {
	static_assert(std::is_same_v<T, int64_t> || std::is_same_v<T, double> || std::is_same_v<T, float>,
	              "Plot only supports int64_t, double and float.");
	static Plot instance;
	return &instance;
}


#endif // TRACY_ENABLE
