#pragma once
#include "Stack.h"

#define amountOperations 10000000

template <typename TElement>
class ArrayStack : public Stack<TElement> {
public:
	TElement Pop();
	int Push(TElement elem);
	int IsEmpty();
	TElement Top();
private:
	void outInFile();
private:
	int size;
	int top;
	TElement *ptrStack;
	TElement *newMass;
public:
	ArrayStack();
	~ArrayStack();
};

template <typename TElement>
ArrayStack<TElement>::ArrayStack() {
	size = 10;
	ptrStack = new TElement[size];
	top = -1;
}

template <typename TElement>
ArrayStack<TElement>::~ArrayStack() {
	delete[] newMass;
}

template <typename TElement>
TElement ArrayStack<TElement>::Pop() {
	if (top > -1) {
		TElement item = ptrStack[top];
		ptrStack[top] = NULL;
		top--;
		return item;
	}
	return false;
}

template <typename TElement>
int ArrayStack<TElement>::Push(TElement elem) {
	if (top == size - 1) {
		size += 1000000;
		newMass = new TElement[size];
		for (int i = 0; i < size - 1000000; i++) {
			newMass[i] = ptrStack[i];
		}
		delete[] ptrStack;
		ptrStack = newMass;
	}
	top++;
	ptrStack[top] = elem;
	return true;
}

template <typename TElement>
int ArrayStack<TElement>::IsEmpty() {
	if (top == -1)
		return true;
	return false;
}

template <typename TElement>
TElement ArrayStack<TElement>::Top() {
	if (top > -1)
		return ptrStack[top];
	return false;
}

template <typename TElement>
void ArrayStack<TElement>::outInFile() {
	ofstream fout("resultArray.txt", ofstream::out);
	while (!this->IsEmpty()) {
		fout << this->Pop() << endl;
	}
	fout.close();
}