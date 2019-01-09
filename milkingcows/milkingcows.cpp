/*
ID: sp.shop1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Farmer {
    int startTime, endTime;
};

/* Comparison methods for sort */
bool compareFarmerStart(Farmer f1, Farmer f2)
{
    return f1.startTime < f2.startTime;
}

bool compareFarmerEnd(Farmer f1, Farmer f2)
{
    return f1.endTime < f2.endTime;
}


/* Returns the start/end time for farmer farmerNumber in the array of farmers 'farmers' */
int getFarmerStart(int farmerNumber, std::vector<Farmer> *farmers) {
    return farmers->at(farmerNumber).startTime;
}
int getFarmerEnd(int farmerNumber, std::vector<Farmer> *farmers) {
    return farmers->at(farmerNumber).endTime;
}

/* Writes to milk2.out a single line with two integers that represent the longest continuous time
 * of milking and the longest idle time
 */
int main()
{
    int numberOfFarmers;
    /* Start/stop times of farmers. */
    std::vector<Farmer> *farmers;

    std::ifstream input;
    input.open("milk2.in");

    /* Read in the farmers stop/start times */
    input >> numberOfFarmers;

    farmers = new std::vector<Farmer>(numberOfFarmers);

    for(int i = 0; i < numberOfFarmers; i++)
    {
        input >> farmers->at(i).startTime;
        input >> farmers->at(i).endTime;
    }

    input.close();

    /* Compute milking & idle times */
    std::sort(farmers->begin(), farmers->end(), compareFarmerStart);

    int currentStart, currentEnd;
    int longestMilk, longestIdle;

    currentStart = getFarmerStart(0, farmers);
    currentEnd = getFarmerEnd(0, farmers);

    longestMilk = currentEnd - currentStart;
    longestIdle = 0;

    for(Farmer f : *farmers)
    {
        /* if the next farmer starts before the previous ends, extend the continuous milking */
        if(f.startTime <= currentEnd)
        {
            if(f.endTime > currentEnd)
                currentEnd = f.endTime;
        }
        else
        {
            /* compare current milking and idle to previous records */
            if(currentEnd - currentStart > longestMilk)
                longestMilk = currentEnd - currentStart;
            if(f.startTime - currentEnd > longestIdle)
                longestIdle = f.startTime - currentEnd;
            
            /* Reset chain after breakage */
            currentStart = f.startTime;
            currentEnd = f.endTime;
        }
    }

    /* Output results */
    std::ofstream output;

    output.open("milk2.out");
    output << longestMilk << " " << longestIdle << std::endl;
    output.close();

	return 0;
}
