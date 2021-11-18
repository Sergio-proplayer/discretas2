#include <iostream>
using namespace std;

int hallarMax(int *dirVec, int nElementos)
{
    int max = 0;

    for(int i = 0; i < nElementos; i++)
        if(*(dirVec+i)>max) // recorrer un arreglo con punteros
            max = *(dirVec+i);

    return max;
}

int main()
{
    const int nElementos = 5;
    int numeros[nElementos] = {1,20,3,4,5};
    cout<<"El mayor es "<<hallarMax(numeros,nElementos)<<endl;

    return 0;
}