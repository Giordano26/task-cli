CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Diretórios
SRC_DIR = src
DOMAIN_DIR = $(SRC_DIR)/domain
REPO_DIR = $(SRC_DIR)/repository
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin

# Includes (adiciona todos os diretórios de headers)
INCLUDES = -I$(DOMAIN_DIR) -I$(REPO_DIR)

# Fontes
DOMAIN_SRCS = $(DOMAIN_DIR)/Task.cpp
REPO_SRCS = $(REPO_DIR)/TaskRepository.cpp
MAIN_SRC = $(SRC_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/repositoryTest.cpp

# Alvos
TARGET = $(BIN_DIR)/task-cli
TEST_TARGET = $(BIN_DIR)/test

# Compilar aplicação principal
all: $(TARGET)

$(TARGET): $(MAIN_SRC) $(DOMAIN_SRCS) $(REPO_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Compilar e rodar testes
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(DOMAIN_SRCS) $(REPO_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Criar diretório bin
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpeza
clean:
	rm -rf $(BIN_DIR)

# Rebuild completo
rebuild: clean all

.PHONY: all test clean rebuild