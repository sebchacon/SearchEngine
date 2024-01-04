# Assignment 4: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Names of all team members:

Sebastian Chacon
Kiersten Wener
Alex Macdonald

Used free extension: [ ] 24 hrs or [X] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## Answers

### Project Management

Complete the tasks and planned completion columns **BEFORE** You start with 
coding!


Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task| Planned completion | Actual completion | Time spent in hrs by Kiersten Time spent in hrs by SebTime spent in hrs by Alex |
| ----------- | :-----------------:| :Kiers|Seb--|Alex-----: | :--------------------: | :--------------------: |
|Query processor | week 1 | week 2-3 | 10  | 8   | 0
|Index Handler   | week 2 | week 4   | 6   | 10  | 5
|Doc parser      | week 2 | week 3   | 8   | 5   | 15
|Search Engine   | week 4 | week 5   | 15  | 15  | 8
|AVL Tree        | week 1 | week 1   | 1  | 5   | 5

### High-level Design of Solution

- Add a UML class diagram, etc.

    named UML.png in respository

- High-level pseudo code for each component. 

    comments?

### Used Data Structures
Explanation of what data structures are used where. For each, state
    - time and space complexity (Big-Oh),
    - why it is the appropriate data structure and what other data structure could have been used.

    For our indexing we used our custom AVL tree that stores a new object called document. The document is an object that stores the specific data for a unique word, name of document appearance, and an int counting the frequency. Using this we can add new words by pushing the vector of documents into each node of their respective trees and when we search simply return said vector with getters for doc names. Using an AVL Tree allows for a big oh of (n) for searching and insertion. 

    Our query processor and document parser communicate to the handler via 2d vector passing sets of strings to access documents and their respective private variables. Using a 2d vector we push 4 vectors of strings containing persons, orgs, words, and not words. Using these strings we can search our tree(s) and grab the vector of documents from each word and then cross compare to narrow down what the user is looking for. The triple nested for loop causes a large slow down in run time causing a runtime of (n^3) due to running a cross comparison of all 3 vectors. On top of that we have to run o(n) for non words halting the time even more. 

### User Documentation
- What are the features of your software?

    The user can enter different arguments based on if they want to read/write from an index, search a query, or enter in their own data to read in from a file. 

- Describe how to use the software.

    In the terminal window the user enters ./supersearch as arg1 and then can enter "index", "query", or "ui" to enter 1 of the 3 features. For index the user must follow up with the file name / <directory> to give the computer the file to read the trees from. If searching just by query, the program will build said trees from previous files indexed and then all strings following will be searched in their respective trees based on input. The user can enter basic words like apple, running, stop and those strings will get cleaned and filtered from stem/stop words before entering the word tree. For a more complex search the user can input "PERSON:" or "ORG:" to filter a special part of the json and finally "-" in front of a word for a "not word" that simply filters out documents with that word in it.

- Some example queries with the results.

### Performance
- Provide statistics (word counts, timing, etc) for indexing all documents (or as many as you can in a reasonable amount of time).

Using sample data (6 documents): 
    -Build Trees: 218 milliseconds

### Bonus Work
Did you attempt any bonuses? If so, please give a brief description of what you did.

   N/A
