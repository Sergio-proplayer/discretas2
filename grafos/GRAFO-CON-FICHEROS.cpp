#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;

int **puntero_matriz;

struct Arista;

struct Vertice{
    char nombre;
    Vertice *sig;
    Arista *ady;
};

struct Arista{
    Vertice *dest;
    Arista *sig;
};

Vertice *grafo = NULL;

void insertarVertice(char nombre)
{
    Vertice *aux,*nuevo = new Vertice();
    nuevo->nombre = nombre;
    nuevo->sig = NULL;
    nuevo->ady = NULL;

    if(grafo == NULL)
        grafo = nuevo;
    else{
        aux = grafo;
        while(aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
    cout<<nuevo->nombre<<" Ingresado al grafo "<<endl;

}

void agregarArista(Vertice *&aux1, Vertice *&aux2, Arista *&nueva_arista)
{
    Arista *ari;
    if(aux1->ady == NULL)
    {
        aux1->ady = nueva_arista;
        nueva_arista->dest = aux2;
    }
    else{
        ari = aux1->ady;
        while(ari->sig != NULL)
            ari = ari->sig;
        nueva_arista->dest = aux2;
        ari->sig = nueva_arista;
    }

}

void insertarArista(char orig, char dest)
{
    Arista *nueva_arista = new Arista();
    Vertice *aux1, *aux2;

    if(grafo == NULL)
    {
        cout<<"No hay grafo"<<endl;
        return;
    }
    nueva_arista->sig = NULL;
    aux1 = grafo;
    aux2 = grafo;

    while(aux2 != NULL)
    {
        if(aux2->nombre == dest)
            break;
        aux2 = aux2->sig;
    }
    while(aux1 != NULL)
    {
        if(aux1->nombre == orig)
        {
            agregarArista(aux1,aux2,nueva_arista);
            return;
        }
        aux1 = aux1->sig;
    }

}

void mostrarGrafo()
{
    Vertice *punt;
    Arista *ari;
    punt = grafo;
    cout<<"Nodo: Adyacencia"<<endl;
    while(punt != NULL)
    {
        cout<<"   "<<punt->nombre<<"->";
        if(punt->ady != NULL)
        {
            ari = punt->ady;
            while(ari != NULL)
            {
                cout<<" "<<ari->dest->nombre;
                ari = ari->sig;
            }
        }
        punt = punt->sig;
        cout<<endl;
    }
}

Vertice *getVertice(char nombre)
{
    Vertice *vert, *aux = grafo;
    while(aux != NULL)
    {
        if(aux->nombre == nombre)
            vert = aux;
        aux = aux->sig;
    }
    return vert;
}

// funciones para la matriz de incidencia
char letraAscii(int num)
{
    char letra = num;
    return letra;
}

int funcionInternos(int n)
{
    int cantNum = 0;
    for(int i = 0; i < n; i++)
    {
        if(i % 2 == 0)
            cantNum++;
    }
    return cantNum;
}

void datosMatriz(string nombreArchivo, int &fi, int &co)
{
    ifstream archivo;
    string texto, linea;

    archivo.open(nombreArchivo);

    int filas = 0, column;
    while(getline(archivo,linea))
    {
        column = linea.length();
        filas++;
    }
    column = funcionInternos(column);

    archivo.close();
    
    fi = filas;
    co = column;
}

void cargarMatriz(string nombreArchivo, int fi, int co)
{
    //reservamos memoria en un puntero
    puntero_matriz = new int*[fi];
    for(int i = 0; i < fi; i++)
        puntero_matriz[i] = new int[co];

    ifstream archivo;
    archivo.open(nombreArchivo);

    for(int i = 0; i < fi; i++)
        for(int  j = 0; j < co; j++)
            archivo>>*(*(puntero_matriz+i)+j);

    archivo.close();
}

void mostrarMatriz(int fi, int co)
{
    for(int i = 0; i < fi; i++)
    {
        for(int j = 0; j < co; j++)
            cout<<*(*(puntero_matriz+i)+j)<<" ";
        cout<<endl;
    }
    cout<<endl;
}


void porColumna(int fi, int nColumn)
{
    int N[2] = {-1,-1}, w = 0;
    for(int i = 0; i < fi; i++)
    {
        if(*(*(puntero_matriz+i)+nColumn) == 1)
        {
            N[w] = i;
            w++;
        }
    }

    if(N[1] == -1)
        N[1] = N[0];

    char n1 = letraAscii(N[0] + 65), 
    n2 = letraAscii(N[1] + 65);

    insertarArista(n1,n2);

}

void grafoFichero(string nombreArchivo, int fi, int co)
{
    int nVertices = fi, nAristas = co, i = 65;
    
    // cargamos la matriz y lo mostramos
    cargarMatriz(nombreArchivo,fi,co);
    cout<<"Mostrando la matriz: "<<endl;
    mostrarMatriz(fi,co);

    // inserto los vertices por cada fila
    while(i < nVertices + 65)
    {
        insertarVertice(letraAscii(i));
        i++;
    }


    // y por columna insertamos la aritas
    for(int i = 0; i < co; i++)
        porColumna(fi,i);

}

// graficar el grafo con graphviz
string instruccionGrafo()
{
    Vertice *punt;
    Arista *ari;
    punt = grafo;

    string texto;

    while(punt != NULL)
    {
        if(punt->ady != NULL)
        {
            ari = punt->ady;
            while(ari != NULL)
            {
                texto += "\t";
                texto += punt->nombre;
                texto += " -- ";
                texto += ari->dest->nombre;
                texto += ";\n"; 
                ari = ari->sig;
            }
        }
        punt = punt->sig;
    }

    return texto;
}

void graficarGrafo()
{
    
    ofstream archivo;
    archivo.open("grap.txt",ios::out);

    if(archivo.fail())
    {
        cout<<"Ocurrio un error";
        exit(1);
    }
    archivo<<"graph A {\n"
    <<instruccionGrafo()
    <<"}";

    archivo.close();
    system("dot -Tpdf grap.txt -o grap.pdf");
}

void abrirPdf()
{
    system("d:");
    system("cd UNSA 2DO SEMESTRE\\ESTRUCTURAS DISCRETAS II\\ArchivosCPP\\grafos");
    system("grap.pdf");
}

// funcion menu

int main()
{
    int fi, co;

    datosMatriz("matriz.txt",fi,co);
    cout<<endl;
    grafoFichero("matriz.txt",fi,co);
    cout<<endl;
    cout<<"Mostrando el grafo: "<<endl;
    cout<<endl;
    mostrarGrafo();
    cout<<endl;
    graficarGrafo();

    char opc;
    cout<<"Desea abrir el pdf? s/n  ";cin>>opc;
    if(opc == 's')
    {
        cout<<"Abriendo grafico";
        abrirPdf();
    }

    return 0;
}