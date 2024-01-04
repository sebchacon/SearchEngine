#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>
#include <iostream>

class document
{
private:
    int num;
    std::string docName;
    std::string word;

public:
    document();
    document(const document &);
    document(std::string &, std::string &,int);
    document &operator=(const document &);
    ~document() = default;

    int getNum() const;
    void setNum(const int &);
    std::string getName() const;
    void setName(const std::string &);
    std::string getWord() const;
    void setWord(const std::string &);
    void incNum();
};
#endif