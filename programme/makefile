# Nom de l'exécutable
TARGET = bin/huffman_compressor

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Iinclude

# Répertoires
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
TEST_DIR = tests

# Liste des fichiers source
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Liste des fichiers objets générés à partir des fichiers source
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Liste des fichiers source des tests
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)

# Liste des fichiers objets générés à partir des fichiers de test
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(BIN_DIR)/%.o)

# Règle par défaut
all: $(TARGET)

# Règle pour générer l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

# Règle pour générer les fichiers objets à partir des fichiers source
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour exécuter l'exécutable
run: $(TARGET)
	./$(TARGET)

# Règle pour compiler et exécuter les tests unitaires
test: $(TEST_OBJECTS)
	$(CC) $^ -o $(BIN_DIR)/tests
	./$(BIN_DIR)/tests

# Règle pour générer les fichiers objets à partir des fichiers de test
$(BIN_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoie les fichiers objets et l'exécutable
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
