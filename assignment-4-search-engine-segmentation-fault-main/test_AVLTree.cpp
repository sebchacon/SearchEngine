#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <iostream>
#include <vector>
#include <string>

#include "DSAVLTree.h"
#include "document.h"

using namespace std;

TEST_CASE("Check that AVL Tree works", "[DSAVLTree]")
{


    DSAVLTree tree;

    for(int i = 0; i < 10; ++i)
    {
        string number = to_string(i);
        document doc(number, number, i);
        tree.insert(number, doc);
    }

    REQUIRE(!tree.isEmpty());

     tree.prettyPrintTree();
    

     string rem = "5";
  
     tree.remove(rem);

    //  tree.prettyPrintTree();

    REQUIRE(!tree.contains(rem));

     DSAVLTree tree2 = tree;

    REQUIRE(tree2.maxDepth() == 3);

    string four = "4";
    string one = "1";
    string two = "2";
    string three = "3";
    string six = "6";
    

    tree2.remove(one);
    tree2.remove(two);
    tree2.remove(three);
    tree2.remove(four);
    tree2.remove(six);

    REQUIRE(tree2.maxDepth() == 2);


}