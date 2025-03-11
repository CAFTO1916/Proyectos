#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mapeo de dígitos a letras como en un teclado telefónico
char *teclado[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

// Función para obtener las letras correspondientes a un dígito
char *obtenerLetras(int digito) {
    if (digito < 2 || digito > 9) return "";
    return teclado[digito];
}

// Función recursiva para generar combinaciones
void generarCombinaciones(char *digitos, int indice, char *combinacion, char **resultado, int *contador) {
    if (digitos[indice] == '\0') {  
        resultado[*contador] = strdup(combinacion);
        (*contador)++;
        return;
    }

    char *letras = obtenerLetras(digitos[indice] - '0');

    for (int i = 0; letras[i] != '\0'; i++) {  
        combinacion[indice] = letras[i];  
        generarCombinaciones(digitos, indice + 1, combinacion, resultado, contador);  
    }
}

// Función principal para obtener todas las combinaciones posibles
char **obtenerCombinaciones(char *digitos, int *tamanoResultado) {
    if (*digitos == '\0') {  
        *tamanoResultado = 0;
        return NULL;
    }

    int totalCombinaciones = 1;
    for (int i = 0; digitos[i] != '\0'; i++) {  
        totalCombinaciones *= strlen(obtenerLetras(digitos[i] - '0'));  
    }

    char **resultado = (char **)malloc(totalCombinaciones * sizeof(char *));  
    char combinacion[5] = {0};  
    int contador = 0;

    generarCombinaciones(digitos, 0, combinacion, resultado, &contador);

    *tamanoResultado = contador;
    return resultado;
}

// Función para imprimir las combinaciones en el formato solicitado
void imprimirCombinaciones(char **combinaciones, int tamano) {
    printf("[");
    for (int i = 0; i < tamano; i++) {
        printf("\"%s\"", combinaciones[i]);
        if (i < tamano - 1) printf(", ");  
    }
    printf("]\n");
}

int main() {
    char digitos[5];  
    printf("Ingrese los dígitos (2-9): ");
    scanf("%s", digitos);

    int tamanoResultado;
    char **combinaciones = obtenerCombinaciones(digitos, &tamanoResultado);

    imprimirCombinaciones(combinaciones, tamanoResultado);

    for (int i = 0; i < tamanoResultado; i++) {
        free(combinaciones[i]);
    }
    free(combinaciones);

    return 0;
}
