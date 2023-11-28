# Nom de l'exécutable
EXECUTABLE := program

# Compilateur
CC := gcc

# Options de compilation
CFLAGS := -Wall -Wextra -g -Isrc

# Emplacements des fichiers sources, objets et exécutables
SRC_DIR := src src/model src/controller/cli src/view/cli
OBJ_DIR := build/obj
BIN_DIR := build/bin

# Trouver les fichiers .c et .o
SRCS := $(wildcard $(SRC_DIR:=/*.c))
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Détection de l'OS et configuration des commandes
ifeq ($(OS),Windows_NT)
    MKDIR_P = if not exist "$(1)" mkdir "$(1)"
    RM_RF = if exist "$(1)" rmdir /s /q "$(1)"
else
    MKDIR_P = mkdir -p "$(1)"
    RM_RF = rm -rf "$(1)"
endif

# Règle par défaut
all: $(BIN_DIR)/$(EXECUTABLE)

# Lier les fichiers objets pour créer l'exécutable
$(BIN_DIR)/$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compiler les fichiers sources en fichiers objets
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(call MKDIR_P,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

# Créer les répertoires obj et bin si nécessaire
$(OBJ_DIR) $(BIN_DIR):
	@$(call MKDIR_P,$@)

# Nettoyer les fichiers compilés
clean:
	@$(call RM_RF,build)
	@echo "Nettoyage termine."

# Exécuter le programme
run: $(BIN_DIR)/$(EXECUTABLE)
	./$<

# Empêcher les conflits avec les fichiers du même nom
.PHONY: all clean run