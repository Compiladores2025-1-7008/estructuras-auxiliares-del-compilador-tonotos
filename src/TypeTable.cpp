#include "TypeTable.hpp"
#include "SymbolTable.hpp"
#include <iostream>

// Función para registrar un TIPO BÁSICO (ej: int, float).
// Devuelve el ID del tipo (si ya existía, devuelve el existente).
int TypeTable::insertType(const std::string& name, int size) {
    auto it = nameToId.find(name);
    // Si el tipo ya existe, devolvemos su ID y evitamos duplicados.
    if (it != nameToId.end()) return it->second; 

    TypeEntry t;
    t.id = static_cast<int>(types.size()); // El ID es el índice del vector.
    t.name = name;
    t.size = size;                        // Almacena el tamaño en bytes.
    t.numElements = 1;
    t.baseTypeId = -1;                    // No tiene tipo base.
    t.kind = TypeKind::BASIC;             // Es un tipo básico.
    t.structFields = nullptr;

    types.push_back(t);
    nameToId[name] = t.id;                // Mapea el nombre al ID para búsqueda rápida.
    return t.id;
}

// Función para registrar un TIPO ARREGLO (ej: int[10]).
// Necesita el ID del tipo base (int) y el número de elementos (10).
int TypeTable::insertArrayType(const std::string& name, int baseTypeId, int elements) {
    // ... (Validaciones: asegura que el tipo base exista y elementos > 0)

    auto it = nameToId.find(name);
    if (it != nameToId.end()) return it->second;

    const auto& base = getType(baseTypeId);

    TypeEntry t;
    t.id = static_cast<int>(types.size());
    t.name = name;
    // Calcula el tamaño total: Tamaño_Base * Num_Elementos.
    t.size = base.size * elements;       
    t.numElements = elements;
    t.baseTypeId = baseTypeId;           // Guarda el ID del tipo de los elementos.
    t.kind = TypeKind::ARRAY;            // Es un arreglo.
    t.structFields = nullptr;

    types.push_back(t);
    nameToId[name] = t.id;
    return t.id;
}

// Función para registrar un TIPO ESTRUCTURA (struct).
// `fields` es la Tabla de Símbolos interna de la estructura.
int TypeTable::insertStructType(const std::string& name, SymbolTable* fields, int sizeBytes) {
    auto it = nameToId.find(name);
    if (it != nameToId.end()) return it->second;

    TypeEntry t;
    t.id = static_cast<int>(types.size());
    t.name = name;
    t.size = sizeBytes;                  // Tamaño total de la estructura.
    t.numElements = 1;
    t.baseTypeId = -1;
    t.kind = TypeKind::STRUCT;           // Es una estructura.
    // Puntero a la tabla de símbolos que describe los campos/miembros.
    t.structFields = fields;             

    types.push_back(t);
    nameToId[name] = t.id;
    return t.id;
}

// Función de consulta: Obtiene la información (TypeEntry) dado su ID.
const TypeEntry& TypeTable::getType(int id) const {
    // ... (Validación de ID)
    return types[id];
}

// Verifica si un nombre de tipo ya está registrado.
bool TypeTable::exists(const std::string& name) const {
    return nameToId.find(name) != nameToId.end();
}

// Devuelve el ID de un tipo dado su nombre.
int TypeTable::idOf(const std::string& name) const {
    auto it = nameToId.find(name);
    // ... (Manejo de error si no se encuentra)
    return it->second;
}

// Función auxiliar para crear arreglos con nombre automático (ej: "int[5]").
int TypeTable::addArrayType(int baseTypeId, int elements) {
    // Nombre por conveniencia: "<base>[<n>]"
    const auto& base = getType(baseTypeId);
    return insertArrayType(base.name + "[" + std::to_string(elements) + "]", baseTypeId, elements);
}

// Imprime el contenido de la tabla (útil para la depuración).
void TypeTable::print() const {
    std::cout << "=== TypeTable (" << types.size() << " tipos) ===\n";
    for (const auto& t : types) {
        // Muestra ID, nombre, tamaño, tipo (BASIC/ARRAY/STRUCT) y tipo base.
        std::cout << "#" << t.id << " " << t.name
                     << " size=" << t.size
                     << " kind=" << (t.kind==TypeKind::BASIC?"BASIC":(t.kind==TypeKind::ARRAY?"ARRAY":"STRUCT"))
                     << " numElements=" << t.numElements
                     << " baseTypeId=" << t.baseTypeId
                     << "\n";
    }
}