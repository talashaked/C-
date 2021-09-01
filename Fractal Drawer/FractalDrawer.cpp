
#include "Fractal.h"
#include<boost/tokenizer.hpp>
#include <iostream>
#include <fstream>

/**
 * @brief checking if to given strings are valid numbers to our program
 * @param a - the supposedly index of the wanted fractal
 * @param b - the supposedly dimension of the wanted fractal
 * @return - true or false
 */
bool checkTwoStringAreValidNums(std::string const &a, std::string const &b);

/**
 * @brief a factory that creates fractals according to the input
 * @param index - a is in {1,2,3}
 * @param dim - 0<b<7
 * @return a pointer to a newly created fractal
 */
Fractal *fractalD(int index, int dim);

int main(int argc, char *argv[])
{
    using namespace std;
    using namespace boost;
    if (argc != 2)
    {
        std::cerr << "Usage: FractalDrawer <file path>\n";
        exit(EXIT_FAILURE);
    }
    string fileS(argv[1]);
    ifstream inp(fileS.c_str());
    if (!inp.is_open())
    {
        std::cerr << "Invalid input\n";
        exit(EXIT_FAILURE);
    }
    string line;
    vector<Fractal *> vectorOfProccess;
    vector<string> vectorOfLine;
    int indexFractal, dimFractal;
    while (getline(inp, line))
    {
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        boost::char_separator<char> sep{","};
        tokenizer tok{line, sep};
        vectorOfLine.assign(tok.begin(), tok.end());
        if (distance(tok.begin(), tok.end()) != 2)
        {
            std::cerr << "Invalid input\n";
            exit(EXIT_FAILURE);
        }
        if (checkTwoStringAreValidNums(vectorOfLine[0], vectorOfLine[1]))
        {
            sscanf(vectorOfLine[0].c_str(), "%d", &indexFractal);
            sscanf(vectorOfLine[1].c_str(), "%d", &dimFractal);
            Fractal *curFractal = fractalD(indexFractal, dimFractal);
            vectorOfProccess.push_back(curFractal);
        }
        else
        {
            std::cerr << "Invalid input\n";
            exit(EXIT_FAILURE);
        }

    }
    Fractal *f;
    while (!vectorOfProccess.empty())
    {
        f = vectorOfProccess.back();
        f->draw();
        vectorOfProccess.pop_back();
        delete (f);
    }
}

Fractal *fractalD(int index, int dim)
{
    switch (index)
    {
        case 1:
            return new SierpinskiCarpet(dim);
        case 2:
            return new SierpinskiTriangle(dim);
        case 3:
            return new Vicsek(dim);
        default:
            return nullptr;
    }
}

bool checkTwoStringAreValidNums(std::string const &a, std::string const &b)
{
    int numA = 0, numB = 0;
    if (sscanf(a.c_str(), "%d", &numA) == (int) a.length() &&
        sscanf(b.c_str(), "%d", &numB) == (int) b.length())
    {
        if (numA >= 1 && numA <= 3 && numB > 0 && numB < 7)
        {
            return true;
        }
    }
    return false;

}