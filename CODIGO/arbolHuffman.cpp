#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
using namespace std;

// estructura de cada nodo
struct Nodo
{
    int fr; // frecuencia
    char letra;  // letra
    struct Nodo *izq, *der, *sig; // izquierda, derecha, siguiente
};

int Abecedario[26]; // abecedario donde se contara la frecuencia de cada letra

// direccion es el lugar donde se encuentran los archivo, cambiar la direccion para la correcta ejecucion del programa
const char *direccion = "cd UNSA 2DO SEMESTRE\\ESTRUCTURAS DISCRETAS II\\ArchivosCPP\\CODIGO",
    *disco = "d:"; // el disco que  utilizo es el d

// baseDatos, de donde se cuentan las letras, lectura de codigo para leer codigo binario
const string baseDatos = "letras.txt", lecturaDeCodigo = "texto.txt";


// Prototipo de funciones
Nodo *crearNodo(char, int);
char letraAscii(int);
void agregarLista(Nodo *&, Nodo *&);
void cargarLetras(Nodo *&);
void mostrarLista(Nodo *);
void sumarFrecuencia(char);
void leerArchivo(string);
void mostrarArchivo(string);
string copiarTexto(string);
void eliminarNodo(Nodo *&, Nodo *&); 
void juntarNodos(Nodo *&, Nodo *&, Nodo *&);
void mostrarArbol(Nodo *, int);
void decodificar(Nodo *, string);
void generarArbol(Nodo *&);
void instrucciones(Nodo *, string & );
void graficar(Nodo *);
void abrirPdf();
bool esBinario(string);
void menu();

int main()
{
    // lista de letras con valor inicial null
    Nodo *lista = NULL; 
    int opc;
    string codigo;

    // leer el archivo y cargar la lista se hace pasivamente
    leerArchivo(baseDatos);
    cargarLetras(lista);

    do{
        menu();
        cout<<"Digite una opcion: ";cin>>opc;
        switch (opc)
        {
            case 1: mostrarArchivo(baseDatos); system("pause"); break;
            case 2: mostrarLista(lista); system("pause"); break;
            case 3: generarArbol(lista); system("pause"); break;
            case 4: 
                graficar(lista);
                abrirPdf();
            system("pause"); break;
            case 5:
                // si es binario se ejecuta la decodificación
                cout<<"Digite un codigo binario: ";
                cin>>codigo;
                if(esBinario(codigo))
                    decodificar(lista,codigo);
                else
                    cout<<"No es un numero binario "<<endl;
                system("pause");
            break;
            case 6:
                cout<<"Leyendo archivo"<<endl;
                codigo = copiarTexto(lecturaDeCodigo);
                if(esBinario(codigo))
                    decodificar(lista,codigo);
                else
                    cout<<"No es un numero binario "<<endl;
            system("pause");
            break;
            case 7: cout<<"Saliendo"<<endl; system("pause"); break;
            default: cout<<"No es una opcion valida"<<endl;system("pause"); break;
        }
        system("cls");
    }while(opc != 7);


    return 0;
}

// crear un nodo
Nodo *crearNodo(char l, int x)
{
    Nodo *nuevoNodo = new Nodo();

    // al inicio solo tiene frecuencia y su letra
    nuevoNodo->fr = x;
    nuevoNodo->letra = l;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    nuevoNodo->sig = NULL;

    return nuevoNodo;
}

// pasar de numero a letra en ascii
char letraAscii(int num)
{
    char letra = num;
    return letra;
}

// agregar nodos a la lista
void agregarLista(Nodo *&lista, Nodo *&nueva_letra)
{
    Nodo *aux1 = lista, *aux2;

    while((aux1 != NULL)&&(aux1 -> fr < nueva_letra->fr))
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

// cargar las letras extraidas desde el archivo
void cargarLetras(Nodo *&lista)
{
    for(int i = 97, j = 0; i <= 122; i++, j++)
        if(Abecedario[j] > 0)
        {
            // creamos y agregamos a la lista
            Nodo *nuevo = crearNodo(letraAscii(i),Abecedario[j]);
            agregarLista(lista,nuevo);
        }
}

// mostrar la lista
void mostrarLista(Nodo *lista)
{
    Nodo *actual = new Nodo();
    actual = lista;

    while (actual != NULL)
    {
        if(actual->fr > 0)
            cout<< actual->letra <<" -> "<< actual->fr<<endl;
        actual = actual->sig;
    }
}

// sumar las frecuencias si coincide con cierta letra
void sumarFrecuencia(char letra)
{
    for(int i = 97, j = 0; i <= 122; i++, j++)
    {
        if(letraAscii(i) == letra)
            Abecedario[j]++;
    }  
}

// leemos el archivo que usamos como base de datos
void leerArchivo(string nombreArchivo)
{
    ifstream archivo;
    string linea;

    archivo.open(nombreArchivo, ios::in);

    while(true)
    {
        archivo >> linea;
    
        // sumamos frecuencia por cada letra
        for(int i = 0; i < linea.length(); i++)
            sumarFrecuencia(linea[i]);
        
        if(archivo.eof()) break;
    }
}

// mostrar lo que se leyo del archivo
void mostrarArchivo(string nombreArchivo)
{
    ifstream archivo;
    string linea;

    archivo.open(nombreArchivo, ios::in);

    while(true)
    {
        archivo >> linea;
        cout<< linea << endl;        
        if(archivo.eof()) break;
    }
}

// devolver el string de lo que se lee de un archivo
string copiarTexto(string nombreArchivo)
{
    ifstream archivo;
    string linea, texto;

    archivo.open(nombreArchivo, ios::in);

    while(true)
    {
        archivo >> linea;
        texto += linea;
        if(archivo.eof()) break;
    }
    return texto;
}

void eliminarNodo(Nodo *&lista, Nodo *&n)
{
    // si la lista no esta vacia
    if(lista != NULL)
    {
        Nodo *aux_borrar;
        Nodo *anterior = NULL;
        // aux borrar señalara el primer valor de lista
        aux_borrar = lista;

        // recorrer la lista
        while((aux_borrar != NULL)&&(aux_borrar != n))
        {
            anterior = aux_borrar;
            aux_borrar = aux_borrar->sig;
        }

        // el elemento no fue encontrado
        if(aux_borrar == NULL)
            return;
        
        // el primer elemento es el que vamos a eliminar
        else if(anterior == NULL)
        {
            lista = lista->sig;
            //delete aux_borrar;
        }

        // el elemento a borrar no es el primer nodo
        else
        {
            anterior->sig = aux_borrar->sig;
            //delete aux_borrar;
        }
    }
}

// juntar los nodos para crear uno nuevo
void juntarNodos(Nodo *&lista, Nodo *&a, Nodo *&b)
{
    Nodo *nuevo = crearNodo('$',a->fr+b->fr);

    // a este nuevo lo asignamos como padre de los otros
    nuevo->izq = a;
    nuevo->der = b;

    // eliminamos los nodos de la lista, mas no se eliminan de la memoria
    eliminarNodo(lista,a);
    eliminarNodo(lista,b);

    // agregamos el nuevo a la lista
    agregarLista(lista,nuevo);

}

// mostramos el arbol
void mostrarArbol(Nodo *arbol, int count)
{
    if(arbol == NULL)
        return;
    else
    {
        mostrarArbol(arbol->der,count+1);
        for(int i = 0; i < count; i++)
            cout<<"    ";
        cout<<arbol->letra<<":"<<arbol->fr<<endl;
        mostrarArbol(arbol->izq,count+1);
    }
}


void decodificar(Nodo *arbol, string codigo)
{
    int i = 0;
    cout<<endl;
    while(i < codigo.length())
    {
        Nodo *aux = arbol;
        while((aux->izq != NULL)||(aux->der != NULL))
        {
            // si es 0 a la izquierda
            if(codigo[i] == '0')
                aux = aux->izq;
            // si es 1 a la derecha
            else if(codigo[i] == '1')
                aux = aux->der;
            i++;
        }
        cout<<aux->letra;
    }
    cout<<endl;
}


void generarArbol(Nodo *&lista)
{
    // generamos el arbol a partir de juntar los dos nodos menores
    while(lista->sig != NULL) // si el siguiente es null estonces no hay mas nodos que juntar
    {
        Nodo *aux = lista;
        juntarNodos(lista,aux,aux->sig);
        cout<<endl;
        mostrarLista(lista);
    }

    cout<<endl<<endl;
    mostrarArbol(lista,0);
}

// instrucciones para generar el grafo en graphviz
void instrucciones(Nodo *arbol, string &t)
{

    if(arbol == NULL)
        return;
    else
    {
        if(arbol->izq != NULL)
        {
            t+= to_string(arbol->fr); 
            t+=" -- ";
            t+= to_string(arbol->izq->fr);
            t+= ";\n";
            // usamos recursion a la izquierda
            instrucciones(arbol->izq,t);
        }
        if(arbol->der != NULL)
        {
            t+= to_string(arbol->fr);
            t+=" -- ";
            t+= to_string(arbol->der->fr);
            t+= ";\n";
            // usamos recursion a la derecha
            instrucciones(arbol->der,t);
        }
        
    }
}

void graficar(Nodo *arbol)
{
    ofstream archivo;
    archivo.open("huffman.txt",ios::out);

    if(archivo.fail())
    {
        cout<<"Ocurrio un error";
        exit(1);
    }

    string t = "";
    t += "graph A {\n";
    // tomamos el texto generado en instrucciones
    instrucciones(arbol,t);
    t += "\n}";

    archivo<<t;
    archivo.close();

    // compilamos desde el programa
    system("dot -Tpdf huffman.txt -o huffman.pdf");
}

void abrirPdf()
{
    // abirmos dependiendo de la direccion
    system(disco);
    system(direccion);
    system("huffman.pdf");
}

// funcion para determinar si lo que se leyó es un codigo binario
bool esBinario(string texto)
{
    bool band = true;
    for(int i = 0; i < texto.length(); i++)
        if(texto[i] != '0' && texto[i] != '1')
            band = false;
    return band;
}

void menu()
{
    cout<<"1. Mostrar Texto"<<endl;
    cout<<"2. Mostrar Lista"<<endl;
    cout<<"3. Generar Arbol"<<endl;
    cout<<"4. Graficar Arbol"<<endl;
    cout<<"5. Decodificar por teclado"<<endl;
    cout<<"6. Leer un archivo y decodificar"<<endl;
    cout<<"7. Salir"<<endl;

}