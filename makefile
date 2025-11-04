CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

JSON_INCLUDE =
ifeq ($(shell uname -s), Darwin)
    BREW_PREFIX = $(shell command -v brew >/dev/null && brew --prefix)
    ifneq ($(BREW_PREFIX),)
        JSON_INCLUDE = -I$(BREW_PREFIX)/include
    endif
endif

SRC_DIR = src
DOMAIN_DIR = $(SRC_DIR)/domain
REPO_DIR = $(SRC_DIR)/repository
DTO_DIR = $(SRC_DIR)/dto
SERVICE_DIR = $(SRC_DIR)/service
TEST_DIR = tests
BIN_DIR = bin
UTILS_DIR = $(SRC_DIR)/utils

INCLUDES = -I$(DOMAIN_DIR) -I$(REPO_DIR) -I$(DTO_DIR) -I$(SERVICE_DIR) -I$(UTILS_DIR) $(JSON_INCLUDE)

DOMAIN_SRCS = $(DOMAIN_DIR)/Task.cpp
REPO_SRCS = $(REPO_DIR)/TaskRepository.cpp
DTO_SRCS = $(DTO_DIR)/TaskDTO.cpp
SERVICE_SRCS = $(SERVICE_DIR)/TaskService.cpp
UTILS_SRCS = $(UTILS_DIR)/DateUtils.cpp

MAIN_SRC = $(SRC_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/repositoryTest.cpp

TARGET = $(BIN_DIR)/task-cli
TEST_TARGET = $(BIN_DIR)/test

all: $(TARGET)

$(TARGET): $(MAIN_SRC) $(DOMAIN_SRCS) $(REPO_SRCS) $(DTO_SRCS) $(SERVICE_SRCS) $(UTILS_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(DOMAIN_SRCS) $(REPO_SRCS) $(DTO_SRCS) $(SERVICE_SRCS) $(UTILS_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

rebuild: clean all

.PHONY: all test clean rebuild
