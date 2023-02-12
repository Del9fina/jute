//
// Created by Del9fina on 11.02.2023.
//

#include <string>
#include <utility>

#ifdef LIBJUTE_ENGINE_DEBUG
    #define LIBJUTE_ENGINE_LOG_LEVEL spdlog::level::trace
#else
    #define LIBJUTE_ENGINE_LOG_LEVEL spdlog::level::err
#endif

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <libjute/engine/core/logger.hpp>

namespace jute_engine {

struct Logger::LoggerImpl {
    spdlog::logger logger;

    LoggerImpl() = delete;

    explicit LoggerImpl(spdlog::logger logger) : logger(std::move(logger)) {}
};

Logger::Logger(const std::string& name) : Logger(name, "log/all.txt") {}

Logger::Logger(const std::string& name, const std::string& filename) {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);

    auto logger = spdlog::logger(name, {console_sink, file_sink});
    logger.set_level(LIBJUTE_ENGINE_LOG_LEVEL);
    logger.set_pattern("[%Y-%m-%d %T.%e] [%^%l%$] [%n] %v");

    logger_impl = std::make_unique<LoggerImpl>(logger);
}

Logger::~Logger() {
    logger_impl = nullptr;
}

void Logger::trace(const std::string& msg) {
    logger_impl->logger.trace(msg);
}

void Logger::debug(const std::string& msg) {
    logger_impl->logger.debug(msg);
}

void Logger::info(const std::string& msg) {
    logger_impl->logger.info(msg);
}

void Logger::warn(const std::string& msg) {
    logger_impl->logger.warn(msg);
}

void Logger::error(const std::string& msg) {
    logger_impl->logger.error(msg);
}

void Logger::critical(const std::string& msg) {
    logger_impl->logger.critical(msg);
}

}
