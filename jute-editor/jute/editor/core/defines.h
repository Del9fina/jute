//
// Created by Del9fina on 05.02.2023.
//

#pragma once

#ifdef _WIN64
    #define J_WINDOWS
#elif defined(__linux__)
    #define J_LINUX
    #error "Linux not supported" // TODO: support linux
#else
    #error "Platform not supported"
#endif

#ifdef J_EXPORT
    #ifdef J_WINDOWS
        #define J_API __declspec(dllexport)
    #else
        #define J_API
    #endif
#else
    #ifdef J_WINDOWS
        #define J_API __declspec(dllimport)
    #else
        #define J_API
    #endif
#endif
