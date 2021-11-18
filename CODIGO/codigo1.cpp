#include<iostream>
#include<fstream>
using namespace std;

struct letras
{
    char letra;
    int frecuencia;
    letras *sig;
};

letras Abecedario[26];

char letraAscii(int num)
{
    char letra = num;
    return letra;
}

void cargarLetras()
{
    for(int i = 97, j = 0; i <= 122; i++, j++)
    {
        Abecedario[j].letra = letraAscii(i);
        Abecedario[j].frecuencia = 0;
    }   
}

void sumarFrecuencia(char letra)
{
    for(int i = 97, j = 0; i <= 122; i++, j++)
    {
        if(Abecedario[j].letra == letra)
            Abecedario[j].frecuencia++;
    }  
}

void leerArchivo(string nombreArchivo)
{
    ifstream archivo;
    string linea;
    char letra;


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

void ordenar()
{
    letras temp;
    for(int i = 0; i < 26; i++)
        for(int j = 0; j < 25; j++)
            if(Abecedario[j].frecuencia > Abecedario[j+1].frecuencia)
            {
                temp = Abecedario[j];
                Abecedario[j] = Abecedario[j+1];
                Abecedario[j+1] = temp;
            }
}



void mostrar()
{
    for(int i = 0; i < 26; i++)
    {
        if(Abecedario[i].frecuencia > 0)
            cout<<Abecedario[i].letra<<" -> "<<Abecedario[i].frecuencia<<endl;
    }
}



int main()
{
    cargarLetras();
    leerArchivo("letras.txt");
    ordenar();
    mostrar();
    
    return 0;
}