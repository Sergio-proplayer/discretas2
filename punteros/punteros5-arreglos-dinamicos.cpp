#include<iostream>
#include<stdlib.h> // funciona new y delete
using namespace std;

int numCalif, *calif;

void pedirNotas()
{
    cout<<"Digite el numero de calificaciones: ";
    cin>>numCalif;

    calif = new int[numCalif]; // creamos un arreglo dinamico

    for(int i = 0; i < numCalif; i++)
    {
        cout<<"Ingrese una nota ";
        cin>>calif[i];
    }
}

void mostrarNotas()
{
    cout<<"\nMostrando notas\n";
    for(int i = 0; i < numCalif; i++)
        cout<<calif[i]<<endl;
}


int main()
{
 
    pedirNotas();
    mostrarNotas();

    delete[] calif; // liberando espacio, que fue reservado con new

    return 0;
}