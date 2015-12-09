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
#include <algorithm> 

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

// substitution numbers to expression
string ReplaceToNumbers(string &str, map<string, vector<double>> &args, int index = 0) {
	auto it = args.find(str);
	int size;
	if (it != args.end()) {
		size = it->second.size();
		while (index > size - 1) {
			cout << "This element of array doesn't exist!" << endl;
			cout << "Please enter correct index for array: ";
			cin >> index;
		}
		str = to_string(it->second[index]);
		return str;
	}
	string value;
	cout << endl << "You should enter a value for " << str << ": ";
	cin >> value;
	args[str].push_back(stod(value));
	return value;
}

int ValidateExpression() {
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; expression[i] != 0; i++) {
		if (expression[i] == '(')
			count1++;
		if (expression[i] == ')')
			count2++;
	}
	if (count1 != count2)
		return 1;
	return 0;
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
	char bracket;
	int k = 0;
	int j = 0;
	int i = 0;
	string tmpStr;
	ListStack<string> func;
	bool flag = true;
	map<char, int> operators;
	map<char, int>::iterator it;
	map<string, string>::iterator iter;
	ListStack<char> list;
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
	operators.insert(pair<char, int>('[', 1));
	operators.insert(pair<char, int>(']', 1));
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
			if (list.IsEmpty())
				flag = true;
			if (flag) {
				list.Push(ch);
				flag = false;
				goto nextElem;
			}
			
			if (it->second > operators.find(list.Top())->second) {
				list.Push(ch);
				goto nextElem;
			}
			else if (it->second <= operators.find(list.Top())->second) {
				// array
				if (it->first == '(' || it->first == '[')
					list.Push(ch);
				if (it->first == ')' || it->first == ']') {
					if (it->first == ']')
						bracket = ch;
						//resultExpression += it->first;
					//else
						tmp = list.Pop();
					while (tmp != '(' && tmp != '\0') {
						if (tmp == '[') {
							resultExpression += tmp;
							resultExpression += bracket;
							resultExpression += " ";
							break;
						}
						else {
							resultExpression += tmp;
							resultExpression += " ";
						}
						tmp = list.Pop();
					}
					/*if (tmp == '[')
						resultExpression += tmp;*/
					if (!func.IsEmpty()) {
						resultExpression += func.Pop();
					}
				}
				else {
					auto it1 = operators.find(ch);
					auto it2 = operators.find(list.Top());
					tmpch = ch;
					while (it2->first != '(' && it2->first != '[' && it1->second <= it2->second) {
						resultExpression += list.Pop();
						resultExpression += " ";
						if (list.IsEmpty()) {
							list.Push(tmpch);
							goto nextElem;
						}
						it2 = operators.find(list.Top());
						if (it2 == operators.end())
							goto nextElem;
					}
					auto it3 = operators.find(tmpch);
					if (it3->second > it2->second)
						list.Push(tmpch);
				}
			}
		}
		else {
			tmpStr.push_back(ch);
			tmpch = expression[i + 1];
			for (auto iter = functions.begin(); iter != functions.end(); iter++) {
				if (iter->second == tmpStr) {
 					func.Push(iter->second);
					i++;
					ch = expression[i];
					tmpStr.pop_back();
					goto check;
				}
			}
			tmpStr.pop_back();

			// if length of operand more than a one character
			resultExpression += ch;
			it = operators.find(tmpch);
			while (tmpch != 0 && it == operators.end()) {
				resultExpression += tmpch;
				i++;
				tmpch = expression[i + 1];
				it = operators.find(tmpch);
			}
			if (tmpch == '[')
				resultExpression += "&";
		}
			resultExpression += " ";
	nextElem:
		i++;
		ch = expression[i];
	}
	while (!list.IsEmpty()) {
		resultExpression += list.Pop();
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
	resExpression.erase(remove(resExpression.begin(), resExpression.end(), '&'), resExpression.end());
	return resultExpression;
}

// Calculating postfix epxression
double Calculating(string &expr) {
	ListStack<double> operands;
	map<string, vector<double>> args;
	int j = 0;
	char help = vars[0];
	string operand, value;
	bool flag = false;
	char ch;
	char tmpch;
	int i = 0;
	double result;
	string tmpStr;
	string operandStr1;
	string charToStr;
	string helper = "";
	string replace;
	ListStack<string> arr;
	double operand1, operand2;
	
	// Parsing arguments...
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
		while (help != '\n') {
			if (help == '-') {
				getMinusNumber:
				j++;
				help = vars[j];
				while (help != ' ' && help != '\n') {
					value += help;
					j++;
					help = vars[j];
				}
				value = ReplaceDotsToCommas(value);
				args[operand].push_back(stod(value) * -1);
				value = "";
			}
			while (help != '\n') {
				if (help == ' ') {
					j++;
					help = vars[j];
				}
				while (help != ' ' && help != '\n') {
					if (help == '-')
						goto getMinusNumber;
					value += help;
					j++;
					help = vars[j];
				}
				value = ReplaceDotsToCommas(value);
				args[operand].push_back(stod(value));
				value = "";
			}
		}
		value = "";
		operand = "";
		j++;
		help = vars[j];
	}

	// Calculating...
	ch = expr[0];
	while (ch != 0) {
		while (ch != '*' && ch != '/' && ch != '+' && ch != '-' && ch != '^' && (ch < -64 || ch > -52)) {
				while (ch != ' ' && ch != 0) {
					if (ch == '[' && !arr.IsEmpty()) {
						replace = ReplaceToNumbers(arr.Pop()+"[]", args, operands.Pop());
						replace = ReplaceDotsToCommas(replace);
						operands.Push(stod(replace));
						/*if (!arr.IsEmpty()) 
							arr.Pop();*/
						i += 2;
						ch = expr[i];
						goto nextOper; 
					}
					helper += ch;
					i++;
					ch = expr[i];
					if (ch == '&') {
						arr.Push(helper);
						helper = "";
						i++;
						ch = expr[i];
					}
					
				}
				if (helper == "" || helper.empty())
					goto nextOper;
				replace = ReplaceToNumbers(helper, args);
				replace = ReplaceDotsToCommas(replace);
				operands.Push(stod(replace));
				helper = "";
			if (ch != ' ')
				helper += ch;
			else if (helper != "") {
					replace = ReplaceToNumbers(helper, args);
					replace = ReplaceDotsToCommas(replace);
					operands.Push(stod(replace));
					helper = "";
				}
			i++;
			ch = expr[i];
		}
		tmpStr.push_back(ch);
		for (auto iter = functions.begin(); iter != functions.end(); iter++) {
			if ( iter->second == tmpStr) {
				operand2 = operands.Pop();
				goto calculate;
			}
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

	size_t find;
	return operands.Pop();
}

int main() {
	setlocale(0, "Russian");
	readFile();
	int check;
	check = ValidateExpression();
	if (check == 1) {
		cout << "Error in brackets!" << endl;
		system("pause");
		return 0;
	}
	cout << "Infix: " << expression << endl << endl;
	string expr = infixToPostfix();
	cout << "Postifx: " << resExpression << endl << endl;
	double result = Calculating(expr);
	cout << "Result: " << setprecision(4) << result << endl << endl;
	system("pause");
	return 0;
}
