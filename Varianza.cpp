#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

int main()
{
	// {600 , 470 , 170 ,  430 , 300}
	float arr[5];
	float arrVar[5];

	// agregando datos

	for(int i = 0; i < 5; i++)
	{	
		cout<<"num? ";
		cin>>arr[i];
	}	
	
	// media
	float suma = 0;
	for(int i = 0; i < 5; i++)
	{	
		suma += arr[i];
	}	

	cout<<"Suma: "<<suma<<"\n";
	
	float media = suma/5;
	cout<<"Media: "<<media<<"\n";

	//varianza
	float sumaCuadrado = 0;
	for(int i = 0; i < 5; i++)
	{
		arrVar[i] = arr[i] - media;
	}

	for(int i = 0; i < 5; i++)
	{
		sumaCuadrado += pow(arrVar[i],2);
	}
	
	float varianza = sumaCuadrado/5;
	cout<<"Varianza: "<<varianza<<"\n";
	
	// desviacion estandar
	float desviacion = sqrt(varianza);
	cout<<"Desviacion estandar: "<<desviacion<<"\n";
	int aproxDesviacion = round(desviacion);
	cout<<"Redondeando: "<<aproxDesviacion<<"\n";
	
	system("pause");
	return 0;

}

