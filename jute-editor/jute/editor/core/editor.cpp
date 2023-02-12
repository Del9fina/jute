//
// Created by Del9fina on 04.02.2023.
//

#include <jute/editor/core/editor.hpp>
#include <libjute/engine/export.hpp>

int main() {
    jute_engine::foo(); // TODO: remove
    jute_engine::Logger logger("editor");
    logger.info("I am a logger");
    logger.error("This is an error");
    return 0;
}

namespace jute_editor {

}
