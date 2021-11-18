#include<iostream>
using namespace std;

void intercambiar(int *dirNum1, int *dirNum2)
{
    float aux;
    aux = *dirNum1;
    *dirNum1 = *dirNum2;
    *dirNum2 = aux;
}

int main()
{
    int num1 = 1, num2 = 3;
    cout<<"Primer numero: "<<num1<<endl;
    cout<<"Segundo numero: "<<num2<<endl;

    intercambiar(&num1,&num2);
    
    cout<<"Primer numero: "<<num1<<endl;
    cout<<"Segundo numero: "<<num2<<endl;
    


    return 0;
}