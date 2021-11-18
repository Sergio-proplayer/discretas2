#include <iostream>
#include<random>
#include<ctime>
#include<fstream>
#include<vector>
#include<stdlib.h>
using namespace std;

const char *direccion = "cd UNSA 2DO SEMESTRE\\ESTRUCTURAS DISCRETAS II\\ArchivosCPP\\ARBOL-RECUBRIDOR",
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
    int peso;
};

void generarMatriz(int **, int);
void conexo(int **, int);
void numerosAleatorios(int **, int);
void mostrar(int **, int n);
void insertarVertice(Vertice *&,char);
void agregarArista(Vertice *&,Vertice *&, Vertice *&, Vertice *&);
void insertarArista(Vertice *&,char,char,int);
char letraAscii(int);
void generarGrafo(Vertice *&, int **, int);
string instruccionGrafo(Vertice *);
void graficarGrafo(Vertice *, string, char*);
void abrirPdf(char *);

//algoritmo de prim
Vertice *getVertice(Vertice *, char);
void recursionPrim(Vertice *, Vertice *&, Vertice *&, int &, char &);
bool todosTomados(Vertice *);
void algoritmoPrim(Vertice *, Vertice *&);
bool seDibujoArista(vector<char>,vector<char>,char,char);
bool existe(vector<char>,char);
bool existeArista(Vertice *, char , char, int);

//algoritmo de kruskal
void algoritmoKruskal(Vertice *, Vertice *&);
void recursionKruskal(Vertice *, Vertice *, char &, char &, int &, int);
bool esCiclo(Vertice *, char, char);


// menu
void menu();

int main() {

    char * grafoCompil = "dot grafo.txt -Tpdf  -o grafo.pdf",
        *primCompil = "dot prim.txt -Tpdf  -o prim.pdf",
        *kruskalCompil = "dot kruskal.txt -Tpdf  -o kruskal.pdf";

    srand(time(0));

	int n = 5; // cantidad de vertices

	int **matriz = new int *[n]; //puntero que apunta a un array de punteros
    
    Vertice *grafo = NULL; // grafo
    Vertice *prim = NULL;
    Vertice *kruskal = NULL;
    
    
    generarMatriz(matriz,n);
    numerosAleatorios(matriz, n);   

    
    generarGrafo(grafo,matriz,n); // generar a partir de matriz
    graficarGrafo(grafo,"grafo.txt",grafoCompil);



    algoritmoPrim(grafo,prim);
    graficarGrafo(prim,"prim.txt",primCompil);

    algoritmoKruskal(grafo,kruskal);
    graficarGrafo(kruskal,"kruskal.txt",kruskalCompil);

    system("cls");
    char opc;
    do{ 
        menu();
        cout<<"Opciones: ";
        cin>>opc;
        switch (opc)
        {
            case 'a': 
                mostrar(matriz, n);
                system("pause"); break;

            case 'b': 
                abrirPdf("grafo.pdf");
                
                system("pause"); break;

            case 'c': 
                abrirPdf("prim.pdf");
                
                system("pause"); break;

            case 'd': 
                abrirPdf("kruskal.pdf");

                system("pause"); break;

            case 'e': cout<<"Saliendo..."<<endl;system("pause"); break;
            default: cout<<"No es una opcion valida"<<endl;system("pause"); break;
        }
        system("cls");
    }while(opc != 'e');

    delete kruskal;
    delete prim;
    delete grafo;

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

void insertarArista(Vertice *&grafo, char orig, char dest, int r)
{
    Arista *nueva_arista = new Arista();
    Arista *nueva_arista2 = new Arista();
    Vertice *aux1, *aux2;


    nueva_arista->peso = r;
    nueva_arista2->peso = r;
    // si el grafo es null, no hay donde insertar aritas
    if(grafo == NULL)
    {
        cout<<"No hay grafo"<<endl;
        return;
    }
    nueva_arista->sig = NULL;
    nueva_arista2->sig = NULL;
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
            agregarArista(aux2,aux1,nueva_arista2);
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
            {
                int r = 1+rand()%10;
                insertarArista(grafo,letraAscii(i+65),letraAscii(j+65),r);
            }
}

bool seDibujoArista(vector<char> vOrig, vector<char> vDest, char orig, char dest)
{
    for(int i = 0; i < vOrig.size(); i++)
    {
        if(vOrig[i] == orig && vDest[i] == dest) 
            return true;
    }   
    return false;
}

string instruccionGrafo(Vertice *grafo)
{
    Vertice *punt;
    Arista *ari;
    punt = grafo;

    string texto;

    vector<char> orig;
    vector<char> dest;
    while(punt != NULL)
    {
        // si el vertice tiene aristas
        if(punt->ady != NULL)
        {
            // recorremos todas las aristas
            ari = punt->ady;
            while(ari != NULL)
            {
                if(seDibujoArista(orig,dest,ari->dest->nombre,punt->nombre) == false)
                {
                    texto += "\t";
                    texto += punt->nombre;
                    texto += " -- ";
                    texto += ari->dest->nombre;
                    texto += "[ label = \"";
                    texto += to_string(ari->peso);
                    texto += "\"];\n";
                
                    orig.push_back(punt->nombre);
                    dest.push_back(ari->dest->nombre);            

                }

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

void graficarGrafo(Vertice *grafo, string nombre, char * compil)
{
    // creamos un archivo
    ofstream archivo;
    archivo.open(nombre,ios::out);

    // si falla
    if(archivo.fail())
    {
        cout<<"Ocurrio un error";
        exit(1);
    }

    // sino creamos con las instrucciones
    archivo<<"graph A {\n rankdir = \"LR\"; \n "
    <<instruccionGrafo(grafo)
    <<"}";

    // lo creamos en formato pdf
    archivo.close();
    system(compil);
}


void abrirPdf(char * nombre)
{
    // abrimos el pdf
    system(disco);
    system(direccion);
    system(nombre);
}

bool todosTomados(Vertice *grafo)
{
    bool band = true;
    Vertice *aux = grafo;
    while(aux != NULL)
    {
        if(aux->taken == false)
            band = false;
        aux = aux->sig;
    }
    return band;
}

Vertice *getVertice(Vertice *grafo, char nombre)
{
    Vertice *vert, *aux = grafo;
    while(aux != NULL)
    {
        // recorremos hasta que el aux tome el valor que queremos
        if(aux->nombre == nombre)
            vert = aux;
        aux = aux->sig;
    }
    // retornamos el vertice
    return vert;
}

bool existe(vector<char> T, char a)
{
    for(int i = 0; i < T.size(); i++)
        if(T[i] == a)
            return true;

    return false;
}

bool existeArista(Vertice *grafo, char orig, char dest, int peso)
{
    Vertice *aux = grafo;
    Arista *ari;
    while(aux != NULL)
    {
        if(aux->nombre == orig)
        {
            ari = aux->ady;
            while(ari != NULL)
            {
                if(ari->dest->nombre == dest && ari->peso == peso)
                    return true;
                ari = ari->sig;
            }
        }
        aux = aux->sig;
    }

    return false;
}


// segunda parte de prim
void algoritmoPrim(Vertice *grafo, Vertice *&arbol)
{
    Vertice *aux = grafo;
    Arista *ari;

    // contadores de vertices y aristas
    int cantVertices = 0;
    int cantAristas = 0;

    // incializamos a todo el arbol y el aux en taken false
    while(aux != NULL)
    {
        insertarVertice(arbol,aux->nombre);
        cantVertices++;
        aux->taken = false;
        aux = aux->sig;
    }

    aux = grafo;
    char destino;
    vector<char> T; // vector T para leer los vertices ya tomado

    Vertice *aux2; // otro auxiliar para tomar el vertice con arista del menor peso

    while(cantAristas != cantVertices-1) // cuando la cantidad de arista llegue a cantidad de vertices -1 termina el bucle
    {
        int menorPeso = 11; // inicializamos el peso como el maximo valor que alcanzan los pesos en el programa

        if(existe(T,aux->nombre) == false) // si el vertice no exite, lo insertamos en el vector
           T.push_back(aux->nombre);

        for(int i = 0; i < T.size(); i++) // analizamos el menor peso con todos los valores del vector
        {
            aux = getVertice(grafo,T[i]);  // aux toma cada valor
            recursionPrim(grafo,aux,arbol,menorPeso,destino);   // ejecutamos el algoritmo     

            if(existeArista(grafo,aux->nombre,destino,menorPeso)) // si existe la arista, aux2 referencia al camino indicado
                aux2 = aux;
        }
        
        Vertice *vert = getVertice(grafo,destino); // hace referencia a destino
        if(aux2->nombre != destino && vert->taken == false)  // si no es un lazo y además no fue tomado
        {
            insertarArista(arbol,aux2->nombre,destino,menorPeso); // insertamos la arita
            cantAristas++;
        }

        aux = getVertice(grafo,destino); // aux toma ahora el valor de destino

    }
}

// este es una primera parte del algoritmo
void recursionPrim(Vertice *grafo, Vertice *&aux, Vertice *&arbol, int &menorPeso, char &destino)
{
    Arista *ari;
    ari = aux->ady;
    aux->taken = true; // aux ya fue tomado

    while(ari != NULL)
    {
        // si el peso es menor y ademas el destino no fue tomado
        if(ari->peso < menorPeso && !(ari->dest->taken))
        {
            menorPeso = ari->peso;
            destino = ari->dest->nombre;
        }
        ari = ari->sig;
    }
}

// ALGORITMO DE KRUSKAL

// funcion que determina que si insertamos una arista, se generaria un ciclo
bool esCiclo(Vertice *grafo, char orig, char dest)
{
    Vertice *aux = grafo;
    Arista *ari;
    char raiz1 = 'x', raiz2 = 'y';

    while(aux != NULL)
    {
        ari = aux->ady;
        while(ari != NULL)
        {
            if(existeArista(grafo,aux->nombre,orig,ari->peso))
                raiz1 = aux->nombre;
            if(existeArista(grafo,aux->nombre,dest,ari->peso))
                raiz2 = aux->nombre;
            ari = ari->sig;
        }
        if(raiz1 == raiz2) // si la raiz de los dos es el mismo, entonces se haria un ciclo
            return true;
        aux = aux->sig;
    }

    return false;
    
}

// la funcion del algoritmo
void algoritmoKruskal(Vertice *grafo, Vertice *&arbol)
{
    Vertice *aux = grafo;
    Arista *ari;
    
    char orig, dest;
    int cantAristas = 0, cantVertices = 0;
    while(aux != NULL)
    {
        insertarVertice(arbol,aux->nombre);
        aux->taken = false;
        aux = aux->sig;
        cantVertices++;
    }

    aux = grafo;

    // el menorpeso se inicializa en un valor mayor a todos, ultimo menor referencia al valor de arista en el que estamos
    int menorPeso = 11, ultimoMenor = 0;

    while(cantAristas != cantVertices-1) // hasta que la cantidad de aristas alcanza el minimo
    {
        // esta funcion no devuelve el origen, el destino y el menorPeso que deberia tomar la siguiente arista
        recursionKruskal(aux,arbol, orig,dest,menorPeso,ultimoMenor);
        
        if(!esCiclo(arbol,orig,dest)) // si no es ciclo
        {
            insertarArista(arbol,orig,dest,menorPeso); // insertamos arista en el arbol
            cantAristas++; // aumena la cantidad de arista
        }
        else
            menorPeso++; // para que el bucle no sea infinito

        ultimoMenor = menorPeso;
        menorPeso = 11;
    }
}

void recursionKruskal(Vertice *grafo, Vertice *arbol, char &orig, char &dest, int &menorPeso, int ultimoMenor)
{
    Vertice *aux = grafo;
    Arista *ari;

    while (aux != NULL)
    {
        ari = aux->ady;
        while (ari != NULL)
        {
            // si cumple con todas las condiciones
            if(ari->peso < menorPeso && ari->peso >= ultimoMenor && !existeArista(arbol,aux->nombre,ari->dest->nombre,ari->peso))
            {
                // se cambia  los valores actuales
                orig = aux->nombre;
                dest = ari->dest->nombre;
                menorPeso = ari->peso;
            }
            ari = ari->sig;
        }
        aux = aux->sig;
    }
}


void menu()
{
    cout<<"MENU"<<endl;
    cout<<"a. Mostrar matriz de adyacencia"<<endl;
    cout<<"b. Mostrar pdf del grafo conexo"<<endl;
    cout<<"c. Mostrar arbol de Prim"<<endl;
    cout<<"d. Mostrar arbol de Kruskal"<<endl;
    cout<<"e. Salir"<<endl;
}