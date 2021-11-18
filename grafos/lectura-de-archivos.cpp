#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

//puntero para la matriz
int **puntero_matriz;

int funcionInternos(int n)
{
    int cantNum = 0;
    for(int i = 0; i < n; i++)
    {
        if(i % 2 == 0)
            cantNum++;
    }
    return cantNum;
}

void datosMatriz(string nombreArchivo, int &fi, int &co)
{
    ifstream archivo;
    string texto, linea;

    archivo.open(nombreArchivo);

    int filas = 0, column;
    while(getline(archivo,linea))
    {
        column = linea.length();
        filas++;
    }
    column = funcionInternos(column);

    archivo.close();
    
    fi = filas;
    co = column;
}


void cargarMatriz(string nombreArchivo, int fi, int co)
{
    //reservamos memoria en un puntero
    puntero_matriz = new int*[fi];
    for(int i = 0; i < fi; i++)
        puntero_matriz[i] = new int[co];

    ifstream archivo;
    archivo.open(nombreArchivo);

    for(int i = 0; i < fi; i++)
        for(int  j = 0; j < co; j++)
            archivo>>*(*(puntero_matriz+i)+j);

    archivo.close();
}

void porColumna(int fi, int nColumn)
{
    int N[2] = {-1,-1}, w = 0;
    for(int i = 0; i < fi; i++)
    {
        cout<< *(*(puntero_matriz+i)+nColumn);
        if(*(*(puntero_matriz+i)+nColumn) == 1)
        {
            N[w] = i;
            w++;
        }
    }

    if(N[1] == -1)
        N[1] = N[0];

    cout<<" "<<N[0]<<" "<<N[1]<<endl;
}


int main()
{
    int fi, co;
    datosMatriz("texto.txt",fi,co);
    cout<<"Filas = "<<fi<<endl;
    cout<<"Columnas = "<<co<<endl;

    cargarMatriz("texto.txt",fi,co);

/*
    for(int i = 0; i < fi; i++)
    {
        for(int j = 0; j < co; j++)
            cout<<*(*(puntero_matriz+i)+j)<<" ";
        cout<<endl;
    }
*/
    for(int i = 0; i < co; i++)
        porColumna(fi,i);

    for(int i = 0; i < fi; i++)
        delete[] puntero_matriz[i];

    return 0;
}
