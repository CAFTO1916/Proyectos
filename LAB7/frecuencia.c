#include <stdio.h>
#include <stdlib.h>

#define ASCII_SIZE 256

int main() {
    FILE *archivo;
    int frecuencias[ASCII_SIZE] = {0};
    int c;

    // Abrir el archivo llamado "diccionario.txt"
    archivo = fopen("diccionario.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo 'diccionario.txt'");
        return 1;
    }

    // Leer el archivo carácter por carácter y contar la frecuencia de cada símbolo
    while ((c = fgetc(archivo)) != EOF) {
        frecuencias[(unsigned char)c]++;
    }

    fclose(archivo);

    // Mostrar el "diccionario" de frecuencias
    printf("Diccionario de frecuencias de caracteres en 'diccionario.txt':\n\n");
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frecuencias[i] > 0) {
            if (i >= 32 && i <= 126)  // Si es un carácter imprimible
                printf("'%c' : %d\n", i, frecuencias[i]);
            else
                printf("'\\x%02X' : %d\n", i, frecuencias[i]); // Caracteres no imprimibles (en formato hexadecimal)
        }
    }

    return 0;
}
