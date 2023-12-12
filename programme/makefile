# Nom de l'exécutable
TARGET = bin/huffman_compressor

# Répertoires
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
BIN_TEST_DIR = $(BIN_DIR)/tests
TEST_DIR = tests
TEST_SOURCE_DIR = $(TEST_DIR)/src
TEST_INCLUDE_DIR = $(TEST_DIR)/include
DOCS_DIR = docs
RAPPORT_DIR = ../rapport

# Compilateur
CC = gcc
DOXYGEN = doxygen
LATEX = pdflatex

# Options de compilation
CFLAGS = -Wall -Wpedantic -I$(INCLUDE_DIR)
CFLAGS_TEST = $(CFLAGS) -I$(TEST_INCLUDE_DIR) -lcunit

# Liste des fichiers source
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Liste des fichiers objets générés à partir des fichiers source
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Liste des fichiers source des tests
TEST_SOURCES = $(wildcard $(TEST_SOURCE_DIR)/*.c)

# Liste des fichiers objets générés à partir des fichiers de test
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_SOURCE_DIR)/%.c=$(BIN_TEST_DIR)/%.o)

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
	$(CC) $^ -o $(BIN_TEST_DIR)/main -lcunit
	./$(BIN_TEST_DIR)/main

# Règle pour générer les fichiers objets à partir des fichiers de test
$(BIN_TEST_DIR)/%.o: $(TEST_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS_TEST) -c $< -o $@ 

docs:
	cd $(DOCS_DIR) && $(DOXYGEN) Doxyfile

rapport:
	cd $(RAPPORT_DIR) && $(LATEX) rapport.tex

# Nettoie les fichiers objets et l'exécutable
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f $(TEST_OBJECTS)
	rm -rf $(DOCS_DIR)/html/
	rm -rf $(DOCS_DIR)/latex/

.PHONY: all clean docs
