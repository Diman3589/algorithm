#include "stdafx.h"
#include "Tree.h"
#include <algorithm>

Tree::Tree() {
	;
}

Tree::~Tree() {
	Node *node;
	for (auto it = listTree.begin(); it != listTree.end(); it++) {
		node = it[0];
		delete node;
		node = NULL;
	}
}

string Tree::ReadFile() {
	ifstream fin("aboutTree.txt", ifstream::in);
	string line;
	string content;

	while (getline(fin, line)) {
		content += line;
		content += "\n";
	}
	fin.close();
	return content;
}

void Tree::FillTree() {
	
	string content = ReadFile();
	char ch;
	string number;
	bool flag = false;
	Node *root = new Node;
	root->left = NULL;
	root->right = NULL;
	for (int i = 0, ch = content[i]; ch != 0; i++) {
		ch = content[i];
		while (ch != '\n' && ch != 0) {
			if (ch == 'r' && !flag) {
				root->parent = NULL;
				i++;
				ch = content[i];
				
			}
			if (ch == 'r') {
				i++;
				ch = content[i];
			}			
			while (ch != 'r' && ch != 'b') {
				number += ch;
				i++;
				ch = content[i];
			}

			if (flag) {
				for (auto it = listTree.begin(); it != listTree.end(); it++) {
					if (it[0]->data.key == stoi(number)) {
						root = new Node;
						root = it[0];
						number = "";
						break;
					}
				}
				goto next_node;
			}
			root->data.key = stoi(number);
			number = "";
			if (ch == 'r')
				root->data.color = false;
			else if (ch == 'b')
				root->data.color = true;
			next_node:
			while (ch < '0' || ch > '9') {
				i++;
				ch = content[i];
			}
			while (ch != 'r' && ch != 'b') {
				number += ch;
				i++;
				ch = content[i];
			}
			Node *node = new Node;
			node->left = NULL;
			node->right = NULL;
			node->data.key = stoi(number);
			number = "";
			if (ch == 'r')
				node->data.color = false;
			else if (ch == 'b')
				node->data.color = true;
			if (node->data.key > root->data.key)
				root->right = node;
			else 
				root->left = node;
			node->parent = root;
			if (!flag)
				listTree.push_back(root);
			listTree.push_back(node);
			flag = true;
			i++;
			ch = content[i];
		}
	}
}

bool Tree::CheckTree() {
	bool check;
	for (auto &it : listTree) {
		if (it->left != NULL && it->right != NULL) {
			if (!it->data.color)
				if(it->left->data.color && it->right->data.color)
					check = true;
			else {
				check = false;
				return check;
			}
		}
		else if (it->left == NULL && it->right != NULL) {
			if (!it->data.color)
				if(!it->right->data.color) {
					check = false;
					return check;
				}
		}
		else if (it->right == NULL && it->left != NULL) {if (!it->data.color)
				if (!it->left->data.color) {
					check = false;
					return check;
				}
		}
		else
		if (it->right == NULL && it->left == NULL){
			check = true;
		}
	}
	return check;
}

int Tree::is_red(Node *root) {
	return root != NULL && root->data.color == false;
}

int Tree::rb_assert(Node *root) {
	int lh, rh;
	if (root == NULL) {
		
		return 1;
	}
	else {
		Node *ln = root->left;
		Node *rn = root->right;
		int j = 0;
		if (ln != NULL && !ln->parent->data.color && ln->parent->right == NULL)
			j = 1;
		else if (rn != NULL && !rn->parent->data.color && rn->parent->left == NULL)
				k = 1;
		lh = rb_assert(ln) + k;
		if (k == 1)
			k = 0;
		rh = rb_assert(rn) + j;
		
		/* Black height mismatch */
		if (lh != 0 && rh != 0 && lh != rh ) {
			cout << "Black height violation!" << endl;
			return 0;
		}
		/* Only count black links */
		if (lh != 0 && rh != 0)
			return is_red(root) ? lh : lh + 1;
		else
			return 0;
	}
}

void Tree::BuildTree(int &n) {

}

//void Tree::ShowTree() {
//	for (auto it = listTree.begin(); it != listTree.end(); it++) {
//		cout << it[0]->data.key << " " << it[0]->data.color << "left: " << it[0]->left->data.key << " right: " << it[0]->right->data.key << endl;
//	}
//}