#include "document.h"
using namespace std;

document::document() //create a new member that stores the document name the word and the incrementation of the word
{
    int num = 0;
    std::string docName;
    std::string word;
}
document::document(const document &rhs)
{
    num = rhs.num;
    docName = rhs.docName;
}
document::document(std::string &s, std::string &t, int x)
{
    num = x;
    docName = s;
    word = t;
}
document &document::operator=(const document &rhs)
{
    this->num = rhs.num;
    this->docName = rhs.docName;
    return *this;
}

int document::getNum() const {return num;} //getter and setters for all the data passed in
void document::setNum(const int &x) {num = x;}
string document::getName() const {return docName;}
void document::setName(const string &rhs) {docName = rhs;}
string document::getWord() const { return word; }
void document::setWord(const string &rhs) { word = rhs; }

void document::incNum() { ++num; } //incrementing the number of times a word is used in given document