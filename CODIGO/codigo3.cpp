#include<iostream>
#include<fstream>
using namespace std;

struct Nodo
{
    char letra;
    int frecuencia;
    struct Nodo *sig;
    struct Nodo *izq, *der;
};

typedef struct Nodo *Arbol;

int Abecedario[26];

char letraAscii(int num)
{
    char letra = num;
    return letra;
}

Arbol crearNodo(char l, int f)
{
    Arbol nuevoNodo = new(struct Nodo);
    nuevoNodo->letra = l;
    nuevoNodo->frecuencia = f;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;

    return nuevoNodo;
}

void modificarArbol(Arbol &arbol, char l, int f)
{
    if(arbol == NULL)
        arbol = crearNodo(l,f);
    else if(f < arbol->frecuencia)
        modificarArbol(arbol->izq,l,f);
    else if(f > arbol->frecuencia)
        modificarArbol(arbol->der,l,f);
}

void crearArbol(Arbol &arbol, Nodo *lista)
{
    Nodo *actual = lista;
    Nodo *siguiente = actual->sig;
    while(siguiente != NULL)
    {
        if(actual < siguiente && siguiente < siguiente->sig)
        {
            modificarArbol(arbol,' ',actual->frecuencia+siguiente->frecuencia);            
            modificarArbol(arbol,actual->letra,actual->frecuencia);
            modificarArbol(arbol,siguiente->letra,siguiente->frecuencia);
        }

        actual = actual->sig;
        siguiente = siguiente->sig;
    }
}

void agregarLetra(Nodo *&lista, char l, int f)
{
    Nodo *nueva_letra = new Nodo();
    nueva_letra->letra = l;
    nueva_letra->frecuencia = f;

    Nodo *aux1 = lista, *aux2;

    while((aux1 != NULL)&&(aux1 -> frecuencia < f))
    {
        aux2 = aux1;
        aux1 = aux1 -> sig;
    }

    if(lista == aux1)
        lista = nueva_letra;
    else
        aux2 -> sig = nueva_letra;
    
    nueva_letra -> sig = aux1;
}

void cargarLetras(Nodo *&lista)
{
    for(int i = 97, j = 0; i <= 122; i++, j++)
    {
        if(Abecedario[j] != 0)
            agregarLetra(lista,letraAscii(i),Abecedario[j]);
    }
}


void sumarFrecuencia(char letra)
{
    for(int i = 97, j = 0; i <= 122; i++, j++)
    {
        if(letraAscii(i) == letra)
            Abecedario[j]++;
    }  
}

void leerArchivo(string nombreArchivo)
{
    ifstream archivo;
    string linea;

    archivo.open(nombreArchivo, ios::in);

    while(true)
    {
        archivo >> linea;
        cout<< linea << endl;

        for(int i = 0; i < linea.length(); i++)
            sumarFrecuencia(linea[i]);
        
        if(archivo.eof()) break;
    }
}


void mostrarLista(Nodo *lista)
{
    Nodo *actual = new Nodo();
    actual = lista;

    while (actual != NULL)
    {
        if(actual->frecuencia > 0)
            cout<< actual->letra <<" -> "<< actual->frecuencia<<endl;
        actual = actual->sig;
    }
}

void preOrden(Arbol arbol)
{
    if(arbol!=NULL)
    {
        cout << arbol->letra <<" : "<<arbol->frecuencia<<" -> ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}


int main()
{
    Arbol tree = NULL;
    Nodo *lista = NULL;
    leerArchivo("letras.txt");
    cargarLetras(lista);
    mostrarLista(lista);
    crearArbol(tree,lista);
    preOrden(tree);
    return 0;
}