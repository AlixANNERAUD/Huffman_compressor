# Répertoires
DOCS_DIR = docs
REPORT_DIR = ../rapport

# Compilateurs
CC = gcc
DOXYGEN = doxygen
LATEX = pdflatex

# Variables pour la compilation du programme
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
TARGET = $(BIN_DIR)/main
CFLAGS = -Wall -Wpedantic -I$(INCLUDE_DIR) -I$(LIB_INCLUDE_DIR) -g -ggdb

# Variables pour la compilation des tests unitaires
TEST_DIR = tests
TEST_SOURCE_DIR = $(TEST_DIR)/src
TEST_INCLUDE_DIR = $(TEST_DIR)/include
TEST_SOURCES = $(wildcard $(TEST_SOURCE_DIR)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_SOURCE_DIR)/%.c=$(BIN_TEST_DIR)/%.o)
BIN_TEST_DIR = $(BIN_DIR)/tests
TEST_TARGET = $(BIN_TEST_DIR)/main
CFLAGS_TEST = -Wall -Wpedantic -I$(TEST_INCLUDE_DIR) -I$(LIB_INCLUDE_DIR) -lcunit

# Variables pour la compilation de la librairie
LIB_DIR = lib
LIB_SOURCE_DIR = $(LIB_DIR)/src
LIB_INCLUDE_DIR = $(LIB_DIR)/include
LIB_SOURCES = $(wildcard $(LIB_SOURCE_DIR)/*.c)
LIB_OBJECTS = $(LIB_SOURCES:$(LIB_SOURCE_DIR)/%.c=$(BIN_LIB_DIR)/%.o)
BIN_LIB_DIR = $(BIN_DIR)/lib
CFLAGS_LIB = -Wall -Wpedantic -I$(LIB_INCLUDE_DIR)

# Règle pour générer les fichiers objets à partir des fichiers source
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour générer les fichiers objets à partir des fichiers source de la librairie
$(BIN_LIB_DIR)/%.o: $(LIB_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS_LIB) -c $< -o $@ 

# Règle pour générer les fichiers objets à partir des fichiers source des tests
$(TEST_SOURCE_DIR)/%.o: $(TEST_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS_TEST) -c $< -o $@

# Règle pour générer l'exécutable
$(TARGET): $(OBJECTS) $(LIB_OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS)

# Règle pour générer l'éxécutable des tests unitaires
$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS_TEST)

# Règle pour exécuter l'exécutable
run: $(TARGET)
	./$(TARGET) 

test_compress: $(TARGET)
	./$(TARGET) c test.txt
	

# Règle pour compiler et exécuter les tests unitaires
test: $(TEST_TARGET) 
	./$(BIN_TEST_DIR)/main

# Règle pour générer les fichiers objets à partir des fichiers de test
$(BIN_TEST_DIR)/%.o: $(TEST_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS_TEST) -c $< -o $@ 

# Règle pour générer la documentation
doc:
	cd $(DOCS_DIR) && $(DOXYGEN) Doxyfile

# Règle pour générer le rapport
report:
	cd $(REPORT_DIR) && $(LATEX) rapport.tex

# Nettoie les fichiers objets et l'exécutable
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f $(LIB_OBJECTS)
	rm -f $(TEST_OBJECTS)
	rm -rf $(DOCS_DIR)/html/
	rm -rf $(DOCS_DIR)/latex/

.PHONY: all clean docs
