#ifndef BST_COMPLETO_H
#define BST_COMPLETO_H

#include <iostream>
#include <fstream>
#include <string>
#include "nadador.h"

struct Nodo {
    Registro dato;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo(Registro r) : dato(r), izquierda(nullptr), derecha(nullptr) {}
};

class BST {
private:
    Nodo* raiz;

    Nodo* insertarRec(Nodo* nodo, Registro r) {
        if (nodo == nullptr) return new Nodo(r);
        if (r.tiempo < nodo->dato.tiempo)
            nodo->izquierda = insertarRec(nodo->izquierda, r);
        else
            nodo->derecha = insertarRec(nodo->derecha, r);
        return nodo;
    }

    void inOrderRec(Nodo* nodo) const {
        if (nodo != nullptr) {
            inOrderRec(nodo->izquierda);
            std::cout << "ID: " << nodo->dato.id << " | " << nodo->dato.nadador 
                      << " | " << nodo->dato.distancia << "m | " << nodo->dato.tiempo << "s\n";
            inOrderRec(nodo->derecha);
        }
    }

    void consultarPorDistanciaRec(Nodo* nodo, int dist) const {
        if (nodo != nullptr) {
            consultarPorDistanciaRec(nodo->izquierda, dist);
            if (nodo->dato.distancia == dist) {
                std::cout << "ID: " << nodo->dato.id << " | " << nodo->dato.nadador 
                          << " | " << nodo->dato.tiempo << "s\n";
            }
            consultarPorDistanciaRec(nodo->derecha, dist);
        }
    }

    void guardarRec(Nodo* nodo, std::ofstream& archivo) const {
        if (nodo != nullptr) {
            guardarRec(nodo->izquierda, archivo);
            archivo << nodo->dato.id << "," << nodo->dato.nadador << ","
                    << nodo->dato.distancia << "," << nodo->dato.tiempo << "\n";
            guardarRec(nodo->derecha, archivo);
        }
    }

    void liberarRec(Nodo* nodo) {
        if (nodo != nullptr) {
            liberarRec(nodo->izquierda);
            liberarRec(nodo->derecha);
            delete nodo;
        }
    }

public:
    BST() : raiz(nullptr) {}
    ~BST() { liberarRec(raiz); }

    void insertar(Registro r) { raiz = insertarRec(raiz, r); }
    void mostrarTodo() const { inOrderRec(raiz); }
    void consultarDistancia(int dist) const { consultarPorDistanciaRec(raiz, dist); }
    
    void guardarEnCSV(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        archivo << "id,nadador,distancia,tiempo\n";
        guardarRec(raiz, archivo);
        archivo.close();
    }
};

#endif
