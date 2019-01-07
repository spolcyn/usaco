/*
ID: sp.shop1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Farmer {
    int startTime, endTime;
};

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
    /* Start/stop times of farmers. 
     * Farmer N's start in [2N], stop in [2N+1]
     */
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

   /* Test Data Read Code */
    std::cout << "Number of farmers: " << numberOfFarmers << std::endl;

    for(int i = 0; i < numberOfFarmers; i++)
    {
        std::cout << getFarmerStart(i, farmers) << ' ';
        std::cout << getFarmerEnd(i, farmers);
        std::cout << std::endl;
    }

    input.close();

	return 0;
}
