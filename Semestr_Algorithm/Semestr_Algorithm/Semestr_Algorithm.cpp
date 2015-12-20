// Semestr_Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

int n1; //���������� ������ � ������ ���� �����
int n2; //���������� ������ �� ������ ���� �����
int m; //���������� ����� � �����
vector<int> *adj; //������ ���������
vector<bool> used; //������ ��� �������� ���������� � ���������� � �� ���������� ��������
int mtSize = 0; //������ ������������� �������������
vector<int> mt; //������ ��� �������� �����, ���������� ������������ �������������

//�������� ���� ������ ������������� �������������
bool kuhn(int v) {
	//���� ������� �������� ����������, �� �� ���������� �� ��� ����� ���������
	if (used[v]) {
		return false;
	}
	used[v] = true; //�������� ������� ������ ����, ��� ����������
	//������������� ��� ������� ������ ����, ������� � ��������������� �������� ������ ����   
	for (int i = 0; i < adj[v].size(); ++i) {
		int w = adj[v][i];
		//����� ������������� ����, ��������� ����� (v, w) � �������������
		if (mt[w] == -1 || kuhn(mt[w])) {
			mt[w] = v;
			return true;
		}
	}
	return false;
}

//��������� ���������� ������� ������ � �������
void readData() {
	//��������� ���������� ������ � ������ � ������ ���� � ���������� ����� �����
	cin >> n1 >> n2 >> m;
	//�������������� ������ ��������� ����������� n1
	adj = new vector<int>[n1];

	//��������� ����, �������� ������� �����
	for (int i = 0; i < m; ++i) {
		int v, w;
		cin >> v >> w;
		v--;
		w--;
		//��������� ����� (v, w) � ����
		adj[v].push_back(w);
	}
	used.assign(n1, false);
	mt.assign(n2, -1);
}

void solve() {
	//������� ������������ �������������
	for (int v = 0; v < n1; ++v) {
		//KEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEK
		used.assign(n1, false);
		//���� ����� ������������� ����, �� ������ ������������� ������������� ����������� �� 1
		if (kuhn(v)) {
			mtSize++;
		}
	}
}

void printData() {
	cout << endl << mtSize << endl;
	for (int i = 0; i < n2; ++i) {
		if (mt[i] != -1) {
			cout << mt[i] + 1 << " " << i + 1 << endl;
		}
	}
}

int main() {
	readData();
	solve();
	printData();
	system("pause");
	return 0;
}