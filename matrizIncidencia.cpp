#include<iostream>
#include <fstream>
using namespace std;

const int v = 5, a = 7;
// cargar ficheros
void cargar(int Ma[][a], int fi,int co, string fichero)
{
    ifstream a; //manejador de la libreria fstream
    a.open(fichero);

    cout<<"Ingrese valores: "<<endl;
    for(int i=0; i<fi;i++)
	    for(int j=0; j<co; j++)
	        a>>Ma[i][j];
}

void mostrar(int Ma[][a], int fi,int co)
{
    for(int i=0; i<fi;i++)
    {
       for(int j=0; j<co;j++)
	        cout<<Ma[i][j]<<" ";
    	cout<<endl;
    }
}

int grado(int Ma[][a],  int co, int index )
{
    int s = 0;
    for (int i = 0; i < co; i++)
    {
        s += Ma[index][i];
    }
    return s;
}

void gradoPorVertice(int Ma[][a], int fi, int co)
{
    cout<<endl;
    for(int i = 0; i < fi; i++)
        cout<<"El grado del vertice "<<i+1<<" = "<<grado(Ma, co, i)<<endl;
}

void incide(int Ma[][a], int arista, int fi)
{
    int incidencia[2], j = 0;

    for(int i = 0; i < fi; i++)
    {
        if(Ma[i][arista] == 1)
        {
            incidencia[j] = i+1;
            j++;
        }
    }

    cout<<"La arista "<<arista<<" incide en los vertices "<<incidencia[0]<<" y "<<incidencia[1]<<endl;

}

int main()
{
    int matriz[v][a];
    cargar(matriz,v,a,"datos3.txt");
    mostrar(matriz, v, a);
    gradoPorVertice(matriz, v, a);
    
    cout<<endl;
    for(int i = 1; i <= a; i++)
        incide(matriz, i, v);
    
    return 0;
}