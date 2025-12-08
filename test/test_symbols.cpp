#include "../src/SymbolTable.hpp"
#include <gtest/gtest.h>

// Pruebas para SymbolTable.
// Verifican que se puedan insertar símbolos y luego
// recuperarlos con la información correcta.

TEST(SymbolTableTest, InsertAndRetrieveSymbol) {
    SymbolTable ts;  // tabla de símbolos vacía

    // Insertamos una variable x con:
    //  typeId = 1
    //  categoría = VarCategory
    //  dirección = 100
    ts.insert("x", 1, VarCategory, 100);

    // Buscamos el símbolo x
    auto sym = ts.get("x");

    // Confirmamos que se encontró 
    ASSERT_TRUE(sym.has_value());

    // Checamos que los datos internos coincidan.
    EXPECT_EQ(sym->typeId, 1);
    EXPECT_EQ(sym->dir, 100);
    EXPECT_EQ(sym->category, VarCategory);

    // Una variable simple no debe tener parámetros.
    EXPECT_TRUE(sym->params.empty());
}

TEST(SymbolTableTest, FunctionSymbol) {
    SymbolTable ts;

    // Insertamos una función sum con:
    //  typeId = 3
    //  categoría = FunctionCategory
    //  dirección = 200
    //  parámetros de tipo 1 y 2
    ts.insert("sum", 3, FunctionCategory, 200, {1,2});

    auto sym = ts.get("sum");

    // La función debe existir en la tabla.
    ASSERT_TRUE(sym.has_value());

    // Y debe tener exactamente dos parámetros.
    EXPECT_EQ(sym->params.size(), 2);
}
