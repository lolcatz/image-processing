
CXX := g++
OBJ := obj
BIN := bin

OUT_DIRS := $(BIN) $(OBJ)

SRC_DIR := src/cpp
TEST_DIR := src/test

SRC_DIRS := $(SRC_DIR) $(TEST_DIR)

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS := $(patsubst %.cpp, $(OBJ)/%.o, $(SRCS))

TARGETS := $(BIN)/main

WARNINGS := -W -Wall -Wextra -pedantic -Wshadow -Wpointer-arith \
	-Wwrite-strings -Wmissing-declarations \
	-Wredundant-decls -Winline -Wno-long-long \
	-Wconversion -Wcast-qual -Wcast-align -Weffc++

IDIRS := -I$(SRC_DIR)
CFLAGS := $(IDIRS) $(WARNINGS) -Werror -std=c++0x

.PHONY: dirs clean all

all: dirs $(TARGETS)

$(OBJ)/%.o: %.cpp
	@echo "CXX $< -> $@"
	@$(CXX) $(CFLAGS) -MMD -MP -MT "$*.d $*.o" -c $< -o $@

$(BIN)/main: $(OBJS)
	@echo "LN $^ -> $@"
	@$(CXX) $^ -o $@ $(LIBS)

clean:
	@$(RM) -r $(OUT_DIRS)

dirs:
	@mkdir -p $(BIN)
	@mkdir -p $(patsubst %, $(OBJ)/%, $(shell find $(SRC_DIRS) -type d))

