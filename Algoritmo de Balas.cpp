#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Funci�n para resolver el problema usando el algoritmo de ramificaci�n y poda
void resolverProblema(int n, const vector<int>& costos, const vector<int>& impactos, int presupuesto) {
    int mejorImpacto = 0;
    vector<int> mejorSeleccion;

    // Vamos a generar todas las combinaciones posibles de proyectos seleccionados
    // Usaremos una m�scara binaria para representar las combinaciones.
    for (int i = 0; i < (1 << n); ++i) {
        int costoTotal = 0;
        int impactoTotal = 0;
        vector<int> seleccion(n);

        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {  // Si el bit j de i est� encendido, seleccionamos el proyecto j
                costoTotal += costos[j];
                impactoTotal += impactos[j];
                seleccion[j] = 1;
            }
            else {
                seleccion[j] = 0;
            }
        }

        // Comprobamos si el costo no excede el presupuesto
        if (costoTotal <= presupuesto && impactoTotal > mejorImpacto) {
            mejorImpacto = impactoTotal;
            mejorSeleccion = seleccion;
        }
    }

    // Imprimir la soluci�n �ptima
    cout << "Solucion Optima:\n";
    cout << "Impacto total: " << mejorImpacto << endl;
    cout << "Proyectos seleccionados: ";
    for (int i = 0; i < n; ++i) {
        if (mejorSeleccion[i] == 1) {
            cout << i + 1 << " ";  // Imprime el n�mero del proyecto seleccionado (1 basado)
        }
    }
    cout << endl;
}

int main() {
    int n, presupuesto;

    // Leer el n�mero de proyectos
    cout << "Introduce el numero de proyectos: ";
    cin >> n;

    vector<int> costos(n), impactos(n);

    // Leer los costos de los proyectos
    cout << "Introduce los costos de los proyectos: ";
    for (int i = 0; i < n; ++i) {
        cin >> costos[i];
    }

    // Leer los impactos de los proyectos
    cout << "Introduce los impactos de los proyectos: ";
    for (int i = 0; i < n; ++i) {
        cin >> impactos[i];
    }

    // Leer el presupuesto m�ximo
    cout << "Introduce el presupuesto maximo: ";
    cin >> presupuesto;

    // Llamar a la funci�n que resuelve el problema
    resolverProblema(n, costos, impactos, presupuesto);

    return 0;
}
