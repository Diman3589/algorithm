// Algorithm_Lab2.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"
#include "Stack.h"
#include "ArrayStack.h"
#include "ListStack.h"
#include <string>
#include <map>
#include <fstream>
#include <sstream>
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
	int k = 0;
	int j = 0;
	int i = 0;
	bool flag = true;
	map<char, int> operands;
	map<char, int>::iterator it;
	map<string, string> functions;
	map<string, string>::iterator iter;
	ListStack<char> lst;
	string resultExpression = "";
	istringstream istreamexpr;
	functions.insert(pair<string, string>("sin", "À"));
	functions.insert(pair<string, string>("cos", "Á"));
	functions.insert(pair<string, string>("tan", "Â"));
	functions.insert(pair<string, string>("ctg", "Ã"));
	functions.insert(pair<string, string>("asin", "Ä"));
	functions.insert(pair<string, string>("acos", "Å"));
	functions.insert(pair<string, string>("atan", "Æ"));
	functions.insert(pair<string, string>("actg", "Ç"));
	functions.insert(pair<string, string>("exp", "È"));
	functions.insert(pair<string, string>("ln", "Ê"));
	functions.insert(pair<string, string>("sqrt", "Ë"));
	functions.insert(pair<string, string>("sqrt3", "Ì"));

	operands.insert(pair<char, int>('(', 1));
	operands.insert(pair<char, int>(')', 1));
	operands.insert(pair<char, int>('-', 2));
	operands.insert(pair<char, int>('+', 2));
	operands.insert(pair<char, int>('*', 3));
	operands.insert(pair<char, int>('/', 3));
	operands.insert(pair<char, int>('^', 4));
	while (ch != 0) {
		start:
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
						resultExpression += " ";
						tmp = lst.Pop();
					}
				}
				else {
					auto it1 = operands.find(ch);
					auto it2 = operands.find(lst.Top());
					tmpch = ch;
					while (it2->first != '(' && it1->second <= it2->second) {
						resultExpression += lst.Pop();
						resultExpression += " ";
						it2 = operands.find(lst.Top());
					}
					if (tmpch > it2->first)
						lst.Push(tmpch);
				}
			}
		}
		else {
			//j = 0;
			//switch (ch) {
			//	case 'a':
			//		k = i;
			//		while (expression[k] != '(') {
			//			arrfunc[j] = expression[k];
			//			j++;
			//			k++;
			//		}
			//		//for (j = 0; arrfunc[j] != 0; j++)
			//			//func += arrfunc[j];
			//		//cout << func << endl;
			//		//it = operands.find(f);
			//		break;

			//	default:
			//		break;
			//}
			resultExpression += ch;
			tmpch = expression[i + 1];
			it = operands.find(tmpch);
			while (tmpch != 0 && tmpch != ' ' && it == operands.end()) {
				resultExpression += tmpch;
				i++;
				tmpch = expression[i + 1];
				it = operands.find(tmpch);
				
			}
			resultExpression += " ";
		}
	nextElem:
		i++;
		ch = expression[i];
	}
	while (lst.IsEmpty() != 0) {
		resultExpression += lst.Pop();
		resultExpression += " ";
	}
	return resultExpression;
}

int main() {
	setlocale(0, "Russian");
	readFile();
	string expr = infixToPostfix();
	cout << expr;
	cout << endl;
	system("pause");
	return 0;
}

