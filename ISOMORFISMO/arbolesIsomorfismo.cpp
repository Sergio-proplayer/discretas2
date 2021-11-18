#include <iostream>
#include <ctime>
#include <random>
#include <fstream>

using namespace std;

struct nodo{
    int nro;
    struct nodo *izq, *der;
};

const char *direccion = "cd UNSA 2DO SEMESTRE\\ESTRUCTURAS DISCRETAS II\\ArchivosCPP\\ISOMORFISMO";

bool existe(int, int [], int);
nodo *crearNodo(int);
void insertar(nodo  *&, int);
void preOrden(nodo *);
void crearArbol(nodo *&,int,int);
void crearArbolAleatorio(nodo *&, int);

void instruccionGrafo(nodo *, string &);
void graficarGrafo(string);
void abrirPdf();

bool hojasIguales(nodo *, nodo *);
bool raicesIsomorfas(nodo *, nodo *);
void arbolesIsomorfos(nodo *, nodo *, int &);

int main()
{
    srand(time(0));

    nodo *arbol1 = NULL, *arbol2 = NULL;
    int opc, n;

    cout<<"Numero de vertices: ";
    cin>>n;    
    cout<<"1. Ingresar valores por teclado"<<endl;
    cout<<"2. Crear arboles aleatoriamente"<<endl;
    cout<<"Digite opcion: ";
    cin>>opc;
    switch (opc)
    {
        case 1:
            crearArbol(arbol1,n,1);
            crearArbol(arbol2,n,2);
        break;
        case 2:
            crearArbolAleatorio(arbol1,n);
            crearArbolAleatorio(arbol2,n);
        break;
        default:
            break;
    
    }

    
    string texto1 = "";
    instruccionGrafo(arbol1,texto1);
    graficarGrafo(texto1);
    abrirPdf();

    string texto2 = "";
    instruccionGrafo(arbol2,texto2);
    graficarGrafo(texto2);
    abrirPdf();
    
    system("cls");

    cout<<"Arbol 1: ";preOrden(arbol1);
    cout << endl;
    
    cout<<"Arbol 2: ";preOrden(arbol2);
    cout << endl;
    

    int c = 0;
    arbolesIsomorfos(arbol1,arbol2, c);

    if(c == n)
        cout<<"Son isomorfos"<<endl;
    else
        cout<<"No son isomorfos"<<endl;

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
    archivo.open("isomorfismo.txt",ios::out);

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
    system("dot -Tpdf isomorfismo.txt -o isomorfismo.pdf");
}

void abrirPdf()
{
    // abrimos el pdf
    system("d:");
    system(direccion);
    system("isomorfismo.pdf");
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

bool hojasIguales(nodo *a, nodo *b)
{
    if(a == NULL && b == NULL)
        return true;
    else if(a != NULL && b != NULL)
        return true;
    return false;
}

bool raicesIsomorfas(nodo *r1, nodo *r2)
{
    if(hojasIguales(r1->izq,r2->izq) && hojasIguales(r1->der,r2->der))
        return true;
    return false;
}

void arbolesIsomorfos(nodo *arbol1, nodo *arbol2, int &count)
{
    if(raicesIsomorfas(arbol1,arbol2))
    {
        count++;
        if(arbol1->izq != NULL)
            arbolesIsomorfos(arbol1->izq,arbol2->izq,count);
        if(arbol2->der != NULL)
            arbolesIsomorfos(arbol1->der,arbol2->der,count);
    }
}
