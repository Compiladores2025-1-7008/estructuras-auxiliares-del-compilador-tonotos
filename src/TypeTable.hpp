#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

class SymbolTable; // forward declaration

enum class TypeKind {
    BASIC,
    ARRAY,
    STRUCT
};

struct TypeEntry {
    int id = -1;
    std::string name;          // e.g. "int", "float[]", "struct Persona"
    int size = 0;              // bytes
    int numElements = 1;       // for arrays; 1 for non-arrays
    int baseTypeId = -1;       // for arrays; -1 otherwise
    TypeKind kind = TypeKind::BASIC;
    SymbolTable* structFields = nullptr; // for structs; nullptr otherwise
};

class TypeTable {
private:
    std::vector<TypeEntry> types;
    std::unordered_map<std::string,int> nameToId;

public:
    TypeTable() = default;

    // ---- Inserción / creación ----
    // Inserta un tipo básico (o cualquier tipo que quieras registrar explícitamente)
    int insertType(const std::string& name, int size);

    // Inserta un tipo arreglo: size = size(base) * elements
    int insertArrayType(const std::string& name, int baseTypeId, int elements);

    // Inserta un tipo struct. (El tamaño real lo podrás fijar después si tu proyecto lo requiere.)
    int insertStructType(const std::string& name, SymbolTable* fields, int sizeBytes = 0);

    // ---- Consultas ----
    const TypeEntry& getType(int id) const;

    bool exists(const std::string& name) const;
    int  idOf(const std::string& name) const; // lanza si no existe

    // Helpers para cumplir también con el PDF (aliases)
    int addBasicType(const std::string& name, int size) { return insertType(name, size); }
    int addArrayType(int baseTypeId, int elements); // nombre auto
    int addStructType(const std::string& name, SymbolTable* fields) { return insertStructType(name, fields); }

    // Getters útiles
    int getSize(int id) const { return getType(id).size; }
    int getNumElements(int id) const { return getType(id).numElements; }
    int getBaseType(int id) const { return getType(id).baseTypeId; }
    SymbolTable* getStructFields(int id) const { return getType(id).structFields; }

    // Depuración
    void print() const;
};
