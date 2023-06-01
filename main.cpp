#include "Mylib.h"
#include "funkcijos.h"

int main()
{
    string inputFileName;
    cout << "Irasykite failo pavadinima: ";
    cin >> inputFileName;

    if (inputFileName.empty()) 
        inputFileName = "tekstas.txt";

    stringstream inputBuffer;
    ifstream inputFile(inputFileName);
    if (!inputFile) 
        throw runtime_error("Ivyko klaida, neina atidaryti " + inputFileName);

    inputBuffer << inputFile.rdbuf();

    int lineCount = 0;
    string line;
    vector<string> urls;
    map<string, Word> wordMap;

    while (getline(inputBuffer, line)) {

        lineCount++;
        stringstream lineStream(line);
        string word;

        while (lineStream >> word) {

            if (isUrl(word)) 
                urls.push_back(word);
            else {
                word = removeNonWord(word);
                word = toLower(word);
                addWord(word, wordMap, lineCount);
            }
        }
    }

    // ištrina tašką iš URL pabaigos
    for (string& url : urls) {
        if (!url.empty() && url.back() == '.') 
            url.pop_back();
    }

    string resultFileName = "rezultataiURL.txt";
    ofstream outFile(resultFileName);

    if (outFile.is_open()) {
        for (const string& url : urls) 
            outFile << url << endl;
        outFile.close();
    }
    else 
        cout << "Rezultatų failas neatsidaro" << endl;

    vector<pair<string, Word>> sortedWords(wordMap.begin(), wordMap.end());
    sort(sortedWords.begin(), sortedWords.end(), CompareWordsByCountWithCondition());

   stringstream resultBuffer;
    resultBuffer << left << setw(15) << "Žodis" << right << setw(10);
    for (int i = 0; i < lineCount; i++) 
        resultBuffer << (i + 1) << " ";

    resultBuffer << endl;

    resultBuffer << string(15 + lineCount * 4, '-') << endl;

    for (const auto& entry : sortedWords) {
        resultBuffer << left << setw(20) << entry.first;
        for (size_t i = 0; i < entry.second.lineIndices.size(); i++) {
            int previousIndex = (i == 0) ? 0 : entry.second.lineIndices[i - 1] + 1;
            int currentIndex = entry.second.lineIndices[i] + 1;
            int distance = currentIndex - previousIndex;
            resultBuffer << setw(4) << "" << string(distance, ' ') << "*";
        }
            resultBuffer << endl;
    }
    resultBuffer << "\nŽodžių pasikartojimas:\n";
    resultBuffer << endl;
    resultBuffer << left << setw(25) << "Žodis" << "Dažnumas" << endl;
    resultBuffer << string(50, '-') << endl;

    for (const auto& entry : sortedWords) 
        resultBuffer << left << setw(25) << entry.first << right << entry.second.count << endl;
    
    resultFileName = "rezultatai.txt";
    saveResults(resultFileName, resultBuffer);
    return 0;
}