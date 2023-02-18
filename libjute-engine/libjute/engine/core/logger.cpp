//
// Created by Del9fina on 11.02.2023.
//

#include <string>

#include <spdlog/logger.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <libjute/engine/core/logger.hpp>

namespace jute_engine {

struct Logger::StaticConstructor {
    StaticConstructor() {
#if LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL == LIBJUTE_ENGINE_LOGGER_LEVEL_TRACE
        const spdlog::level::level_enum LEVEL = spdlog::level::trace;
#elif LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL == LIBJUTE_ENGINE_LOGGER_LEVEL_DEBUG
        const spdlog::level::level_enum LEVEL = spdlog::level::debug;
#elif LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL == LIBJUTE_ENGINE_LOGGER_LEVEL_INFO
        const spdlog::level::level_enum LEVEL = spdlog::level::info;
#elif LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL == LIBJUTE_ENGINE_LOGGER_LEVEL_WARN
        const spdlog::level::level_enum LEVEL = spdlog::level::warn;
#elif LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL == LIBJUTE_ENGINE_LOGGER_LEVEL_ERROR
        const spdlog::level::level_enum LEVEL = spdlog::level::err;
#elif LIBJUTE_ENGINE_LOGGER_ACTIVE_LEVEL == LIBJUTE_ENGINE_LOGGER_LEVEL_CRITICAL
        const spdlog::level::level_enum LEVEL = spdlog::level::critical;
#else
        const spdlog::level::level_enum LEVEL = spdlog::level::off;
#endif
        const std::string PATTERN = "[%Y-%m-%d %T.%e] [%^%l%$] [%g:%#] [%!] %v";
        const std::string LOGGER_NAME = "jute-engine";
        const std::string FILE_NAME = "log/all.txt";

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(FILE_NAME, true);

        auto logger = spdlog::logger(LOGGER_NAME, {console_sink, file_sink});
        logger.set_level(LEVEL);
        logger.set_pattern(PATTERN);

        spdlog::set_default_logger(std::make_shared<spdlog::logger>(logger));
    }
};

// this causes above setup to run
[[maybe_unused]] Logger::StaticConstructor Logger::static_constructor;

void Logger::trace(const std::string& msg) {
    spdlog::trace(msg);
}

void Logger::debug(const std::string& msg) {
    spdlog::debug(msg);
}

void Logger::info(const std::string& msg) {
    spdlog::info(msg);
}

void Logger::warn(const std::string& msg) {
    spdlog::warn(msg);
}

void Logger::error(const std::string& msg) {
    spdlog::error(msg);
}

void Logger::critical(const std::string& msg) {
    spdlog::critical(msg);
}

}
