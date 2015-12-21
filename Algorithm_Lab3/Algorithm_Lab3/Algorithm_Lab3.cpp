// Algorithm_Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include <iostream>
#include <algorithm>
#include <boost/bind.hpp>

using namespace std;



int main() {
	Tree *tree = new Tree();
	tree->FillTree();
	tree->ShowTree();
	/*auto it = find_if(vect->begin(), vect->end(),
		boost::bind(&Data::key, _1) == n.data.key);
	cout << it[0]->data.key << endl;*/
	//tree->listTree->push_back(Node());
	/*tree->listTree[0].data.key = 5;
	Node *n = new Node;
	n->data.key = 5;
	if (find(tree->listTree->begin(), tree->listTree->end(), n) != tree->listTree->end())
		cout << "find!";
	else
		cout << "not find!";*/

	//
	//Node v;
	//Node v1;
	//Node v2;
	//v.data.key = 5;
	//v.data.color = true;
	//v.left = &v1;
	//v.right = &v2;
	//v.parent = NULL;
	//v1.data.key = 3;
	//v1.data.color = false;
	//v1.parent = &v;
	//v2.data.key = 7;
	//v2.data.color = false;
	//v2.parent = &v;

	//tree->listTree->push_back(&v);
	//tree->listTree->push_back(&v1);
	//tree->listTree->push_back(&v2);
	//
	//delete tree;

	system("pause");
	return 0;
}