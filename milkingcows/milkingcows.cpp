/*
ID: sp.shop1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>

int main()
{
    int numberOfFarmers;
    /* Start/stop times of farmers. 
     * Farmer N's start in [2N], stop in [2N+1]
     */
    int* farmerTimes; // start/stop times of farmers. 
    int bufferSize = 5;
    char buffer[bufferSize];

    std::ifstream input;
    input.open("milk2.in");

    input.get(buffer, bufferSize);
    std::cout << "Number of farmers: " << buffer << std::endl;

    input.close();

	return 0;
}
