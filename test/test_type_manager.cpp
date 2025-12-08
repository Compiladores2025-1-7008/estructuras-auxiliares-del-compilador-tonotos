#include "../src/TypeManager.hpp"
#include <gtest/gtest.h>

// Pruebas para TypeManager.
// La idea es checar que las funciones de manejo de tipos
// regresen el tipo esperado según los parámetros.

TEST(TypeManagerTest, MaxType) {
    TypeManager tm;

    // maxType(0, 1) debe regresar 1:
    EXPECT_EQ(tm.maxType(0, 1), 1);
}

TEST(TypeManagerTest, MinType) {
    TypeManager tm;

    // minType(0, 1) debe regresar 0:
    EXPECT_EQ(tm.minType(0, 1), 0);
}

TEST(TypeManagerTest, Amplify) {
    TypeManager tm;

    // amplify(0, 0, 1) debe regresar 1:
    EXPECT_EQ(tm.amplify(0, 0, 1), 1);
}

TEST(TypeManagerTest, Reduce) {
    TypeManager tm;

    // reduce(0, 1, 0) debe regresar 0:
    // hace una reducción hacia el tipo más pequeño.
    EXPECT_EQ(tm.reduce(0, 1, 0), 0);
}
