/*
ID: sp.shop1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

struct Farmer {
    int startTime, endTime;
};

/* Returns the start/end time for farmer farmerNumber in the array of farmers 'farmers' */
int getFarmerStart(int farmerNumber, Farmer* farmers) {
    return (farmers + farmerNumber)->startTime;
}
int getFarmerEnd(int farmerNumber, Farmer* farmers) {
    return (farmers + farmerNumber)->endTime;
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
    Farmer* farmers; // farmer data

    std::ifstream input;
    input.open("milk2.in");

    /* Read in the farmers stop/start times */
    input >> numberOfFarmers;

    farmers = new Farmer[numberOfFarmers];

    for(int i = 0; i < numberOfFarmers; i++)
    {
        input >> (farmers + i)->startTime;
        input >> (farmers + i)->endTime;
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
