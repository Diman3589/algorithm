// Algorithm_Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	Tree *task1 = new Tree();
	// Task1
	task1->FillTree();
	if (task1->CheckTree())
		task1->rb_assert(task1->listTree[0]);
	else cout << "Red violation" << endl;
	/*if (tree->CheckTree())
		cout << "It's a red-black tree!" << endl;
	else
		cout << "It isn't red-black tree!" << endl;
	delete tree;*/
	//tree->ShowTree();

	system("pause");
	return 0;
}