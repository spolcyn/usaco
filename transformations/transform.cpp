/* transform.cpp */
/* Author: Stephen Polcyn */

#include <iostream>
#include <fstream>

/* Represents a square with a grid inside */
class Square {

public:
    
    /* Returns true if s1 and s2 have the same sidelength, false otherwise */
    static bool verifySameDimensions(Square* s1, Square* s2)
    {
        return s1->getLength() == s2->getLength();
    }

    /* Returns a square equal to initial rotated 90 degrees clockwise */
    static Square* rotate90DegCW(Square* initial)
    {
        Square* rotated = new Square(initial);

        return rotated;
    }

    /* all possible transformations */
    enum Transformations { CW_90_DEG, CW_180_DEG, CW_270_DEG, REFLECT, COMBO, NO_CHANGE, INVALID
    };

    Square(int sideLength) 
    { 
        n = sideLength; 
        square = new bool[n * n]; 
    }

    Square(Square* s)
    {
        n = s->getLength();
        square = new bool[n * n];
    }


    /* 0-indexed*/
    void setPoint(int i, int j, bool val)
    {
        *(square + i * n + j) = val;
    }

    /* 0-indexed */
    void setPoint(int i, int j, char val)
    {
        *(square + i * n + j) = (val == '@');
    }

    /* 0-indexed */
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

    /* Checks if this square was rotated 180 degrees CW relative to original */
    /* Returns True if so, false otherwise. */
    bool analyze180CW(Square* original)
    {
        assert(verifySameDimensions(this, original));

        /* Inefficiency: Doesn't skip center row on n is odd length squares */
        for(int row = 0; row < n; row++)
        {
            for(int col = 0; col < n; col++)
            {
                if(getPoint(row, col) != original->getPoint((n-1) - row, (n-1) - col))
                    return false;
            }
        }

        return true;
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
    /* Set up data structures */
    std::ifstream* input = new std::ifstream("transform.in", std::ifstream::in);

    int n;
    *input >> n;

    Square* initial = new Square(n);
    Square* after = new Square(n);
    
    /* Read in and verify squares output */
    Transform_readSquares(input, initial, after);

    initial->printSquare();
    after->printSquare();

    /* Clean up */
    delete(initial);
    delete(after);
    delete(input);
    input->close();

    input = new std::ifstream("180CW.in", std::ifstream::in);
    *input >> n;
    initial = new Square(n);
    after = new Square(n);
    Transform_readSquares(input, initial, after);
    initial->printSquare();
    after->printSquare();
    std::cout << after->analyze180CW(initial) << std::endl;

    delete(input);
}

    
