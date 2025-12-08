#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include <stdexcept>

// Definimos qué es un símbolo 
enum class Category {
    VAR,       
    CONST,     
    STRUCT,    
    FUNCTION,  
    PARAM      
};

inline constexpr Category VarCategory      = Category::VAR;
inline constexpr Category ConstCategory    = Category::CONST;
inline constexpr Category StructCategory   = Category::STRUCT;
inline constexpr Category FunctionCategory = Category::FUNCTION;
inline constexpr Category ParamCategory    = Category::PARAM;

//  info de un símbolo
struct SymbolEntry {
    std::string id;
    int typeId = -1;                
    Category category = Category::VAR;
    int dir = 0;                     
    std::vector<int> params;         // Si es función, guardamos qué tipos de argumentos espera
};

class SymbolTable {
private:
    std::unordered_map<std::string, SymbolEntry> table;

public:
    SymbolTable() = default;

    // Intenta meter un símbolo nuevo, si ya existe uno con ese nombre, regresa false 
    bool insert(const std::string& id, int typeId, Category category, int dir,
                const std::vector<int>& params = {});

    // Busca un símbolo y regresa una copia si lo encuentra
    std::optional<SymbolEntry> get(const std::string& id) const;

    // Funciones para sacar datos específicos
    int getType(const std::string& id) const;
    int getDir(const std::string& id) const;
    Category getCategory(const std::string& id) const;
    std::vector<int> getParams(const std::string& id) const;

    // Búsqueda eficiente nos da un puntero directo a la memoria 
    const SymbolEntry* lookup(const std::string& id) const {
        auto it = table.find(id);
        return (it != table.end()) ? &it->second : nullptr;
    }

    void print() const;
};
