#include<iostream>
#include<stdlib.h>
#include<fstream>

using namespace std;

void escribir()
{
    ofstream archivo;
    archivo.open("grap.txt",ios::out);

    if(archivo.fail())
    {
        cout<<"Ocurrio un error";
        exit(1);
    }
    

    archivo<<"graph A {\n"
    <<"\t"
    <<"}";


    archivo.close();
}

int main()
{
    escribir();
    return 0;
}