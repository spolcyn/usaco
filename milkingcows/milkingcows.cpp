/*
ID: sp.shop1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    int numberOfFarmers;
    /* Start/stop times of farmers. 
     * Farmer N's start in [2N], stop in [2N+1]
     */
    int* farmerTimes; // start/stop times of farmers. 
    int bufferSize = 10;
    char buffer[bufferSize];

    std::ifstream input;
    input.open("milk2.in");

/*    input.get(buffer, bufferSize);
    numberOfFarmers = std::stoi(buffer, nullptr, 10); */
    input >> numberOfFarmers;

//    while(input.get(buffer, bufferSize))


    std::cout << "Number of farmers: " << numberOfFarmers << std::endl;

    input.close();

	return 0;
}
