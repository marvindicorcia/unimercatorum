# Nome dell'eseguibile finale
TARGET = arrayUtils

# Compilatore
CC = gcc

# Opzioni di compilazione ( -Wall mostra i warning )
CFLAGS = -Wall -Wextra -std=c11

# File sorgenti e oggetti
SRCS = main.c array_utils.c
OBJS = $(SRCS:.c=.o)

# Regola principale
all: $(TARGET)

# Link finale
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regola generica per compilare i .c in .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pulizia file oggetto e binario
clean:
	rm -f $(OBJS) $(TARGET)
