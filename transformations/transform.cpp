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
            Square rotated(n);

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
            Square reflected(n);

            for(int row = 0; row < n; row++)
                for(int col = 0; col < n; col++)
                    reflected.setPoint(row, (n-1) - col, initial.getPoint(row, col));

            return reflected;
        }

        /* all possible transformations */
        enum Transformations { CW_90_DEG = 1, CW_180_DEG, CW_270_DEG, REFLECT, COMBO, NO_CHANGE, INVALID
        };

        /* Constructor */
        Square(int sideLength) { 
            //std::cout << "constructing" << std::endl;
            n = sideLength; 
            square = new bool[n * n]; 
        }

        /* Copy constructor */
        Square(const Square& s) {
            //std::cout << "copying" << std::endl;
            n = s.getLength();
            square = new bool[n * n];

            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    *(square + i * n + j) = s.getPoint(i,j);                    
        }

        /* Destructor */
        ~Square() {
            //std::cout << "destructing" << std::endl;
            delete[] square;
        }

        /* Move constructor */
        Square(Square&& s)
        {
            //std::cout << "moving" << std::endl;
        }

        friend void swap(Square& s1, Square& s2)
        {
            std::swap(s1.n, s2.n);
            std::swap(s1.square, s2.square);
        }

        /* Copy assignment operator */
        Square& operator=(Square s)
        {
            //std::cout << "copy assignmenting" << std::endl;
            swap(*this, s);
            return *this;
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

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            input >> c;

            original.setPoint(i, j, c);
        }
    }

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
 * Tests each of the conditions, returns the transformation code that was applied to get transformed from initial
 */
Square::Transformations recognizeTransformation(Square& initial, Square& transformed)
{
    Square::Transformations ret = Square::INVALID;

    /* Test NO_CHANGE */
    if(transformed == initial)
        ret = Square::NO_CHANGE;

    /* Test 90 Deg CW turn */
    Square temp = Square::rotate90DegCW(initial);
    if(transformed == temp)
        ret = Square::CW_90_DEG;

    std::cout << "After 90CW turn: " << std::endl;
    temp.printSquare();

    /* Test 180 Deg CW turn */
    temp = Square::rotate90DegCW(temp);
    if(transformed == temp)
        ret = Square::CW_180_DEG;

    /* Test 270 Deg CW turn */
    temp = Square::rotate90DegCW(temp);
    if(transformed == temp)
        ret = Square::CW_270_DEG;

    /* Test horizontal reflection */
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
    std::ifstream input("transform.in");

    int n;
    input >> n;

    Square initial(n);
    Square transformed(n);

    /* Read in and verify squares output */
    Transform_readSquares(input, initial, transformed);
    initial.printSquare();
    transformed.printSquare();

    /* Analyze transformation */
    Square::Transformations result = recognizeTransformation(initial, transformed);

    /* Write out */
    std::ofstream output("transform.out");
    output << result << std::endl;

    input.close();
    input.open("test3.in");
    input >> n;
    initial = Square(n);
    transformed = Square(n);
    Transform_readSquares(input, initial, transformed);
    initial.printSquare();
    transformed.printSquare();
    assert(recognizeTransformation(initial, transformed) == 2);

    /* Clean up */
    /* Don't need to do this on account of RAII (Resource Acquisition Is Initialization)
     input.close();
    output.close();
    */
}


