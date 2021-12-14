#include<iostream>
#include<fstream>
using namespace std;

void leer(string, string &);
bool pertenece(char, char[]);
int posLetra(char [], char);
void sumarFrecuencias(string,char [],float []);

int main()
{
    char letras[26];
    for(int i = 'a',j = 0; i <= 'z'; i++, j++)
        letras[j] = i;

    float frecuencias[26];
    sumarFrecuencias("frecuencia.txt",letras,frecuencias);

    for(int i = 0; i < 26; i++)
        cout<<frecuencias[i]<<" ";
    
    return 0;
}

void leer(string nombreArchivo, string &texto)
{
    ifstream archivo;
    archivo.open(nombreArchivo,ios::in);
    while(!archivo.eof())
        getline(archivo,texto);
    archivo.close();
}


bool pertenece(char l,char letras[])
{
    for(int i = 0; i < 26; i++)
    {
        if(letras[i] == l)
            return true;
    }
    return false;
}

int posLetra(char letras[], char l)
{
    for(int i = 0; i < 26; i++)
        if(letras[i] == l)
            return i;
    return -1;
}

void sumarFrecuencias(string nombreArchivo, char letras[], float frecuencias[])
{
    string nuevoLetras;
    for(int i = 0; i < 26; i++)
        frecuencias[i] = 0;
        
    leer(nombreArchivo,nuevoLetras);

    int total = 0;
    for(int i = 0; i < nuevoLetras.length(); i++)
    {
        if(pertenece(nuevoLetras[i],letras))
        {
            frecuencias[posLetra(letras,nuevoLetras[i])]++;
            total++;
        }
    }

    for(int i = 0; i < 26; i++)
        frecuencias[i] = (frecuencias[i]*100)/total;
}