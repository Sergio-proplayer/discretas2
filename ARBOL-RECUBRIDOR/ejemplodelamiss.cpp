#include <fstream>
#include <iostream>
using namespace std;

void ceros(int **Ma, int fi,int co)
{
	for(int i=0; i<fi;i++)
	   for(int j=0; j<co;j++)
			Ma[i][j]=0;
}


void leer(int **Ma, int fi,int co)
{	
	cout<<"Llenando la matriz con un camino básico "<<endl;
	for(int i=0; i<(fi-1);i++)
	{
		Ma[i][i+1]=1;
		Ma[i+1][i]=1;
	}	

    // n ee el numero de aristas como maximo que podemos aumentar al grafo
	int n=((fi*(fi-1))/2)-(fi-1);
	int *v = new int[n];
	
	cout << endl;
	cout << "tamano del vector " << n << endl;
	
	//esquina superior derecha
	int k=0;
	for(int i=0;i<fi;i++)
		for(int j=(i+2);j<co;j++)
			v[k++]=i*fi+j;
	
	//Posiciones del vector
	cout << endl;
/*	for(int i=0;i<n;i++)
		cout << v[i] << "-";
	cout << endl;
*/	
	int r;
	int nf,nc;
	int mod=n;
	int ar;
	
	cout << "Ingrese el numero de arista: ";
	cin >> ar;
	for(int i=0;i<ar;i++)
	{	
		r = rand()%mod;
		nf= v[r]/fi;
		nc= v[r]-(nf*fi);
		Ma[nf][nc]=1;
		Ma[nc][nf]=1;
		//reordenando el vector
		
for(int k=r;k<(n-(i+1));k++)
			v[k]=v[k+1];
		mod--;
	}
	
	delete [] v;
}
void mostrar(int **Ma, int fi,int co)
{	for(int i=0; i<fi;i++)
	{   for(int j=0; j<co;j++)
		{
			cout<<Ma[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main(int argc, char *argv[]) 
{
	int fi, col;
	
	cout << "Ingrese el numero de vertices: ";
	cin >> fi;
	col = fi;
	
	//int matriz[fi][col];
	int **matriz=new int *[fi]; //puntero que apunta a un array de punteros
	for(int i=0; i<fi;i++)
		matriz[i]=new int[col]; 
	
	ceros(matriz, fi, col);
	leer(matriz, fi, col);
	cout<<"Los datos ingresados fueron"<<endl;
	mostrar(matriz, fi, col);
	
	//escribirDOT(matriz, fi, col);
	

	
	for(int i=0;i<fi;i++)
	{
		delete [] matriz[i];
	}
	delete [] matriz;

    return 0;
}