#include <stdio.h>
#include <stdlib.h>

// Función para verificar si un número es primo
int esPrimo(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; ++i)
        if (num % i == 0) return 0;
    return 1;
}

// Función para generar la secuencia de Fibonacci filtrada
void generarFibonacciFiltrado(int fib[], int *tam, int K) {
    fib[0] = 0;
    fib[1] = 1;
    int idx = 2;
    int pos = 2; // posición actual en la secuencia (0-based)
    
    while (fib[idx - 1] <= K) {
        int nuevo = fib[idx - 1] + fib[idx - 2];
        // Verificamos si la posición NO es prima
        if (!esPrimo(pos)) {
            fib[idx++] = nuevo;
        }
        ++pos;
    }
    *tam = idx - 1; // El último puede ser > K, no lo incluimos
}

// Función principal
int main() {
    int dia, mes, anio;
    printf("Ingresa tu fecha de nacimiento (dia mes anio): ");
    scanf("%d %d %d", &dia, &mes, &anio);

    int K = (dia * 100) + (mes * 10) + (anio % 100);
    printf("\nValor calculado de K = %d\n", K);

    // Generamos la secuencia filtrada
    int fib[1000]; // suficiente espacio
    int tam = 0;
    generarFibonacciFiltrado(fib, &tam, K);

    printf("\nSecuencia de Fibonacci filtrada:\n");
    for (int i = 0; i < tam; ++i)
        printf("%d ", fib[i]);
    printf("\n");

    // Seleccionar términos para sumar K
    int suma = 0, contador = 0;
    printf("\nTérminos usados:\n");

    for (int i = tam - 1; i >= 0 && K > 0; --i) {
        if (fib[i] <= K) {
            printf("%d ", fib[i]);
            K -= fib[i];
            contador++;
            i--; // Saltar el consecutivo para evitar usar términos consecutivos
        }
    }

    if (K == 0) {
        printf("\n\nTotal de términos usados: %d\n", contador);
    } else {
        printf("\n\nNo se pudo formar exactamente K.\n");
    }

    return 0;
}
