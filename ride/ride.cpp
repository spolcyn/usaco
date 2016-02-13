/*
ID: sp.shop1
LANG: C++
TASK: ride
*/

#include <cstdio>

int convertToInt(char* string)
{

	int product = 1;
	int index = 0;

	while (*(string + index) != '\0')
	{
		product *= *(string + index) - 65 + 1;
		index++;
	}

	return product;

}

int main()
{
	FILE* fin = fopen("ride.in", "r");
	FILE* fout = fopen("ride.out", "w");

	if(fin)
	{
		char* comet = new char[8];
		char* group = new char[8];

		fscanf(fin, "%s", comet);
		fscanf(fin, "%s", group);

		if(convertToInt(comet) % 47 == convertToInt(group) % 47)
			fprintf(fout, "%s\n", "GO");
		else
			fprintf(fout, "%s\n", "STAY");
	}	
}