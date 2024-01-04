#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <filesystem>
#include <cctype>


#include <sstream>
#include <unordered_map>
#include "document.h"
#include "porter2_stemmer.h"
#include "IndexHandler.h"

//move into a cpp create stemmer h file 
//put stemnmner class in here

// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

using namespace std;

class DocumentParser
{
private:
   IndexHandler* handler;

public:
    DocumentParser() = default;
    explicit DocumentParser(IndexHandler*);
    // vector<docValue> keywordFind();
    void readJson(const string &fileName);
    void fileSystem(const string &path);
    bool removeStopWords(std::string);
    std::string stemmingWords(std::string words); // will fix grammar USE WEBSITES
    int frequency(std::string& word);         // will search up how many times this certain word is used
    std::string cleanWords(const std::string words);
};


#endif