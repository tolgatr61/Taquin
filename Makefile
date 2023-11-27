# Nom de l'exécutable
EXECUTABLE := program

# Compilateur
CC := gcc

# Options de compilation
CFLAGS := -Wall -Wextra -g -Isrc

# Emplacements des fichiers sources, objets et exécutables
SRC_DIR := src src/model
OBJ_DIR := build\obj
BIN_DIR := build\bin

# Trouver les fichiers .c et .o
SRCS := $(wildcard $(SRC_DIR:=/*.c))
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Règle par défaut
all: $(BIN_DIR)/$(EXECUTABLE)

# Lier les fichiers objets pour créer l'exécutable
$(BIN_DIR)/$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compiler les fichiers sources en fichiers objets
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

# Créer les répertoires obj et bin si nécessaire
$(OBJ_DIR) $(BIN_DIR):
	@if not exist "$@" mkdir "$@"

# Nettoyer les fichiers compilés
clean:
	if exist build rmdir /s /q build

# Exécuter le programme
run: $(BIN_DIR)/$(EXECUTABLE)
	./$<

# Empêcher les conflits avec les fichiers du même nom
.PHONY: all clean run