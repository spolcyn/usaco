/* transform.cpp */
/* Author: Stephen Polcyn */

#include <iostream>
#include <fstream>

bool interpretData(char c)
{
    return c == '@';
}

class Square {

public:
    Square(int sideLength) 
    { 
        n = sideLength; 
        square = new bool[n * n]; 
    }

    void setPoint(int i, int j, bool val)
    {
        *(square + i * n + j) = val;
    }

    void setPoint(int i, int j, char val)
    {
        *(square + i * n + j) = (val == '@');
    }

    bool getPoint(int i, int j)
    {
        return *(square + i * n + j);
    }

    int getLength()
    {
        return n;
    }

    void printSquare()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
                std::cout << toChar(getPoint(i, j));

            std::cout << std::endl;
        }
    }


private:
    char toChar(bool val)
    {
        return val ? '@' : '-';
    } 

     /* The side length of the square */
    int n;
    /* The array representing the square */
    bool* square;
};

/**
 * Reads characters from input into square initial and after
 */
static void Transform_readSquares(std::ifstream* input, Square* initial, Square* after)
{
    char c;
    int n = initial->getLength();

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
           *input >> c;

           initial->setPoint(i, j, c);
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
           *input >> c;

           after->setPoint(i, j, c);
        }
    }
}

/* Determines which transformation was applied in the file transform.in.
 * Writes the number of the transformation applied in the file transform.out.
 */
int main()
{
    /* Read input */
    std::ifstream* input;

    input->open("transform.in");

    int n;
    *input >> n;

    Square* initial = new Square(n);
    Square* after = new Square(n);
    
    Transform_readSquares(input, initial, after);

    initial->printSquare();
    after->printSquare();

    input->close();
}

    
