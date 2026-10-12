#include <stdio.h>

#define V 6
#define INF 999999

void dijkstra(int grafo[V][V], int origem) {
    int dist[V];
    int visitado[V];

    // Inicializa as distâncias e os vértices visitados
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visitado[i] = 0;
    }

    // A distância da origem para ela mesma é zero
    dist[origem] = 0;

    // Processa os vértices
    for (int cont = 0; cont < V - 1; cont++) {
        int menor = INF;
        int u = -1;

        // Encontra o vértice não visitado
        // que possui a menor distância conhecida
        for (int i = 0; i < V; i++) {
            if (!visitado[i] && dist[i] < menor) {
                menor = dist[i];
                u = i;
            }
        }

        // Se não há mais vértices alcançáveis, encerra
        if (u == -1)
            break;

        visitado[u] = 1;

        // Atualiza as distâncias dos vizinhos de u
        for (int v = 0; v < V; v++) {
            if (!visitado[v] &&
                grafo[u][v] != 0 &&
                dist[u] + grafo[u][v] < dist[v]) {

                dist[v] = dist[u] + grafo[u][v];
            }
        }
    }

    // Exibe as menores distâncias encontradas
    printf("Vertice | Distancia da origem\n");

    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("%d       | Inalcancavel\n", i);
        else
            printf("%d       | %d\n", i, dist[i]);
    }
}

int main() {
    int grafo[V][V] = {
        {0, 10, 3, 0, 0, 0},
        {10, 0, 1, 2, 0, 0},
        {3, 1, 0, 8, 2, 0},
        {0, 2, 8, 0, 7, 0},
        {0, 0, 2, 7, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };

    // Começa pelo vértice 0
    dijkstra(grafo, 0);

    return 0;
}
