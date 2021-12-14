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
void leer(string &);

void guardarDiccionario(string [], int);
bool coincide(string,string [],int);

int main()
{
    // abecedario
    srand(time(0));
    int k = 1+rand()%25;
    char letras[26];
    for(int i = 'a',j = 0; i <= 'z'; i++, j++)
        letras[j] = i;

    // diccionario
    int size = 12;
    string diccionario[size];
    guardarDiccionario(diccionario,size);

    // mensaje, mensaje cifrado, mensaje para descifrarse
    string msj, cMsj, dMsj;
    leer(msj);
    cMsj = msj;

    // cifrando
    for(int i = 0; i < cMsj.length(); i++)
        if(pertenece(msj[i],letras))
            cMsj[i] = cifrar(msj[i],letras,k);

    // escribimos el mensaje cifrado en codigo.txt
    escribir(cMsj);
    cout<<"Codigo a descifrar"<<endl;
    cout<<cMsj<<endl;


    // el mensaje a descifrar toma primero el valor del mensaje cifrado
    dMsj = cMsj; 
    int kPrueba = 1; // la primera llave a probar sera 1

    // descifrando
    while (kPrueba <= 25)
    {
        for(int i = 0; i < cMsj.length(); i++)
            if(pertenece(cMsj[i],letras))
                dMsj[i] = desCifrar(cMsj[i],letras,kPrueba);


        cout<<endl<<"Probando con llave "<<kPrueba<<endl;
        cout<<dMsj<<endl;

        // si el mensaje descifrado coincide con alguna palabra del diccionario
        if(coincide(dMsj,diccionario,size))  
            break;

        kPrueba++;
    }

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

void leer(string &texto)
{
    ifstream archivo;
    archivo.open("texto.txt",ios::in);
    while(!archivo.eof())
        getline(archivo,texto);
    archivo.close();
}

void guardarDiccionario(string diccionario[], int size)
{
    ifstream archivo;
    archivo.open("diccionario.txt",ios::in);
    for(int i = 0; i < size; i++)
        archivo>>diccionario[i];        
    archivo.close();
}

bool coincide(string texto, string diccionario[], int size)
{
    istringstream split(texto);
    vector<string> mensaje;
    for(string each ; getline(split,each,' ') ; mensaje.push_back(each));

    for(auto i = mensaje.begin(); i != mensaje.end(); i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(*i == diccionario[j])
                return true;
        }
    }
    return false;
}