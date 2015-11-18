// Algorithm_Lab2.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"
#include "Stack.h"
#include "ArrayStack.h"
#include "ListStack.h"
#include <string>
#include <map>
#include <fstream>
#include <cmath>

#define PI 3.14159265

#include <iostream>

using namespace std;

string expression;
string vars;

void readFile() {
	ifstream fin("expression.txt", ifstream::in);
	string line;
	getline(fin, expression);
	while (getline(fin, line)) {
		vars += line;
		vars += "\n";
	}
	fin.close();
}

string infixToPostfix() {
	char ch = expression[0];
	char tmpch;
	char tmp;
	int i = 0;
	bool flag = true;
	map<char, int> operands;
	map<char, int>::iterator it;
	ListStack<char> lst;
	string resultExpression = "";
	operands.insert(pair<char, int>('(', 1));
	operands.insert(pair<char, int>(')', 1));
	operands.insert(pair<char, int>('-', 2));
	operands.insert(pair<char, int>('+', 2));
	operands.insert(pair<char, int>('*', 3));
	operands.insert(pair<char, int>('/', 3));
	operands.insert(pair<char, int>('^', 4));
	while (ch != 0) {
		it = operands.find(ch);
		if (it != operands.end()) {
			if (lst.IsEmpty() == 0)
				flag = true;
			if (flag) {
				lst.Push(ch);
				flag = false;
				goto nextElem;
			}
			if (it->second > operands.find(lst.Top())->second) {
				lst.Push(ch);
				goto nextElem;
			}
			else if (it->second <= operands.find(lst.Top())->second) {
				if (it->first == '(')
					lst.Push(ch);
				if (it->first == ')') {
					tmp = lst.Pop();
					while (tmp != '(' && tmp != '\0') {
						resultExpression += tmp;
						tmp = lst.Pop();
					}
				}
				else {
					auto it1 = operands.find(ch);
					auto it2 = operands.find(lst.Top());
					tmpch = ch;
					while (it2->first != '(' && it1->second <= it2->second) {
						resultExpression += lst.Pop();
						it2 = operands.find(lst.Top());
					}
					if (tmpch > it2->first)
						lst.Push(tmpch);
				}
			}
		}
		else {
			if (ch == 's') {

			}
			resultExpression += ch;
		}
	nextElem:
		i++;
		ch = expression[i];
	}
	while (lst.IsEmpty() != 0)
		resultExpression += lst.Pop();
	return resultExpression;
}

string Calculating(string expr){
	ListStack<string> operands;

	char ch = expr[0];
	int i = 0, first, second;
	string helper;

	while (ch != 0){
		helper = "";
		if (ch >= 0 && ch <= 9){
			while (ch != ' ' || ch != 0 || ch != '*' || ch != '/' || ch != '+' || ch != '-' || ch != '^'){
				helper += ch;
				i++;
				ch = expr[i];
			}
			operands.Push(helper);
		}
		else if (ch != ' '){		// Если ch - знак
			if (!operands.IsEmpty()){
				second = (int)operands.Pop();
			}
		}
		i++;
		ch = expr[i];
	}
	return operands.Pop();
}

int main() {
	readFile();
	string expr = infixToPostfix();
	cout << expr;
	cout << endl;

	
	string result = Calculating(expr);
	cout << result;
	cout << endl;

	system("pause");
	return 0;
}