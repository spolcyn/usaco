/*
ID: sp.shop1
LANG: C++
TASK: ride
*/

#include <cstdio>

int main()
{
	FILE* fin = fopen("ride.in", "r");

	if(fin)
	{
		char* comet = new char[6];
		char* group = new char[6];

		while(!feof(fin))
		{
			fscanf(fin, "%s", comet);
			fscanf(fin, "%s", group);

			printf("%s\n", comet);
			printf("%s\n", group);
		}
	}	
}