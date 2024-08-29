// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in Export.hpp

#pragma once

namespace VkTests {
    template <typename... Tags>
    Tag<Tags...>::Tag() {
        m_STags = {Tag<Tags>::Id...};
    }

    template <typename... Tags>
    void Tag<Tags...>::Member() {
    }

    template <typename... Tags>
    bool Tag<Tags...>::HasTag(TagID id) {
        return std::ranges::find(m_STags, id) != m_STags.end();
    }

    template <typename... Tags>
    template <typename C>
    bool Tag<Tags...>::HasTag() {
        return HasTag(Tag<C>::Id);
    }

    template <typename... Tags>
    template <typename... C>
    bool Tag<Tags...>::HasTags() {
        std::vector<TagID> query = {Tag<C>::Id...};
        bool res = true;
        for (const auto id : query) {
            res &= HasTag(id);
        }
        return res;
    }
}
