/*
ID: sp.shop1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

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

	string necklace;
	fin >> necklace;
	necklace = necklace + necklace;

	short maxLength = 1, startIndex = 0, midIndex = 0;
	bool firstStrand = true;
	char currentBeadColor = necklace.at(0);	

	for(int bead = 1; bead < necklace.length(); bead++)
	{
		//if started strand on white, find desired color
		if(currentBeadColor == 'w' && necklace.at(bead) != 'w')
			currentBeadColor = necklace.at(bead);

		if(same(currentBeadColor, necklace.at(bead)))
		{
		}
		else if(firstStrand)  //keep going for longest path, if looking for 2nd set
		{
			firstStrand = false;
			currentBeadColor = necklace.at(bead);
			midIndex = bead;
		}
		else  //restart the path
		{
			firstStrand = true;
			currentBeadColor = necklace.at(bead);
			startIndex = midIndex;
		}

		if(bead - startIndex > maxLength)
			maxLength = bead - startIndex;
		
		cout << "bead: " << bead << " start: " << startIndex << " mid: " << midIndex << " length: " << (bead - startIndex) << " maxLength: " << maxLength << " firstStrand: " << firstStrand << endl;

		if(startIndex == bead % (size - 1) && bead >= size)
			break;
	}

	fout << maxLength << endl;

	return 0;
}