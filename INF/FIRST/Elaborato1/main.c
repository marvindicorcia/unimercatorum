#include <stdio.h>
#include "biblioteca.h"

int main() {
    int scelta;

    do {
        printf("\n=== Biblioteca ===\n");
        printf("1. Inserisci libro\n");
        printf("2. Modifica libro\n");
        printf("3. Ricerca libro\n");
        printf("4. Cancella libro\n");
        printf("5. Stampa catalogo\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar();

        switch (scelta) {
            case 1: inserisciLibro(); break;
            case 2: modificaLibro(); break;
            case 3: ricercaLibro(); break;
            case 4: cancellaLibro(); break;
            case 5: stampaCatalogo(); break;
            case 0: printf("Uscita...\n"); break;
            default: printf("Scelta non valida.\n");
        }
    } while (scelta != 0);

    return 0;
}
