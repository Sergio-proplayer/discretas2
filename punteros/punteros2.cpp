#include<iostream>
using namespace std;

int main()
{
    int n, *dir_n;

    cout<<"Digite un numero: ";cin>>n;
    dir_n = &n;

    if(*dir_n % 2 == 0)
        cout<<*dir_n<<" es par"<<endl;
    else
        cout<<*dir_n<<" es impar"<<endl;
    
    cout<<"La posicion de memoria es: "<<dir_n;

    return 0;
}