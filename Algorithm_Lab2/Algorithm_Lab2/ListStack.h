#pragma once
#include "Stack.h"

template <typename TElement>
class Node {
public:
	TElement data;
	Node<TElement> *next;
public:
	Node();
};

template <typename TElement>
Node<TElement>::Node() {
	next = NULL;
}

template <typename TElement>
class ListStack : public Stack<TElement> {
public:
	TElement Pop();
	int Push(TElement elem);
	int IsEmpty();
	TElement Top();
private:
	void outInFile();
private:
	Node<TElement> *head;
public:
	ListStack();
	~ListStack();
};

template <typename TElement>
ListStack<TElement>::ListStack() {
	head = NULL;
}

template <typename TElement>
ListStack<TElement>::~ListStack() {
	Node<TElement> *node;
	while (head != NULL) {
		node = head;
		head = head->next;
		delete node;
		node = NULL;
	}
}

template <typename TElement>
int ListStack<TElement>::Push(TElement elem) {
	Node<TElement> *newNode = new Node<TElement>;
	newNode->next = head;
	newNode->data = elem;
	head = newNode;
	return true;
}

template <typename TElement>
TElement ListStack<TElement>::Pop() {
	TElement elem;
	if (head != NULL) {
		Node<TElement> *tmpNode;
		elem = head->data;
		tmpNode = head;
		head = head->next;
		delete tmpNode;
	}
	else return false;
	return elem;
}

template <typename TElement>
int ListStack<TElement>::IsEmpty() {
	if (head == NULL)
		return 0;
	return 1;
}

template <typename TElement>
TElement ListStack<TElement>::Top() {
	if (head != NULL)
		return head->data;
	return false;
}

template <typename TElement>
void ListStack<TElement>::outInFile() {
	ofstream fout("resultList.txt", ofstream::out);
	while (!this->IsEmpty()) {
		fout << this->Pop() << endl;
	}
	fout.close();
}