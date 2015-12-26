#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Data {
	int key;
	bool color;
};

// узел
struct Node {
	Data data;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
};

// дерево
class Tree {
private:
	int k;
public:
	vector<Node*> listTree;
public:
	void BuildTree(int &n);
	void FillTree();
	bool CheckTree();
	void ShowTree();
	int rb_assert(Node *root);
	int is_red(Node *root);
private:
	string ReadFile();
public:
	Tree();
	~Tree();
};