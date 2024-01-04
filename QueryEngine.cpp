#include "QueryEngine.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


vector<vector<std::string>> QueryEngine::parseInput()
{
    vector<string> p;
    vector<string> o;
    vector<string> w;
    vector <string> badWord;
    vector<vector<string>> result;
    result.push_back(p);
    result.push_back(o);
    result.push_back(w);
    result.push_back(badWord);
    // look through the vector of words, if PERSON/ORG is i , push the i+1 into the corresponding vector
    for (int i = 0; i < temp.size(); i++)
    {
        //person or org can only be one word for now 
        string person = "PERSON:";
        string org= "ORG:";
        if (temp[i].substr(0, person.size()) == person)
        {
            //need to remove PERSON: from the front of the string before u push it 
            //people.push_back(temp[i + 1]);
            result.at(0).push_back(temp[i].substr(person.size()));
            ++i;
            continue;
        }
        else if (temp[i].substr(0, org.size()) == org)
        {
            //if necessary, enter the not query before the person and/or org 
            result.at(1).push_back(temp[i].substr(org.size()));
            ++i;    
            continue;
        }
        else
        {
            // if there is no dash in front of the word, add it to the stack of other words
            if (dashCompare(temp[i]) != true)
            {
                //words.push_back(temp[i]);
                result.at(2).push_back(temp[i]);

            }
            if(dashCompare(temp[i])==true){
                result.at(3).push_back(temp[i]);
            }
        }
    }

    //return docValue object that holds 3 vectors of persons, orgs, words
    return result;
}

// if there is a - in front of the word, return true
bool QueryEngine::dashCompare(const std::string &a)
{
    if (a[0] == '-') //detects if dash then if it is true returns true if not false
    {
        return true;
    }
    else
    {
        return false;
    }
}
void QueryEngine::query()
{
    // get user input and read in the line
    std::string userInput;
    std::cout << "Enter search: ";
    std::getline(std::cin, userInput);

    std::istringstream iss(userInput);
    std::string word;
    // split the input string into words and push it back to vector
    while (iss >> word)
    {
        temp.push_back(word);
    }

    // parseInput(temp);
}