#include <iostream>
using namespace std;

struct Nodo
{
    int nro;
    struct Nodo *izq, *der, *sig;
};

Nodo *crearNodo(int x)
{
    Nodo *nuevoNodo = new Nodo();

    nuevoNodo->nro = x;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    nuevoNodo->sig = NULL;

    return nuevoNodo;
}
void insertar(Nodo *&arbol, int x)
{
    if(arbol==NULL)
        arbol = crearNodo(x);

    else if(x < arbol->nro)
        insertar(arbol->izq, x);

    else if(x > arbol->nro)
        insertar(arbol->der, x);
}

void mostrarArbol(Nodo *arbol, int count)
{
    if(arbol == NULL)
        return;
    else
    {
        mostrarArbol(arbol->der,count+1);
        for(int i = 0; i < count; i++)
            cout<<"   ";
        cout<<arbol->nro<<endl;
        mostrarArbol(arbol->izq,count+1);
    }
}
int main()
{
    Nodo *arbol = NULL;
    insertar(arbol,4);
    insertar(arbol,8);
    insertar(arbol,9);
    insertar(arbol,2);
    insertar(arbol,3);

    mostrarArbol(arbol,0);

    return 0;
}