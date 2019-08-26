#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{
	AVLtree tree;

	int mas[] = { 2,3,5,8,10,15,13,17,20,20,21,25,30,28 };

	for (int i = sizeof(mas) / sizeof(int) - 1; i >= 0; i--)
		tree.push(mas[i]);

	tree.printTree();

	system("pause");
	return 0;
}