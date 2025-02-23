#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int elemento;

typedef struct nodo {
    elemento dato;
    struct nodo *siguiente;
} Nodo;

typedef struct {
    Nodo *tope;
    int tamano;
} Pila;

void IniciarPila(Pila *p) {
    p->tope = NULL;
    p->tamano = 0;
}

void Push(Pila *p, elemento e) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("ERROR: no se puede asignar memoria\n");
        return;
    }

    nuevo->dato = e;
    nuevo->siguiente = p->tope;
    p->tope = nuevo;
    p->tamano++;
}

elemento Pop(Pila *p) {
    if (p->tope == NULL) {
        printf("ERROR: la pila está vacía\n");
        exit(1); // Salir con código de error
    }
    Nodo *temp = p->tope;
    elemento dato = temp->dato;
    p->tope = temp->siguiente;
    free(temp);
    p->tamano--;
    return dato;
}

int VaciaPila(Pila *p) {
    return (p->tope == NULL);
}

void Convertir(int numero, char *cadena) {
    sprintf(cadena, "%d", numero);
}

int main() {
    int num, j = 0;
    char cadena[100];
    char invertida[100];
    Pila pila;

    IniciarPila(&pila);

    printf("Ingrese un número: ");
    scanf("%d", &num);

    Convertir(num, cadena);
    printf("El número ingresado fue: %s\n", cadena);

    // Apilar cada carácter del número
    for (int i = 0; i < strlen(cadena); ++i) {
        Push(&pila, cadena[i]); // Guardamos caracteres, pero la pila almacena int
    }

    // Desapilar y construir el número invertido
    while (!VaciaPila(&pila)) {
        invertida[j++] = (char)Pop(&pila);
    }
    invertida[j] = '\0';

    printf("El número invertido es: %s\n", invertida);

    // Comparar el original con el invertido
    if (strcmp(cadena, invertida) == 0) {
        printf("El número es palíndromo\n");
    } else {
        printf("El número no es palíndromo\n");
    }

    return 0;
}
