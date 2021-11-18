#include<iostream>
using namespace std;

int main()
{
    int num = 20, *dir_num; // dir_num es un puntero
    // toda &variable es la direccion de memoria de la variable
    dir_num = &num; // este puntero apunta a la vairable num

    cout<<"Numero: "<<*dir_num<<endl; // imprime a dodnde apunta, el 20
    cout<<"Direcciond de mem: "<<dir_num<<endl; // imprime el espacion de memoria

    return 0;
}