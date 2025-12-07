# Estructuras Auxiliares del Compilador

Este repositorio contiene la implementación de las estructuras base para el proyecto de Compiladores 2025-1, incluyendo el manejo de Tablas de Símbolos, Tablas de Tipos y Generador de Código.

## Integrantes del Equipo

*   **Israel Rivera** - 320490747
*   **Ariadna Perez Aparicio** - 320215122
*   **Joshua Abel Hurtado Aponte** - 320176900
*   **Mauricio Flores Muñoz** - 320236589
*   **José Eduardo Cruz Campos** - 319312087

## Instrucciones de Compilación y Ejecución
### Requisitos

*   Compilador C++17 (`g++`)
*   `make` (o `mingw32-make` en Windows)

### Compilar

Para compilar el proyecto completo y los tests, simplemente ejecuta en la raíz:

```bash
make
```

El sistema detectará automáticamente tu sistema operativo y generará el ejecutable correcto:
*   **Windows:** `build/tests.exe`
*   **Linux/Mac:** `build/tests`

### Ejecutar Pruebas
Para correr las pruebas y verificar que todo funcione:

```bash
make test
```

### Limpiar
Si se quiere borrar los archivos compilados:
```bash
make clean
```
