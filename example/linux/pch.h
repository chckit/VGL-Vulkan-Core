#define _USE_MATH_DEFINES 
#include <math.h>
#include <string.h>
#include <vulkan.h>
#include "vglcore.h"

#ifdef MACOSX
#include <vulkan_macos.h>
#endif

#ifdef __linux
#ifdef VGL_VULKAN_CORE_USE_XCB
#include <vulkan_xcb.h>
#else
#include <vulkan_xlib.h>
#endif
#endif

#ifdef max
#undef max
#endif

//#define MAT_TYPES_VULKAN_DEPTH_RANGE 1

#ifdef VGL_VULKAN_CORE_STANDALONE
#include <iostream>
#define verr cerr
#define vout cout
#define vgl_runtime_error runtime_error

#ifdef DEBUG
#define DebugBuild() 1
#else
#define DebugBuild() 0
#endif
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4005)
#pragma warning(disable: 4305)
#endif
