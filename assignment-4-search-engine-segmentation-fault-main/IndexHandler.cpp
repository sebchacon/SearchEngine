#include "IndexHandler.h"


void IndexHandler::addWord(string& word, document& d) 
{
    wordTree.insert(word, d); //add a word to the given doc

}

void IndexHandler::addPerson(string& person, document& d) {
    personTree.insert(person, d); //add person to the given doc
}

void IndexHandler::addOrg(string& org, document& d) {
    orgTree.insert(org, d); //add org to the given doc

}


vector<string> IndexHandler::searchTree(vector<vector<string>> &key)
{
    cout<<"index" << endl;
    //search key in tree
    vector<document> results;
    vector<document> persons;
    vector<document> orgs;
    vector<document> words;
    bool found = false; 
   

    for(auto doc : key.at(0))
    {
        for(auto x : personTree.findDocs(doc))
            persons.push_back(x); //will find doc and then push 
           
             
    }
    cout<<"2";
    for(auto doc : key.at(1))
    {
        for(auto x : orgTree.findDocs(doc))
            orgs.push_back(x); //same
    }
    cout<<"3";
    for(auto doc : key.at(2))
    {
        for(auto x : wordTree.findDocs(doc))
            words.push_back(x); //same
         
    }
    
    if(persons.empty() || orgs.empty())
    {
        int tf = 0;
        if(!persons.empty())
        {
            for(auto person : persons)
            {
                for(auto word : words)
                {
                    if(person.getWord() == word.getWord())
                    {
                        if(!orgs.empty())
                        {
                            for(auto org : orgs)
                            {
                                if(org.getWord() == person.getWord())
                                {
                                    results.push_back(person);
                                    tf = 1;
                                    found = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if((!orgs.empty()) && (tf == 0))
        {
            for(auto org : orgs)
            {
                for(auto word : words)
                {
                    if(org.getWord() == word.getWord())
                    {
                        if(!persons.empty())
                        {
                            for(auto person : persons)
                            {
                                if(person.getWord() == org.getWord())
                                {
                                    results.push_back(org);
                                    found = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<"5";
    if(found == false)    
        results = words;

    vector<string> names;
    for(auto result : results)
    {
        names.push_back(result.getName());
    }

    return names;
}


void IndexHandler::write(){
    // wordTree.printToFile(wordTree, "./build/word_tree_print.txt");
    wordTree.printToFile(wordTree, "word_tree_print.txt"); //it will take the tree of each and print to its given file
    personTree.printToFile(personTree,"person_tree_print.txt");
    orgTree.printToFile(orgTree, "org_tree_print.txt");
}
void IndexHandler::read()
{
    wordTree.writeToTree(wordTree, "word_tree_print.txt"); //will call the matching file and read it back in from the file
    personTree.writeToTree(personTree, "person_tree_print.txt");
    orgTree.writeToTree(orgTree, "org_tree_print.txt");
}


void IndexHandler::print() {
    wordTree.prettyPrintTree(); //will print each individual tree
    personTree.prettyPrintTree();
    orgTree.prettyPrintTree();
}