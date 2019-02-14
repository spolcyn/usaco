/*
ID: sp.shop1
LANG: C++
PROG: transform
*/
/* Author: Stephen Polcyn */

#include <iostream>
#include <fstream>

/* Represents a square with a grid inside */
class Square {

    public:

        /* Returns true if s1 and s2 have the same sidelength, false otherwise */
        static bool verifySameDimensions(Square& s1, Square& s2)
        {
            return s1.getLength() == s2.getLength();
        }

        /* Returns a new square equal to initial rotated 90 degrees clockwise */
        static Square rotate90DegCW(Square& initial)
        {
            int n = initial.getLength();
            Square rotated = Square(n);

            /* do the rotation */
            for(int row = 0; row < n; row++)
                for(int col = 0; col < n; col++)
                    rotated.setPoint(col, (n-1) - row, initial.getPoint(row, col));

            return rotated;
        }

        /* Returns a new sqaure equal to initial reflected about a vertical line in the middle of the image */
        static Square reflectHorizontal(Square& initial)
        {
            int n = initial.getLength();
            Square reflected = Square(n);

            for(int row = 0; row < n; row++)
                for(int col = 0; col < n; col++)
                    reflected.setPoint(row, (n-1) - col, initial.getPoint(row, col));

            return reflected;
        }


        /* all possible transformations */
        enum Transformations { CW_90_DEG = 1, CW_180_DEG, CW_270_DEG, REFLECT, COMBO, NO_CHANGE, INVALID
        };

        Square(int sideLength) { 
            n = sideLength; 
            square = new bool[n * n]; 
        }

        Square(Square* s) {
            n = s->getLength();
            square = new bool[n * n];
        }

        ~Square() {
            delete square;
        }

        /* 0-indexed*/
        void setPoint(int i, int j, bool val) {
            *(square + i * n + j) = val;
        }

        /* 0-indexed */
        void setPoint(int i, int j, char val) {
            *(square + i * n + j) = (val == '@');
        }

        /* 0-indexed */
        bool getPoint(int i, int j) const {
            return *(square + i * n + j);
        }

        int getLength() const {
            return n;
        }

        void printSquare() const {
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                    std::cout << toChar(getPoint(i, j));

                std::cout << std::endl;
            }
        }

        /* Tests if this object and rhs are the same dimensions and have 
         * the same entries at the same positions.
         * Returns TRUE if the same, FALSE otherwise.
         */
        bool operator==(const Square& rhs)
        {
            Square::verifySameDimensions(this, &rhs);

            int n = getLength();

            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    if(getPoint(i, j) != rhs.getPoint(i, j))
                        return false;

            return true;
        }

    private:
        char toChar(bool val) const {
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

/**
 * Tests each of the conditions, returns the transformation code that was applied to get transformed from initial
 */
Square::Transformations recognizeTransformation(Square& initial, Square& transformed)
{
    Square::Transformations ret = Square::INVALID;

    if(transformed == initial)
        ret = Square::NO_CHANGE;

    Square temp = Square::rotate90DegCW(initial);
    if(transformed == temp)
        ret = Square::CW_90_DEG;

    temp = Square::rotate90DegCW(temp);

    if(transformed == temp)
        ret = Square::CW_180_DEG;

    temp = Square::rotate90DegCW(temp);

    if(transformed == temp)
        ret = Square::CW_270_DEG;

    temp = Square::reflectHorizontal(initial);

    if(transformed == temp)
        ret = Square::REFLECT;

    /* Test if it's a combo with the reflection */
    for(int i = 0; i < 3; i++)
    {
        temp = Square::rotate90DegCW(temp);
        if(transformed == temp)
        {
            ret = Square::COMBO;
            break;
        }
    }

    return ret;
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
    Square* transformed = new Square(n);

    /* Read in and verify squares output */
    Transform_readSquares(input, initial, transformed);
/*    std::cout << "Test rotate 90 CW: Expected: " << Square::CW_90_DEG << " Actual: " << recognizeTransformation(initial, after) << std::endl;
    std::cout << "Test same squares: Expected: " << Square::NO_CHANGE << " Actual: "  << recognizeTransformation(initial, initial) << std::endl;

    std::cout << "initial: " << std::endl;
    initial->printSquare();
    std::cout << "final: " << std::endl;
    after->printSquare();
    std::cout << "rotated" << std::endl;
    Square* temp = Square::rotate90DegCW(initial);
    temp->printSquare();
    bool test = (*temp == *after);
    std::cout << "Equal? (expect 1): " << test << std::endl;

    std::cout << "reflected" << std::endl;
    (Square::reflectHorizontal(initial))->printSquare();
*/
    /* Analyze transformation */
    Square::Transformations result = recognizeTransformation(*initial, *transformed);

    /* Write out */
    std::ofstream output;
   output.open("transform.out");
    output << result << std::endl;
    output.close();

    /* Clean up */
    input->close();
    delete initial;
    delete transformed;
    delete input;
}


