#include<iostream>
#include"Header.h"
#include<math.h>
#include<string>
using namespace std;
int main()
{	
	int i = 0;
	Animal* a[20];
	while (i < 1)
	{
		AddAnimal(a, i);
	}
	cout << "\tChao mung cac ban den voi Nong Trai Allice\n";

	while (true)
	{
		XulyMenu(a, i);
	}
	system("pause");

	return 0;
}