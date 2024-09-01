set_xmakever("2.9.3")

set_project("VulkanTests")

set_allowedplats("windows", "mingw", "linux")

add_rules("mode.debug", "mode.release")
set_languages("cxx20")

add_repositories("pixfri https://github.com/Pixfri/xmake-repo")

add_requires("glfw", "glm", "spdlog v1.9.0", "volk", "vulkan-memory-allocator", "stb", "glslang", 
             "spirv-cross", "spirv-reflect", "spirv-tools")
add_requires("ktx")

local outputdir = "$(mode)-$(os)-$(arch)"
    
if is_plat("windows", "mingw") then
    add_defines("VK_TESTS_PLATFORM_WINDOWS")
    add_defines("WIN32_LEAN_AND_MEAN", "NOMINMAX")
elseif is_plat("linux") then
    add_defines("VK_TESTS_PLATFORM_UNIX")
end

if is_mode("debug") then
    add_defines("VK_TESTS_DEBUG")
else
    set_optimize("fastest")
end

option("tracy", {description = "Enable tracy frame debugger", default = false, type = "boolean"})

if has_config("tracy") then
    add_requires("tracy")
end

option("vk-validation-layers", {description = "Enable Vulkan validation layers (requires the Vulkan SDK to be installed on your machine)", default = is_mode("debug"), type = "boolean"})
option("vk-validation-layers-gpu-assisted", {description = "Enable GPU-assisted validation layers", default = false, type = "boolean"})
option("vk-validation-layers-best-practices", {description = "Enable best practices validation layers", default = false, type = "boolean"})
option("vk-validation-layers-synchronization", {description = "Enable synchronization validation layers", default = false, type = "boolean"})
option("vk-portability", {description = "Enable Vulkan Portability Enumeration and Portability Subset extensions", default = false, type = "boolean"})

add_defines("VK_NO_PROTOTYPES")

target("VulkanTests")
    set_kind("static")

    set_targetdir("build/" .. outputdir .. "/VulkanTests/bin")
    set_objectdir("build/" .. outputdir .. "/VulkanTests/obj")

    add_files("Source/**.cpp")
    add_headerfiles("Include/**.hpp", "Include/**.inl")
    add_includedirs("Include")
    
    add_headerfiles("ThirdParty/**.hpp", "ThirdParty/**.h")
    add_includedirs("ThirdParty")
    
    if is_plat("windows", "mingw") then
        remove_headerfiles("Include/VulkanTests/Platform/Unix/**.hpp")
        remove_files("Source/VulkanTests/Platform/Unix/**.cpp")
    elseif is_plat("linux") then
        remove_headerfiles("Include/VulkanTests/Platform/Win32/**.hpp")
        remove_files("Source/VulkanTests/Platform/Win32/**.cpp")
    end

    if not has_config("tracy") then
        remove_headerfiles("Include/VulkanTests/Core/Profiling.hpp", "Include/VulkanTests/Core/Profiling.inl")
        remove_files("Source/VulkanTests/Core/Profiling.cpp")
    end

    if has_config("vk-validation-layers") then
        add_defines("VK_TESTS_VALIDATION_LAYERS")
    end
        
    if has_config("vk-validation-layers-gpu-assisted") then
        add_defines("VK_TESTS_VALIDATION_LAYERS_GPU_ASSISTED")
    end
    
    if has_config("vk-validation-layers-best-practices") then
        add_defines("VK_TESTS_VALIDATION_LAYERS_BEST_PRACTICES")
    end
    
    if has_config("vk-validation-layers-synchronization") then
        add_defines("VK_TESTS_VALIDATION_LAYERS_SYNCHRONIZATION")
    end

    if has_config("vk-portability") then
        add_defines("VK_TESTS_PORTABILITY")
    end
    
    if has_config("tracy") then
        add_defines("TRACY_ENABLE")
        add_packages("tracy")
    end

    set_pcxxheader("Include/VulkanTests/pch.hpp")

    add_packages("glfw", "glm", "spdlog", "volk", "vulkan-memory-allocator", "glslang", "stb", "spirv-cross", 
                 "spirv-reflect", "spirv-tools")
    add_packages("ktx")

includes("xmake/**.lua")