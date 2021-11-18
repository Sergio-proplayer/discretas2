/*
Crear una matriz cuadrada y mediante un Men� realizar las siguientes opciones:
a) Leer Datos.
b) Modificar Datos.
c) Mostrar Datos.
d) Mostrar la suma de la diagonal principal.
e) Mostrar la suma de la diagonal secundaria.
f) Salir
*/

#include<iostream>
#include<stdlib.h>

using namespace std;

void mostrarMenu()
{
	cout<<"\n***********************MENU***********************"<<endl;
	cout<<"a) Leer Datos."<<endl;
	cout<<"b) Modificar Datos."<<endl;
	cout<<"c) Mostrar Datos."<<endl;
	cout<<"d) Mostrar la suma de la diagonal principal."<<endl;
	cout<<"e) Mostrar la suma de la diagonal secundaria."<<endl;
	cout<<"f) Salir"<<endl;
	cout<<"Escribir 'm' si desea que se muestre el menu de nuevo"<<endl;
	cout<<"\n***************************************************"<<endl;
}

int definirOrden()
{
	cout<<"Comenzemos con definir el orden\n"<<endl;
	int orden;
	cout<<"Orden de la matriz: ";
	cin>>orden;
	cout<<"\n";
	return orden;
}

int leerDatos(int M[100][100], int orden)
{
	cout<<"Leyendo datos\n";
	M[orden][orden];
	for(int i = 0; i < orden; i++)
	{
		for(int j = 0; j < orden; j++)
		{	
			cout<<"Numero posicion ["<<i<<"]["<<j<<"] : ";
			cin>>M[i][j];
		}
	}
	return M[orden][orden];
}

void mostrarDatos(int M[100][100], int orden)
{
	cout<<"\nMostrando datos\n";
	for(int i = 0; i < orden; i++)
	{
		for(int j = 0; j < orden; j++)
		{	
			cout<<M[i][j]<<" ";
		}
		cout<<endl;
	}
}

void modificarDato(int M[100][100], int orden)
{
	cout<<"Ubicacion del dato a reemplazar? \n";
	int i_, j_, newNum;
	cout<<"Fila:"; cin>>i_;
	cout<<"Columna: ",cin>>j_;

	
	if((i_ >= orden)||(j_ >= orden))
	{
		cout<<"La posicion ["<<i_<<"]["<<j_<<"]"<<" no existe en la matriz\n";
		cout<<"Recuerde que el numero de filas y columnas solo van de 0 a "<<orden-1<<endl;
	}else{
	
		cout<<"\nNuevo Numero: ";cin>>newNum;

		cout<<endl<<M[i_][j_]<<" fue cambiado por -> "<<newNum<<endl;
		M[i_][j_] = newNum;
		
		cout<<"La matriz queda asi: \n";
		mostrarDatos(M,orden);
	}
}

void diagonalPrincipal(int M[100][100], int orden)
{	
	int suma = 0;
	int diag[orden];
	
	for(int i = 0; i < orden; i++)
	{	
		suma += M[i][i];
		diag[i] = M[i][i];		
	}
	
	cout<<"Elementos de la diagonal principal son: \n";
	for(int i = 0; i < orden; i++)
	{
		cout<<diag[i]<<" ";
	}
	
	cout<<"y su suma es "<<suma<<endl;
}

void diagonalSecundaria(int M[100][100], int orden)
{	
	int suma = 0;
	int diag[orden];
	
	for(int i = 0; i < orden; i++)
	{
		for(int j = 0; j < orden; j++)
		{	
			if(i + j == orden - 1)
			{
				suma += M[i][j];
				diag[i] = M[i][j];
			}
		}
	}
	cout<<"Elementos de la diagonal secundaria son: \n";
	for(int i = 0; i < orden; i++)
	{
		cout<<diag[i]<<" ";
	}
	
	cout<<"y su suma es "<<suma<<endl;
}


int main()
{
	int M[100][100];
	int orden;
	
	mostrarMenu();

	char opcion;
	cout<<"\nOpcion: ";cin>>opcion;cout<<endl;
	
	if(opcion != 'f')
	{
		orden = definirOrden();
		do{
			switch(opcion)
			{
				case 'a': leerDatos(M,orden);break;
				case 'b': modificarDato(M,orden);break;
		 		case 'c': mostrarDatos(M,orden);break;
				case 'd': diagonalPrincipal(M, orden);break;
				case 'e': diagonalSecundaria(M, orden);break;
				case 'm': mostrarMenu();break;
			}
		
			cout<<"\nOpcion: ";cin>>opcion;cout<<endl;
			
		}while(opcion != 'f');
	
	}
	system("pause");
	return 0;
}



