#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#define MAX_STR 100
#define FILENAME "library.dat"

typedef struct {
    char titolo[MAX_STR];
    char autore[MAX_STR];
    char editore[MAX_STR];
    int anno;
    char isbn[20];
} Libro;

// Prototipi delle funzioni
void inserisciLibro();
void modificaLibro();
void ricercaLibro();
void cancellaLibro();
void stampaCatalogo();

#endif
