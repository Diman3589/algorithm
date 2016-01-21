#pragma once
#include <iostream>
#include <qgraphicsview>
#include <qtextstream>
#include <qprocess>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct Node {
	int key;
	bool color;
	Node *left;
	Node *right;
	Node *parent;
};

class RBTree {

public:
	void init(QGraphicsScene* scene, QGraphicsView* view);
	void show();
	void BuildTree(int n);
	void FillTree(const string &filename);
	void FillBSTree(const string &filename);
	bool CheckTree();
	int RBAssert(Node *root);
	int Coloring(Node *root);
	RBTree();
	~RBTree();
private:
	QByteArray _prepareGraph();
	void _graphWalk(Node* p, QTextStream* stream);
	string ReadFile(const string &filename);
	vector<Node*> CreateLevel(vector<Node*> level, bool color, int &n);
	int GetRandNumb(int numb, bool place);
	void ColoringToRed(int difference, Node *node);
	void InvertColor(Node *node);
	int IsRed(Node *root);
public:
	vector<Node*> listTree;
private:
	QGraphicsScene* _scene;
	QGraphicsView* _view;
	int addition1;
	int addition2;
	set<int> randoms;
};