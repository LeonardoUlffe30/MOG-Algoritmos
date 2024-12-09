#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

// Función BFS para encontrar un camino aumentante
bool bfs(vector<vector<int>>& digrafoResidual, int fuente, int sumidero, vector<int>& anterior) {
    int nodos = digrafoResidual.size();
    vector<bool> visitado(nodos, false);
    queue<int> q;
    q.push(fuente);
    visitado[fuente] = true;
    anterior[fuente] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < nodos; v++) {
            if (!visitado[v] && digrafoResidual[u][v] > 0) { // Hay capacidad residual
                if (v == sumidero) {
                    anterior[v] = u;
                    return true; // Se encontró un camino aumentante
                }
                q.push(v);
                anterior[v] = u;
                visitado[v] = true;
            }
        }
    }
    return false; // No se encontró camino aumentante
}

// Implementación del algoritmo de Ford-Fulkerson
int fordFulkerson(vector<vector<int>>& digrafo, int fuente, int sumidero) {
    int nodos = digrafo.size();
    vector<vector<int>> digrafoResidual = digrafo; // digrafo residual
    vector<int> anterior(nodos); // anterior[i] = nodo anterior al llegar a nodo i
    int maxFlujo = 0;

    // Mientras haya un camino aumentante
    while (bfs(digrafoResidual, fuente, sumidero, anterior)) {
        int flujoCamino = INT_MAX;

        // Encontrar la capacidad mínima en el camino aumentante
        for (int v = sumidero; v != fuente; v = anterior[v]) {
            int u = anterior[v];
            flujoCamino = min(flujoCamino, digrafoResidual[u][v]);
        }

        // Actualizar capacidades residuales
        for (int v = sumidero; v != fuente; v = anterior[v]) {
            int u = anterior[v];
            digrafoResidual[u][v] -= flujoCamino;
            digrafoResidual[v][u] += flujoCamino;
        }

        // Sumar flujo al flujo máximo
        maxFlujo += flujoCamino;
    }

    return maxFlujo;
}

int main() {
    int numNodos, numAristas;
    std::cout << "Introduce el numero de nodos: ";
    std::cin >> numNodos;

    std::cout << "Introduce el numero de aristas: ";
    std::cin >> numAristas; std::cout << "\n";

    // Representación del grafo como matriz de adyacencia
    vector<vector<int>> digrafo(numNodos, vector<int>(numNodos, 0));
    for (int i = 0; i < numAristas; ++i) {
        int origen, destino, capacidad;
        std::cout << "ARISTA " << i+1 << std::endl;
        std::cout << "Introduce el nodo origen, nodo destino y capacidad: "; 
        std::cin >> origen >> destino >> capacidad;
        std::cout << "----------------------------------------------\n";
        digrafo[origen - 1][destino - 1] = capacidad;
    }

    int fuente, sumidero;
    std::cout << "Introduce el nodo fuente (source): "; std::cin >> fuente;
    std::cout << "Introduce el nodo sumidero (sink): "; std::cin >> sumidero;

    cout << "El flujo maximo es: " << fordFulkerson(digrafo, fuente - 1, sumidero - 1) << endl;

    return 0;
}
