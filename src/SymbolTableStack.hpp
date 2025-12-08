#pragma once
#include <deque>
#include <string>
#include "SymbolTable.hpp"

// Maneja la pila de tablas scopes.
// - Solo podemos buscar en el tope  o en la base.
class SymbolTableStack {
private:
    std::deque<SymbolTable*> stk; 

public:
    SymbolTableStack() = default;

    // Métodos para meter tablas a la pila
    void pushTop(SymbolTable* t)  { stk.push_back(t); }  // Meter scope nuevo 
    void pushBase(SymbolTable* t) { stk.push_front(t); } // Meter scope global 

    // Sacar la tabla de hasta arriba 
    SymbolTable* pop() {
        if (stk.empty()) return nullptr;
        SymbolTable* t = stk.back();
        stk.pop_back();
        return t; 
    }

    // Busca el scope más interno 
    const SymbolEntry* lookupTop(const std::string& id) const {
        if (stk.empty()) return nullptr;
        return stk.back()->lookup(id);
    }
    
    // Buscar en el scope global
    const SymbolEntry* lookupBase(const std::string& id) const {
        if (stk.empty()) return nullptr;
        return stk.front()->lookup(id);
    }

    // Getters 
    SymbolTable* top() const  { return stk.empty() ? nullptr : stk.back(); }
    SymbolTable* base() const { return stk.empty() ? nullptr : stk.front(); }

    // Cuántos niveles de anidamiento tenemos
    size_t levels() const { return stk.size(); }
};
