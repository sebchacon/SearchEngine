
#include "DocumentParser.h"


DocumentParser::DocumentParser(IndexHandler* h) {
    handler = h;
}

void DocumentParser::readJson(const string &fileName)
{
    ifstream input(fileName); // opens file
    if (!input.is_open())
    {
        cerr << "cannot open file: " << fileName << endl; //throws error if not open
        return;
    }

    rapidjson::IStreamWrapper isw(input);

    rapidjson::Document d;
    d.ParseStream(isw);

    //gets title
    auto title = d["title"].GetString();
    //for now 
    // cout << "Title: " << title << "\n";

    //gets array of people 
    auto persons = d["entities"]["persons"].GetArray(); //detects if person, org, or word
    auto orgs = d["entities"]["organizations"].GetArray();
    auto text = d["text"].GetString();

    document doc;
    doc.setName(title); //creates new doc
    doc.setNum(1);
    
    string newText = cleanWords(text); //will clean text

    std::istringstream iss(newText);
    std::string word;
    while (iss >> word) // while we input every word from given doc
    {
        if (!removeStopWords(word)) 
        {
            stemmingWords(word); // if not stop word will stem and clean then return word to document
            handler->addWord(word, doc);
        }
    }

    for (auto &p : persons)
    {
        string person = p["name"].GetString(); //go through persons then add
        handler->addPerson(person, doc);
    }
    for (auto &l : orgs)
    {
        string org = l["name"].GetString(); //will find name of org then add
        handler->addOrg(org, doc);
    }   

}

void DocumentParser::fileSystem(const string &path){
    auto it = filesystem::recursive_directory_iterator(path);

    int count =  1;
    // loop over all the entries.
    for (const auto &entry : it)
    {
        if (count % 1000 == 0) {
            cout << "# of parsed files " << count << endl;
        }

        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
        {
            readJson(entry.path().string());            
        }
    }
}


bool DocumentParser::removeStopWords(std::string word)
{
    std::string stopWords[] = {"able", "about", "above", "abroad", "according", "accordingly", "across",
                               "actually", "adj", "after", "afterwards", "again", "against", "ago", "ahead", "ain't", "all", "allow", "allows",
                               "almost", "alone", "along", "alongside", "already", "also", "although", "always", "am", "amid", "amidst",
                               "among", "amongst", "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything", "anyway",
                               "anyways", "anywhere", "apart", "appear", "appreciate", "appropriate", "are", "aren't", "around", "as", "a's",
                               "aside", "ask", "asking", "associated", "at", "available", "away", "awfully", "back", "backward", "backwards",
                               "be", "became", "because", "become", "becomes", "becoming", "been", "before", "beforehand", "begin", "behind",
                               "being", "believe", "below", "beside", "besides", "best", "better", "between", "beyond", "both", "brief", "but",
                               "by", "came", "can", "cannot", "cant", "can't", "caption", "cause", "causes", "certain", "certainly", "changes",
                               "clearly", "c'mon", "co", "co.", "com", "come", "comes", "concerning", "consequently", "consider", "considering",
                               "contain", "containing", "contains", "corresponding", "could", "couldn't", "course", "c's", "currently", "dare",
                               "daren't", "definitely", "described", "despite", "did", "didn't", "different", "directly", "do", "does", "doesn't",
                               "doing", "done", "don't", "down", "downwards", "during", "each", "edu", "eg", "eight", "eighty", "either", "else",
                               "elsewhere", "end", "ending", "enough", "entirely", "especially", "et", "etc", "even", "ever", "evermore", "every",
                               "everybody", "everyone", "everything", "everywhere", "ex", "exactly", "example", "except", "fairly", "far", "farther",
                               "few", "fewer", "fifth", "first", "five", "followed", "following", "follows", "for", "forever", "former", "formerly",
                               "forth", "forward", "found", "four", "from", "further", "furthermore", "get", "gets", "getting", "given", "gives",
                               "go", "goes", "going", "gone", "got", "gotten", "greetings", "had", "hadn't", "half", "happens", "hardly", "has",
                               "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "hello", "help", "hence", "her", "here", "hereafter", "hereby", "herein", "here's", "hereupon", "hers", "herself", "he's", "hi", "him",
                               "himself", "his", "hither", "hopefully", "how", "howbeit", "however", "hundred", "i'd", "ie", "if", "ignored", "i'll", "i'm", "immediate", "in", "inasmuch", "inc", "inc.", "indeed", "indicate", "indicated", "indicates", "inner", "inside", "insofar", "instead", "into", "inward", "is", "isn't", "it", "it'd", "it'll", "its", "it's", "itself", "i've", "just", "k", "keep", "keeps", "kept", "know", "known", "knows",
                               "last", "lately", "later", "latter", "latterly", "least", "less", "lest", "let", "let's", "like", "liked", "likely", "likewise", "little", "look", "looking", "looks", "low", "lower", "ltd", "made", "mainly", "make", "makes", "many", "may", "maybe", "mayn't", "me", "mean", "meantime", "meanwhile", "merely", "might", "mightn't", "mine",
                               "minus", "miss", "more", "moreover", "most", "mostly", "mr", "mrs", "much", "must", "mustn't", "my", "myself", "name", "namely", "nd", "near", "nearly", "necessary", "need", "needn't", "needs", "neither", "never", "neverf", "neverless", "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non", "none", "nonetheless", "noone",
                               "no-one", "nor", "normally", "not", "nothing", "notwithstanding", "novel", "now", "nowhere", "obviously", "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "ones", "one's", "only", "onto", "opposite", "or", "other", "others", "otherwise", "ought", "oughtn't", "our", "ours", "ourselves", "out", "outside", "over", "overall", "own", "particular", "particularly", "past", "per", "perhaps", "placed", "please", "plus", "possible", "presumably", "probably", "provided", "provides", "que", "quite", "qv", "rather", "rd", "re", "really", "reasonably", "recent", "recently", "regarding", "regardless", "regards", "relatively", "respectively", "right", "round", "said", "same", "saw", "say", "saying", "says", "second", "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sensible", "sent", "serious",
                               "seriously", "seven", "several", "shall", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't", "since", "six", "so", "some", "somebody", "someday", "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry", "specified", "specify", "specifying", "still", "sub", "such", "sup", "sure",
                               "take", "taken", "taking", "tell", "tends", "th", "than", "thank", "thanks", "thanx", "that", "that'll", "thats", "that's", "that've", "the", "their", "theirs", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "there'd", "therefore", "therein", "there'll", "there're", "theres", "there's", "thereupon", "there've", "these", "they", "they'd", "they'll", "they're", "they've", "thing", "things", "think", "third", "thirty", "this", "thorough", "thoroughly", "those", "though", "three", "through", "throughout", "thru", "thus", "till", "to", "together", "too", "took", "toward", "towards", "tried", "tries", "truly", "try", "trying", "t's", "twice", "two", "un", "under",
                               "underneath", "undoing", "unfortunately", "unless", "unlike", "unlikely", "until", "unto", "up", "upon", "upwards", "us", "use", "used", "useful", "uses", "using", "usually", "v", "value", "various", "versus", "very", "via", "viz", "vs", "want", "wants", "was", "wasn't",
                               "way", "we", "we'd", "welcome", "well", "we'll", "went", "were", "we're", "weren't", "we've", "what", "whatever", "what'll", "what's", "what've", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "where's", "whereupon", "wherever",
                               "whether", "which", "whichever", "while", "whilst", "whither", "who", "who'd", "whoever", "whole", "who'll", "whom", "whomever", "who's", "whose", "why", "will", "willing", "wish", "with", "within", "without", "wonder", "won't", "would", "wouldn't", "yes", "yet", "you",
                               "you'd", "you'll", "your", "you're", "yours", "yourself", "yourselves", "you've", "zero"};
    int sizeStopWords = sizeof(stopWords) / sizeof(stopWords[0]);
    // string array of 600+ stop words

    for (int z = 0; z < sizeStopWords; z++)
    {
        if (word == stopWords[z]) //will go through every stop word and return true if it is a stop word
        {
            return true;
        }
    }

    return false; //false when is not a stop word
}



std::string DocumentParser::stemmingWords(std::string word)
{ // dont know if doing correct
    std::string newWord = word;
    Porter2Stemmer::stem(newWord); // will stem using step 0-5
    Porter2Stemmer::trim(newWord); // after it is stemmed it will trim the word
    return newWord;
} // how to use other class

std::string DocumentParser::cleanWords(std::string word) //what is function??
{
    std::string newWord;
    for (size_t i = 0; i < word.length(); ++i) //turns all text to a lower case 
    {
        if (isalpha(word[i]))
        {
            newWord += tolower(word[i]);
        } else {
            newWord += ' ';
        }
    }

    return newWord;
}
