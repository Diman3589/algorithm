// Algorithm_Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Stack.h"
#include "ArrayStack.h"
#include "ListStack.h"
#include <string>
#include <map>
#include <fstream>

using namespace std;

void foo(){}

int main() {
	ifstream fin("expression.txt", ifstream::in);
	string expression;
	string vars;
	string line;
	getline(fin, expression);
	while (getline(fin, line)) {
		vars += line;
		vars += "\n";
	}
	fin.close();
	char ch = expression[0];
	char tmpch;
	char tmp;
	int i = 0;
	bool flag = true;
	map<char, int> operands;
	ListStack<char> lst;
	string resultExpression = "";
	operands.insert(pair<char, int>('(', 1));
	operands.insert(pair<char, int>(')', 1));
	operands.insert(pair<char, int>('-', 2));
	operands.insert(pair<char, int>('+', 2));
	operands.insert(pair<char, int>('*', 3));
	operands.insert(pair<char, int>('/', 3));
	operands.insert(pair<char, int>('^', 4));
	map<char, int>::iterator it;
	
	while (ch != 0) {
		it = operands.find(ch);
		if (it != operands.end() && it->first == ch) {
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
					lst.Push(ch);;
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
					if (tmpch> it2->first)
						lst.Push(tmpch);
				}
			}
		}
		else {
			resultExpression += ch;
		}
		nextElem:
		i++;
		ch = expression[i];
	}
	while (lst.IsEmpty() != 0)
		resultExpression += lst.Pop();
	cout << resultExpression;
	cout << "lololol";
	cout << endl;
	system("pause");
	return 0;
}

