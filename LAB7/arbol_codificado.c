#include <stdio.h>
#include <stdlib.h>

// Estructura básica del nodo
typedef struct Nodo {
    char caracter;
    int frecuencia;
    struct Nodo *izq, *der;
} Nodo;

// Función para crear un nodo nuevo
Nodo* crearNodo(char caracter, int frecuencia) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->caracter = caracter;
    nuevo->frecuencia = frecuencia;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// Función recursiva para imprimir el árbol en formato DOT
void imprimirNodoDOT(FILE *fp, Nodo *n, int *id) {
    if (!n) return;

    int id_actual = (*id)++;

    // Nodo hoja (carácter)
    if (!n->izq && !n->der) {
        fprintf(fp, "  node%d [label=\"'%c'\\n%d\", shape=box];\n", id_actual, n->caracter, n->frecuencia);
    } else {
        // Nodo interno (solo frecuencia)
        fprintf(fp, "  node%d [label=\"%d\"];\n", id_actual, n->frecuencia);
    }

    if (n->izq) {
        int id_izq = *id;
        imprimirNodoDOT(fp, n->izq, id);
        fprintf(fp, "  node%d -> node%d [label=\"0\"];\n", id_actual, id_izq);
    }
    if (n->der) {
        int id_der = *id;
        imprimirNodoDOT(fp, n->der, id);
        fprintf(fp, "  node%d -> node%d [label=\"1\"];\n", id_actual, id_der);
    }
}

// Función para crear el archivo .dot
void generarArchivoDOT(Nodo *raiz, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("No se pudo abrir archivo para escribir");
        return;
    }

    fprintf(fp, "digraph Huffman {\n");
    fprintf(fp, "  node [fontname=\"Arial\"];\n");

    int id = 0;
    imprimirNodoDOT(fp, raiz, &id);

    fprintf(fp, "}\n");
    fclose(fp);
}

int main() {
    // Ejemplo simple: construimos un árbol pequeño manualmente

    // Nodos hoja
    Nodo* nA = crearNodo('A', 5);
    Nodo* nB = crearNodo('B', 9);
    Nodo* nC = crearNodo('C', 12);
    Nodo* nD = crearNodo('D', 13);

    // Nodos internos
    Nodo* nI1 = crearNodo('\0', nA->frecuencia + nB->frecuencia); // frecuencia 14
    nI1->izq = nA;
    nI1->der = nB;

    Nodo* nI2 = crearNodo('\0', nC->frecuencia + nD->frecuencia); // frecuencia 25
    nI2->izq = nC;
    nI2->der = nD;

    Nodo* raiz = crearNodo('\0', nI1->frecuencia + nI2->frecuencia); // frecuencia 39
    raiz->izq = nI1;
    raiz->der = nI2;

    // Generar archivo .dot
    generarArchivoDOT(raiz, "arbol.dot");

    printf("Archivo arbol.dot generado exitosamente.\n");
    printf("Usa 'dot -Tpng arbol.dot -o arbol.png' para generar la imagen.\n");

    // Liberar memoria (opcional)
    free(nA);
    free(nB);
    free(nC);
    free(nD);
    free(nI1);
    free(nI2);
    free(raiz);

    return 0;
}
