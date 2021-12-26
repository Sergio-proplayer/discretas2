#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;

// datos a cambiar de ser necesario
const char *direccion = "cd UNSA 2DO SEMESTRE\\ESTRUCTURAS DISCRETAS II\\ArchivosCPP\\PROYECTO";
const string archivoMatriz = "matrizejemplo.txt";

// matriz dinamica para guardar datos en caso de leer un archivp
float **puntero_matriz;
// filas y columnas de la matriz dinamica
int fi, co;

// matriz para alamacenar los datos de las aristas
float **aristas;
// las aristas del camino clave encontrado
int **aristas_camino_clave;


// las estructuras para la arita y el vertice
struct Arista;

struct Vertice{
    int nombre;
    Vertice *sig;
    Arista *ady;
};

struct Arista{
    Vertice *dest;
    Arista *sig;
    float peso;
};

// el vertice principal o el primero, al que llamaremos grafo
Vertice *arbol = NULL;

// prototipos de funciones

void insertarVertice(int);
void agregarArista(Vertice *&, Vertice *&, Arista *&);
void insertarArista(int, int);
string instruccionGrafo();
void graficarGrafo(string);
void abrirPdf();
int funcionInternos(int);
void datosMatriz(string);
void cargarMatriz(string);
void mostrarMatriz();
void grafoFichero(string);

bool esHoja(Vertice *);
void conjuntoFinales(vector<int>&);
void getAristas();
float hallarCaminos(int);
void hallarCaminoClave(vector<int>, vector<float>&, int &);
int cantVertices(int);
void construirCamino(int);
string instruccionGrafoCaminoClave(int);

int posColumna(int , bool []);
bool columnasTomadas(bool []);
void unirNodos(int &, bool [], vector<int> &);
int cantHijos(int,bool []);

int main()
{
    // vector para guardar los nodos finales u hojas
    vector<int> hojas;
    // vector para guardar el peso acumulado desde el nodo inicial hacia las hojas
    vector<float> caminos;
    // hojas final a encontrar
    int hojaFinal;

    // sumamos cuantas filas y columnas tiene la matriz
    datosMatriz(archivoMatriz);
    // usando los datos de la matriz formamos el arbol o grafo
    grafoFichero(archivoMatriz);
    //mostrarMatriz();
    
    // usando el arbol, generamos unas instrucciones para graficar en graphviz
    string instrucciones  = instruccionGrafo();
    graficarGrafo(instrucciones);
    system("cls");
    abrirPdf();

    // en el vector hojas, almacenamos los nodos finales    
    conjuntoFinales(hojas);
    // tomamos los pares de las aristas en un arreglo
    getAristas();

    // tomando en cuenta las hojas, y los caminos, llegamos a saber cual es la hoja final    
    hallarCaminoClave(hojas,caminos,hojaFinal);
    cout<<cantVertices(hojaFinal)<<endl;
    
    // utilizando la hoja final, generamos una segunda instruccion, resaltando el camino clave
    string segundaInstruccion = instruccionGrafoCaminoClave(hojaFinal);
    system("cls");
    graficarGrafo(segundaInstruccion);
    abrirPdf();

    // liberamos memoria
    for(int i = 0; i < fi; i++)
		delete [] puntero_matriz[i];
	delete [] puntero_matriz;
    
    for(int i = 0; i < cantVertices(hojaFinal); i++)
        delete [] aristas_camino_clave[i];
    delete [] aristas_camino_clave;

    for(int i = 0; i < co; i++)
        delete [] aristas[i];
    delete [] aristas;

    Vertice *aux;
    Arista *ari;
    while(arbol != NULL)
    {
        while(arbol->ady != NULL)
        { 
            ari = arbol->ady;
            arbol->ady = arbol->ady->sig;
            delete ari;
        }
        aux = arbol;
        arbol = arbol->sig;
        delete aux;
    }

    return 0;
}

void datosMatriz(string nombreArchivo)
{
    // dinamicamente averiguamos cuales son el numero de filas y columnas
    ifstream archivo;
    string texto, linea;

    archivo.open(nombreArchivo);

    int filas = 0, column = 0;
    while(getline(archivo,linea))
    {
        for(int i = 0; i < linea.length(); i++)
            if(linea[i] == '\t') // cada tabulacion es una columna
                column++;
        filas++;
    }

    column /= filas; 
    archivo.close();
    
    fi = filas;
    co = column;
}

void cargarMatriz(string nombreArchivo)
{
    //reservamos memoria en un puntero
    puntero_matriz = new float*[fi];
    for(int i = 0; i < fi; i++)
        puntero_matriz[i] = new float[co];

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

void insertarVertice(int nombre)
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

void insertarArista(int orig, int dest, float peso)
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
                texto += to_string(punt->nombre);
                texto += " -- ";
                texto += to_string(ari->dest->nombre);
                texto += "[label = ";
                stringstream ss;
                ss<<ari->peso;
                string str = ss.str();
                texto += str;
                texto += "]";
                texto += ";\n"; 
                ari = ari->sig;
            }
        }
        // sino solo imprimimos el vertice
        else
        {
            texto += "\t";
            texto += to_string(punt->nombre);
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

// se crea el grafo en si
void grafoFichero(string nombreArchivo)
{
    // el numero de vertices son las filas y las columnas las aristas
    int nVertices = fi, nAristas = co, i = 0;
    
    // cargamos la matriz y lo mostramos
    cargarMatriz(nombreArchivo);
    // inserto los vertices por cada fila
    while(i < nVertices)
    {
        insertarVertice(i+1);
        i++;
    }

    // vector de booleanos para contabilizar columnas tomadas
    bool columnas[co];
    for(int i = 0; i < co; i++)
        columnas[i] = false;

    int posNodo = 0; // comenzamos con el primer nodo
    vector<int> anteriores;
    while(columnasTomadas(columnas) == false)
        unirNodos(posNodo,columnas,anteriores);
}

// posNodo = la fila donde se encuentra el nodo
void unirNodos(int &  posNodo, bool columnas[], vector<int> & anteriores)
{
    // la columna donde se encuentra el nodo
    int column = posColumna(posNodo,columnas);

    if(column != -1)
    {
        columnas[column] = true;
        int sigNodo;
        float peso;

        for(int i = 0; i < fi; i++)
            if(puntero_matriz[i][column] > 0 && i != posNodo)
            {
                peso = puntero_matriz[i][column];
                sigNodo = i;
            }

        insertarArista(posNodo+1,sigNodo+1,peso);
        anteriores.push_back(posNodo);
        posNodo = sigNodo;
    }
    else{
        int lenght = anteriores.size();
        while(lenght > 0){
            int val = anteriores[lenght-1];
            if(cantHijos(val,columnas) > 0)
                posNodo = val;

            lenght--;
        }
    }
}

// cantidad de hijos que aun le queda al nodo
int cantHijos(int n, bool columnas[])
{
    int count = 0;
    for(int i = 0; i < co; i++)
        if(columnas[i] == false && puntero_matriz[n][i] > 0)
            count++;
    return count;
}

// retorna la columna en la que el nodo tenga alguna arista
int posColumna(int fila, bool columnas[])
{
    for(int i = 0; i < co; i++)
        if(columnas[i] == false && puntero_matriz[fila][i] > 0)
            return i;
    return -1;
}

// si todas las columnas fueron tomadas o no
bool columnasTomadas(bool columnas[])
{
    for(int i = 0; i < co; i++)
        if(columnas[i] == false)
            return false;
    return true;
}

// si no tiene hijos, entonces es hoja
bool esHoja(Vertice *vert)
{
    Arista *ari = vert->ady;
    if(ari == NULL)
        return true;
    return false;
}

//  el vector que guarda los conjunto finales
void conjuntoFinales(vector<int> &hojas)
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
    aristas = new float*[co];
    for(int i = 0; i < co; i++)
        aristas[i] = new float[3];   

    Vertice *aux = arbol;
    Arista *ari;
    int i = 0;
    while(aux != NULL)
    {
        ari = aux->ady;
        while(ari != NULL)
        {   
            *(*(aristas+i)+0) = aux->nombre; // padre
            *(*(aristas+i)+1) = ari->dest->nombre; // hijo
            *(*(aristas+i)+2) = ari->peso; // peso
            ari = ari->sig;
            i++; 
        }
        aux = aux->sig;
    }
}

float hallarCaminos(int l)
{
    int orig, dest = l;
    float peso = 0;
    while(orig != 1) // el programa se ejecuta hasta llegar al primer nodo
    {
        for(int i = 0; i < co; i++)
        {
            if(dest == *(*(aristas+i)+1)) 
            {
                orig = *(*(aristas+i)+0);
                peso += *(*(aristas+i)+2); // sumamos los pesos
            }
        }
        dest = orig; // el destino ahora es el origen
    }
    
    return peso;
}

void hallarCaminoClave(vector<int> hojas, vector<float> & caminos, int & hojaFinal)
{   
    for(auto i = hojas.begin(); i != hojas.end(); i++)
        caminos.push_back(hallarCaminos(*i)); // buscamos los pesos totales desde el punto inicial hasta cada nodo final

    // buscamos el mayor
    float mayor = 0;
    int j = 0;
    for(auto i = caminos.begin(); i != caminos.end(); i++, j++)
        if(*i > mayor)
        {
            mayor = *i;
            hojaFinal = hojas[j]; // la hoja final sera el camino de mayor peso
        }    

}

// cantidad de vertices del camino clave
int cantVertices(int l)
{
    int orig, dest = l;
    int cantVert = 0;
    while(orig != 1)
    {
        for(int i = 0; i < co; i++)
        {
            if(dest == *(*(aristas+i)+1))
            {
                orig = *(*(aristas+i)+0);
                cantVert++;
            }
        }
        dest = orig;
    }
    return cantVert;
}

// construimos el camino clave, y lo guardamos en una matriz
void construirCamino(int l)
{
    int cantVert = cantVertices(l);
    aristas_camino_clave = new int*[cantVert];
    for(int i = 0; i < cantVert; i++)
        aristas_camino_clave[i] = new int[2];

    int orig, dest = l;
    int j = 0;
    while(orig != 1)
    {
        for(int i = 0; i < co; i++)
        {
            if(dest == *(*(aristas+i)+1))
            {
                orig = *(*(aristas+i)+0);
                *(*(aristas_camino_clave+j)+0) = orig;
                *(*(aristas_camino_clave+j)+1) = dest;
                j++;
            }
        }
        dest = orig;
    }
    
}


string instruccionGrafoCaminoClave(int hojaFinal)
{
    construirCamino(hojaFinal);
    int longitudCamino = cantVertices(hojaFinal);

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
                texto += to_string(punt->nombre);
                texto += " -- ";
                texto += to_string(ari->dest->nombre);
                texto += "[label = ";
                stringstream ss;
                ss<<ari->peso;
                string str = ss.str();
                texto += str;
                texto += "]";
                for(int i = 0; i < longitudCamino; i++)
                    if(punt->nombre ==  *(*(aristas_camino_clave+i)+0) && ari->dest->nombre == *(*(aristas_camino_clave+i)+1))
                        texto += "[color = \"red\"]";
                texto += ";\n"; 
                ari = ari->sig;
            }
        }
        // sino solo imprimimos el vertice
        else
        {
            texto += "\t";
            texto += to_string(punt->nombre);
            texto += ";\n";
        }
        punt = punt->sig;
    }

    // retornamos las instrucciones
    return texto;
}
