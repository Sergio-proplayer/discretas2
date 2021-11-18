/*
    Se consideró que para este ejercicio
    la matriz de adyacencia sea de 2x3
    puesto que la caracteristica de un 
    grafo bipartito es que los vertices
    de un mismo grupo nunca se enlazaran
    entonces para no mal gastar el
    espacio en memoria es que decidi usar 
    la matriz de 2x3 y no la 6x6
*/

#include<iostream>
#include<fstream>

using namespace std;

// se necesita filas de 2 y columnas de 3
const int fi = 2, co = 3;

void cargarMatriz(string nombreArchivo, int M[][co])
{
    ifstream archivo;
    archivo.open(nombreArchivo);

    for(int i = 0; i < fi; i++)
        for(int  j = 0; j < co; j++)
            archivo>>M[i][j];

    archivo.close();
}

void mostrarMatriz(int M[][co])
{
    for(int i = 0; i < fi; i++)
    {
        for(int j = 0; j < co; j++)
            cout<<M[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void hallaComplemento(int M[][co], int C[][co])
{
    for(int i = 0; i < fi; i++)
    {
        for(int j = 0; j < co; j++)
        {
            if(M[i][j] == 0)
                C[i][j] = 1;
            else if(M[i][j] == 1)
                C[i][j] = 0;
        }
    }

}

int main()
{   

    int M[fi][co], C[fi][co];
    cargarMatriz("ad.txt",M); //puede cambiar el nombre del archivo por cualquier otro
    cout<<"Mostrando matriz K(2,3)"<<endl;
    mostrarMatriz(M);
    hallaComplemento(M,C);
    cout<<"Su complemento es: "<<endl;
    mostrarMatriz(C);

    return 0;
}