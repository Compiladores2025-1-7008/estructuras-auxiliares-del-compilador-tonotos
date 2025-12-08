#include "CodeGenerator.hpp"
#include <string>

std::string CodeGenerator::newTemp() {
    // Generamos "t0", "t1", "t2", ... en cada llamada.
    return "t" + std::to_string(nextTemp++);
}

std::string CodeGenerator::newLabel() {
    // Generamos "L0", "L1", "L2", ... en cada llamada.
    return "L" + std::to_string(nextLabel++);
}

void CodeGenerator::reset() {
    // Reiniciamos ambos contadores.
    nextTemp = 0;
    nextLabel = 0;
}
