#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

template <typename TElement>
class Stack {
public:
	virtual TElement Pop() = 0;
	virtual int Push(TElement elem) = 0;
	virtual bool IsEmpty() = 0;
	virtual TElement Top() = 0;
protected:
	virtual void outInFile() = 0;
public:
	Stack(){ ; };
	~Stack(){ ; };
};