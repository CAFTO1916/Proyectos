#include <stdio.h>

#define N 4
#define MAX_W 100

struct Item {
    int peso;
    int valor;
    char nombre[20];
};

int knapsack(int W, struct Item items[], int n, int dp[n + 1][MAX_W]) {
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            else if (items[i-1].peso <= w) {
                int incluido = items[i-1].valor + dp[i-1][w - items[i-1].peso];
                int excluido = dp[i-1][w];
                
                dp[i][w] = (incluido > excluido) ? incluido : excluido;
            }
            else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    return dp[n][W];
}

void imprimirObjetos(int dp[N + 1][MAX_W], struct Item items[], int n, int W) {
    int w = W;
    int i = n;

    printf("Objetos en la mochila:\n");

    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i-1][w]) {
            printf("- %s (Valor: %d, Peso: %d)\n", items[i-1].nombre, items[i-1].valor, items[i-1].peso);
            w -= items[i-1].peso;
        }
        i--;
    }
}

int main()
{
    struct Item items[N] = {
        {1, 1500, "Guitarra"},
        {3, 2000, "Laptop"},
        {4, 3000, "Estereo"},
        {1, 2000, "iPhone"}
    };
    int capacidad = 4;
    int dp[N + 1][MAX_W] = {0};

    int maxValor = knapsack(capacidad, items, N, dp);
    printf("Valor maximo que podemos llevar en la maleta: %d\n", maxValor);
    imprimirObjetos(dp, items, N, capacidad);
    return 0;
}
