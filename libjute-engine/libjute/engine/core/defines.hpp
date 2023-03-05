/*!
 * @file defines.hpp
 * @author Del9fina
 * @date 05.02.2023
 */

#pragma once

#ifdef _WIN64
    #define LIBJUTE_ENGINE_WINDOWS
#elif defined(__linux__)
    #define LIBJUTE_ENGINE_LINUX
    #error "Linux not supported" // TODO: support linux
#else
    #error "Platform not supported"
#endif

#ifdef LIBJUTE_ENGINE_EXPORT
    #ifdef LIBJUTE_ENGINE_WINDOWS
        #define LIBJUTE_ENGINE_API __declspec(dllexport)
    #else
        #define LIBJUTE_ENGINE_API (void)0
    #endif
#else
    #ifdef LIBJUTE_ENGINE_WINDOWS
        #define LIBJUTE_ENGINE_API __declspec(dllimport)
    #else
        #define LIBJUTE_ENGINE_API (void)0
    #endif
#endif
