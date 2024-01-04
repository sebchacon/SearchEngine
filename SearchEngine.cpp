#include "SearchEngine.h"


void SearchEngine::ui(int argc, char** argv)
{
    //the following if statements detect what the user wants to do using the search engine
    if(string(argv[1]) == "index")
    {
        IndexHandler handler;
        DocumentParser doc(&handler);
        cout << argv[2] << endl;
        doc.fileSystem(argv[2]);
        
        handler.write();
    }
    if(string(argv[1]) == "query")
    {
        IndexHandler handler;
        handler.read();
        handler.print();        
    }
    if(string(argv[1]) == "ui")
    {
        bool input = true;
        string command;
        handler = new IndexHandler();
        while(input)
        { //while there is an input we will prompt user with optuons a,b,c, and d
            std::cout << "a : create an index from a directory" << std::endl;
            std::cout << "b : write to an index" << std::endl;
            std::cout << "c : Search index by query " << std::endl;
            std::cout << "d : exit " <<std::endl;
            std::cout << "Enter command: ";
            getline(cin, command);

            if (command == "A" || command == "a")
            {
                createIndex();
            }
            if (command == "B" || command == "b")
            {
                writeIndex();
            }
            if (command == "C" || command == "c")
            {
                searchIndex();
            }
            if (command == "D" || command == "d")
            {
                input = false;
            }
        }
        delete handler;

    }

   
}

void SearchEngine::writeIndex()
{
    handler->write(); //calls to write
}

void SearchEngine::searchIndex()
{
    //need to create the trees before searching the trees 
    vector<vector<string>> x;
    QueryEngine que;
    que.query();
    x = que.parseInput();
    vector<string> results = handler->searchTree(x);

    cout<< "Results based on Query: " <<endl;
    for(auto result : results)
    {
        cout<<"  -" << result << endl;
    }
}

void SearchEngine::createIndex() 
{
    std::cout << "Enter filename: "; //will create a new filename index
    string filename;
    getline(cin, filename);

    DocumentParser doc(handler);
    doc.fileSystem(filename);
    
}
