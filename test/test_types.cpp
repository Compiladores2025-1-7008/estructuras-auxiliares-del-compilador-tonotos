#include "../src/TypeTable.hpp"
#include <gtest/gtest.h>

// Pruebas para TypeTable.
//  insertar tipos básicos (como int, float)
//  insertar tipos arreglo basados en esos tipos
// y luego recuperar su información correctamente.

TEST(TypeTableTest, InsertAndRetrieveBasicType) {
    TypeTable tt;

    // Insertamos int con tamaño 4.
    int id = tt.insertType("int", 4);

    // Obtenemos el tipo usando el id que regresó insertType.
    auto t = tt.getType(id);

    EXPECT_EQ(t.name, "int");
    EXPECT_EQ(t.size, 4);

    //  numElements = 1 
    //  baseTypeId = -1 
    EXPECT_EQ(t.numElements, 1);
    EXPECT_EQ(t.baseTypeId, -1);
}

TEST(TypeTableTest, InsertArrayType) {
    TypeTable tt;

    // Creamos primero float de tamaño 8
    int baseId = tt.insertType("float", 8);

    // definimos un tipo arreglo float[] de 5 elementos
    // basado en ese tipo base
    int arrId = tt.insertArrayType("float[]", baseId, 5);

    auto arrType = tt.getType(arrId);
    auto baseType = tt.getType(baseId);

    // El tamaño del arreglo debe ser
    //   size(baseType) * numElementos
    EXPECT_EQ(arrType.size, baseType.size * 5);

    // Debe almacenar correctamente el número de elementos.
    EXPECT_EQ(arrType.numElements, 5);

    // Y el baseTypeId del arreglo debe apuntar al tipo base.
    EXPECT_EQ(arrType.baseTypeId, baseId);
}
