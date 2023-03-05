/*!
 * @file editor.cpp
 * @author Del9fina
 * @date 04.02.2023
 */

#include <jute/editor/core/editor.hpp>
#include <libjute/engine/export.hpp>

int main() {
    jute_engine::foo(); // TODO: remove
    jute_engine::Logger::info("{}", "I am a logger");
    jute_engine::Logger::error("{}", "This is an error");
    LIBJUTE_ENGINE_LOG_INFO("{}", "I am a logger (macro)");
    LIBJUTE_ENGINE_LOG_ERROR("{}", "This is an error (macro)");
    return 0;
}

namespace jute_editor {

}
