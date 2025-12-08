
# Makefile para compilar el proyecto + pruebas con GoogleTest
# make test para compilar todo y correr los test
# make clean borra la carpeta de build

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -I./src
BUILD_DIR := build
SRC_DIR   := src
TEST_DIR  := test


# GoogleTest
# se espera esto:
# external/googletest/googletest/include/gtest/gtest.h
# external/googletest/googletest/src/gtest-all.cc
# external/googletest/googletest/src/gtest_main.cc

GTEST_DIR := external/googletest
GTEST_INC := $(GTEST_DIR)/googletest/include
GTEST_ROOT_INC := $(GTEST_DIR)/googletest
GTEST_SRC := $(GTEST_DIR)/googletest/src

# paths de gtest cuando compilamos tests y objetos de gtest

GTEST_CXXFLAGS := -I$(GTEST_INC) -I$(GTEST_ROOT_INC)

# fuentes del proyecto 

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SRCS))

# Objetos de gtest
GTEST_OBJS := $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gtest_main.o

# Binario que corre las pruebas
TEST_BIN := $(BUILD_DIR)/tests

# Default target
.PHONY: all
all: test

# Asegurarse de que exista la carpeta de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilar los .cpp del proyecto a .o (en build/)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar los .cpp de tests a .o (en build/)
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -c $< -o $@

# Compilar los objetos de GoogleTest (sin CMake)
# gtest-all.cc espera encontrar otros headers relativos a googletest
$(BUILD_DIR)/gtest-all.o: $(GTEST_SRC)/gtest-all.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/gtest_main.o: $(GTEST_SRC)/gtest_main.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -c $< -o $@

# unir todo y generar el binario de tests
$(TEST_BIN): $(OBJS) $(TEST_OBJS) $(GTEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# tests
.PHONY: test
test: $(TEST_BIN)
	./$(TEST_BIN)

# Clean
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
