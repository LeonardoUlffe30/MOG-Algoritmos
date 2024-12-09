#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>

using namespace std;

// Calcular el costo total de un recorrido
int calcularCoste(const vector<int>& recorrido, const vector<vector<int>>& distancias) {
    int coste = 0;
    for (int i = 0; i < recorrido.size() - 1; ++i) {
        coste += distancias[recorrido[i]][recorrido[i + 1]];
    }
    coste += distancias[recorrido.back()][recorrido.front()]; // Volver a la ciudad inicial
    return coste;
}

// Búsqueda tabú para el problema del agente viajero
vector<int> busquedaTabu(int n, const vector<vector<int>>& distancias, int iteraciones, int tamTabu) {
    vector<int> mejorRecorrido(n);
    iota(mejorRecorrido.begin(), mejorRecorrido.end(), 0); // Recorrido inicial: { 0, 1, 2, ..., n-1}
    // Partimos de una cualquiera, escogemos partir inicialmente del recorrido que va visitando las ciudades en orden 1-2-3-4...

    int mejorCoste = calcularCoste(mejorRecorrido, distancias);

    vector<int> actualRecorrido = mejorRecorrido;
    int actualCosto = mejorCoste;
    cout << "Coste inicial: " << mejorCoste << "\n";
    vector<pair<int, int>> listaTabu; // Lista tabú para intercambios de ciudades

    for (int iter = 0; iter < iteraciones; ++iter) {
        vector<int> mejorVecino = actualRecorrido;
        int mejorVecinoCoste = INT_MAX;
        int mejorI, mejorJ;
        bool seleccionado = false;
        // Explorar vecinos intercambiando dos ciudades
        for (int i = 0; i < n; ++i) {
            int j = i + 1;
            if (j == n) {
                j = 0;
            }
            
            // Crear un nuevo vecino intercambiando i y j
            vector<int> vecino = actualRecorrido;
            swap(vecino[i], vecino[j]);
            int vecinoCoste = calcularCoste(vecino, distancias);

            // Condición de aspiración: permitir intercambio tabú si mejora globalmente
            if (vecinoCoste < mejorCoste && !seleccionado) {
                mejorVecino = vecino;
                mejorVecinoCoste = vecinoCoste;
                mejorI = i;
                mejorJ = j;
                seleccionado = true;
                continue;
            }

            // Verificar si el intercambio está en la lista tabú
            if (find(listaTabu.begin(), listaTabu.end(), make_pair(i, j)) != listaTabu.end() ||
                find(listaTabu.begin(), listaTabu.end(), make_pair(j, i)) != listaTabu.end()) {
                continue;
            }

            // Verificar si es el mejor vecino encontrado
            if (vecinoCoste < mejorVecinoCoste) {
                mejorVecino = vecino;
                mejorVecinoCoste = vecinoCoste;
                mejorI = i;
                mejorJ = j;
            }
        }

        // Actualizar la solución actual
        actualRecorrido = mejorVecino;
        actualCosto = mejorVecinoCoste;

        // Actualizar la lista tabú
        if (listaTabu.size() >= tamTabu) {
            listaTabu.erase(listaTabu.begin());
        }
        listaTabu.push_back({ mejorI, mejorJ }); // Guardar los índices intercambiados correctamente

        // Actualizar la mejor solución global
        if (actualCosto < mejorCoste) {
            mejorRecorrido = actualRecorrido;
            mejorCoste = actualCosto;
        }

        // Mostrar el progreso
        cout << "Iteracion " << iter + 1 << ": Mejor coste de los posibles vecinos = " << mejorVecinoCoste << endl;
    }

    return mejorRecorrido;
}

int main() {
    int n; // Número de ciudades
    int iteraciones; // Número de iteraciones
    int tamTabu; // Tamaño de la lista tabú

    cout << "Introduce el numero de ciudades, el de iteraciones y el tamanyo de la lista tabu: ";
    cin >> n >> iteraciones >> tamTabu;
    vector<vector<int>> distancias(n);
    for (int a = 0; a < n; a++) {
        cout << "Introduce los datos de la fila " << a + 1 << ": ";
        for (int b = 0; b < n; b++) {
            int dato;
            cin >> dato;
            distancias[a].push_back(dato);
            cout << "Se ha introducido el dato: " << dato << " en la fila " << a << " columna " << b << endl;
        }
    }

    cout << "Matriz de distancias:\n";
    for (const auto& fila : distancias) {
        for (int d : fila) {
            cout << d << " ";
        }
        cout << endl;
    }

    // Resolver el problema usando búsqueda tabú
    vector<int> mejorRecorrido = busquedaTabu(n, distancias, iteraciones, tamTabu);

    // Mostrar el resultado
    cout << "Mejor recorrido encontrado: ";
    for (int ciudad : mejorRecorrido) {
        cout << ciudad + 1 << " ";
    }
    cout << mejorRecorrido.front() + 1 << endl; // Volver a la ciudad inicial
    cout << "Costo total: " << calcularCoste(mejorRecorrido, distancias) << endl;

    return 0;
}
