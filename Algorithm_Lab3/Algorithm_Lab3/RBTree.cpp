#include "RBTree.h"
#include <ctime>

RBTree::RBTree() {
	addition1 = 1;
	addition2 = 1;
}

RBTree::~RBTree() {
	Node *node;
	for (auto it = listTree.begin(); it != listTree.end(); it++) {
		node = it[0];
		delete node;
		node = NULL;
	}
}

void RBTree::init(QGraphicsScene* scene, QGraphicsView* view) {

	this->_scene = scene;
	this->_view = view;
}

string RBTree::ReadFile(const string &filename) {
	ifstream fin(filename, ifstream::in);
	string line;
	string content;

	while (getline(fin, line)) {
		content += line;
		content += "\n";
	}
	fin.close();
	return content;
}

void RBTree::FillBSTree(const string &filename) {
	string content = ReadFile(filename);
	char ch;
	int i = 0;
	ch = content[i];
	string number;
	Node *root = new Node;
	root->left = NULL;
	root->right = NULL;
	bool flag = false;
	while (ch != 0) {
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


			while (ch < '0' || ch > '9') {
				i++;
				ch = content[i];
			}
			while (ch != '>') {
				number += ch;
				i++;
				ch = content[i];
			}


			if (flag) {
				for (auto it : listTree) {
					if (it->key == stoi(number)) {
						root = new Node;
						root = it;
						number = "";
						break;
					}
				}
				goto next_node;
			}
			root->key = stoi(number);
			number = "";
		next_node:
			while (ch < '0' || ch > '9') {
				i++;
				ch = content[i];
			}
			while (ch != '\n') {
				number += ch;
				i++;
				ch = content[i];
			}
			Node *node = new Node;
			node->left = NULL;
			node->right = NULL;
			node->key = stoi(number);
			number = "";
			if (node->key > root->key)
				root->right = node;
			else
				root->left = node;
			node->parent = root;
			if (!flag)
				listTree.push_back(root);
			listTree.push_back(node);
			flag = true;
			/*i++;
			ch = content[i];*/
		}
		i++;
		ch = content[i];
	}
}

void RBTree::FillTree(const string &filename) {

	string content = ReadFile(filename);
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
				for (auto it : listTree) {
					if (it->key == stoi(number)) {
						root = new Node;
						root = it;
						number = "";
						break;
					}
				}
				goto next_node;
			}
			root->key = stoi(number);
			number = "";
			if (ch == 'r')
				root->color = false;
			else if (ch == 'b')
				root->color = true;
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
			node->key = stoi(number);
			number = "";
			if (ch == 'r')
				node->color = false;
			else if (ch == 'b')
				node->color = true;
			if (node->key > root->key)
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

bool RBTree::CheckTree() {
	bool check;
	for (auto &it : listTree) {
		if (it->left != NULL && it->right != NULL) {
			if (!it->color)
			if (it->left->color && it->right->color)
				check = true;
			else {
				check = false;
				return check;
			}
		}
		else if (it->left == NULL && it->right != NULL) {
			if (!it->color)
			if (!it->right->color) {
				check = false;
				return check;
			}
		}
		else if (it->right == NULL && it->left != NULL) {
			if (!it->color)
			if (!it->left->color) {
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

int RBTree::Coloring(Node *root) {
	int leftH = 0, rightH = 0, length = 0;
	if (root->left != NULL)
		leftH = Coloring(root->left);
	if (root->right != NULL)
		rightH = Coloring(root->right);
	length = leftH;
	if (leftH < rightH) {
		ColoringToRed(rightH - leftH, root->right);
	}
	if (leftH > rightH) {
		ColoringToRed(leftH - rightH, root->left);
	//length = rightH;
	}
	if (root->color) {
		length++;
	}
	return length;
}

void RBTree::ColoringToRed(int difference, Node *node) {
	if (node->parent->color) {
		node->color = false;
		difference -= 1;
	}
	if (node->left && node->right) {
		if (node->left->color == false && node->right->color == true)
			InvertColor(node->left);
		if (node->left->color == true && node->right->color == false)
			InvertColor(node->right);
	}
	if (node->left && difference)
		ColoringToRed(difference, node->left);
	if (node->right && difference)
		ColoringToRed(difference, node->right);
}

void RBTree::InvertColor(Node *node) {
	if (node->color == false)
		node->color = true;
	else if (node->parent->color == true)
		node->color = false;
	if (node->left)
		InvertColor(node->left);
	if (node->right)
		InvertColor(node->right);
}

int RBTree::IsRed(Node *root) {
	return root != NULL && root->color == false;
}

int RBTree::RBAssert(Node *root) {
	int lh, rh;
	if (root == NULL) {
		return 1;
	}
	else {
		Node *ln = root->left;
		Node *rn = root->right;

		lh = RBAssert(ln);
		if (lh == -1)
			return -1;
		rh = RBAssert(rn);
		if (rh == -1)
			return -1;

		/* Black height mismatch */
		if (lh != 0 && rh != 0 && lh != rh) {
			return -1;
		}
		/* Only count black links */
		if (lh != 0 && rh != 0)
			return IsRed(root) ? lh : lh + 1;
		else
			return -1;
	}
}

int RBTree::GetRandNumb(int numb, bool place) {
	
	int random;
	srand(time(NULL));
	random = 50 + rand() % 150;
	if (place) {
		while (randoms.find(random) != randoms.end() || random <= numb) {
			random = 50 + rand() % 150;
			if (numb >= 150 || random == 150) {
				random = 150 + addition1;
				addition1++;
			}
		}
		randoms.insert(random);
		return random;
	}
	if (!place) {
		while (randoms.find(random) != randoms.end() || random >= numb) {
			random = 50 + rand() % 150;
			if (numb <= 50 || random == 50) {
				random = 50 - addition2;
				addition2++;
			}
		}
		randoms.insert(random);
		return random;
	}
}

vector<Node*> RBTree::CreateLevel(vector<Node*> level, bool color, int &n) {
	vector<Node*> newlevel;
	for (auto it : level) {
		if (n > 1) {
			Node *node = new Node;
			Node *node1 = new Node;
			node->color = color;
			node1->color = color;
			node->parent = it;
			node->left = NULL;
			node->right = NULL;
			node->key = GetRandNumb(it->key, false);
			node1->parent = it;
			node1->left = NULL;
			node1->right = NULL;
			node1->key = GetRandNumb(it->key, true);
			it->left = node;
			it->right = node1;
			n -= 2;
			newlevel.push_back(it->left);
			newlevel.push_back(it->right);
		}
		else if (n == 1) {
			Node *node = new Node;
			node->color = color;
			node->parent = it;
			node->left = NULL;
			node->right = NULL;
			node->key = GetRandNumb(it->key, false);
			it->left = node;
			n--;
			newlevel.push_back(it->left);
		}
		else break;
	}
	return newlevel;
}

void RBTree::BuildTree(int n) {
	Node *node = new Node;
	node->color = true;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->key = GetRandNumb(0, true);
	Node* root = node;
	n--;
	vector<Node*> leftLevel;
	vector<Node*> rightLevel;
	//if (n) {
		node = new Node;
		node->color = false;
		node->parent = root;
		node->left = NULL;
		node->right = NULL;
		node->key = GetRandNumb(root->key, true);
		root->right = node;
		n--;
		rightLevel.push_back(root->right);
	//}
	bool color = false;
	while (n > 0) {
		if (color) {
			color = false;
			rightLevel = CreateLevel(rightLevel, false, n);
		}
		else {
			if (n <= 2 && !leftLevel.size()) {
				root->right->color = true;
				n--;
				if (n) {
					Node *node = new Node;
					node->color = false;
					node->parent = root->right;
					node->left = NULL;
					node->right = NULL;
					node->key = GetRandNumb(root->right->key, false);
					root->right->left = node;
				}
				Node *node = new Node;
				node->color = true;
				node->parent = root;
				node->left = NULL;
				node->right = NULL;
				node->key = GetRandNumb(root->key, false);
				root->left = node;
				n--;
			}
			else if (n >= (leftLevel.size() + rightLevel.size()) * 2) {
				if (leftLevel.size())
					leftLevel = CreateLevel(leftLevel, true, n);
				else {
					Node *node = new Node;
					node->color = true;
					node->parent = root;
					node->left = NULL;
					node->right = NULL;
					node->key = GetRandNumb(root->key, false);
					root->left = node;
					n--;
					leftLevel.push_back(root->left);
				}
				rightLevel = CreateLevel(rightLevel, true, n);
			}
			else {
				if (n >= leftLevel.size() * 2) {
					leftLevel = CreateLevel(leftLevel, true, n);
					vector<Node*> newRightLevel;
					for (auto it : rightLevel) {
						it->color = true;
						if (n > 1) {
							Node *node = new Node;
							node->color = false;
							node->parent = it;
							node->left = NULL;
							node->right = NULL;
							node->key = GetRandNumb(it->key, false);
							Node *node1 = new Node;
							node1->color = false;
							node1->parent = it;
							node1->left = NULL;
							node1->right = NULL;
							node1->key = GetRandNumb(it->key, true);
							it->left = node;
							it->right = node1;
							n -= 2;
							newRightLevel.push_back(it->left);
							newRightLevel.push_back(it->right);
						}
						else if (n == 1) {
							Node *node = new Node;
							node->color = false;
							node->parent = it;
							node->left = NULL;
							node->right = NULL;
							node->key = GetRandNumb(it->key, false);
							it->left = node;
							n--;
							newRightLevel.push_back(it->left);
						}
					}
				}
				else {
					CreateLevel(leftLevel, false, n);
				}
			}
			color = true;
		}
	}
	listTree.push_back(root);
}

void RBTree::_graphWalk(Node* p, QTextStream *stream) {
	if (p != NULL) {
		/*if (p->key < 0)
			p->key += 10000;*/
		if (p->color)
			*stream << "\t\t" << "n" << p->key << "[label=\"" << p->key << "\", fontcolor=white, color=black, style=filled];" << endl;
		else *stream << "\t\t" << "n" << p->key << "[label=\"" << p->key << "\", fontcolor=white, color=red, style=filled];" << endl;

		if (p->left != NULL) {
			*stream << "\t\tn" << p->key << "--" << "n" << p->left->key << ";" << endl;
			this->_graphWalk(p->left, stream);
		}
		else {
			
			*stream << "\t\t" << "n" << p->key << "leftNull" << "[shape=square, height=.2, width=.3, style=filled, label=NIL, fontcolor=white, color=black];" << endl;
			*stream << "\t\tn" << p->key << "--" << "n" << p->key << "leftNull" << endl;
		}

		if (p->right != NULL){
			*stream << "\t\tn" << p->key << "--" << "n" << p->right->key << ";" << endl;
			this->_graphWalk(p->right, stream);
		}
		else {
			*stream << "\t\t" << "n" << p->key << "rightNull" << "[shape=square, height=.2, width=.3, style=filled, label=NIL, fontcolor=white, color=black];" << endl;
			*stream << "\t\tn" << p->key << "--" << "n" << p->key << "rightNull" << endl;
		}
	}
}

QByteArray RBTree::_prepareGraph(){
	QByteArray a = QByteArray();

	QTextStream stream(&a, QIODevice::ReadWrite);
	stream << "graph ""{" << endl;
	stream << "\tnode[shape=circle, fontsize=10, margin=0, width=.4, height=.3];" << endl;
	stream << "\tsubgraph cluster17{" << endl;
	this->_graphWalk(this->listTree[0], &stream);
	stream << "\t}\n" << "}" << endl;
	stream.flush();

	return a;
}

void RBTree::show() {
	QProcess* p = new QProcess();
	QByteArray a = this->_prepareGraph();

	p->setProcessChannelMode(QProcess::MergedChannels);
	p->start("c:/Program Files (x86)/Graphviz2.38/bin/dot.exe", QStringList() << "-Tpng");
	p->write(a);

	QByteArray data;
	QPixmap pixmap = QPixmap();

	while (p->waitForReadyRead(10000)) {
		data.append(p->readAll());
	}

	pixmap.loadFromData(data);

	this->_scene->addPixmap(pixmap);
	this->_view->show();
}