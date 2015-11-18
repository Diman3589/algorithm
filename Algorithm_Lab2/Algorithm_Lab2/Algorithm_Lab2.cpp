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
	cout << vars[0];
	fin.close();
}

string infixToPostfix() {
	char tmpch;
	char tmp;
	int k = 0;
	int j = 0;
	int i = 0;
	size_t find;
	bool flag = true;
	map<char, int> operators;
	map<char, int>::iterator it;
	map<string, string> functions;
	map<string, string>::iterator iter;
	ListStack<char> lst;
	string resultExpression = "";
	functions.insert(pair<string, string>("sin", "А"));
	functions.insert(pair<string, string>("cos", "Б"));
	functions.insert(pair<string, string>("tan", "В"));
	functions.insert(pair<string, string>("ctg", "Г"));
	functions.insert(pair<string, string>("asin", "Д"));
	functions.insert(pair<string, string>("acos", "Е"));
	functions.insert(pair<string, string>("atan", "Ж"));
	functions.insert(pair<string, string>("actg", "З"));
	functions.insert(pair<string, string>("exp", "И"));
	functions.insert(pair<string, string>("ln", "К"));
	functions.insert(pair<string, string>("sqrt", "Л"));
	functions.insert(pair<string, string>("sqrt3", "М"));

	operators.insert(pair<char, int>('(', 1));
	operators.insert(pair<char, int>(')', 1));
	operators.insert(pair<char, int>('-', 2));
	operators.insert(pair<char, int>('+', 2));
	operators.insert(pair<char, int>('*', 3));
	operators.insert(pair<char, int>('/', 3));
	operators.insert(pair<char, int>('^', 4));

	//replace functions to aliases
	/*for (iter = functions.begin(); iter != functions.end(); iter++) {
		find = expression.find(iter->first);
		if (find != string::npos)
			expression.replace(find, iter->first.length(), iter->second);
	}*/
	char ch = expression[0];
	while (ch != 0) {
		it = operators.find(ch);
		if (it != operators.end()) {
			if (lst.IsEmpty() == 0)
				flag = true;
			if (flag) {
				lst.Push(ch);
				flag = false;
				goto nextElem;
			}
			if (it->second > operators.find(lst.Top())->second) {
				lst.Push(ch);
				goto nextElem;
			}
			else if (it->second <= operators.find(lst.Top())->second) {
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
					auto it1 = operators.find(ch);
					auto it2 = operators.find(lst.Top());
					tmpch = ch;
					while (it2->first != '(' && it1->second <= it2->second) {
						resultExpression += lst.Pop();
						resultExpression += " ";
						if (lst.IsEmpty() == 0) {
							lst.Push(tmpch);
							goto nextElem;
						}
						it2 = operators.find(lst.Top());
						if (it2 == operators.end())
							goto nextElem;
					}
					if (tmpch > it2->first)
						lst.Push(tmpch);
				}
			}
		}
		else {
			resultExpression += ch;
			tmpch = expression[i + 1];
			if (tmpch == '(') {
				while (tmpch != ')') {
					resultExpression += tmpch;
					i++;
					tmpch = expression[i+1];
				}
				resultExpression += tmpch;
				i++;
			}
			else {
				it = operators.find(tmpch);
				while (tmpch != 0 && it == operators.end()) {
					resultExpression += tmpch;
					i++;
					tmpch = expression[i + 1];
					it = operators.find(tmpch);
				}
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

	//replace aliases to functions
	/*for (iter = functions.begin(); iter != functions.end(); iter++) {
		find = resultExpression.find(iter->second);
		if (find != string::npos)
			resultExpression.replace(find, iter->second.length(), iter->first);
	}*/


	return resultExpression;

}

string Calculating(string &expr) {
	ListStack<string> operands;
	map<string, int> args;
	size_t find;

	map<string, int>::iterator iter = args.begin();
	for (int i = 0; expr[i] != 0; i++) {
		
		find = expr.find(iter->first);
		if (find != string::npos)
			expr.replace(find, iter->first.length(), iter->second);
	}

	int j = 0;
	char help = vars[0];
	string operand, value;
	bool flag = false;
	while (help != 0) {
		while (help != ' ') {
			operand += help;
			j++;
			help = vars[j];
		}
		while (help != '-' && !(help >= '0' && help <= '9')) {
			j++;
			help = vars[j];
		}
		if (help == '-') {
			flag = true;
			j++;
			help = vars[j];
		}
		while (help != '\n') {
			value += help;
			j++;
			help = vars[j];
		}
		int number = stoi(value);
		if (flag) {
			number *= -1;
			flag = false;
		}

		args.insert(pair<string, int>(operand, number));
		value = "";
		operand = "";
		j++;
		help = vars[j];
	}

	char ch = expr[0];
	int i = 0, result;
	string helper, operand1, operand2;
	map<string, int>::iterator iter1;
	map<string, int>::iterator iter2;

	while (ch != 0) {
		helper = "";
		if (ch >= 'a' && ch <= 'z') {
			while (ch != ' ' || ch != 0 || ch != '*' || ch != '/' || ch != '+' || ch != '-' || ch != '^') {
				helper += ch;
				i++;
				ch = expr[i];
			}
			operands.Push(helper);
		}
		if (ch != ' ') {	// Если ch - знак
			if (operands.IsEmpty() != 0) {
				operand2 = operands.Pop();
				operand1 = operands.Pop();

				iter2 = args.find(operand2);
				iter1 = args.find(operand1);

				switch (ch){
				case '*':
					result = iter1-> * 
					break;
				case '/':
					break;
				case '+':
					break;
				case '-':
					break;
				case '^':
					break;
				}

				result = ;
		}
		i++;
		ch = expr[i];
	}
	return operands.Pop();
}
}

int main() {
	setlocale(0, "Russian");
	readFile();
	string expr = infixToPostfix();
	cout << expr;
	cout << endl;
	/*
	string result = Calculating(expr);
	cout << result;
	cout << endl;*/

	system("pause");
	return 0;
}
