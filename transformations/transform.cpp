/* transform.cpp */
/* Author: Stephen Polcyn */

#include <stdio>
#include <fstream>

/* Determines which transformation was applied in the file transform.in.
 * Writes the number of the transformation applied in the file transform.out.
 */
int main()
{
    /* The side length of the square */
    int n;
    /* The array representing the square */
    bool* square;

    /* Read input */
    std::ifstream input;

    input.open("transform.in");

    input >> n;
    square = new bool[n * n];

    char c;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
           input >> c;

           if(c == '@')
               // edit data
           else
               // edit data
        }
    }

}

    
