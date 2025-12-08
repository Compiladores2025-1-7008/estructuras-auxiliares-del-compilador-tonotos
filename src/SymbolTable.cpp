#include "SymbolTable.hpp"
#include <iostream>

// Función para guardar variables o funciones nuevas
bool SymbolTable::insert(const std::string& id, int typeId, Category category, int dir,
                         const std::vector<int>& params) {
    if (table.find(id) != table.end()) return false;
    
    SymbolEntry e;
    e.id = id;
    e.typeId = typeId;
    e.category = category;
    e.dir = dir;
    e.params = params;
    
    table[id] = std::move(e);
    return true;
}

// Busca un símbolo
std::optional<SymbolEntry> SymbolTable::get(const std::string& id) const {
    auto it = table.find(id);
    if (it == table.end()) return std::nullopt; 
    return it->second;
}

// Regresa el tipo de un símbolo
int SymbolTable::getType(const std::string& id) const {
    auto it = table.find(id);
    if (it == table.end()) throw std::out_of_range("getType: símbolo no encontrado: " + id);
    return it->second.typeId;
}

// Regresa la dirección de un símbolo
int SymbolTable::getDir(const std::string& id) const {
    auto it = table.find(id);
    if (it == table.end()) throw std::out_of_range("getDir: símbolo no encontrado: " + id);
    return it->second.dir;
}

// Regresa la categoría de un símbolo
Category SymbolTable::getCategory(const std::string& id) const {
    auto it = table.find(id);
    if (it == table.end()) throw std::out_of_range("getCategory: símbolo no encontrado: " + id);
    return it->second.category;
}

// Regresa los parámetros de una función
std::vector<int> SymbolTable::getParams(const std::string& id) const {
    auto it = table.find(id);
    if (it == table.end()) throw std::out_of_range("getParams: símbolo no encontrado: " + id);
    return it->second.params;
}

// Imprime la tabla de símbolos
void SymbolTable::print() const {
    std::cout << "=== SymbolTable (" << table.size() << " símbolos) ===\n";
    for (const auto& kv : table) {
        const auto& s = kv.second;
        std::cout << "  -> " << s.id << " | tipo: " << s.typeId
                  << " | dir: " << s.dir
                  << " | cat: " << static_cast<int>(s.category) 
                  << " | params: " << s.params.size() << "\n";
    }
}
