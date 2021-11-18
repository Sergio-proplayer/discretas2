#include<iostream>
#include<stdlib.h>
using namespace std;


int fibonacci(int n)
{
	int num1 = 1;
	int num2 = 1;
	
	if((n == 1)||(n==2))
	{
		return 1;
	}
	else{
		n = n - 3;
	}
	
	int result = 0;
	result += num1 + num2;
	
	for(int i = 0; i < n; i++)
	{
		num1 = result;
		result = num1 + num2;
		num2 = num1;
	}
	return result;
}
int main()
{
	int r;
	cin>>r;
	
	int arr[r];
	cout<<"Fibonacci hasta la pos("<<r<<") : ";
	
	for(int i = 0; i < r; i++){
		arr[i] = fibonacci(i + 1);
	}
	
	for(int i = 0; i < r; i++){
		cout<<arr[i]<<" ";
	}
	
	cout<<endl;
	cout<<"Multiplos de tres: ";
	int arrMult3[r];
	
	int j = 0;
	
	for(int i = 0; i < r; i++){
		if(arr[i] % 3 == 0){
			arrMult3[j] = arr[i];
			cout<<arrMult3[j]<<" ";
			j += 1;
		}
	}	
	
	cout<<endl;
	cout<<"De manera decreciente: ";
	for(int i = j - 1; i >= 0; i--){
		cout<<arrMult3[i]<<" ";
	}

	cout<<endl;
	
	system("pause");
	return 0;
	
}
