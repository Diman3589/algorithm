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
#include <iomanip> 
#include <iostream>

#define PI 3.14159265

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
	int gg = resultExpression.length();
	resultExpression[resultExpression.length() - 1] = 0;
	return resultExpression;
}

double Calculating(string &expr) {
	ListStack<double> operands;
	map<string, int> args;
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
	
	size_t find;
	for (int i = 0; expr[i] != 0; i++) {
		for (auto iter = args.begin(); iter != args.end(); iter++) {
			find = expr.find(iter->first);
			if (find != string::npos)
				expr.replace(find, iter->first.length(), to_string(iter->second));
		}
	}

	char ch = expr[0];
	char tmpch;
	int i = 0;
	double result;
	string helper = "";
	double operand1, operand2;

	while (ch != 0) {
		while (ch != '*' && ch != '/' && ch != '+' && ch != '-' && ch != '^') {
			/*tmpch = expr[i + 1];
			if (tmpch >= '0' && tmpch <= '9') {

			}*/
			if (ch != ' ')
				helper += ch;
			else if (helper != ""){
				operands.Push(stoi(helper));
				helper = "";
			}

			i++;
			ch = expr[i];
		}
		operand2 = operands.Pop();
		operand1 = operands.Pop();
		switch (ch) {
			case '*':
				result = operand1 * operand2;
				operands.Push(result);
				break;
			case '/':
				result = operand1 / operand2;
				operands.Push(result);
				break;
			case '+':
				result = operand1 + operand2;
				operands.Push(result);
				break;
			case '-':
				result = operand1 - operand2;
				operands.Push(result);
				break;
			case '^':
				result = pow(operand1, operand2);
				operands.Push(result);
				break;
		}
		i++;
		ch = expr[i];
		
	}
	cout << "Postfix(numbers): " << expr << endl << endl;
	return operands.Pop();
}

int main() {
	setlocale(0, "Russian");
	readFile();
	string expr = infixToPostfix();
	cout << "Infix: " << expression << endl << endl;
	cout << "Postifx: " << expr << endl << endl;
	double result = Calculating(expr);
	cout << "Result:"  << setprecision(4) << result << endl << endl;
	system("pause");
	return 0;
}
