/*
ID: sp.shop1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

bool same(char bead1, char bead2)
{
	return bead1 == bead2 || bead1 == 'w' || bead2 == 'w';
}

int main()
{
	ifstream fin("beads.in");
	ofstream fout("beads.out");

	short size;
	fin >> size;

	char* input = new char[size];
	fin >> input;

	short maxLength = 1, tempLength = 1, startIndex = 0, midIndex = 0;
	bool firstStrand = true;
	char currentBeadColor = *input;	

	for(int bead = 1; bead < size * 2; bead++)
	{
		//if started strand on white, find desired color
		if(currentBeadColor == 'w' && *(input + bead) != 'w')
			currentBeadColor = *(input + bead);

		if(bead % size == startIndex)  //ensure doesn't go through start again
		{
			break;
		}
		else if(same(currentBeadColor, *(input + bead % size)))  //% wraps around string
		{
			tempLength += 1;
		}
		else if(firstStrand)  //keep going for longest path, if looking for 2nd set
		{
			firstStrand = false;
			currentBeadColor = *(input + bead);
			tempLength += 1;
			midIndex = bead;
		}
		else  //restart the path
		{
			firstStrand = true;
			tempLength = tempLength - (midIndex - startIndex);
			startIndex = bead % size;
		}

		//update max length
		if(tempLength > maxLength)
			maxLength = tempLength;
	
		cout << startIndex << endl;
	}

	fout << maxLength << endl;
}