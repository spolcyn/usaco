/*
ID: sp.shop1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

int getFarmerStart(int farmerNumber, int* farmerTimes)
{
    return *(farmerTimes + farmerNumber * 2);
}

int getFarmerEnd(int farmerNumber, int* farmerTimes)
{
    return *(farmerTimes + farmerNumber * 2 + 1);
}

int main()
{
    int numberOfFarmers;
    /* Start/stop times of farmers. 
     * Farmer N's start in [2N], stop in [2N+1]
     */
    int* farmerTimes; // start/stop times of farmers. 

    std::ifstream input;
    input.open("milk2.in");

    /* Read in the farmers stop/start times */
    input >> numberOfFarmers;

    farmerTimes = new int[numberOfFarmers * 2];

    for(int i = 0; i < numberOfFarmers; i++)
    {
        input >> *(farmerTimes + i * 2);
        input >> *(farmerTimes + i * 2 + 1);
    }

    std::cout << "Number of farmers: " << numberOfFarmers << std::endl;

    for(int i = 0; i < numberOfFarmers; i++)
    {
        std::cout << getFarmerStart(i, farmerTimes) << ' ';
        std::cout << getFarmerEnd(i, farmerTimes);
        std::cout << std::endl;
    }

    input.close();

	return 0;
}
