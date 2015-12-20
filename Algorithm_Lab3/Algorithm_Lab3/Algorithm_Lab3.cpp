// Algorithm_Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Data {
	int key;
	bool colour;
};

struct Vertex {		//вершина
	Data data;
	Vertex* left;
	Vertex* right;
};

string readFile() {
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


int main() {
	vector<Vertex> listTree;
	Vertex v;// = new Vertex;
	Vertex v1;// = new Vertex;
	Vertex v2;// = new Vertex;

	v.data.key = 5;
	v.data.colour = true;
	v.left = &v1;
	v.right = &v2;
	v1.data.key = 3;
	v1.data.colour = false;
	v2.data.key = 7;
	v2.data.colour = false;
	listTree.push_back(v);

	string fileContents = readFile();
	//parsingFile();

	

	system("pause");
	return 0;
}