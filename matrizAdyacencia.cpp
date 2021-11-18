#include <iostream>

// libreria para cargar ficheros
#include <fstream>
using namespace std;


const int fi=6, co=6;
// cargar ficheros
void cargar(int Ma[][co], int fi,int co)
{
    ifstream a; //manejador de la libreria fstream
    a.open("datos2.txt");

    cout<<"Ingrese valores: "<<endl;
    for(int i=0; i<fi;i++)
	    for(int j=0; j<co; j++)
	        a>>Ma[i][j];
}

void mostrar(int Ma[][co], int fi,int co)
{
    for(int i=0; i<fi;i++)
    {
       for(int j=0; j<co;j++)
	        cout<<Ma[i][j]<<" ";
    	cout<<endl;
    }
}


int grado(int Ma[][co],int co, int index)
{
    int s = 0;
    for(int j = 0; j < co; j++)
    {
        s += Ma[index][j];
    } 
    return s;
}

int cantAristas(int Ma[][co], int fi, int co)
{
    int w = 0, z = 0;
    for(int i = 0; i < fi; i++)
    {
        int g = grado(Ma,co,i);
        w += g;
        z += Ma[i][i];
    }
    w /= 2;
    int aristas = w + z;
    return aristas;

}

void gradoYaristas(int Ma[][co], int fi, int co)
{
    cout<<endl;
    for(int i = 0; i < fi; i++)
    {
        int g = grado(Ma,co,i);
        cout<<"El grado del vertice "<<i+1<<" es "<<g<<endl;
    }

    cout<<"\nLa cantidad de aristas es: "<<cantAristas(Ma,fi,co);
}


int matrizAlCuadrado(int Ma[][co], int a, int b)
{
    int efi, eco, r = 0;
    for(int i = 0; i < 4; i ++)
    {
        
        efi = Ma[a][i];
        eco = Ma[i][b];
        r  += eco*efi;

    }

    return r;
}

int main(int argc, char *argv[]) {
	
    
    int matriz[fi][co];

	cargar(matriz, fi, co);
    mostrar(matriz,fi,co);
    gradoYaristas(matriz,fi,co);


    cout<<endl;
    cout<<endl;

    int matriz2[fi][co];
    for(int i=0; i<fi;i++)
    {
       for(int j=0; j<co;j++)
	        matriz2[i][j] =  matrizAlCuadrado(matriz, i, j);
    
    }

    mostrar(matriz2,fi,co);



	return 0;
}