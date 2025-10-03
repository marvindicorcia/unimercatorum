#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

// Inserisci nuovo libro
void inserisciLibro() {
    FILE *fp = fopen(FILENAME, "ab");
    if (!fp) {
        perror("Errore apertura file");
        return;
    }

    Libro l;
    printf("Titolo: ");
    fgets(l.titolo, MAX_STR, stdin);
    l.titolo[strcspn(l.titolo, "\n")] = 0;

    printf("Autore/i: ");
    fgets(l.autore, MAX_STR, stdin);
    l.autore[strcspn(l.autore, "\n")] = 0;

    printf("Editore: ");
    fgets(l.editore, MAX_STR, stdin);
    l.editore[strcspn(l.editore, "\n")] = 0;

    printf("Anno: ");
    scanf("%d", &l.anno);
    getchar();

    printf("ISBN: ");
    fgets(l.isbn, 20, stdin);
    l.isbn[strcspn(l.isbn, "\n")] = 0;

    fwrite(&l, sizeof(Libro), 1, fp);
    fclose(fp);

    printf("Libro inserito con successo!\n");
}

// Modifica libro cercando per ISBN
void modificaLibro() {
    FILE *fp = fopen(FILENAME, "r+b");
    if (!fp) {
        perror("Errore apertura file");
        return;
    }

    char isbn[20];
    printf("Inserisci ISBN del libro da modificare: ");
    fgets(isbn, 20, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    Libro l;
    int trovato = 0;

    while (fread(&l, sizeof(Libro), 1, fp)) {
        if (strcmp(l.isbn, isbn) == 0) {
            trovato = 1;
            printf("Libro trovato: %s (%s)\n", l.titolo, l.autore);

            printf("Nuovo titolo: ");
            fgets(l.titolo, MAX_STR, stdin);
            l.titolo[strcspn(l.titolo, "\n")] = 0;

            printf("Nuovo autore: ");
            fgets(l.autore, MAX_STR, stdin);
            l.autore[strcspn(l.autore, "\n")] = 0;

            printf("Nuovo editore: ");
            fgets(l.editore, MAX_STR, stdin);
            l.editore[strcspn(l.editore, "\n")] = 0;

            printf("Nuovo anno: ");
            scanf("%d", &l.anno);
            getchar();

            fseek(fp, -sizeof(Libro), SEEK_CUR);
            fwrite(&l, sizeof(Libro), 1, fp);

            printf("Libro modificato con successo!\n");
            break;
        }
    }

    if (!trovato) printf("Nessun libro trovato con ISBN %s.\n", isbn);

    fclose(fp);
}

// Ricerca per titolo autore o ISBN
void ricercaLibro() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("Errore apertura file");
        return;
    }

    int scelta;
    char query[MAX_STR];
    printf("Cerca per: 1.Titolo  2.Autore  3.ISBN\n");
    scanf("%d", &scelta);
    getchar();

    printf("Inserisci stringa di ricerca: ");
    fgets(query, MAX_STR, stdin);
    query[strcspn(query, "\n")] = 0;

    Libro l;
    int trovato = 0;

    while (fread(&l, sizeof(Libro), 1, fp)) {
        if ((scelta == 1 && strcasestr(l.titolo, query)) ||
            (scelta == 2 && strcasestr(l.autore, query)) ||
            (scelta == 3 && strcmp(l.isbn, query) == 0)) {

            printf("\n--- Libro trovato ---\n");
            printf("Titolo: %s\n", l.titolo);
            printf("Autore: %s\n", l.autore);
            printf("Editore: %s\n", l.editore);
            printf("Anno: %d\n", l.anno);
            printf("ISBN: %s\n", l.isbn);
            trovato = 1;
        }
    }

    if (!trovato) printf("Nessun libro trovato.\n");

    fclose(fp);
}

// Cancellazione libro per ISBN
void cancellaLibro() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("Errore apertura file");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        perror("Errore creazione file temporaneo");
        fclose(fp);
        return;
    }

    char isbn[20];
    printf("Inserisci ISBN del libro da cancellare: ");
    fgets(isbn, 20, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    Libro l;
    int trovato = 0;

    while (fread(&l, sizeof(Libro), 1, fp)) {
        if (strcmp(l.isbn, isbn) == 0) {
            trovato = 1;
            printf("Libro \"%s\" di %s eliminato.\n", l.titolo, l.autore);
        } else {
            fwrite(&l, sizeof(Libro), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (!trovato)
        printf("Nessun libro trovato con ISBN %s.\n", isbn);
}

// Stampa catalogo
void stampaCatalogo() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("Errore apertura file");
        return;
    }

    Libro l;
    int count = 0;

    // Definizione larghezze colonne
    const int w_id = 4;
    const int w_titolo = 30;
    const int w_autore = 20;
    const int w_editore = 15;
    const int w_anno = 6;
    const int w_isbn = 15;

    int table_width = w_id + w_titolo + w_autore + w_editore + w_anno + w_isbn + 7*3 + 1;
    // 7 colonne 8 separatori "|", + spazi di padding

    printf("\n=== Catalogo Biblioteca ===\n");

    for (int i = 0; i < table_width; i++) printf("-");
    printf("\n");

    // intestazione
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           w_id, "ID", w_titolo, "Titolo", w_autore, "Autore",
           w_editore, "Editore", w_anno, "Anno", w_isbn, "ISBN");

    // linea separatrice
    for (int i = 0; i < table_width; i++) printf("-");
    printf("\n");

    // contenuto file 
    while (fread(&l, sizeof(Libro), 1, fp)) {
        printf("| %-d | %-*s | %-*s | %-*s | %-*d | %-*s |\n",
               w_id, ++count,
               w_titolo, l.titolo,
               w_autore, l.autore,
               w_editore, l.editore,
               w_anno, l.anno,
               w_isbn, l.isbn);
    }

    if (count == 0) {
        printf("| %-*s |\n", table_width-4, "Nessun libro presente in archivio.");
    }

    // linea finale
    for (int i = 0; i < table_width; i++) printf("-");
    printf("\n");

    fclose(fp);
}
