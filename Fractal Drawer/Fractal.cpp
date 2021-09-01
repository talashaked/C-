//
// Created by tal.shaked3 on 06/01/2020.
//

#include "Fractal.h"
#include <iostream>
#include <vector>
#include <cmath>

#define FILL '#'
#define BLANK ' '

/**
 * @brief - default constructor defined virtual so that inheriting classes would be
 * destructed before.
 */
Fractal::Fractal(int l, int i)
{
    _level = l;
    _numToDup = i;
}

/**
 * @brief - draw the fractal out to cout. this function uses checkWhatToFill, and according
 * to it fills in a table (constructed in our case as a vector) with '#' or ' '.
 */
void Fractal::draw()
{

    double numOfRows = pow(this->getFracSize(), this->getLevel());
    double numOfCols = numOfRows;
    std::vector<char> allPic;
    for (int row = 0; row < numOfRows; row++)
    {
        for (int col = 0; col < numOfCols; col++)
        {
            char toPut = checkWhatToFill(row, col);
            allPic.push_back(toPut);
        }
    }
    printFrac(allPic, numOfRows, numOfCols);
}

/**
 * @brief prints a given fractal that already is given as a vector of chars, and the
 * dimensions of this vectors lines and rows
 * @param frac - the fractal as a vector of chars
 * @param numOfRows - the number of rows that this vector is supposed to be divided in to.
 * @param numOfCols - the number of cols that this vector is supposed to be divided in to.
 */
void Fractal::printFrac(std::vector<char> frac, double numOfRows, double numOfCols)
{
    for (int i = 0; i < numOfRows * numOfCols; i++)
    {
        std::cout << frac[i];
        if (i > 0 && i % (int) numOfCols == numOfCols - 1)
        {
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

/**
 * @brief gets the dimension of the wanted fractal, and creates a SierpinskiCarpet
 * @param l - the dimension wanted
 */
SierpinskiCarpet::SierpinskiCarpet(int l) : Fractal(l, CARPETNUM)
{
}

/**
 * @brief - based on the algorithm that defines whether to fill this index or to leave it
 * empty, in a given fractal square table, this function get this index in a table and
 * returns the char to put in it, "#' or ' '.
 * @param row - the row of the index questioned
 * @param col - the col of the index questioned
 * @return -' ' or '#'
 */
char SierpinskiCarpet::checkWhatToFill(int row, int col) const
{
    while (row > 0 || col > 0)
    {
        if (row % getFracSize() == 1 && col % getFracSize() == 1)
        {
            return BLANK;
        }
        row /= getFracSize();
        col /= getFracSize();
    }
    return FILL;
}

/**
 * @brief gets the dimension of the wanted fractal, and creates a SierpinskiTriangle
 * @param l - the dimension wanted
 */
SierpinskiTriangle::SierpinskiTriangle(int l) : Fractal(l, TRIANGLENUM)
{
}

/**
 * @brief - based on the algorithm that defines whether to fill this index or to leave it
 * empty, in a given fractal square table, this function get this index in a table and
 * returns the char to put in it, "#' or ' '.
 * @param row - the row of the index questioned
 * @param col - the col of the index questioned
 * @return -' ' or '#'
 */
char SierpinskiTriangle::checkWhatToFill(int row, int col) const
{
    while (row > 0 || col > 0)
    {
        if (row % getFracSize() == 1 && col % getFracSize() == 1)
        {
            return BLANK;
        }
        row /= getFracSize();
        col /= getFracSize();
    }
    return FILL;
}

/**
 * @brief gets the dimension of the wanted fractal, and creates a Vicsek
 * @param l - the dimension wanted
 */
Vicsek::Vicsek(int l) : Fractal(l, VICSEKNUM)
{
}

/**
     * @brief - based on the algorithm that defines whether to fill this index or to leave it
     * empty, in a given fractal square table, this function get this index in a table and
     * returns the char to put in it, "#' or ' '.
     * @param row - the row of the index questioned
     * @param col - the col of the index questioned
     * @return -' ' or '#'
     */
char Vicsek::checkWhatToFill(int row, int col) const
{
    while (row > 0 || col > 0)
    {
        if ((row % getFracSize() == 0 && col % getFracSize() == 1) ||
            (row % getFracSize() == 1 && col % getFracSize() == 0) ||
            (row % getFracSize() == 2 && col % getFracSize() == 1) ||
            (row % getFracSize() == 1 && col % getFracSize() == 2))
        {
            return BLANK;
        }
        row /= getFracSize();
        col /= getFracSize();
    }
    return FILL;
}


