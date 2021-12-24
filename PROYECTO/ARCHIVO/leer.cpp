#include<iostream>
#include<fstream>

using namespace std;

float **puntero_matriz;
int fi, co;

void datosMatriz(string nombreArchivo)
{
    // dinamicamente averiguamos cuales son el numero de filas y columnas
    ifstream archivo;
    string texto, linea;

    archivo.open(nombreArchivo);

    int filas = 0, column = 0;
    while(getline(archivo,linea))
    {
        for(int i = 0; i < linea.length(); i++)
            if(linea[i] == '\t')
                column++;
        filas++;
    }
    //column = funcionInternos(column);
    column /= filas;
    archivo.close();
    
    fi = filas;
    co = column;
}

void cargarMatriz(string nombreArchivo)
{
    //reservamos memoria en un puntero
    puntero_matriz = new float*[fi];
    for(int i = 0; i < fi; i++)
        puntero_matriz[i] = new float[co];

    ifstream archivo;
    archivo.open(nombreArchivo);

    // comenzamo a guardar los datos del archivo en una matriz dinamica
    for(int i = 0; i < fi; i++)
        for(int  j = 0; j < co; j++)
            archivo>>*(*(puntero_matriz+i)+j);

    archivo.close();
}

void mostrarMatriz()
{
    // mostrar los datos de la matriza
    for(int i = 0; i < fi; i++)
    {
        for(int j = 0; j < co; j++)
            cout<<*(*(puntero_matriz+i)+j)<<" ";
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
    datosMatriz("MatrizIncidencia.txt");
    cout<<fi<<" "<<co<<endl;
    cargarMatriz("MatrizIncidencia.txt");
    mostrarMatriz();

    return 0;
}