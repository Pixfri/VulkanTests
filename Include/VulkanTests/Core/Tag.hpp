// Copyright (C) 2024 Jean "Pixfri" Letessier 
// This file is part of Vulkan Tests.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef VK_TESTS_CORE_TAG_HPP
#define VK_TESTS_CORE_TAG_HPP

#include <VulkanTests/pch.hpp>

namespace VkTests {
    typedef void (*TagID)();

    /**
     * @brief Tag acts as a unique identifier to categories objects.
     *
     * Tags are uniquely defined using different type names. The easiest way to create a new tag is to use an empty struct.
     * ```cpp
     * struct TagName{};
     * struct DifferentTag{};
     * Tag<TagName>::Id = Tag<TagName>::Member != Tag<DifferentTag>::Member;
     *
     * @tparam Tags A set of tags
     * ```
     */
    template <typename... Tags>
    class Tag {
    public:
        Tag();
        ~Tag() = default;

        Tag(const Tag&) = delete;
        Tag(Tag&&) = delete;

        Tag& operator=(const Tag&) = delete;
        Tag& operator=(Tag&&) = delete;

        static void Member();

        /**
         * @brief Unique TagID for a given Tag<TagName>
         */
        constexpr static TagID Id = &Member;

        static bool HasTag(TagID id);

        template <typename C>
        static bool HasTag();

        template <typename... C>
        static bool HasTags();

    private:
        static std::vector<TagID> m_STags;
    };

    template <typename... Tags>
    std::vector<TagID> Tag<Tags...>::m_STags;
}

#include <VulkanTests/Core/Tag.inl>

#endif // VK_TESTS_CORE_TAG_HPP
