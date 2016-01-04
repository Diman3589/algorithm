#include <QtWidgets/QApplication>
#include <iostream>
#include "RBTree.h"

using namespace std;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QGraphicsScene scene;
	QGraphicsView view(&scene);
	RBTree *tree;
	string fn;
	int oper = 0;
	int n = 0;
	cout << "1. Execute task 1" << endl;
	cout << "2. Execute task 2" << endl;
	cout << "3. Execute task 3" << endl;
	cout << "4. Exit" << endl;
	cout << "Choose the operation: ";
	cin >> oper;
	switch (oper) {
	case 1:
		tree = new RBTree;
		tree->init(&scene, &view);
		fn = "task1.txt";
		tree->FillTree(fn);
		if (!tree->CheckTree()) {
			cout << "Red violation!" << endl;
			delete tree;
			break;
		}
		else if (tree->RBAssert(tree->listTree[0]) == -1) {
				cout << "Black height violation!" << endl;
				delete tree;
				break;
			}
		tree->show();
		delete tree;
		break;
	case 2:
		tree = new RBTree;
		tree->init(&scene, &view);
		cout << "Enter count of vertex: ";
		cin >> n;
		tree->BuildTree(n);
		if (tree->RBAssert(tree->listTree[0]) == -1) {
			cout << "Black height violation!" << endl;
			delete tree;
			break;
		}
		tree->show();
		delete tree;
		break;
	case 3:
		tree = new RBTree;
		tree->init(&scene, &view);
		fn = "task3.txt";
		tree->FillBSTree(fn);
		tree->Coloring(tree->listTree[0]);
		if (!tree->CheckTree()) {
			cout << "Red violation!" << endl;
			delete tree;
			break;
		}
		else if (tree->RBAssert(tree->listTree[0]) == -1) {
			cout << "Black height violation!" << endl;
			delete tree;
			break;
		}
		tree->show();
		delete tree;
		break;
	}
	return app.exec();
}
