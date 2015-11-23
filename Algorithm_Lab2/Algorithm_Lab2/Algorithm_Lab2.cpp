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
string resExpression;
string vars;
map<string, string> functions;

string FromAliasesToFunctions(string &expr) {
	size_t pos;
	for (auto iter = functions.begin(); iter != functions.end(); iter++) {
		for (int k = 0; expr[k] != 0; k++) {
			if (expr[k] == iter->second[0])
				expr.replace(k, iter->second.length(), iter->first);
		}
		/*pos = resExpression.find(iter->second);
		if (pos != string::npos)*/
	}
	return expr;
}

string FromFunctionsToAliases(string &expr) {
	size_t pos;
	for (auto iter = functions.begin(); iter != functions.end(); iter++) {
		pos = expression.find(iter->first);
		if (pos != string::npos)
			expr.replace(pos, iter->first.length(), iter->second);
	}
	return expr;
}

string ReplaceDotsToCommas(string &value) {
	size_t pos;
	for (int k = 0; value[k] != 0; k++) {
		if (value[k] == '.')
			value[k] = ',';
	}
	return value;
}

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
	string tmpStr;
	string func;
	bool flag = true;
	map<char, int> operators;
	map<char, int>::iterator it;
	map<string, string>::iterator iter;
	ListStack<char> lst;
	string resultExpression = "";
	functions.insert(pair<string, string>("sin", "À"));
	functions.insert(pair<string, string>("cos", "Á"));
	functions.insert(pair<string, string>("tan", "Â"));
	functions.insert(pair<string, string>("cot", "Ã"));
	functions.insert(pair<string, string>("asin", "Ä"));
	functions.insert(pair<string, string>("acos", "Å"));
	functions.insert(pair<string, string>("atan", "Æ"));
	functions.insert(pair<string, string>("actg", "Ç"));
	functions.insert(pair<string, string>("exp", "È"));
	functions.insert(pair<string, string>("ln", "Ê"));
	functions.insert(pair<string, string>("sqrt", "Ë"));
	functions.insert(pair<string, string>("sqr3", "Ì"));

	operators.insert(pair<char, int>('(', 1));
	operators.insert(pair<char, int>(')', 1));
	operators.insert(pair<char, int>('-', 2));
	operators.insert(pair<char, int>('+', 2));
	operators.insert(pair<char, int>('*', 3));
	operators.insert(pair<char, int>('/', 3));
	operators.insert(pair<char, int>('^', 4));

	//replace functions to aliases
	expression = FromFunctionsToAliases(expression);
	char ch = expression[0];
	while (ch != 0) {
	check:
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
					if (!func.empty()) {
						resultExpression += func;
						func = "";
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
			tmpStr.push_back(ch);
			tmpch = expression[i + 1];
			for (auto iter = functions.begin(); iter != functions.end(); iter++) {
				if (iter->second == tmpStr) {
 					func = iter->second;
					i++;
					ch = expression[i];
					tmpStr.pop_back();
					goto check;
				}
			}
			tmpStr.pop_back();
			resultExpression += ch;
			it = operators.find(tmpch);
			while (tmpch != 0 && it == operators.end()) {
				resultExpression += tmpch;
				i++;
				tmpch = expression[i + 1];
				it = operators.find(tmpch);
			}
		}
			resultExpression += " ";
	nextElem:
		i++;
		ch = expression[i];
	}
	while (lst.IsEmpty() != 0) {
		resultExpression += lst.Pop();
		resultExpression += " ";
	}

	// delete unnecessary spaces
	for (int k = 0; resultExpression[k] != 0; k++) {
		if (resultExpression[0] == ' ')
			resultExpression.erase(0, 1);
		if (resultExpression[k] == ' ' && resultExpression[k + 1] == ' ' && resultExpression[k + 2] == ' ')
			resultExpression.erase(k, 2);
		if (resultExpression[k] == ' ' && resultExpression[k + 1] == ' ')
			resultExpression.erase(k, 1);
	}
	resultExpression[resultExpression.length() - 1] = 0;

	// replace aliases to functions
	resExpression = resultExpression;
	resExpression = FromAliasesToFunctions(resExpression);
	return resultExpression;
}

double Calculating(string &expr) {
	ListStack<double> operands;
	map<string, double> args;
	int j = 0;
	char help = vars[0];
	string operand, value;
	bool flag = false;
	double number;
	char ch;
	char tmpch;
	int i = 0;
	double result;
	string tmpStr;
	string operandStr1;
	string charToStr;
	string helper = "";
	double operand1, operand2;

	// convert arguments to numbers
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

		value = ReplaceDotsToCommas(value);
		number = stod(value);

		if (flag) {
			number *= -1;
			flag = false;
		}
	
		args.insert(pair<string, double>(operand, number));
		value = "";
		operand = "";
		j++;
		help = vars[j];
	}

	// substitution numbers to expression
	size_t find;
	for (int i = 0; expr[i] != 0; i++) {
		for (auto iter = args.begin(); iter != args.end(); iter++) {
			find = expr.find(iter->first);
			if (find != string::npos)
				expr.replace(find, iter->first.length(), to_string(iter->second));
		}
	}

	expr = ReplaceDotsToCommas(expr);
	ch = expr[0];
	while (ch != 0) {
		while (ch != '*' && ch != '/' && ch != '+' && ch != '-' && ch != '^' && (ch < -64 || ch > -52)) {
			if (ch == ',') {
				while (ch != ' ') {
					helper += ch;
					i++;
					ch = expr[i];
				}
				operands.Push(stod(helper));
				helper = "";
			}
			if (ch != ' ')
				helper += ch;
			else if (helper != ""){
				operands.Push(stod(helper));
				helper = "";
			}
			i++;
			ch = expr[i];
		}
		if (ch == '-' && expr[i + 1] != ' ') {
			i++;
			ch = expr[i];
			while (ch != ' ') {
				helper += ch;
				i++;
				ch = expr[i];
			}
			operands.Push(stod(helper) * (-1));
			helper = "";
			goto nextOper;
		}
		tmpStr.push_back(ch);
		for (auto iter = functions.begin(); iter != functions.end(); iter++) {
			if (iter->second == tmpStr) {
				operand2 = operands.Pop();
				goto calculate;
			}
			else break;
		}
		operand2 = operands.Pop();
		operand1 = operands.Pop();
		calculate:
			tmpStr.pop_back();
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
				case 'À':
					result = sin(operand2 * PI / 180);
					operands.Push(result);
					break;
				case 'Á':
					result = cos(operand2 * PI / 180);
					operands.Push(result);
					break;
				case 'Â':
					result = tan(operand2 * PI / 180);
					operands.Push(result);
					break;
				case 'Ã':
					result = 1 / tan(operand2 * PI / 180);
					operands.Push(result);
					break;
				case 'Ä':
 					result = asin(operand2) * 180.0 / PI;
					operands.Push(result);
					break;
				case 'Å':
					result = acos(operand2) * 180.0 / PI;
					operands.Push(result);
					break;
				case 'Æ':
					result = atan(operand2) * 180.0 / PI;
					operands.Push(result);
					break;
				case 'Ç':
					result = 1 / atan(operand2) * 180.0 / PI;
					operands.Push(result);
					break;
				case 'È':
					result = exp(operand2 * PI / 180);
					operands.Push(result);
					break;
				case 'Ê':
					result = log(operand2);
					operands.Push(result);
					break;
				case 'Ë':
					result = sqrt(operand2);
					operands.Push(result);
					break;
				case 'Ì':
					result = cbrt(operand2);
					operands.Push(result);
					break;
			}
		nextOper:
			i++;
			ch = expr[i];
		
	}
	expr = FromAliasesToFunctions(expr);
	cout << "Postfix(numbers): " << expr << endl << endl;
	return operands.Pop();
}

int main() {
	setlocale(0, "Russian");
	readFile();
	string expr = infixToPostfix();
	cout << "Infix: " << expression << endl << endl;
	cout << "Postifx: " << resExpression << endl << endl;
	double result = Calculating(expr);
	cout << "Result: " << setprecision(4) << result << endl << endl;
	system("pause");
	return 0;
}
