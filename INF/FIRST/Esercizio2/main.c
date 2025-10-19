#include <stdio.h>
#include "array_utils.h"

int main() {
    int n;

    printf("Quanti elementi vuoi inserire? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Dimensione non valida.\n");
        return 1;
    }

    int arr[n];
    printf("Inserisci %d numeri interi:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int min = find_min(arr, n);
    int max = find_max(arr, n);
    double avg = find_avg(arr, n);

    printf("Minimo: %d\n", min);
    printf("Massimo: %d\n", max);
    printf("Media: %.2f\n", avg);

    return 0;
}
