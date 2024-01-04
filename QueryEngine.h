#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class QueryEngine
{

private:
    // should i make a 2d vector to pass into the next class or should i do it as 3 seperate vectprs?
    std::vector<std::string> people;
    std::vector<std::string> orgs;
    std::vector<std::string> words;
    std::vector<std::string> temp;


public:
    QueryEngine() = default;
    std::vector<std::vector<std::string>> parseInput();
    bool dashCompare(const std::string &);
    void query();
};

#endif
