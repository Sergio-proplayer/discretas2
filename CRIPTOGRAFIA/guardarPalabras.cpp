#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

int main()
{
    string palabras[8];
    ifstream archivo;
    archivo.open("diccionario.txt",ios::in);
    for(int i = 0; i < 8; i++)
        archivo>>palabras[i];        

    for(int i = 0; i < 8; i++)
        cout<<palabras[i]<<endl;

    archivo.close();
    return 0;
}