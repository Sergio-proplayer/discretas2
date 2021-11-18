#ifndef GRAFO_H
#define GRAFO_H

#include<iostream>
using namespace std;

class Arista;

class Vertice{

    Vertice *siguiente;
    Arista *adyacente;
    string nombre;
    friend class Grafo;

};

class Arista{

    Arista *siguiente;
    Vertice *adyacente;
    int peso;
    friend class Grafo;

};

class Grafo{

    Vertice *grafo;
    public:
        void iniciarGrafo();
        bool vacio();
        int numVertices();
        Vertice *getVertice(string nombre);
        void insertarVertice(string nombre);
        void insertarArista(Vertice *origen, Vertice *destino, int peso);
        void listaAdyacencia();
        void eliminarArista(Vertice *origen, Vertice *destino);
        void anular();
};

#endif
