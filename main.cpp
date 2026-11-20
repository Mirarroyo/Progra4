#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "nadador.h"
#include "BST_completo.h"


void merge(std::vector<Registro>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    std::vector<Registro> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i].tiempo <= R[j].tiempo) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<Registro>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void insertarBalanceado(BST& arbol, const std::vector<Registro>& arr, int inicio, int fin) {
    if (inicio > fin) return;
    int mid = inicio + (fin - inicio) / 2;
    arbol.insertar(arr[mid]);
    insertarBalanceado(arbol, arr, inicio, mid - 1);
    insertarBalanceado(arbol, arr, mid + 1, fin);
}

int main() {
    BST arbol;
    std::vector<Registro> listaTemporal;

    // archivo
    std::ifstream archivo("tiempos_natacion.csv");
    std::string linea;
    if (std::getline(archivo, linea)) {
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string idStr, nombre, distStr, tiempoStr;
            std::getline(ss, idStr, ',');
            std::getline(ss, nombre, ',');
            std::getline(ss, distStr, ',');
            std::getline(ss, tiempoStr, ',');
            listaTemporal.push_back({std::stoi(idStr), nombre, std::stoi(distStr), std::stod(tiempoStr)});
        }
    }
    archivo.close();


    if (!listaTemporal.empty()) {
        mergeSort(listaTemporal, 0, listaTemporal.size() - 1);
        insertarBalanceado(arbol, listaTemporal, 0, listaTemporal.size() - 1);
    }

    int opcion = 0;
    do {
    
        std::cout << "1. Mostrar todos los tiempos ordenados\n";
        std::cout << "2. Consultar ranking por distancia (50m, 100m, 200m)\n";
        std::cout << "3. Agregar nuevo registro de tiempo\n";
        std::cout << "4. Guardar reporte ordenado en CSV\n";
        std::cout << "5. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::cout << "\n RANKING \n";
            arbol.mostrarTodo();
        } else if (opcion == 2) {
            int dist;
            std::cout << "Ingresa distancia (50, 100 o 200): ";
            std::cin >> dist;
            std::cout << "\n RANKING " << dist << "m \n";
            arbol.consultarDistancia(dist);
        } else if (opcion == 3) {
            Registro nuevo;
            std::cout << "ID: "; std::cin >> nuevo.id;
            std::cout << "Nadador: "; std::cin >> nuevo.nadador;
            std::cout << "Distancia (m): "; std::cin >> nuevo.distancia;
            std::cout << "Tiempo (seg): "; std::cin >> nuevo.tiempo;
            arbol.insertar(nuevo);
            std::cout << "Registro agregado correctamente.\n";
        } else if (opcion == 4) {
            arbol.guardarEnCSV("reporte_ordenado.csv");
            std::cout << "Datos guardados en 'reporte_ordenado.csv'.\n";
        }
    } while (opcion != 5);

    return 0;
}
