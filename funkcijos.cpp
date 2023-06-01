#include "funkcijos.h"

// patikrina, ar žodis yra URL.
bool isUrl(const string& word)
{
    static const regex urlPattern("[(http(s)?):\\/\\/(www\\.)?a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");

    static const vector<string> excludedExtensions = {".txt", ".jpg", ".png", ".pdf", ".doc", ".svg"};

    if (regex_match(word, urlPattern)) {
        for (const string& extension : excludedExtensions) {
            if (word.length() >= extension.length() && word.substr(word.length() - extension.length()) == extension) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// pašalina ne raidinius simbolius iš žodžio.
string removeNonWord(const string& word)
{
    string cleanedWord = regex_replace(word, regex("[^a-zA-Z]"), "");
    return cleanedWord;
}

// paverčia raides į mažąsias
string toLower(const string& word)
{
    string lowerCaseWord = word;
    transform(lowerCaseWord.begin(), lowerCaseWord.end(), lowerCaseWord.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return lowerCaseWord;
}

// prideda žodį į map su informacija apie pasikartojimus
void addWord(const string& word, map<string, Word>& wordMap, int lineIndex)
{
    if (word.empty() || word.size() <= 1 || word.size() >= 15) {
        return;
    }

    auto iterator = wordMap.find(word);
    if (iterator == wordMap.end()) {
        wordMap.insert({ word, Word(lineIndex) });
    }
    else {
        if (lineIndex != iterator->second.lineIndices.back()) {
            iterator->second.lineIndices.push_back(lineIndex);
        }
        iterator->second.count++;
    }
}

// rezultatus išsaugo į failą
void saveResults(const string& filePath, const stringstream& resultBuffer)
{
    ofstream outputFile(filePath);
    if (!outputFile) {
        throw runtime_error("Unable to create result file: " + filePath);
    }
    outputFile << resultBuffer.rdbuf();
    outputFile.close();
}