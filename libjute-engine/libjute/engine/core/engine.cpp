//
// Created by Del9fina on 04.02.2023.
//

#include <iostream>
#include <memory>

#include <spdlog/spdlog.h>

#include <libjute/engine/core/engine.hpp>
#include <libjute/engine/core/logger.hpp>

namespace jute_engine {

void foo() { // TODO: remove
    spdlog::info("{}", "Test spdlog global");
    spdlog::debug("{}", "Test spdlog global debug");
    spdlog::info(0);

    auto logger = std::make_unique<Logger>("engine", "log/test_log.txt");

    logger->trace("test trace");
    logger->debug("test debug");
    logger->info("test info");
    logger->warn("test warn");
    logger->error("test error");
    logger->critical("test critical");
}

}
