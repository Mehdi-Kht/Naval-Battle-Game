# Variables
CC=gcc
CFLAGS=-Wall -g
OBJ=jeu.o main.o
EXE=mon_jeu

# Cible par défaut
all: $(EXE)

# Compilation
compile: $(OBJ)

jeu.o: jeu.c jeu.h
	$(CC) $(CFLAGS) -c jeu.c -o jeu.o

main.o: main.c jeu.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Link
link: compile
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

# Exécutable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

# Test
test: $(EXE)
	./$(EXE)

# HTML
html: README.md
	pandoc README.md -o README.html

# Nettoyage
clean:
	rm -f $(OBJ) $(EXE) README.html

.PHONY: all compile link test html clean