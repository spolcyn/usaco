/*
ID: sp.shop1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream fin("beads.in");
	ofstream fout("beads.out");

	short size;
	fin >> size;
	
	char* beads = new char[size];
	fin >> beads;

	
}