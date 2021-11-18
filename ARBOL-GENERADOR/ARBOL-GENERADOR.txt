#include <iostream>
#include<random>
#include<ctime>
#include<fstream>
using namespace std;

const char *direccion = "cd UNSA 2DO SEMESTRE\\ESTRUCTURAS DISCRETAS II\\ArchivosCPP\\ARBOL-GENERADOR",
            *disco = "d:";

struct Arista;

struct Vertice{
    char nombre;
    Vertice *sig;
    Arista *ady;
    bool taken;
};

struct Arista{
    Vertice *dest;
    Arista *sig;
};



void generarMatriz(int **, int);
void conexo(int **, int);
void numerosAleatorios(int **, int);
void mostrar(int **, int n);
void insertarVertice(Vertice *&,char);
void agregarArista(Vertice *&,Vertice *&, Vertice *&, Vertice *&);
void insertarArista(Vertice *&,char,char);
char letraAscii(int);
void generarGrafo(Vertice *&, int **, int);
string instruccionGrafo(Vertice *);
void graficarGrafo(Vertice *);
void abrirPdf();
void busquedaAnchura(Vertice *, Vertice *&);
void busquedaProfundidad(Vertice *, Vertice *&);

int main() {

    srand(time(0));
	int n = 7;

	int **matriz=new int *[n]; //puntero que apunta a un array de punteros
    generarMatriz(matriz,n);

    numerosAleatorios(matriz, n);

	mostrar(matriz, n);

    Vertice *grafo = NULL; // grafo

    generarGrafo(grafo,matriz,n);
    graficarGrafo(grafo);
    abrirPdf();

    Vertice *arbolAnchura = NULL;
    busquedaAnchura(grafo,arbolAnchura);
    graficarGrafo(arbolAnchura);
    abrirPdf();

    Vertice *arbolProfundidad = NULL;
    busquedaProfundidad(grafo,arbolProfundidad);
    graficarGrafo(arbolProfundidad);
    abrirPdf();

    delete grafo;
    delete arbolAnchura;
    delete arbolProfundidad;
	for(int i=0;i<n;i++)
	{
		delete [] matriz[i];
	}
	delete [] matriz;


	return 0;
}	



void generarMatriz(int **matriz, int n)
{
    int fi = n, col = n;

	for(int i=0; i<fi;i++)
		matriz[i]=new int[col];

	conexo(matriz, n);
}


void conexo(int **Ma, int n)
{
    int fi = n, co = n;
    for(int i = 0; i < fi; i++)
        for(int j = 0; j < co; j++)
        {
            Ma[i][j] = 0;
            if((i+1 == j)||(i == j+1))
                Ma[i][j] = 1;
        }
}

bool existen(int M[],int N[], int n, int a, int b)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
            {
                if(M[i] == a && N[j] == b)
                    return true;
            }
        }
    }

    return false;
}

void numerosAleatorios(int **Ma, int n)
{

    int restante = n*(n-1)/2 - n + 1,
    cant = 1 + rand()%restante,
    fi, co;

    int coord1[cant], coord2[cant], i = 0;

    while(cant > 0)
    {
        fi = 2+rand()%(n-2);
        co = rand()%(fi-1);  

        if(!existen(coord1,coord2,i,fi,co))
        {
            coord1[i] = fi;
            coord2[i] = co;

            Ma[fi][co] = 1;
            Ma[co][fi] = 1;
        
            cant--;
            i++;
        }        
    }

}

void mostrar(int **Ma, int n)
{ 
    int fi = n, co = n;
    for(int i=0; i<fi;i++)
    { 
        for(int j=0; j<co;j++)
	        cout<<Ma[i][j]<<" ";
	        cout<<endl;
    }
}

// Grafo
void insertarVertice(Vertice *&grafo, char nombre)
{
    // creamos un nuevo vertice
    Vertice *aux,*nuevo = new Vertice();
    nuevo->nombre = nombre;
    nuevo->sig = NULL;
    nuevo->ady = NULL;
    nuevo->taken = false;

    // si el grafo es null, el vertice es el grafo
    if(grafo == NULL)
        grafo = nuevo;
    else{
        aux = grafo;
        // si no lo insertamos al inicio
        while(aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }

}

void agregarArista(Vertice *&aux1, Vertice *&aux2, Arista *&nueva_arista)
{
    // creamos una nueva arista
    Arista *ari;
    // si el origen no tiene arista, entonce lo agregamos hacia el aux2
    if(aux1->ady == NULL)
    {
        aux1->ady = nueva_arista;
        nueva_arista->dest = aux2;
    }
    else{
        ari = aux1->ady;
        // sino insertamos la arista al final de la lista de aristas
        while(ari->sig != NULL)
            ari = ari->sig;
        nueva_arista->dest = aux2;
        ari->sig = nueva_arista;
    }

}

void insertarArista(Vertice *&grafo, char orig, char dest)
{
    Arista *nueva_arista = new Arista();
    Vertice *aux1, *aux2;

    // si el grafo es null, no hay donde insertar aritas
    if(grafo == NULL)
    {
        cout<<"No hay grafo"<<endl;
        return;
    }
    nueva_arista->sig = NULL;
    aux1 = grafo;
    aux2 = grafo;

    // recorremos el grafo hasta tomar el valor de destino
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
            // si llegamos al origen, cremos la arista de origen a destino
            agregarArista(aux1,aux2,nueva_arista);
            return;
        }
        aux1 = aux1->sig;
    }

}

char letraAscii(int num)
{
    char letra = num;
    return letra;
}

void generarGrafo(Vertice *&grafo, int **matriz, int n)
{
    for(int i = 0; i < n; i++)
        insertarVertice(grafo,letraAscii(i+65));
    
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            if(matriz[i][j] == 1)
                insertarArista(grafo,letraAscii(i+65),letraAscii(j+65));
}


string instruccionGrafo(Vertice *grafo)
{
    Vertice *punt;
    Arista *ari;
    punt = grafo;

    string texto;

    while(punt != NULL)
    {
        // si el vertice tiene aristas
        if(punt->ady != NULL)
        {
            // recorremos todas las aristas
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
        // sino solo imprimimos el vertice
        else
        {
            texto += "\t";
            texto += punt->nombre;
            texto += ";\n";
        }
        punt = punt->sig;
    }

    // retornamos las instrucciones
    return texto;
}

void graficarGrafo(Vertice *grafo)
{
    // creamos un archivo
    ofstream archivo;
    archivo.open("grafo.txt",ios::out);

    // si falla
    if(archivo.fail())
    {
        cout<<"Ocurrio un error";
        exit(1);
    }

    // sino creamos con las instrucciones
    archivo<<"graph A {\n"
    <<instruccionGrafo(grafo)
    <<"}";

    // lo creamos en formato pdf
    archivo.close();
    system("dot grafo.txt -Tpdf  -o grafo.pdf");
}


void abrirPdf()
{
    // abrimos el pdf
    system(disco);
    system(direccion);
    system("grafo.pdf");
}


void busquedaAnchura(Vertice *grafo, Vertice *&arbolAnchura)
{
    Vertice *aux = grafo;
    Arista *ari;
    while(aux != NULL)
    {   
        insertarVertice(arbolAnchura,aux->nombre);
        aux->taken = false;
        aux = aux->sig;
    }

    aux = grafo;
    while(aux != NULL)
    {  
        ari = aux->ady;
        while(ari != NULL)
        {  
            if(ari->dest->taken == false)
            {
                insertarArista(arbolAnchura,aux->nombre,ari->dest->nombre);
                ari->dest->taken = true;
            }
            ari = ari->sig;
        }

        aux = aux->sig;
    }
}


void busquedaProfundidad(Vertice *grafo, Vertice *&arbolProf)
{
    Vertice *aux = grafo;
    Arista *ari;
    while(aux != NULL)
    {   
        insertarVertice(arbolProf,aux->nombre);
        aux->taken = false;
        aux = aux->sig;
    }

    aux = grafo;

    while(aux != NULL)
    {
        ari = aux->ady;
        while(ari != NULL)
        {
            if(ari->dest->taken == false)
            {
                insertarArista(arbolProf,aux->nombre,ari->dest->nombre);
                break;
            }
            ari = ari->sig;
        }
        aux = aux->sig;
    }

}

