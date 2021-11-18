#include "Grafo.h"

void Grafo::iniciarGrafo()
{
    grafo = NULL;
}

bool Grafo::vacio()
{
    if(grafo == NULL)
        return true;
    return false;
}

int Grafo::numVertices()
{
    Vertice *aux;
    aux = grafo;
    int i = 0;
    while(aux != NULL)
    {
        i++;
        aux = aux->siguiente;
    }

    return i;
}

Vertice *Grafo::getVertice(string nombre)
{
    Vertice *aux;
    aux = grafo;
    while(aux != NULL)
    {
        if(aux->nombre == nombre)
            return aux;
        aux = aux->siguiente;
    }
    return NULL;
}

void Grafo::insertarVertice(string nombre)
{
    Vertice *nuevoVertice = new Vertice;
    nuevoVertice->nombre = nombre;
    nuevoVertice->siguiente = NULL;
    nuevoVertice->adyacente = NULL;

    if(vacio())
        grafo = nuevoVertice;
    else
    {
        Vertice *aux;
        aux = grafo;
        while(aux->siguiente != NULL)
            aux = aux->siguiente;
        
        aux->siguiente = nuevoVertice;
    }
}

void Grafo::insertarArista(Vertice *origen, Vertice *destino, int peso)
{
    Arista *nuevaArista = new Arista;
    nuevaArista->siguiente = NULL;
    nuevaArista->adyacente = NULL;
    nuevaArista->peso = peso;

    Arista *aux;
    aux = origen->adyacente;


    if(aux == NULL)
        origen->adyacente = nuevaArista;
    else
    {
        while(aux != NULL)
            aux = aux->siguiente;

        aux->siguiente = nuevaArista;
    }
    
    nuevaArista->adyacente = destino;
}

void Grafo::listaAdyacencia()
{
    Vertice *auxVertice;   
    Arista *auxArista;

    auxVertice = grafo;
    while(auxVertice != NULL)
    {
        cout<<auxVertice->nombre<<" -> ";
        auxArista = auxVertice->adyacente;
        while(auxArista != NULL)
        {
            cout<<auxArista->adyacente->nombre<<" -> ";
            auxArista = auxArista->siguiente;
        }
        auxVertice = auxVertice->siguiente;
        cout<<endl;
    }

}

void Grafo::anular()
{
    Vertice *aux;

    while(grafo != NULL)
    {
        aux = grafo;
        grafo = grafo->siguiente;
        delete aux;
    }
}

void Grafo::eliminarArista(Vertice *origen, Vertice *destino)
{
    Arista *actual, *anterior;
    bool band = false;

    actual = origen->adyacente;

    if(actual == NULL)
        cout<<"El origen no tiene aristas"<<endl;
    else if(actual->adyacente == destino)
    {
        origen->adyacente = actual->siguiente;
        delete actual;
    }
    else
    {
        while(actual != NULL)
        {
            if(actual->adyacente == destino)
            {
                band = true;
                anterior->siguiente = actual->siguiente;
                delete actual;
                break;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        if(band == false)
            cout<<"Esos dos vertices no estan conectados"<<endl;       
    }

}