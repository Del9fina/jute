/*!
 * @file logger.cpp
 * @author Del9fina
 * @date 11.02.2023
 */

#include <filesystem>
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
        const std::string PATTERN = "[%Y-%m-%d %T.%e] [%^%l%$] %v";
        const std::string LOGGER_NAME = "jute-engine";

        auto sinks_list = std::vector<spdlog::sink_ptr>();

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sinks_list.push_back(console_sink);

#ifdef LIBJUTE_ENGINE_LOG_DIR
        // TODO: set up file sink at runtime instead to allow different paths for different apps using same dll
        const auto LOG_FILE_PATH = std::filesystem::path(LIBJUTE_ENGINE_LOG_DIR) / std::filesystem::path("all.txt");
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(LOG_FILE_PATH.string(), true);
        sinks_list.push_back(file_sink);
#endif

        auto logger = spdlog::logger(LOGGER_NAME, sinks_list.begin(), sinks_list.end());
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

} // namespace jute_engine
