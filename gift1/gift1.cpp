/*
ID: sp.shop1
PROG: gift1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

int main()
{
	ofstream fout ("gift1.out");
	ifstream fin ("gift1.in");

	short numberOfPeople;
	fin >> numberOfPeople;

	map<string, int> people;

	string name;

	for(int x = 0; x < numberOfPeople; x++)
	{
		fin >> name;
		people[name] = 0;
	}

	int divisor;
	int amount;

	string giftTo;

	while(!fin.eof())
	{
		fin >> name;
		fin >> amount;
		fin >> divisor;

		if(divisor != 0)
		{
			for(int x = 0; x < divisor; x++)
			{
				fin >> giftTo;
				people[giftTo] += amount / divisor;
			}

			people[name] += 0 - amount + amount % divisor;
		}
	}

	for(auto iter : people)
	{
		cout << iter.first << " " << iter.second << endl;
	}



}