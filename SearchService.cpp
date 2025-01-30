#include "SearchService.h"
#include <sstream>
#include <unordered_set>

std::vector<RelativeIndex> SearchServer::proccessRequest(const std::string& requestOfWords) {
    std::vector<Entry> infoAboutWord;
    std::vector<RelativeIndex> relativeIndexes;
    std::stringstream cleanWord;
    std::string currentWord;
    float maxRank = 0.0;
    std::unordered_set<std::string> listOfUniqueWords;
    cleanWord << requestOfWords;
    while (!cleanWord.eof()) {
        std::getline(cleanWord, currentWord, ' ');
        if (!currentWord.empty()) {
            listOfUniqueWords.insert(currentWord);
        }
    }

    for (auto& word : listOfUniqueWords) {
        infoAboutWord = _index.GetWordCount(word);
        bool isDocIdInRelatives = false;
        for (int i = 0; i < infoAboutWord.size(); i++) {
            for (int j = 0; j < relativeIndexes.size(); j++) {
                if (relativeIndexes[j].doc_id == infoAboutWord[i].doc_id) {
                    relativeIndexes[j].rank += infoAboutWord[i].count;
                    if (maxRank < relativeIndexes[j].rank) {
                        maxRank = relativeIndexes[j].rank;
                    }
                    isDocIdInRelatives = true;
                    break;
                }
            }
            if (!isDocIdInRelatives) {
                relativeIndexes.push_back({infoAboutWord[i].doc_id, static_cast<float>(infoAboutWord[i].count)});
                isDocIdInRelatives = false;
            }
        }
    }

    for (int i = 0; i < relativeIndexes.size(); i++) {
        relativeIndexes[i].rank /= maxRank;
    }
    return relativeIndexes;
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> resultOfSearchForSpecifiedRequests;
    std::vector<RelativeIndex> resultOfCountingForCurrentRequest;
    std::stringstream cleanWord;
    std::string currentWord;
    for (int i = 0; i < queries_input.size(); i++) {
        resultOfSearchForSpecifiedRequests.push_back(proccessRequest(queries_input[i]));
    }
    return resultOfSearchForSpecifiedRequests;
}
