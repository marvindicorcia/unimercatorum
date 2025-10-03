# Nome eseguibile
TARGET = biblioteca

# Compilatore e flag
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# File sorgenti e oggetti
SRC = main.c biblioteca.c
OBJ = $(SRC:.c=.o)

# Regola principale
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compilazione file .c in .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Esegui programma (compila se serve)
run: $(TARGET)
	./$(TARGET)

# Pulizia
clean:
	rm -f $(OBJ) $(TARGET)

# Pulizia anche dei file binari della libreria
distclean: clean
	rm -f library.dat temp.dat
