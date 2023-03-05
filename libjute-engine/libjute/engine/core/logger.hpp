/*!
 * @file logger.hpp
 * @author Del9fina
 * @date 11.02.2023
 */

#pragma once

#include <spdlog/fmt/bundled/core.h> // TODO: switch to C++20 STD implementation when available

#include <libjute/engine/core/defines.hpp>

namespace jute_engine {

template<typename... Args>
using format_string_t = fmt::format_string<Args...>;

class LIBJUTE_ENGINE_API Logger {
private:
    struct StaticConstructor;
    [[maybe_unused]] static StaticConstructor static_constructor;

    template<typename... Args>
    static std::string format_string(format_string_t<Args...> fmt, Args&& ... args) {
        return fmt::format(fmt, std::forward<Args>(args)...);
    }

public:
    static void trace(const std::string& msg);
    static void debug(const std::string& msg);
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);
    static void critical(const std::string& msg);

    template<typename... Args>
    static void trace(format_string_t<Args...> fmt, Args&& ... args) {
        trace(format_string(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void debug(format_string_t<Args...> fmt, Args&& ... args) {
        debug(format_string(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void info(format_string_t<Args...> fmt, Args&& ... args) {
        info(format_string(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void warn(format_string_t<Args...> fmt, Args&& ... args) {
        warn(format_string(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void error(format_string_t<Args...> fmt, Args&& ... args) {
        error(format_string(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void critical(format_string_t<Args...> fmt, Args&& ... args) {
        critical(format_string(fmt, std::forward<Args>(args)...));
    }
};

} // namespace jute_engine

#define LIBJUTE_ENGINE_LOGGER_LEVEL_TRACE 0
#define LIBJUTE_ENGINE_LOGGER_LEVEL_DEBUG 1
#define LIBJUTE_ENGINE_LOGGER_LEVEL_INFO 2
#define LIBJUTE_ENGINE_LOGGER_LEVEL_WARN 3
#define LIBJUTE_ENGINE_LOGGER_LEVEL_ERROR 4
#define LIBJUTE_ENGINE_LOGGER_LEVEL_CRITICAL 5
#define LIBJUTE_ENGINE_LOGGER_LEVEL_OFF 6

#ifdef LIBJUTE_ENGINE_SET_LOGGER_LEVEL_TRACE
    #define LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL LIBJUTE_ENGINE_LOGGER_LEVEL_TRACE
#elifdef LIBJUTE_ENGINE_SET_LOGGER_LEVEL_DEBUG
    #define LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL LIBJUTE_ENGINE_LOGGER_LEVEL_DEBUG
#elifdef LIBJUTE_ENGINE_SET_LOGGER_LEVEL_INFO
    #define LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL LIBJUTE_ENGINE_LOGGER_LEVEL_INFO
#elifdef LIBJUTE_ENGINE_SET_LOGGER_LEVEL_WARN
    #define LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL LIBJUTE_ENGINE_LOGGER_LEVEL_WARN
#elifdef LIBJUTE_ENGINE_SET_LOGGER_LEVEL_ERROR
    #define LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL LIBJUTE_ENGINE_LOGGER_LEVEL_ERROR
#elifdef LIBJUTE_ENGINE_SET_LOGGER_LEVEL_CRITICAL
    #define LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL LIBJUTE_ENGINE_LOGGER_LEVEL_CRITICAL
#else
    #define LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL LIBJUTE_ENGINE_LOGGER_LEVEL_OFF
#endif

#if LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL <= LIBJUTE_ENGINE_LOGGER_LEVEL_TRACE
    #define LIBJUTE_ENGINE_LOG_TRACE(...) jute_engine::Logger::trace(__VA_ARGS__)
#else
    #define LIBJUTE_ENGINE_LOG_TRACE(...) (void)0
#endif
#if LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL <= LIBJUTE_ENGINE_LOGGER_LEVEL_DEBUG
    #define LIBJUTE_ENGINE_LOG_DEBUG(...) jute_engine::Logger::debug(__VA_ARGS__)
#else
    #define LIBJUTE_ENGINE_LOG_DEBUG(...) (void)0
#endif
#if LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL <= LIBJUTE_ENGINE_LOGGER_LEVEL_INFO
    #define LIBJUTE_ENGINE_LOG_INFO(...) jute_engine::Logger::info(__VA_ARGS__)
#else
    #define LIBJUTE_ENGINE_LOG_INFO(...) (void)0
#endif
#if LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL <= LIBJUTE_ENGINE_LOGGER_LEVEL_WARN
    #define LIBJUTE_ENGINE_LOG_WARN(...) jute_engine::Logger::warn(__VA_ARGS__)
#else
    #define LIBJUTE_ENGINE_LOG_WARN(...) (void)0
#endif
#if LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL <= LIBJUTE_ENGINE_LOGGER_LEVEL_ERROR
    #define LIBJUTE_ENGINE_LOG_ERROR(...) jute_engine::Logger::error(__VA_ARGS__)
#else
    #define LIBJUTE_ENGINE_LOG_ERROR(...) (void)0
#endif
#if LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL <= LIBJUTE_ENGINE_LOGGER_LEVEL_CRITICAL
    #define LIBJUTE_ENGINE_LOG_CRITICAL(...) jute_engine::Logger::critical(__VA_ARGS__)
#else
    #define LIBJUTE_ENGINE_LOG_CRITICAL(...) (void)0
#endif
