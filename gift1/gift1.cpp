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
	string* peopleOrder = new string[numberOfPeople];

	string name;

	for(int x = 0; x < numberOfPeople; x++)
	{
		fin >> name;
		people[name] = 0;
		*(peopleOrder + x) = name;
	}

	int divisor;
	int amount;

	string giftTo;

	fin >> name;
	fin >> amount;
	fin >> divisor;

	while(!fin.eof())
	{
		if(divisor != 0)  //ensure no divide by 0 error
		{
			//add to each of the people
			for(int x = 0; x < divisor; x++)
			{
				fin >> giftTo;
				people[giftTo] += amount / divisor;
			}

			people[name] += 0 - amount + amount % divisor;
		}

		//get the new data
		fin >> name;
		fin >> amount;
		fin >> divisor;
	}

	//output to file
	for(int index = 0; index < numberOfPeople; index++)
	{
		fout << *(peopleOrder + index) << " " << people[*(peopleOrder + index)] << endl;
	}

	return 0;
}