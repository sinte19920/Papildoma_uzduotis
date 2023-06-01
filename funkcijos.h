#include "Mylib.h"

class Word {
public:
    vector<int> lineIndices;
    int count;

    Word(int lineIndex)
    {
        lineIndices.push_back(lineIndex);
        count = 1;
    }
};

// nusprendžia kaip rūšiuoti
struct CompareWordsByCountWithCondition
{
    bool operator()(const pair<string, Word>& a, const pair<string, Word>& b) const
    {
        if (a.second.count == b.second.count)
            return a.first < b.first; // jeigu dažnis lygus - pagal abecėlę
        else
            return a.second.count > b.second.count; // mažėjančia tvarka
    }
};

bool isUrl(const string&);
string removeNonWord(const string&);
string toLower(const string&);
void addWord(const string&, map<string, Word>&, int );
void saveResults(const string&, const stringstream& );