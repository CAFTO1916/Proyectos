#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////// FUNCIONES AUXILIARES //////////////////////

int** crearMatriz(int n) {
    int **matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matriz[i] = (int*)malloc(n * sizeof(int));
    return matriz;
}

void liberarMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

void generarMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matriz[i][j] = rand() % 10; // valores 0..9
}

void copiarMatriz(int **origen, int **destino, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            destino[i][j] = origen[i][j];
}

void sumarMatrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void restarMatrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

////////////////////// MÉTODO 1: TRADICIONAL //////////////////////

void multiplicacionTradicional(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

////////////////////// MÉTODO 2: DIVIDE AND CONQUER //////////////////////

void multiplicacionDaC(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int nuevoN = n / 2;
    int **A11 = crearMatriz(nuevoN), **A12 = crearMatriz(nuevoN);
    int **A21 = crearMatriz(nuevoN), **A22 = crearMatriz(nuevoN);
    int **B11 = crearMatriz(nuevoN), **B12 = crearMatriz(nuevoN);
    int **B21 = crearMatriz(nuevoN), **B22 = crearMatriz(nuevoN);
    int **C11 = crearMatriz(nuevoN), **C12 = crearMatriz(nuevoN);
    int **C21 = crearMatriz(nuevoN), **C22 = crearMatriz(nuevoN);
    int **temp1 = crearMatriz(nuevoN), **temp2 = crearMatriz(nuevoN);

    // Dividir matrices
    for (int i = 0; i < nuevoN; i++) {
        for (int j = 0; j < nuevoN; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + nuevoN];
            A21[i][j] = A[i + nuevoN][j];
            A22[i][j] = A[i + nuevoN][j + nuevoN];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + nuevoN];
            B21[i][j] = B[i + nuevoN][j];
            B22[i][j] = B[i + nuevoN][j + nuevoN];
        }
    }

    // C11 = A11*B11 + A12*B21
    multiplicacionDaC(A11, B11, temp1, nuevoN);
    multiplicacionDaC(A12, B21, temp2, nuevoN);
    sumarMatrices(temp1, temp2, C11, nuevoN);

    // C12 = A11*B12 + A12*B22
    multiplicacionDaC(A11, B12, temp1, nuevoN);
    multiplicacionDaC(A12, B22, temp2, nuevoN);
    sumarMatrices(temp1, temp2, C12, nuevoN);

    // C21 = A21*B11 + A22*B21
    multiplicacionDaC(A21, B11, temp1, nuevoN);
    multiplicacionDaC(A22, B21, temp2, nuevoN);
    sumarMatrices(temp1, temp2, C21, nuevoN);

    // C22 = A21*B12 + A22*B22
    multiplicacionDaC(A21, B12, temp1, nuevoN);
    multiplicacionDaC(A22, B22, temp2, nuevoN);
    sumarMatrices(temp1, temp2, C22, nuevoN);

    // Combinar resultados
    for (int i = 0; i < nuevoN; i++) {
        for (int j = 0; j < nuevoN; j++) {
            C[i][j] = C11[i][j];
            C[i][j + nuevoN] = C12[i][j];
            C[i + nuevoN][j] = C21[i][j];
            C[i + nuevoN][j + nuevoN] = C22[i][j];
        }
    }

    liberarMatriz(A11, nuevoN); liberarMatriz(A12, nuevoN);
    liberarMatriz(A21, nuevoN); liberarMatriz(A22, nuevoN);
    liberarMatriz(B11, nuevoN); liberarMatriz(B12, nuevoN);
    liberarMatriz(B21, nuevoN); liberarMatriz(B22, nuevoN);
    liberarMatriz(C11, nuevoN); liberarMatriz(C12, nuevoN);
    liberarMatriz(C21, nuevoN); liberarMatriz(C22, nuevoN);
    liberarMatriz(temp1, nuevoN); liberarMatriz(temp2, nuevoN);
}

////////////////////// MÉTODO 3: STRASSEN //////////////////////

void multiplicacionStrassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int nuevoN = n / 2;
    int **A11 = crearMatriz(nuevoN), **A12 = crearMatriz(nuevoN);
    int **A21 = crearMatriz(nuevoN), **A22 = crearMatriz(nuevoN);
    int **B11 = crearMatriz(nuevoN), **B12 = crearMatriz(nuevoN);
    int **B21 = crearMatriz(nuevoN), **B22 = crearMatriz(nuevoN);

    int **M1 = crearMatriz(nuevoN), **M2 = crearMatriz(nuevoN);
    int **M3 = crearMatriz(nuevoN), **M4 = crearMatriz(nuevoN);
    int **M5 = crearMatriz(nuevoN), **M6 = crearMatriz(nuevoN);
    int **M7 = crearMatriz(nuevoN);
    int **tempA = crearMatriz(nuevoN), **tempB = crearMatriz(nuevoN);

    for (int i = 0; i < nuevoN; i++) {
        for (int j = 0; j < nuevoN; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + nuevoN];
            A21[i][j] = A[i + nuevoN][j];
            A22[i][j] = A[i + nuevoN][j + nuevoN];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + nuevoN];
            B21[i][j] = B[i + nuevoN][j];
            B22[i][j] = B[i + nuevoN][j + nuevoN];
        }
    }

    sumarMatrices(A11, A22, tempA, nuevoN);
    sumarMatrices(B11, B22, tempB, nuevoN);
    multiplicacionStrassen(tempA, tempB, M1, nuevoN);

    sumarMatrices(A21, A22, tempA, nuevoN);
    multiplicacionStrassen(tempA, B11, M2, nuevoN);

    restarMatrices(B12, B22, tempB, nuevoN);
    multiplicacionStrassen(A11, tempB, M3, nuevoN);

    restarMatrices(B21, B11, tempB, nuevoN);
    multiplicacionStrassen(A22, tempB, M4, nuevoN);

    sumarMatrices(A11, A12, tempA, nuevoN);
    multiplicacionStrassen(tempA, B22, M5, nuevoN);

    restarMatrices(A21, A11, tempA, nuevoN);
    sumarMatrices(B11, B12, tempB, nuevoN);
    multiplicacionStrassen(tempA, tempB, M6, nuevoN);

    restarMatrices(A12, A22, tempA, nuevoN);
    sumarMatrices(B21, B22, tempB, nuevoN);
    multiplicacionStrassen(tempA, tempB, M7, nuevoN);

    for (int i = 0; i < nuevoN; i++) {
        for (int j = 0; j < nuevoN; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + nuevoN] = M3[i][j] + M5[i][j];
            C[i + nuevoN][j] = M2[i][j] + M4[i][j];
            C[i + nuevoN][j + nuevoN] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    liberarMatriz(A11, nuevoN); liberarMatriz(A12, nuevoN);
    liberarMatriz(A21, nuevoN); liberarMatriz(A22, nuevoN);
    liberarMatriz(B11, nuevoN); liberarMatriz(B12, nuevoN);
    liberarMatriz(B21, nuevoN); liberarMatriz(B22, nuevoN);
    liberarMatriz(M1, nuevoN); liberarMatriz(M2, nuevoN);
    liberarMatriz(M3, nuevoN); liberarMatriz(M4, nuevoN);
    liberarMatriz(M5, nuevoN); liberarMatriz(M6, nuevoN);
    liberarMatriz(M7, nuevoN);
    liberarMatriz(tempA, nuevoN); liberarMatriz(tempB, nuevoN);
}

////////////////////// PROGRAMA PRINCIPAL //////////////////////

int main() {
    srand(time(NULL));
    int n;
    printf("Introduce el tamaño de la matriz (potencia de 2): ");
    scanf("%d", &n);

    int **A = crearMatriz(n);
    int **B = crearMatriz(n);
    int **C = crearMatriz(n);

    generarMatriz(A, n);
    generarMatriz(B, n);

    clock_t inicio, fin;
    double tiempo;

    // Tradicional
    inicio = clock();
    multiplicacionTradicional(A, B, C, n);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo Tradicional: %.6f segundos\n", tiempo);

    // Divide and Conquer
    inicio = clock();
    multiplicacionDaC(A, B, C, n);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo Divide and Conquer: %.6f segundos\n", tiempo);

    // Strassen
    inicio = clock();
    multiplicacionStrassen(A, B, C, n);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo Strassen: %.6f segundos\n", tiempo);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}
