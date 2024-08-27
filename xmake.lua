set_xmakever("2.9.3")

set_project("VulkanTests")

set_allowedplats("windows", "linux")

add_rules("mode.debug", "mode.release")
set_languages("cxx20")
set_optimize("fastest")

add_requires("glfw", "spdlog v1.9.0", "volk")

local outputdir = "$(mode)-$(os)-$(arch)"

rule("cp-resources")
    after_build(function (target)
        os.cp(target:name() .. "/Resources", "build/" .. outputdir .. "/" .. target:name() .. "/bin")
    end)

target("VulkanTests")
    set_kind("binary")

    set_targetdir("build/" .. outputdir .. "/VulkanTests/bin")
    set_objectdir("build/" .. outputdir .. "/VulkanTests/obj")

    add_files("Source/**.cpp")
    add_headerfiles("Include/**.hpp", "Include/**.inl")
    add_includedirs("Include")

    set_pcxxheader("Include/VulkanTests/pch.hpp")

    add_packages("glfw", "spdlog", "volk")

includes("xmake/**.lua")