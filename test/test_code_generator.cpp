#include "CodeGenerator.hpp"
#include <gtest/gtest.h>

// Pruebas para CodeGenerator.
// Verifica que los métodos newTemp() y newLabel()
// vayan generando nombres consecutivos con el formato esperado.

TEST(CodeGeneratorTest, GenerateNewTemporary) {
    CodeGenerator cg;  // generador de código con contadores en cero

    // newTemp debe generar t0, t1, t2, ... en orden
    EXPECT_EQ(cg.newTemp(), "t0");
    EXPECT_EQ(cg.newTemp(), "t1");
    EXPECT_EQ(cg.newTemp(), "t2");
}

TEST(CodeGeneratorTest, GenerateNewLabel) {
    CodeGenerator cg;  // nuevo generador, contador de labels reiniciado

    // newLabel debe generar L0, L1, L2, ... en orden
    EXPECT_EQ(cg.newLabel(), "L0");
    EXPECT_EQ(cg.newLabel(), "L1");
    EXPECT_EQ(cg.newLabel(), "L2");
}
