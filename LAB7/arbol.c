#include <stdio.h>
#include <stdlib.h>

#define ASCII_SIZE 256

typedef struct Nodo {
    unsigned char caracter;
    unsigned int frecuencia;
    struct Nodo *izq, *der;
} Nodo;

// Funciones para crear nodo y minHeap
Nodo* nuevoNodo(unsigned char caracter, unsigned int frecuencia) {
    Nodo* temp = (Nodo*) malloc(sizeof(Nodo));
    temp->caracter = caracter;
    temp->frecuencia = frecuencia;
    temp->izq = temp->der = NULL;
    return temp;
}

typedef struct {
    Nodo **array;
    int size;
    int capacidad;
} MinHeap;

MinHeap* crearMinHeap(int capacidad) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    minHeap->array = (Nodo**) malloc(capacidad * sizeof(Nodo*));
    minHeap->size = 0;
    minHeap->capacidad = capacidad;
    return minHeap;
}

void swapNodo(Nodo** a, Nodo** b) {
    Nodo* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int menor = idx;
    int izq = 2 * idx + 1;
    int der = 2 * idx + 2;

    if (izq < minHeap->size && minHeap->array[izq]->frecuencia < minHeap->array[menor]->frecuencia)
        menor = izq;

    if (der < minHeap->size && minHeap->array[der]->frecuencia < minHeap->array[menor]->frecuencia)
        menor = der;

    if (menor != idx) {
        swapNodo(&minHeap->array[menor], &minHeap->array[idx]);
        minHeapify(minHeap, menor);
    }
}

void insertarMinHeap(MinHeap* minHeap, Nodo* nodo) {
    int i = minHeap->size;
    minHeap->array[i] = nodo;
    minHeap->size++;

    while (i && minHeap->array[i]->frecuencia < minHeap->array[(i - 1) / 2]->frecuencia) {
        swapNodo(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Nodo* extraerMin(MinHeap* minHeap) {
    Nodo* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

MinHeap* construirMinHeap(unsigned int freq[]) {
    MinHeap* minHeap = crearMinHeap(ASCII_SIZE);
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (freq[i] > 0) {
            Nodo* nodo = nuevoNodo((unsigned char)i, freq[i]);
            insertarMinHeap(minHeap, nodo);
        }
    }
    return minHeap;
}

Nodo* construirArbolHuffman(unsigned int freq[]) {
    Nodo *izq, *der, *nuevo;
    MinHeap* minHeap = construirMinHeap(freq);

    while (minHeap->size > 1) {
        izq = extraerMin(minHeap);
        der = extraerMin(minHeap);

        nuevo = nuevoNodo('\0', izq->frecuencia + der->frecuencia);
        nuevo->izq = izq;
        nuevo->der = der;

        insertarMinHeap(minHeap, nuevo);
    }

    Nodo* raiz = extraerMin(minHeap);
    free(minHeap->array);
    free(minHeap);
    return raiz;
}

// Función que imprime en archivo DOT el nodo y sus hijos recursivamente
void imprimirNodoDOT(FILE *f, Nodo *nodo, int *id) {
    int id_actual = (*id)++;
    if (!nodo) return;

    if (!nodo->izq && !nodo->der) {
        if (nodo->caracter >= 32 && nodo->caracter <= 126)
            fprintf(f, "  node%d [label=\"'%c'\\n%d\", shape=box, style=filled, color=lightblue];\n", id_actual, nodo->caracter, nodo->frecuencia);
        else
            fprintf(f, "  node%d [label=\"\\x%02X\\n%d\", shape=box, style=filled, color=lightblue];\n", id_actual, nodo->caracter, nodo->frecuencia);
    } else {
        fprintf(f, "  node%d [label=\"%d\"];\n", id_actual, nodo->frecuencia);
    }

    if (nodo->izq) {
        int id_izq = *id;
        imprimirNodoDOT(f, nodo->izq, id);
        fprintf(f, "  node%d -> node%d [label=\"0\"];\n", id_actual, id_izq);
    }
    if (nodo->der) {
        int id_der = *id;
        imprimirNodoDOT(f, nodo->der, id);
        fprintf(f, "  node%d -> node%d [label=\"1\"];\n", id_actual, id_der);
    }
}

int main() {
    FILE *archivo = fopen("diccionario.txt", "r");
    if (!archivo) {
        perror("Error al abrir 'diccionario.txt'");
        return 1;
    }

    unsigned int frecuencias[ASCII_SIZE] = {0};
    int c;
    while ((c = fgetc(archivo)) != EOF) {
        frecuencias[(unsigned char)c]++;
    }
    fclose(archivo);

    Nodo* raiz = construirArbolHuffman(frecuencias);

    FILE *f = fopen("huffman.dot", "w");
    if (!f) {
        perror("No se pudo crear archivo 'huffman.dot'");
        return 1;
    }

    fprintf(f, "digraph Huffman {\n");
    fprintf(f, "  node [fontname=\"Arial\"];\n");

    int id = 0;
    imprimirNodoDOT(f, raiz, &id);

    fprintf(f, "}\n");
    fclose(f);

    printf("Archivo 'huffman.dot' generado.\n");
    printf("Para generar imagen usa:\n");
    printf("dot -Tpng huffman.dot -o huffman.png\n");

    return 0;
}
