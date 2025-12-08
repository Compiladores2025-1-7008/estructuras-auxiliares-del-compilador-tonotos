#pragma once
#include <string>

class CodeGenerator {
private:
    // Siguiente índice para temporal (tN)
    int nextTemp = 0;
    // Siguiente índice para etiqueta (LN).
    int nextLabel = 0;

public:
    //Genera un nuevo nombre de temporal
    std::string newTemp();

    // Genera un nuevo nombre de etiqueta
    std::string newLabel() ;

    // Reinicia el generador
    void reset() ;
};
