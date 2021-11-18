#include<iostream>
using namespace std;

int main()
{
    int numeros[] = {1,2,3,4,5} , *dir_numeros;
    dir_numeros = numeros; // es igual a : dir_numeros = &numeros[0];

    for(int i = 0; i < 5; i++)
    //comenzamos a aumento la dir_numeros pues los valores de la matriz estan juntos
        cout<<"Elemento del vector ["<<i<<"]: "<<*dir_numeros++<<endl;


    return 0;
}