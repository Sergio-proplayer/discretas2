#include<iostream>
#include<stdlib.h>

using namespace std;

int cantAristas(int vertices)
{
    int aristas = (vertices*(vertices-1))/2;
    return aristas;
}

int valencia(int vertices)
{
    int val = vertices - 1;
    return val;
}


int main()
{
    int a;
    cout<<"Vertice ";cin>>a;
    int b = cantAristas(a);
    cout<<"Cantidad de Aristas "<<b<<endl;
    int c = valencia(a);
    cout<<"Valencia de las vertices "<<c<<endl;

    system("pause");
    return 0;
}


