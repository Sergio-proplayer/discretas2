#include<iostream>
#include<fstream>
#include<string.h>
#include<random>
#include<ctime>
#include<vector>
#include<sstream>

using namespace std; 

int mod(int,int);
bool pertenece(char,char []);
char cifrar(char,char [],int);
char desCifrar(char,char [],int);
void escribir(string);
void leer(string, string &);

int posLetra(char [], char);

int main()
{
    // abecedario
    srand(time(0));
    int k = 1+rand()%25;
    char letras[26];
    for(int i = 'a',j = 0; i <= 'z'; i++, j++)
        letras[j] = i;

    
    // mensaje, mensaje cifrado, mensaje para descifrarse
    string msj, cMsj, dMsj;
    leer("texto.txt",msj);
    cMsj = msj;
    cout<<"El mensaje a cifrar: "<<msj<<endl;

    // creando la clave
    string clave;
    leer("clave.txt",clave);
    cout<<"Clave: "<<clave<<endl;
    // aumentando los valores para qu esea iguales a los del mensaje
    if(msj.length() > clave.length())
    {
        string aux = clave;
        int dif = msj.length() - clave.length(),
            j = 0;
        while(dif > 0)
        {
            clave += aux[j];
            j++;
            dif--;
        }
    }

    cout<<"Clave completa: "<<clave<<endl;
    // cifrando
    for(int i = 0; i < cMsj.length(); i++)
    {
        if(pertenece(msj[i],letras))
            cMsj[i] = cifrar(msj[i],letras,posLetra(letras,clave[i]));
    }

    // escribimos el mensaje cifrado en codigo.txt
    escribir(cMsj);
    cout<<"Codigo a descifrar: ";
    cout<<cMsj<<endl;

    dMsj = cMsj;
    for(int i = 0; i < cMsj.length(); i++)
    {
        if(pertenece(cMsj[i],letras))
            dMsj[i] = desCifrar(cMsj[i],letras,posLetra(letras,clave[i]));
    }
    cout<<"Mensaje descifrado: "<<dMsj<<endl;

    return 0;
}

int mod (int a, int b)
{
    if(b < 0) 
        return mod(a, -b);   
    int ret = a % b;
    if(ret < 0)
        ret+=b;
    return ret;
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

char cifrar(char l, char letras[], int k)
{
    int pos;
    for(int i = 0; i < 26; i++)
    {
        if(letras[i] == l)
        {
            pos = i;
            break;
        }
    }

    return letras[mod((pos + k),26)];
}

char desCifrar(char l, char letras[],int k)
{   
    int pos;
    for(int i = 0; i < 26; i++)
    {
        if(letras[i] == l)
        {
            pos = i;
            break;
        }
    }
    
    return letras[mod((pos - k),26)];
}

void escribir(string texto)
{
    ofstream archivo;
    archivo.open("codigo.txt",ios::out);
    archivo<<texto;
    archivo.close();
}

void leer(string nombreArchivo,string &texto)
{
    ifstream archivo;
    archivo.open(nombreArchivo,ios::in);
    while(!archivo.eof())
        getline(archivo,texto);
    archivo.close();
}

int posLetra(char letras[], char l)
{
    for(int i = 0; i < 26; i++)
        if(letras[i] == l)
            return i;
    return -1;
}