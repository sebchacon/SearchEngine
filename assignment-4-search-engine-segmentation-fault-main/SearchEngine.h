#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <vector>
#include <string>
#include <queue>
#include <iostream>

#include "IndexHandler.h"
#include "DocumentParser.h"
#include "QueryEngine.h"

class SearchEngine
{
public:
    SearchEngine() = default;
    SearchEngine( const SearchEngine &) = default;
    SearchEngine &operator=(const SearchEngine &) = default;
    ~SearchEngine() = default;

    void ui(int, char**);
    //void buildTree(int, char**);
    void writeIndex();
    void searchIndex();
    void createIndex();
private:
    IndexHandler* handler;
};

#endif