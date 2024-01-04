#ifndef DSAVLTREE_H
#define DSAVLTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "document.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

class DSAVLTree
{
private:
    struct Node
    {
    public:
        std::string key;
        vector<document> documents;
        Node* left;
        Node* right;
        int height;

        Node(const std::string &theKey, const vector<document> &rhs, Node* lt, Node* rt, int h) :
         key{theKey}, documents{rhs}, left{lt}, right{rt}, height{h} {}

        Node(const std::string &theKey, const document &rhs, Node* lt, Node* rt, int h) :
         key{theKey}, left{lt}, right{rt}, height{h} {
            documents.push_back(rhs);
         }
    };

    Node* root;
public:
    DSAVLTree() { root = nullptr; }

    DSAVLTree(const DSAVLTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    ~DSAVLTree()
    {
        makeEmpty(root);
    }

    DSAVLTree &operator=(const DSAVLTree &rhs)
    {
        makeEmpty(root);

        root = clone(rhs.root);
        return *this;
    }

    void addFrequency(const string &key, const document &rhs) {
        Node* t = find(key, root);

        for (int i = 0; i < t->documents.size(); ++i) {
            if (t->documents.at(i).getName() == rhs.getName()) {
                t->documents.at(i).setNum(t->documents.at(i).getNum() + 1);
            }
        }
    }

    bool containsDocument(const string &key, const document &rhs) {
        Node* t = find(key, root);

        for (int i = 0; i < t->documents.size(); ++i) {
            if (t->documents.at(i).getName() == rhs.getName()) {
                return true;
            }
        }

        return false;
    }

    bool isEmpty() const
    {
        return (root == nullptr);
    }

    void insert(const string &key, const document &rhs)
    {
        // insert(key, rhs);
        insert(key, rhs, root);
    }

    void remove(const std::string &rhs)
    {
        remove(rhs, root); //will remove from tree
    }

    bool contains(const std::string &rhs) const
    {
        return (find(rhs, root) != nullptr);  //detects if the part of tree has a value
    }

    void add(const string &key, const document &d)
    {
        add(key, d, root); //add to tree
    }

    vector<document> findDocs(const std::string &key)
    {
        // return (findDocs(key, root));
        return findDocs(key, root);
    }

    int maxDepth()
    {
        return maxDepth(root, -1); // we start with a depth of -1 in case there is no root node
    }

    /**
     * @brief Print the tree contents in sorted order (i.e., inorder traversal).
     * This is Tree Sort.
     */
    void printTreeSort(std::ostream &out = cout) const
    {
        if (isEmpty())
            out << "Empty tree" << std::endl;
        else
            printTreeSort(root, out); //calls other print function
    }

    /**
     * @brief Print the tree structure (for debugging)
     */
    void prettyPrintTree() const
    {
        prettyPrintTree("", root, false);
    }

    /**
     * @brief Print the tree contents in sorted order.
     */

    void printTreeByLevel(std::ostream &out = cout) const
    {
        printTreeByLevel(root, out); //will print the tree by level
    }

    void printToFile(DSAVLTree tree, string file){
         Node *rootPtr = tree.root;
        std::ofstream outputTree(file);
    if(!outputTree.is_open()){
        throw std:: runtime_error("file not opened"); //detects if it is file
    }
   
    else{
        if(rootPtr == nullptr){
            std::cout<<"Tree is empty. Nothing to print"<<std::endl;
        }
        //writing as if ''point''
        std::queue <Node*> point;
        point.push(rootPtr);
        while(!point.empty()){ //while point in tree is not empty
            Node * current = point.front();
            point.pop();
            vector<document> docs= current->documents ;

            // cout << "number of documents: " << docs.size() << endl;
            if (!docs.empty()) {
                outputTree << current->key<< ':' << docs.at(0).getName() << "\t" <<  docs.at(0).getNum();
                for(int i = 1; i < docs.size(); i++){
                    outputTree << "~" << docs.at(i).getName() <<"\t" << docs.at(i).getNum();
                }
                if (!point.empty()) {
                    outputTree << std::endl;
                }
            }

            if (current->left != nullptr) {
                point.push(current->left);
            }
            if (current->right != nullptr) 
            {
                point.push(current->right);
            }
        }

    }
    outputTree.close();

    }
    void writeToTree(DSAVLTree& tree, const string& fileName) {
        ifstream inputFile(fileName);
        if (!inputFile.is_open()) {
            throw std::runtime_error("File not opened"); //needs to open tree if not throws error
        }

        while(inputFile.good()){
            string key;
            getline(inputFile, key, ':');
            string documentInfo;
            string documentName;
            string numberStr;
            int number;

            string line;
            string dummy;
            getline(inputFile, line);
            stringstream stream(line);

            while (getline(stream, documentInfo, '~')) //goes through each line of file 
            {
                stringstream docStream(documentInfo);
                getline(docStream, documentName, '\t'); //will get the liens 
                getline(docStream, numberStr);
                number = stoi(numberStr);
                document doc(key, documentName, number);
                insert(key, doc, root); //once reads in info from file will insert into the tree
            }
            getline(stream, documentName, '\t');
            getline(stream, numberStr);
            number = stoi(numberStr);
            document doc(key, documentName, number);
            insert(key, doc, root);

        }
        inputFile.close(); //close the file
    }

private:
    /**
     * Note on the use of the parameter Node* &t used in makeEmpty, insert and delete.
     * This is a (non-constant) reference to a Node-Pointer. It is used in the
     * recursive functions to modify the pointer t in the calling function (e.g., make it
     * point to a newly created node).
     *
     * Other functions like clone() use the parameter Node* t which is not a
     * reference, put just a pointer. This is used when we just want to look at
     * the tree but not modify its structure.
     */

    /**
     * Internal method to make subtree empty uses postorder traversal (LRN)
     * Note the pointer reference for t.
     */
    void makeEmpty(Node *&t)
    {
        if (t == nullptr)
            return;

        // recursion
        makeEmpty(t->left);  // L
        makeEmpty(t->right); // R

        t->documents.clear();
        delete t; // N
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     * -> preorder traversal (NLR)
     */
    Node *clone(Node *t) const
    {
        if (t == nullptr)
            return nullptr;

        // recursion
        return new Node{t->key, t->documents, clone(t->left), clone(t->right), t->height};
    }

    int height(Node *t) const
    {
        return t == nullptr ? -1 : t->height; //will return the height of the tree
    }

    vector<document> findDocs(const std::string &key, Node *&t)
    {
        //will pass in the name of the word and try to find the document
        if (t == nullptr)
            throw std::runtime_error("No documents available for word");

        else if (key < t->key)
            findDocs(key, t->left);
        else if (t->key < key)
            findDocs(key, t->right);
        else
        {
            return t->documents;
        };
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t a non-const reference to the pointer to the node that roots the subtree.
     */
    void insert(const string &key, const document &rhs, Node *&t)
    {
        // Base case: found an empty spot? insert a new node
        //   This can be done because t is a reference to a pointer! We could also use a pointer-pointer
        if (t == nullptr)
        {
            t = new Node{key, rhs, nullptr, nullptr, 0};
            return;
        }

        // recursively find the insert position
        else if (key < t->key)
            insert(key, rhs, t->left);
        else if (t->key < key)
            insert(key, rhs, t->right);
        else
        {
            if (!containsDocument(key, rhs)) {
                t->documents.push_back(rhs);
            } else {
                addFrequency(key, rhs);
            }

        }; // Duplicate: key == x; do nothing... we could do other things.
        balance(t);
    }

    static const int ALLOWED_IMBALANCE = 1;
    // We could easily implement a iterative version with a while loop....
    void balance(Node *&t)
    {
        // special case: empty tree
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }
        // else ... no imbalance was created

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    void rotateWithLeftChild(Node *&k2)
    {
        Node *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(Node *&k1)
    {
        Node *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(Node *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(Node *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     *
     *
     * Note: This implementation of case C relinks the smallest node in the right subtree rather than copy the
     *    key value like it is done in the text book. The reason is that nodes may store additional information
     *    (like values in a map) which may be expensive to copy.
     */
    void remove(const string &x, Node *&t)
    {
        // Recursively find the node to delete using binary search.
        if (t == nullptr)
            return; // Item not found; do nothing

        // must be in left subtree
        if (x < t->key)
            return remove(x, t->left);

        // must be in right subtree
        if (t->key < x)
            return remove(x, t->right);

        // we get here only for t->key == x!!!
        // Do the deletion

        // Cases:

        if (t->left == nullptr && t->right == nullptr)
        {
            // A. No children: Just remove the node.
            delete t;
            t = nullptr;
        }
        else if (t->left != nullptr && t->right != nullptr)
        {
            // C. Two children case: replace node with the smallest node in the right subtree.
            Node *replacement = unlinkMinNode(t->right); // recursively find and unlink the smallest node in the right subtree

            // relink the replacement node in place of t (use t's children, delete the node t and link replacement instead)
            replacement->right = t->right;
            replacement->left = t->left;
            delete t;
            t = replacement;
        }
        else
        {
            // B. One child case: replace the node with the only child.
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method
     * 1. find the smallest item in a subtree t,
     * 2. unlink the minimum node form the tree by breaking the link in its parent, and
     * 3. return it.
     * This recursive funtion is used in case C of remove() to unlink the samllest node for the right subtree and
     * relink it to replace the removed node.
     */
    Node *unlinkMinNode(Node *&t)
    {
        // special case: no root node
        if (t == nullptr)
            return nullptr;

        // base case: we have reached the minimum node
        if (t->left == nullptr)
        {
            Node *min = t;
            // break the link in the parent node (this works because t is a reference) to unlink the node from the tree.
            // Note: The minimum can have a right child node which needs to go back in the tree!
            t = min->right;

            // return the found minimum node
            return min;
        }

        // recursively traverse down left (smaller values)
        return unlinkMinNode(t->left);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */

    /**
     * Internal method to find a node.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    Node *find(const string &x, Node *t) const
    {
        // base case 1: not found
        if (t == nullptr)
            return nullptr;

        // recursion
        if (x < t->key)
            return find(x, t->left);

        if (t->key < x)
            return find(x, t->right);

        // base case 2: found: we have t->key == x
        return t; // Match
    }

    void add(const string &key, const document &d, Node* root)
    {
        Node* t = find(key, root);

        t->documents.push_back(d);
    }

    /****** NONRECURSIVE VERSION*************************
    Node* find( const string & x, Node *t ) const
        {
            while( t != nullptr )
                if( x < t->key )
                    t = t->left;
                else if( t->key < x )
                    t = t->right;
                else
                    return t;    // Match

            return nullptr;   // No match
        }
    *****************************************************/

    /**
     * maxDepth = height of the node as the path length to the farthest down leaf node
     *
     * Calls this method with the root node and depth = -1 (a tree without a root node)
     *
     * -> postorder traversal (LRN)
     */
    int maxDepth(Node *t, int depth)
    {
        // Leaf node? Report the depth.
        if (t == nullptr)
            return depth;

        // max depth of left (L) and right (R) subtree. N does not do anything.
        return (std::max(maxDepth(t->left, depth + 1),
                         maxDepth(t->right, depth + 1)));
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * This is inorder traversal (LNR)
     */
    void printTreeSort(Node *t, ostream &out) const
    {
        if (t == nullptr)
            return;

        // recursion
        printTreeSort(t->left, out); // L

        std::cout << t->key << ": ";
        for (size_t i = 0; i < t->documents.size(); ++i)
        {
            // std::cout << t->documents.at(i) << endl;
        }
        // N
        printTreeSort(t->right, out); // R
    }

    /**
     *  Pretty print the tree structure
     *  Uses preorder traversal with R and L swapped (NRL)
     *
     *  Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */
    void prettyPrintTree(const string &prefix, const Node *node, bool isRight) const
    {
        if (node == nullptr)
            return;

        // N: print the value of the node
        cout << prefix;
        cout << (isRight ? "├──" : "└──");

        // print the value of the node
        std::cout << node->key << std::endl;

        // R, L: enter the next tree level - right and left branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    /**
     * Internal method to print a subtree rooted.
     * This is level-order traversal.
     * We use a loop and a queue an auxiliary data structure to remember what node to process next.
     */
    void printTreeByLevel(Node *t, ostream &out) const
    {
        if (t == nullptr)
            return;

        Node *current;
        queue<Node *> q;

        // start with the root node in the queue
        q.push(t);

        while (!q.empty())
        {
            // take the next node from the front of the queue
            current = q.front();
            q.pop();

            out << current->key << ": ";
            for (size_t i = 0; i < current->documents.size(); ++i)
            {
                // std::cout<< current->documents.at(i) << ", ";
            }

            // add children to the end of the queue
            if (current->left != nullptr)
                q.push(current->left);

            if (current->right != nullptr)
                q.push(current->right);
        }
    }

    // bool check_balance(Node *node)
    // {
    //     if (node == nullptr)
    //     {
    //         return true;
    //     }

    //     int lHeight = check_balance(node->left) + 1;
    //     int rHeight = check_balance(node->right) + 1;

    //     if (std::abs(lHeight - rHeight) > 1)
    //     {
    //         //throw std::invalid_argument("tree is not balance.");
    //         return false
    //     }

    //     int trueNodeHeight = std::max(lHeight, rHeight);

    //     if (trueNodeHeight != node->height)
    //     {
    //         //throw std::invalid_argument("node does not have correct height value.");
    //         return false
    //     }

    //     return trueNodeHeight;
    // }
};
#endif