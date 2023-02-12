//
// Created by Del9fina on 11.02.2023.
//

#pragma once

#include <memory>
#include <string>

#include <libjute/engine/core/defines.hpp>

namespace jute_engine {

// using opaque pointer pattern to hide spdlog dependency
class LIBJUTE_ENGINE_API Logger {
private:
    struct LoggerImpl;
    std::unique_ptr<LoggerImpl> logger_impl;

public:
    explicit Logger(const std::string& name);

    Logger(const std::string& name, const std::string& filename);

    void trace(const std::string& msg);
    void debug(const std::string& msg);
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);
    void critical(const std::string& msg);

    // TODO: support formatting by either waiting for compilers (gcc) to implement std::format or adding transitive dependency on fmt

    virtual ~Logger();
};

}
