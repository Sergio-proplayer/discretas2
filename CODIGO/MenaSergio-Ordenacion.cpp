#include<iostream>
#include<fstream>
using namespace std;

struct letras
{
    char letra;
    int frecuencia;
    struct letras *sig;
};

letras *lista = NULL;
int Abecedario[26];

char letraAscii(int num)
{
    char letra = num;
    return letra;
}


void agregarLetra(letras *&lista, char l, int f)
{
    letras *nueva_letra = new letras();
    nueva_letra->letra = l;
    nueva_letra->frecuencia = f;

    letras *aux1 = lista, *aux2;

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

void cargarLetras()
{
    for(int i = 97, j = 0; i <= 122; i++, j++)
        agregarLetra(lista,letraAscii(i),Abecedario[j]);
}
void mostrarLista(letras *lista)
{
    letras *actual = new letras();
    actual = lista;

    while (actual != NULL)
    {
        if(actual->frecuencia > 0)
            cout<< actual->letra <<" -> "<< actual->frecuencia<<endl;
        actual = actual->sig;
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



int main()
{
    leerArchivo("letras.txt"); // cambiar a la direccion del archivo
    cargarLetras();
    mostrarLista(lista);
    
    return 0;
}