#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
using namespace std;

// datos a cambiar de ser necesario
const char *direccion = "cd UNSA 2DO SEMESTRE\\ESTRUCTURAS DISCRETAS II\\ArchivosCPP\\PROYECTO";
const string archivoMatriz = "matrizT.txt";

// matriz dinamica para guardar datos en caso de leer un archivp
int **puntero_matriz;
// filas y columnas de la matriz dinamica
int fi, co;

// matriz para alamacenar los datos de las aristas
int **aristas;
char **aristas_camino_clave;


// las estructuras para la arita y el vertice
struct Arista;

struct Vertice{
    char nombre;
    Vertice *sig;
    Arista *ady;
};

struct Arista{
    Vertice *dest;
    Arista *sig;
    int peso;
};

// el vertice principal o el primero, al que llamaremos grafo
Vertice *arbol = NULL;

// prototipos de funciones
char letraAscii(int);
int numeroAscii(char);
void insertarVertice(char);
void agregarArista(Vertice *&, Vertice *&, Arista *&);
void insertarArista(char, char);
string instruccionGrafo();
void graficarGrafo(string);
void abrirPdf();
int funcionInternos(int);
void datosMatriz(string);
void cargarMatriz(string);
void mostrarMatriz();
void porColumna(int);
void grafoFichero(string);

bool esHoja(Vertice *);
void conjuntoFinales(vector<char>&);
void getAristas();
int hallarCaminos(char);
void hallarCaminoClave(vector<char>, vector<int>&, char &);
int cantVertices(char);
void construirCamino(char);
string instruccionGrafoCaminoClave(char);

int main()
{
    vector<char> hojas;
    vector<int> caminos;
    char hojaFinal;

    datosMatriz(archivoMatriz);
    grafoFichero(archivoMatriz);
    string instrucciones  = instruccionGrafo();
    graficarGrafo(instrucciones);
    abrirPdf();
    
    conjuntoFinales(hojas);
    getAristas();
    hallarCaminoClave(hojas,caminos,hojaFinal);
    string segundaInstruccion = instruccionGrafoCaminoClave(hojaFinal);
    system("cls");
    graficarGrafo(segundaInstruccion);
    abrirPdf();

    for(int i = 0; i < fi; i++)
		delete [] puntero_matriz[i];
	delete [] puntero_matriz;

    for(int i = 0; i < cantVertices(hojaFinal); i++)
        delete [] aristas_camino_clave[i];
    delete [] aristas_camino_clave;

    for(int i = 0; i < co; i++)
        delete [] aristas[i];
    delete [] aristas;

    
    return 0;
}

void insertarVertice(char nombre)
{
    // creamos un nuevo vertice
    Vertice *aux,*nuevo = new Vertice();
    nuevo->nombre = nombre;
    nuevo->sig = NULL;
    nuevo->ady = NULL;

    // si el grafo es null, el vertice es el grafo
    if(arbol == NULL)
        arbol = nuevo;
    else{
        aux = arbol;
        // si no lo insertamos al inicio
        while(aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }
   // cout<<nuevo->nombre<<" Ingresado al grafo "<<endl;

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

void insertarArista(char orig, char dest, int peso)
{
    Arista *nueva_arista = new Arista();
    Vertice *aux1, *aux2;

    // si el grafo es null, no hay donde insertar aritas
    if(arbol == NULL)
    {
        cout<<"No hay grafo"<<endl;
        return;
    }
    nueva_arista->sig = NULL;
    nueva_arista->peso = peso;
    aux1 = arbol;
    aux2 = arbol;

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


// damos un numero y lo devuelve en caracter
char letraAscii(int num)
{
    char letra = num;
    return letra;
}

int numeroAscii(char letra)
{
    int num = letra;
    return num;
}

// graficar el grafo con graphviz
string instruccionGrafo()
{
    Vertice *punt;
    Arista *ari;
    punt = arbol;

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
                texto += "[label = ";
                texto += to_string(ari->peso);
                texto += "]";
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

void graficarGrafo(string instrucciones)
{
    // creamos un archivo
    ofstream archivo;
    archivo.open("arbol.txt",ios::out);

    // si falla
    if(archivo.fail())
    {
        cout<<"Ocurrio un error";
        exit(1);
    }

    // sino creamos con las instrucciones
    archivo<<"graph A {\n"
    <<instrucciones
    <<"}";

    // lo creamos en formato pdf
    archivo.close();
    system("dot -Tpdf arbol.txt -o arbol.pdf");
}

void abrirPdf()
{
    // abrimos el pdf
    system("d:");
    system(direccion);
    system("arbol.pdf");
}

// para leer los espacios de columna a columna de la matriz del archivo
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

void datosMatriz(string nombreArchivo)
{
    // dinamicamente averiguamos cuales son el numero de filas y columnas
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

void cargarMatriz(string nombreArchivo)
{
    //reservamos memoria en un puntero
    puntero_matriz = new int*[fi];
    for(int i = 0; i < fi; i++)
        puntero_matriz[i] = new int[co];

    ifstream archivo;
    archivo.open(nombreArchivo);

    // comenzamo a guardar los datos del archivo en una matriz dinamica
    for(int i = 0; i < fi; i++)
        for(int  j = 0; j < co; j++)
            archivo>>*(*(puntero_matriz+i)+j);

    archivo.close();
}

void mostrarMatriz()
{
    // mostrar los datos de la matriza
    for(int i = 0; i < fi; i++)
    {
        for(int j = 0; j < co; j++)
            cout<<*(*(puntero_matriz+i)+j)<<" ";
        cout<<endl;
    }
    cout<<endl;
}

// como es una matriz de incidencia, las aristas se forman por columnas
void porColumna(int nColumn)
{
    // se crea un arreglo con las posiciones de los vertices
    int N[2] = {-1,-1}, w = 0, peso;
    for(int i = 0; i < fi; i++)
    {
        if(*(*(puntero_matriz+i)+nColumn) >= 1)
        {
            peso = *(*(puntero_matriz+i)+nColumn);
            // solo si hay un uno, el valor cambia a la posicion
            N[w] = i;
            w++;
        }
    }

    if(N[1] == -1) // si el segundo punto sigue siendo -1, entonces es un lazo
        N[1] = N[0];

    char n1 = letraAscii(N[0] + 65), // les asignamos letras
    n2 = letraAscii(N[1] + 65);

    // insertamos arista de n1 a n2
    insertarArista(n1,n2,peso);

}

// se crea el grafo en si
void grafoFichero(string nombreArchivo)
{
    // el numero de vertices son las filas y las columnas las aristas
    int nVertices = fi, nAristas = co, i = 65;
    
    // cargamos la matriz y lo mostramos
    cargarMatriz(nombreArchivo);
 //   cout<<"Mostrando la matriz: "<<endl;
 //   mostrarMatriz();

    // inserto los vertices por cada fila
    while(i < nVertices + 65)
    {
        insertarVertice(letraAscii(i));
        i++;
    }


    // y por columna insertamos la aritas
    for(int i = 0; i < co; i++)
        porColumna(i);

}

bool esHoja(Vertice *vert)
{
    Arista *ari = vert->ady;
    if(ari == NULL)
        return true;
    return false;
}

void conjuntoFinales(vector<char> &hojas)
{
    Vertice *aux = arbol;
    while(aux != NULL)
    {
        if(esHoja(aux))
            hojas.push_back(aux->nombre);
        aux = aux->sig;
    }
}

void getAristas()
{
    aristas = new int*[co];
    for(int i = 0; i < co; i++)
        aristas[i] = new int[3];   

    Vertice *aux = arbol;
    Arista *ari;
    int i = 0;
    while(aux != NULL)
    {
        ari = aux->ady;
        while(ari != NULL)
        {
            *(*(aristas+i)+0) = numeroAscii(aux->nombre);
            *(*(aristas+i)+1) = numeroAscii(ari->dest->nombre);
            *(*(aristas+i)+2) = ari->peso;
            ari = ari->sig;
            i++; 
        }
        aux = aux->sig;
    }
}

int hallarCaminos(char l)
{
    char orig, dest = l;
    int peso = 0;
    while(orig != 'A')
    {
        for(int i = 0; i < co; i++)
        {
            if(dest == letraAscii(*(*(aristas+i)+1)))
            {
                orig = letraAscii(*(*(aristas+i)+0));
                peso += *(*(aristas+i)+2);
            }
        }
        dest = orig;
    }
    return peso;
}

void hallarCaminoClave(vector<char> hojas, vector<int> & caminos, char & hojaFinal)
{   
    for(auto i = hojas.begin(); i != hojas.end(); i++)
        caminos.push_back(hallarCaminos(*i));

    int mayor = 0, j = 0;
    for(auto i = caminos.begin(); i != caminos.end(); i++, j++)
        if(*i > mayor)
        {
            mayor = *i;
            hojaFinal = hojas[j];
        }

}

int cantVertices(char l)
{
    char orig, dest = l;
    int cantVert = 0;
    while(orig != 'A')
    {
        for(int i = 0; i < co; i++)
        {
            if(dest == letraAscii(*(*(aristas+i)+1)))
            {
                orig = letraAscii(*(*(aristas+i)+0));
                cantVert++;
            }
        }
        dest = orig;
    }
    return cantVert;
}


void construirCamino(char l)
{
    int cantVert = cantVertices(l);
    aristas_camino_clave = new char*[cantVert];
    for(int i = 0; i < cantVert; i++)
        aristas_camino_clave[i] = new char[2];

    char orig, dest = l;
    int j = 0;
    while(orig != 'A')
    {
        for(int i = 0; i < co; i++)
        {
            if(dest == letraAscii(*(*(aristas+i)+1)))
            {
                orig = letraAscii(*(*(aristas+i)+0));
                *(*(aristas_camino_clave+j)+0) = orig;
                *(*(aristas_camino_clave+j)+1) = dest;
                j++;
            }
        }
        dest = orig;
    }
    
}


string instruccionGrafoCaminoClave(char hojaFinal)
{
    construirCamino(hojaFinal);

    Vertice *punt;
    Arista *ari;
    punt = arbol;

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
                texto += "[label = ";
                texto += to_string(ari->peso);
                texto += "]";
                for(int i = 0; i < cantVertices(hojaFinal); i++)
                {   
                    cout<<punt->nombre<<" = "<<*(*(aristas_camino_clave+i)+0)<<" / "<<ari->dest->nombre<<" = "<<*(*(aristas_camino_clave+i)+1)<<endl;
                    if(punt->nombre ==  *(*(aristas_camino_clave+i)+0) && ari->dest->nombre == *(*(aristas_camino_clave+i)+1))
                    {
                        texto += "[color = \"red\"]";
                       // cout<<punt->nombre<<" "<<ari->dest->nombre<<endl;

                    }
                }
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


