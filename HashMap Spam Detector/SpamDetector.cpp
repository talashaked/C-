//
// Created by tal.shaked3 on 21/01/2020.
//
#include <iostream>
#include "HashMap.hpp"
#include <string>
#include <fstream>
#include<boost/tokenizer.hpp>

typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

/**
 * @brief this function checks if a string is a valid number. if so returns true, if not returns
 * true,
 * @param a - the string to check
 * @param flag - if this flag equals 0, '0' is also legal. if the flag equas 1 it is not
 * @return
 */
bool checkStringIsValidNum(std::string const &a, int flag);

/**
 * @brief parses the db, given as a string. extracts out of it a hashmap (assuming it is given in
 * a csv format)
 * @param filename - the filename of the db
 * @param flag - a flag given as 0. if the flag value is changed after the function is called,
 * there was an error while reading the file.
 * @return - the extracted hashmap of the file
 */
HashMap<std::string, int> processDB(const std::string &filename, int &flag);

/**
 * @brief parses the text file into a string, lowering the letters
 * @param msgFile - the file containing the message that is needed to parse
 * @param flag - a flag given as 0. if the flag value is changed after the function is called,
 * there was an error while reading the file.
 * @return
 */
std::string messageParser(char *msgFile, int &flag);

/**
 * @brief this function counts the appearences of a word inside a given text
 * @param word - the word to check
 * @param msg - the whole text
 * @return - the count
 */
int countApInMsg(std::string &word, std::string &msg);

/**
 * @brief - recieves text as string, deep copies it, and then lowers the copy's letters
 * @param str - the str to change
 * @return - the copied string after lowering
 */
std::string lowercase(std::string &str);

int main(int argc, char *argv[])
{
    using namespace std;
    using namespace boost;
    if (argc != 4)
    {
        std::cerr << "Usage: SpamDetector <database path> <message path> <threshold>\n";
        exit(EXIT_FAILURE);
    }
    if (!checkStringIsValidNum(argv[3], 1))
    {
        std::cerr << "Invalid input\n";
        exit(EXIT_FAILURE);
    }
    try
    {
        int threshold;
        int flag = 0;
        sscanf(argv[3], "%d", &threshold);
        HashMap<string, int> hmDB;
        string s = argv[1];
        hmDB = processDB(s, flag);
        if (flag == -1)
        {
            return EXIT_FAILURE;
        }
        string message = (messageParser(argv[2], flag));
        if (flag == -1)
        {
            return EXIT_FAILURE;
        }
        int sum = 0, count, i = 0;
        for (auto p: hmDB)
        {
            i++;
            count = countApInMsg(p.first, message);
            sum += (count * p.second);
        }
        if (sum >= threshold)
        {
            cout << "SPAM" << endl;
        }
        else
        {
            cout << "NOT_SPAM" << endl;
        }
    }
    catch (NoKeyFoundException &e)
    {
        std::cout << e.what() << endl;
    }
    catch (VectorDontMatchException &e)
    {
        std::cout << e.what() << endl;
    }
    return 0;
}

bool checkStringIsValidNum(std::string const &a, int flag)
{
    int numA = 0;
    sscanf(a.c_str(), "%d", &numA);
    int length = std::to_string(numA).length();
    if (length == (int) a.length())
    {
        if (numA >= 0 && flag == 0)
        {
            return true;
        }
        else if (numA > 0 && flag == 1)
        {
            return true;
        }
    }
    return false;
}

HashMap<std::string, int> processDB(const std::string &filename, int &flag)
{
    using namespace std;
    std::ifstream readFile(filename);
    if (!readFile.is_open())
    {
        std::cerr << "Invalid input\n";
        flag = -1;
        HashMap<string, int> h;
        return h;
    }
    string line;
    HashMap<std::string, int> hmDB{};
    vector<string> vectorOfLine;
    string word;
    int damage;
    boost::char_separator<char> sep{","};
    while (getline(readFile, line))
    {
        if (line.find_first_of(',') != line.find_last_of(','))
        {
            readFile.close();
            std::cerr << "Invalid input\n";
            flag = -1;
            HashMap<string, int> h;
            return h;
        }
        tokenizer tok{line, sep};
        vectorOfLine.assign(tok.begin(), tok.end());
        if (distance(tok.begin(), tok.end()) != 2)
        {
            readFile.close();
            std::cerr << "Invalid input\n";
            flag = -1;
            HashMap<string, int> h;
            return h;
        }
        if (checkStringIsValidNum(vectorOfLine[1], 0))
        {
            sscanf(vectorOfLine[1].c_str(), "%d", &damage);
            string key = lowercase(vectorOfLine[0]);
            hmDB[key] = damage;
        }
        else
        {
            readFile.close();
            std::cerr << "Invalid input\n";
            flag = -1;
            HashMap<string, int> h;
            return h;
        }
    }
    readFile.close();
    return hmDB;
}

std::string lowercase(std::string &str)
{
    std::string word = str;
    for (auto &c:word)
    {
        c = ::tolower(c);
    }
    return word;
}


std::string messageParser(char *msgFile, int &flag)
{
    std::ifstream readFile(msgFile);
    std::string txt, allT;
    if (!readFile.is_open())
    {
        std::cerr << "Invalid input\n";
        flag = -1;
        return txt;
    }
    while (getline(readFile, txt))
    {
        std::string ltext = lowercase(txt);
        allT += ltext;
        allT += "\n";
    }
    readFile.close();
    return allT;
}

int countApInMsg(std::string &word, std::string &msg)
{
    int count = 0;
    int mlen = msg.length();
    int wlen = word.length();
    for (int i = 0; i < (mlen - wlen); i++)
    {
        std::string ss = msg.substr(i, wlen);
        if (word == ss)
        {
            count++;
        }
    }
    return count;

}