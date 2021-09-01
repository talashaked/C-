//
// Created by tal.shaked3 on 06/01/2020.
//
#include <vector>

#ifndef UNTITLED_FRACTAL_H
#define UNTITLED_FRACTAL_H


#define CARPETNUM 3
#define TRIANGLENUM 2
#define VICSEKNUM 3

/**
 * @brief - an abstract fractal class, consisting of a constructor, a virtual defaultive
 * destructor and more. in order to derive this class, implentation of the function
 * checkWhatToFill is neccessary.
 */
class Fractal
{
private:
    int _level;
    int _numToDup;


public:
    /**
     * @brief constructor
     * @param l - the dimension of the fractal
     * @param i - the number of the base fractal duplication
     */
    Fractal(int l, int i);

    /**
     * @brief - default constructor defined virtual so that inheriting classes would be
     * destructed before.
     */
    virtual ~Fractal() = default;

    /**
     * @brief - draw the fractal out to cout. this function uses checkWhatToFill, and according
     * to it fills in a table (constructed in our case as a vector) with '#' or ' '.
     */
    void draw();

    /**
     * @brief prints a given fractal that already is given as a vector of chars, and the
     * dimensions of this vectors lines and rows
     * @param frac - the fractal as a vector of chars
     * @param numOfRows - the number of rows that this vector is supposed to be divided in to.
     * @param numOfCols - the number of cols that this vector is supposed to be divided in to.
     */
    void static printFrac(std::vector<char> frac, double numOfRows, double numOfCols);

    /**
     * @brief a virtual function not implemented here
     * @param row - that current index row
     * @param col -the current index col
     * @return - the char is needed to be filled in this index in the fractal
     */
    virtual char checkWhatToFill(int row, int col) const = 0;

    /**
     * @return the level of the fractal wanted (=dimension)
     */
    int getLevel() const
    {
        return this->_level;
    }

    /**
     * @return returns the base multiplier of the fractal (for instance the Vicsek is 3)
     */
    int getFracSize() const
    {
        return _numToDup;
    }

};

/**
 * @brief - the Sierpinski Carpet fractal class, derives from fractal
 */
class SierpinskiCarpet : public Fractal
{
public:
    /**
     * @brief gets the dimension of the wanted fractal, and creates a SierpinskiCarpet
     * @param l - the dimension wanted
     */
    explicit SierpinskiCarpet(int l);

    /**
     * @brief - based on the algorithm that defines whether to fill this index or to leave it
     * empty, in a given fractal square table, this function get this index in a table and
     * returns the char to put in it, "#' or ' '.
     * @param row - the row of the index questioned
     * @param col - the col of the index questioned
     * @return -' ' or '#'
     */
    char checkWhatToFill(int row, int col) const override;
};

/**
 * @brief the Sierpinski Triangle fractal class, derives from fractal
 */
class SierpinskiTriangle : public Fractal
{
public:
    /**
     * @brief gets the dimension of the wanted fractal, and creates a SierpinskiTriangle
     * @param l - the dimension wanted
     */
    explicit SierpinskiTriangle(int l);

    /**
     * @brief - based on the algorithm that defines whether to fill this index or to leave it
     * empty, in a given fractal square table, this function get this index in a table and
     * returns the char to put in it, "#' or ' '.
     * @param row - the row of the index questioned
     * @param col - the col of the index questioned
     * @return -' ' or '#'
     */
    char checkWhatToFill(int row, int col) const override;
};

/**
 * @brief the Vicsek fractal class, derives from fractal
 */
class Vicsek : public Fractal
{
public:
    /**
     * @brief gets the dimension of the wanted fractal, and creates a Vicsek
     * @param l - the dimension wanted
     */
    explicit Vicsek(int l);

    /**
     * @brief - based on the algorithm that defines whether to fill this index or to leave it
     * empty, in a given fractal square table, this function get this index in a table and
     * returns the char to put in it, "#' or ' '.
     * @param row - the row of the index questioned
     * @param col - the col of the index questioned
     * @return -' ' or '#'
     */
    char checkWhatToFill(int row, int col) const override;
};

#endif //UNTITLED_FRACTAL_H
