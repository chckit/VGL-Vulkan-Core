# VGL Vulkan Core

![](https://vertostudio.com/img/vkcore_thumb.png)

This is an open source distribution of the core that runs the Verto Studio Graphics Library (VGL) engine.
The design goals are firstmost to support the general purpose OpenGL-like engine that powers Verto Studio 3D, a cross-platform 3D modeling application.
Secondly, with the first goal in mind, the engine should offer reasonable high performance.  MoktenVK is a required target for this system, so certain Vulkan features will not be exposed/utilized.

Because this core is utilized by a real-world product, it may be less elegant than typical Vulkan tutorial code
or similair open source software.  Nonetheless, the motivations for providing this code are to aid in learning how to do
somewhat complicated tasks using Vulkan and how to provide general rendering APIs to service a non-game application such as 
a 3D modeling tool.

To get an idea of how this core can be used to replace an OpenGL 3.x engine, see the example source code (ExampleRenderer.cpp & Example.cpp)

## Features

- High-level `VulkanSwapChain` class with implementation for triple-buffering, mailbox presentation modes, etc.
- `VulkanSurface` construction from native window handle implementations for windows, mac & linux.
- Built-in thread-safe memory manager & heap manager using tier-based allocation capable of providing suballocations to various resources (such as buffers, images, etc).  
- Online GLSL compilation via shaderc built in to high-level `VulkanShaderProgram` object.
- Simple SPIR-V shader reflection to determine information about common shader resources such as sampled image and uniform buffer members in built shader programs.
- Support for per-shader dynamic UBO data updating via simple `VulkanShaderProgram::updateDynamicUboState` interface.
- Grouped Buffer objects via high-level `VulkanBufferGroup` class.
- High-level Vertex array state management via `VulkanVertexArray` class.
- High-level Texture class `VulkanTexture` supporting texture initialization from image bytes (data) or uninitialized for use as a render target.
- Fast cache-based pipeline creation by mapping POD pipeline state structs to `VulkanPipeline` objects.
- Async reference-based resource wrapper `VulkanAsyncResourceHandle` faciliated by dedicated resource monitor (create-use-release-and-forget.  Resource monitor checks fences to determine when resources are no longer needed, and then destroys underlying vulkan resources only when safe).  
- Example context-like `ExampleRenderer` class which demonstrates dynamic pipeline creation, on-the-fly command buffer building, and managing renderer state.

## Dependencies

You will need to have [SDL2](https://www.libsdl.org/download-2.0.php), [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h), [linearalg](https://github.com/sgorsten/linalg) and the [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/).  
At the time of this release, the vesions I'm using are SDL2 2.0.9, stb_image 2.19, linearalg 2.1, and LunarG 1.1.73.0

Optionally, if you want to use fast (and not terrible) shader reflection, you'll want to have SPIRV-cross and enable the VGL_VULKAN_USE_SPIRV_CROSS preprocessor flag.

The memory manager implementation is compatible with latest VulkanMemoryAllocator (as of 2.3.0) and can be enabled via VGL_VULKAN_CORE_USE_VMA.

Online compilation from glsl requires linking against shaderc and enabling the VGL_VULKAN_USE_SHADERC flag.

## How to build example program

As of now, there's no separate .lib project for this core (yet).  I usually embed its source files inside the larger engine that builds it.  
An example program that shows basic core usage is contained within the example folder.

### Windows

Once you have all your dependencies, place all the headers from (vulkansdk/include/vulkan, optional shaderc, stb_image, linearalg, and SDL2) into example/include and the corresponding libs inside example/lib
Then, open the Visual Studio 2017 solution and build the project.

### Linux

Ensure you have SDL2 development libraries installed on your system.
Next, checkout & place all the single-header-file libraries from (stb_image, linearalg) into example/include
Then, cd into the example/linux directory and run 

`CMake -DVULKANSDK=/path/to/vulkansdk . && make` to build the project.

### Mac

Once you have all your dependencies, place all the headers from (vulkansdk/include/vulkan, optional shaderc, linearalg, stb_image, and SDL2) into example/include and the following frameworks/libs inside example/mac

- MoltenVK.framework
- SDL2.framework
- libMoltenVK.dylib
- libshaderc_combined.a
- libvulkan.1.dylib

Then, open the Example.xcode Project and build.

## How Can I Help?

- The core currently lacks the ability to compile GLSL 150 and auto-convert to vulkan-enabled GLSL 450.  Currently my higher-level engine implements this (on top of this core) using tons of regex which is a giant hack.  I'd like to have a more graceful solution to this.

- Rendering performant OpenGL-style thick lines WITHOUT using a geometry shader would be a nice addition.

**When submitting pull requests**, please take a look at the [Coding Style Guide](StyleGuide.md).  I am not sure if this project is at the point yet where multiple contributors will be a thing, but keep in mind that all changes must preserve compatability with existing engines that use this core.  So no major API changes or anything like that will be accepted at this point.

## License

This software is licensed under the [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0)
