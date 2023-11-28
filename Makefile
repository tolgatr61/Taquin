# Nom de l'exécutable
EXECUTABLE := program

# Compilateur
CC := gcc

# Options de compilation
CFLAGS := -Wall -Wextra -g -Isrc

# Emplacements des fichiers sources, objets et exécutables
SRC_DIR := src src/model
OBJ_DIR := build/obj
BIN_DIR := build/bin

# Trouver les fichiers .c et .o
SRCS := $(wildcard $(SRC_DIR:=/*.c))
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Détection de l'environnement (Windows ou autre)
ifdef SystemRoot
	# Environnement Windows
	RMDIR := rmdir /s /q
	MKDIR := mkdir
else
	# Environnement autre (Unix/Linux)
	RMDIR := rm -rf
	MKDIR := mkdir -p
endif

# Règle par défaut
all: $(BIN_DIR)/$(EXECUTABLE)

# Lier les fichiers objets pour créer l'exécutable
$(BIN_DIR)/$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compiler les fichiers sources en fichiers objets
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Créer les répertoires obj et bin si nécessaire
$(OBJ_DIR) $(BIN_DIR):
	$(MKDIR) $(OBJ_DIR)
	$(MKDIR) $(BIN_DIR)

# Nettoyer les fichiers compilés
clean:
	$(RMDIR) build

# Exécuter le programme
run: $(BIN_DIR)/$(EXECUTABLE)
	./$<

# Empêcher les conflits avec les fichiers du même nom
.PHONY: all clean run