#ifndef INDEX_HANDLER_H
#define INDEX_HANDLER_H

#include <iostream>
#include <vector>
#include <utility>

#include "DSAVLTree.h"
#include "document.h"

using namespace std;

class IndexHandler
{
private:
    DSAVLTree wordTree;
    DSAVLTree personTree;
    DSAVLTree orgTree;
public:
    IndexHandler() = default;
    void addWord(string&, document&);
    void addPerson(string&, document&);
    void addOrg(string&, document&);

    vector<string> searchTree(vector<vector<string>> &);
    void write();
    void read();
    void print();
};

#endif