#pragma once
#include <algorithm>
#include <string>
#include "TypeTable.hpp"

// Manejador de tipos: max/min/promoción y conversión.
// Para pasar los tests del esqueleto, también soporta usar IDs como "rango" numérico directo.
class TypeManager {
public:
    // --- Versión simple (IDs ya representan jerarquía) ---
    int maxType(int t1, int t2) const { return std::max(t1, t2); }
    int minType(int t1, int t2) const { return std::min(t1, t2); }

    int amplify(int /*dir*/, int t1, int t2) const { return maxType(t1, t2); }
    int reduce (int /*dir*/, int t1, int t2) const { return minType(t1, t2); }

    // Alias en español (como en el PDF)
    int maximo(int t1, int t2) const { return maxType(t1, t2); }
    int minimo(int t1, int t2) const { return minType(t1, t2); }
    int ampliar(int dir, int t1, int t2) const { return amplify(dir, t1, t2); }
    int reducir(int dir, int t1, int t2) const { return reduce(dir, t1, t2); }

    // --- Versión basada en TypeTable (más cercana al proyecto real) ---
    static int rankFromName(const std::string& name) {
        // Jerarquía típica del PDF: void < bool < char < int < float < double
        if (name == "void")   return 0;
        if (name == "bool")   return 1;
        if (name == "char")   return 2;
        if (name == "int")    return 3;
        if (name == "float")  return 4;
        if (name == "double") return 5;
        return -1; // desconocido / no numérico
    }

    static bool areNumeric(const TypeTable& tt, int id) {
        return rankFromName(tt.getType(id).name) >= 0;
    }

    static int maxType(const TypeTable& tt, int t1, int t2) {
        const auto& a = tt.getType(t1);
        const auto& b = tt.getType(t2);

        // Tipos no-numéricos: sólo compatibles si son el mismo id
        int ra = rankFromName(a.name), rb = rankFromName(b.name);
        if (ra < 0 || rb < 0) return (t1 == t2) ? t1 : -1;

        return (ra >= rb) ? t1 : t2;
    }

    static int minType(const TypeTable& tt, int t1, int t2) {
        const auto& a = tt.getType(t1);
        const auto& b = tt.getType(t2);

        int ra = rankFromName(a.name), rb = rankFromName(b.name);
        if (ra < 0 || rb < 0) return (t1 == t2) ? t1 : -1;

        return (ra <= rb) ? t1 : t2;
    }

    static int ampliar(const TypeTable& tt, int /*dir*/, int t1, int t2) {
        return maxType(tt, t1, t2);
    }

    static int reducir(const TypeTable& tt, int /*dir*/, int t1, int t2) {
        return minType(tt, t1, t2);
    }
};
