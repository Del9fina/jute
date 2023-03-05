/*!
 * @file engine.cpp
 * @author Del9fina
 * @date 04.02.2023
 */

#include <spdlog/spdlog.h>

#include <libjute/engine/core/engine.hpp>
#include <libjute/engine/core/logger.hpp>
#include <libjute/engine/core/version.hpp>

namespace jute_engine {

void foo() { // TODO: remove
    Logger::trace("{}", "test trace");
    Logger::debug("{}", "test debug");
    Logger::info("{}", "test info");
    Logger::warn("{}", "test warn");
    Logger::error("{}", "test error");
    Logger::critical("{}", "test critical");

    LIBJUTE_ENGINE_LOG_TRACE("{}", "test macro trace");
    LIBJUTE_ENGINE_LOG_DEBUG("{}", "test macro debug");
    LIBJUTE_ENGINE_LOG_INFO("{}", "test macro info");
    LIBJUTE_ENGINE_LOG_WARN("{}", "test macro warn");
    LIBJUTE_ENGINE_LOG_ERROR("{}", "test macro error");
    LIBJUTE_ENGINE_LOG_CRITICAL("{}", "test macro critical");

    LIBJUTE_ENGINE_LOG_INFO("Jute Engine version: {}", LIBJUTE_ENGINE_VERSION);
}

} // namespace jute_engine
