// Algorithm_Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	Tree *tree = new Tree();
	// Task1
	tree->FillTree();
	tree->rb_assert(tree->listTree[0]);
	/*if (tree->CheckTree())
		cout << "It's a red-black tree!" << endl;
	else
		cout << "It isn't red-black tree!" << endl;
	delete tree;*/
	//tree->ShowTree();

	system("pause");
	return 0;
}