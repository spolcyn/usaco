/*
ID: sp.shop1
PROG: friday
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

#define START_YEAR 1900
#define START_MONTH 1
#define START_DAY 1

enum DAYS
{
	SATURDAY, SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY
};

enum MONTHS
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, NOVEMBER, DECEMBER
};

int main()
{
	ifstream fin("friday.in");
	ofstream fout("friday.out");

	short day = START_DAY, month = START_MONTH, year = START_YEAR, n, weekday = MONDAY;
	int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int thirteenthOccurences[] = {0, 0, 0, 0, 0, 0, 0};

	fin >> n;

	while(year < START_YEAR + n)
	{
		if(day == 13)
		{
			thirteenthOccurences[weekday] += 1;
		}

		if(day < daysInMonth[month])
		{
			day++;
		}
		else
		{
			month = (month + 1) % 13;  //next month

			if(month == 0)  //check for change of year
			{
				month++;
				year++;

				if(year % 4 == 0)  //check for leap year february
				{
					if(year % 100 == 0)
					{
						if(year % 400 == 0)
							daysInMonth[FEBRUARY] = 29;
						else
							daysInMonth[FEBRUARY] = 28;
					}
					else
						daysInMonth[FEBRUARY] = 29;
				}
				else
					daysInMonth[FEBRUARY] = 28;
			}

			day = 1;  //first day of month
		}

		weekday = (weekday + 1) % 7 == 0 ? SATURDAY : weekday + 1;  //new weekday
	}

	//output
	for(short day = SATURDAY; day <= FRIDAY; day++)
	{
		fout << thirteenthOccurences[day];

		if(day != FRIDAY)
			fout << " ";
	}

	fout << endl;
}