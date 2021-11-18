#include<iostream>
#include "Grafo.h"

using namespace std;


int main()
{
    Grafo G;
    G.iniciarGrafo();

    G.insertarVertice("A");
    G.insertarVertice("B");
    G.insertarVertice("C");
    G.insertarVertice("D");

    G.insertarArista(G.getVertice("A"),G.getVertice("B"),1);
    G.insertarArista(G.getVertice("A"),G.getVertice("C"),1);
    G.insertarArista(G.getVertice("D"),G.getVertice("B"),1);

    G.listaAdyacencia();
    
    return 0;
}