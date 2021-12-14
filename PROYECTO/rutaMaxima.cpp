#include <iostream>
#include <ctime>
#include <random>
#include <fstream>
#include <vector>

using namespace std;

struct nodo{
    int nro;
    struct nodo *izq, *der;
};

const char *direccion = "cd UNSA 2DO SEMESTRE\\ESTRUCTURAS DISCRETAS II\\ArchivosCPP\\ISOMORFISMO",
            *disco = "d:";

bool existe(int, int [], int);
nodo *crearNodo(int);
void insertar(nodo  *&, int);
void preOrden(nodo *);
void crearArbol(nodo *&,int,int);
void crearArbolAleatorio(nodo *&, int);

void instruccionGrafo(nodo *, string &);
void graficarGrafo(string);
void abrirPdf();

void nivel(nodo *&, int &, vector<int> &);
int cantHijos(nodo *);

int main()
{
    srand(time(0));

    nodo *arbol1 = NULL;
    int n = 10;
    
//    crearArbol(arbol1,n,1);    
    crearArbolAleatorio(arbol1,n);
    
    string texto1 = "";
    instruccionGrafo(arbol1,texto1);
    graficarGrafo(texto1);
    abrirPdf();
    
    int contador = 0;
    nodo *aux = arbol1;
    vector<int> camino;
    nivel(aux,contador,camino);
    cout<<contador<<endl;
    for(auto i = camino.begin(); i != camino.end(); i++)
        cout<<*i<<" ";
    return 0;
}


// graficar el grafo con graphvis
void instruccionGrafo(nodo *punt, string &texto)
{    
    texto +=  to_string(punt->nro);
    texto += "[label = \"<f0> | <f1>";
    texto +=  to_string(punt->nro);
    texto += " |<f2> \"];\n";

    if(punt->izq != NULL)
    {
        texto += to_string(punt->nro);
        texto += ":f0:sw -- ";    
        texto += to_string(punt->izq->nro);
        texto += ":f1;\n";
        instruccionGrafo(punt->izq, texto);
    }

    if(punt->der != NULL)
    {
        texto += to_string(punt->nro);
        texto += ":f2:se -- ";    
        texto += to_string(punt->der->nro);
        texto += ":f1;\n";
        instruccionGrafo(punt->der, texto);
    }
}

void graficarGrafo(string texto)
{
    // creamos un archivo
    ofstream archivo;
    archivo.open("tree.txt",ios::out);

    // si falla
    if(archivo.fail())
    {
        cout<<"Ocurrio un error";
        exit(1);
    }

    // sino creamos con las instrucciones
    archivo<<"graph A {\n"
    << "node[shape = record];\n"
    <<texto
    <<"}";

    // lo creamos en formato pdf
    archivo.close();
    system("dot -Tpdf tree.txt -o tree.pdf");
}

void abrirPdf()
{
    // abrimos el pdf
    system(disco);
    system(direccion);
    system("tree.pdf");
}


bool existe(int x, int numeros[],int index)
{
    for(int i = 0; i < index; i++)
        if(numeros[i] == x)
            return true;
    return false;
}


nodo *crearNodo(int x)
{
    nodo *nuevoNodo = new(struct nodo);
    nuevoNodo->nro = x;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;

    return nuevoNodo;
}

void insertar(nodo *&arbol,int x)
{
    if(arbol==NULL)
        arbol = crearNodo(x);
    else if(x < arbol->nro)
        insertar(arbol->izq, x);
    else if(x > arbol->nro)
        insertar(arbol->der, x);   
}

void preOrden(nodo *arbol)
{
    if(arbol!=NULL)
    {
        cout << arbol->nro <<" ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

void crearArbol(nodo *&arbol, int n, int nro)
{
    int numeros[n], i = 0, x;
    cout<<endl<<"Arbol: "<<nro<<endl;
    while(i < n)
    {
        cout<<"Num: ";cin>>x;
        if(existe(x,numeros,i) == false)
        {
            insertar(arbol,x);
            numeros[i] = x;
            i++;
        }
    }
}

void crearArbolAleatorio(nodo *&arbol, int n)
{
    int numeros[n], i = 0, x;
    while(i < n)
    {
        x = 1+rand()%(10+n);
        if(existe(x,numeros,i) == false)
        {
            insertar(arbol,x);
            numeros[i] = x;
            i++;
        }
    }
}

int cantHijos(nodo *rama)
{
    if(rama == NULL)
        return -1;
    int c = 0;
    if(rama->izq != NULL)
        c++;
    if(rama->der != NULL)
        c++;
    return c;
}   

void nivel(nodo *&aux, int &contador,vector<int> &camino)
{
    if(aux != NULL)
    {
        int cIzq = cantHijos(aux->izq),
        cDer = cantHijos(aux->der);

        contador++;

        //cout<<"Nivel "<<contador<<endl;   
        //cout<<aux->nro<<" izq = "<<cIzq<<" der = "<<cDer<<endl;
        camino.push_back(aux->nro);
        if(cIzq >= cDer)
        {
            aux = aux->izq;
        }
        else
        {
            aux = aux->der;
        }
        nivel(aux,contador,camino);
    }
}