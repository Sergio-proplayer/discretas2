#include<iostream>
#include<stdlib.h>
using namespace std;

//Creamos el objeto nodo, que contiene el dato y un nodo apuntando al siguiente
struct Nodo{
    int dato;
    Nodo *siguiente;
};


Nodo *lista = NULL; //inicializamos la lista, con valor null

void insertarLista(Nodo *&lista, int n)
{
    Nodo *nuevo_nodo = new Nodo(); // creamos un nuevo ndo
    nuevo_nodo -> dato = n; // el dato del nuevo nodo sera "n"



    // creamos dos auxiliares que nos sirviran mas adelante
    Nodo *aux1 = lista; 
    Nodo *aux2;

    // si queremos insertar un nodo al inicio
    while((aux1 != NULL)&&(aux1 -> dato < n))
    {
        aux2 = aux1;
        aux1 = aux1 -> siguiente;
    }

    if(lista == aux1)
        lista = nuevo_nodo;
    else
        aux2 -> siguiente = nuevo_nodo;
    
    nuevo_nodo -> siguiente = aux1;

    cout<<n<<" insertado a la lista \n";
}

void mostrarLista(Nodo *lista)
{
    Nodo *actual = new Nodo();
    actual = lista;

    while (actual != NULL)
    {
        cout<< actual->dato <<" -> ";
        actual = actual->siguiente;
    }

}



void buscarLista(Nodo *lista, int n)
{
    Nodo *actual = new Nodo();
    actual = lista;
    bool band = false;

    while((actual != NULL)&&(actual->dato <= n))
    {
        if(actual->dato == n)
            band = true;
        
        actual = actual->siguiente;
    }
    if(band)
        cout<<n<<" SI ha sido encontrado en lista"<<endl;
    else
        cout<<n<<" NO ha sido encontrado en lista"<<endl;

}

void eliminarNodo(Nodo *&lista, int n)
{
    // si la lista no esta vacia
    if(lista != NULL)
    {
        Nodo *aux_borrar;
        Nodo *anterior = NULL;
        // aux borrar señalara el primer valor de lista
        aux_borrar = lista;

        // recorrer la lista
        while((aux_borrar != NULL)&&(aux_borrar->dato != n))
        {
            anterior = aux_borrar;
            aux_borrar = aux_borrar->siguiente;
        }

        // el elemento no fue encontrado
        if(aux_borrar == NULL)
            cout<<"El elemento no ha sido encontrado"<<endl;
        
        // el primer elemento es el que vamos a eliminar
        else if(anterior == NULL)
        {
            lista = lista->siguiente;
            delete aux_borrar;
        }

        // el elemento a borrar no es el primer nodo
        else
        {
            anterior->siguiente = aux_borrar->siguiente;
            delete aux_borrar;
        }
    }
}

// vaciar la lista
void eliminarLista(Nodo *&lista, int &n)
{
    Nodo *aux = lista;
    n = aux->dato;
    lista = aux->siguiente;
    delete aux;
}

void menu()
{
    int opcion, dato;
    do{
        cout<<"\t :MENU: \n";
        cout<<"1. Insertar datos\n";
        cout<<"2. Mostrar datos\n";
        cout<<"3. Buscar elemento en lista\n";
        cout<<"4. Eliminar un nodo\n";
        cout<<"5. Eliminar toda la lista\n";
        cout<<"6. Salir\n";
        cout<<"Opcion: ";cin>>opcion;

        switch (opcion)
        {
        case 1: cout<<"Digite un numero ";cin>>dato;
                insertarLista(lista,dato);
                system("pause");
            break;
        case 2: cout<<"Mostrando datos \n";
                mostrarLista(lista);
                system("pause");
            break;
        case 3: cout<<"Elemento a buscar ";cin>>dato;
                buscarLista(lista,dato);
                system("pause");
            break;
        case 4: cout<<"Elemento a eliminar ";cin>>dato;
                eliminarNodo(lista,dato);
                system("pause");
            break;
        case 5: cout<<"Vaciando la lista..."<<endl;
                while(lista != NULL)
                    eliminarLista(lista,dato);
                system("pause");
            break;
        }
    system("cls");
    }while(opcion != 6);
}

int main()
{
    menu();

    return 0;
}