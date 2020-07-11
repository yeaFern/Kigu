#pragma once

// Platform macros.
#ifdef _WIN32
    #ifdef _WIN64
        #define KIGU_WINDOWS
    #else
        #error "x86 Windows not supported."
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator not supported."
    #elif TARGET_OS_IPHONE == 1
        #define KIGU_IOS
        #error "IOS not supported."
    #elif TARGET_OS_MAC == 1
        #define KIGU_MACOS
        #error "MacOS not supported."
    #else
        #error "Unknown platform."
    #endif
#elif defined(__ANDROID__)
    #define KIGU_ANDROID
    #error "Android not supported."
#elif defined(__linux__)
    #define KIGU_LINUX
    #error "Linux is not supported."
#else
    #error "Unknown platform."
#endif

// Debug macros.
#ifdef DEBUG
	#define KIGU_DEBUG
#endif
