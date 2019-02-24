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

        /* Returns a new square equal to initial rotated 90 degrees clockwise */
        static Square rotate90DegCW(Square& initial)
        {
            int n = initial.getLength();
            Square rotated(n);

            /* rotate */
            for(int row = 0; row < n; row++)
                for(int col = 0; col < n; col++)
                    rotated.setPoint(col, (n-1) - row, initial.getPoint(row, col));

            return rotated;
        }

        /* Returns a new sqaure equal to initial reflected about a vertical line in the middle of the image */
        static Square reflectHorizontal(Square& initial)
        {
            int n = initial.getLength();
            Square reflected(n);

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

        Square(const Square& s) {
            n = s.getLength();
            square = new bool[n * n];

            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    *(square + i * n + j) = s.getPoint(i,j);                    
        }

        ~Square() {
            delete[] square;
        }

        friend void swap(Square& s1, Square& s2) {
            std::swap(s1.n, s2.n);
            std::swap(s1.square, s2.square);
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

        /** Operator Overloads **/
        Square& operator=(Square s) {
            swap(*this, s);
            return *this;
        }

        bool operator==(const Square& rhs)
        {
            if(this->getLength() != rhs.getLength())
                return false;

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
static void Transform_readSquares(std::ifstream& input, Square& original, Square& after)
{
    char c;
    int n = original.getLength();

    /* Read in original square */
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            input >> c;

            original.setPoint(i, j, c);
        }
    }

    /* Read in transformed square */
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            input >> c;

            after.setPoint(i, j, c);
        }
    }
}

/**
 * Tests each of the conditions, returns the transformation code that was applied to get transformed from original 
 */
Square::Transformations recognizeTransformation(Square& original, Square& transformed)
{
    Square::Transformations ret = Square::INVALID;

    /* Test 90 Deg CW turn */
    Square temp = Square::rotate90DegCW(original);
    if(transformed == temp)
        return Square::CW_90_DEG;

    /* Test 180 Deg CW turn */
    temp = Square::rotate90DegCW(temp);
    if(transformed == temp)
        return Square::CW_180_DEG;

    /* Test 270 Deg CW turn */
    temp = Square::rotate90DegCW(temp);
    if(transformed == temp)
        return Square::CW_270_DEG;

    /* Test horizontal reflection */
    temp = Square::reflectHorizontal(original);
    if(transformed == temp)
        return Square::REFLECT;

    /* Test if it's a combo with the reflection */
    for(int i = 0; i < 3; i++)
    {
        temp = Square::rotate90DegCW(temp);
        if(transformed == temp)
            return Square::COMBO;
    }

    /* Test NO_CHANGE */
    if(transformed == original)
        return Square::NO_CHANGE;

    return Square::INVALID;
}

/* Determines which transformation was applied in the file transform.in.
 * Writes the number of the transformation applied in the file transform.out.
 */
int main()
{
    /* Set up data structures */
    std::ifstream input("transform.in");

    int n;
    input >> n;
    Square original(n);
    Square transformed(n);

    /* Read in squares */
    Transform_readSquares(input, original, transformed);

    /* Analyze transformation */
    Square::Transformations result = recognizeTransformation(original, transformed);

    /* Write out */
    std::ofstream output("transform.out");
    output << result << std::endl;
}
