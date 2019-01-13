/* transform.cpp */
/* Author: Stephen Polcyn */

#include <stdio>
#include <fstream>

bool interpretData(char c)
{
    return c == '@';
}

class Square {

    Square(int sideLength) 
    { 
        n = sideLength; 
        square = new bool[n * n]; 
    }

    void setPoint(int i, int j, bool val)
    {
        *(i * n + j) = val;
    }

    void setPoint(int i, int j, char val)
    {
        *(i * n + j) = val == '@';
    }

private:
     /* The side length of the square */
    int n;
    /* The array representing the square */
    bool* square;
}

/* Determines which transformation was applied in the file transform.in.
 * Writes the number of the transformation applied in the file transform.out.
 */
int main()
{

    /* Read input */
    std::ifstream input;

    input.open("transform.in");

    int n;
    input >> n;

    Square s = new Square(n);

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

    
