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

int length(int startIndex, int endIndex)
{
	return endIndex - startIndex + 1; //extra 1 to account for inclusivity
}

bool firstStrand(int startIndex, int midIndex)
{
	return startIndex == midIndex;
}

int seekBackToWhite(int midIndex, string necklace)
{
	for(int x = midIndex - 1; x >= 0; x--)
	{
		if(necklace.at(x) != 'w')
			return x + 1;
	}

	return 0;
}

int main()
{
	ifstream fin("beads.in");
	ofstream fout("beads.out");

	int size;
	fin >> size;

	string necklace;
	fin >> necklace;
	necklace = necklace + necklace;

	int startIndex = 0, midIndex = 0;
	int maxLength = length(startIndex, midIndex);
	char currentBeadColor = necklace.at(0);	

	for(int bead = 1; bead < necklace.length(); bead++)
	{
		//if started strand on white, find desired color
		if(currentBeadColor == 'w' && necklace.at(bead) != 'w')
			currentBeadColor = necklace.at(bead);

		if(same(currentBeadColor, necklace.at(bead)))
		{
			if(length(startIndex, bead) > maxLength)
				maxLength = length(startIndex, bead);
		}
		else  //restart the path
		{
			currentBeadColor = necklace.at(bead);
			startIndex = seekBackToWhite(midIndex, necklace);
			midIndex = bead;
		}

		if(startIndex == (bead % size) && bead >= size)
		{
			maxLength -= 1;
			break;
		}

		
		//cout << "bead: " << bead << " start: " << startIndex << " mid: " << midIndex << " length: " << length(startIndex, bead) << " maxLength: " << maxLength << " firstStrand: " << firstStrand(startIndex, midIndex) << endl;


	}

	fout << maxLength << endl;

	return 0;
}