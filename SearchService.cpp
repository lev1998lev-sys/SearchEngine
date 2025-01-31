#include "SearchService.h"
#include <sstream>
#include <unordered_set>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> resultOfSearchForSpecifiedRequests;
    for (int i = 0; i < queries_input.size(); i++) {
        std::stringstream cleanWord;
        std::string currentWord;
        std::vector<Entry> infoAboutWord;
        std::vector<RelativeIndex> relativeIndexes;
        float maxRank = 0.0;
        std::unordered_set<std::string> listOfUniqueWords;
        cleanWord << queries_input[i];
        while (!cleanWord.eof()) {
            std::getline(cleanWord, currentWord, ' ');
            if (!currentWord.empty()) {
                listOfUniqueWords.insert(currentWord);
            }
        }

        for (auto& word : listOfUniqueWords) {
            infoAboutWord = _index->GetWordCount(word);
            bool isDocIdInRelatives = false;
            for (int j = 0; j < infoAboutWord.size(); j++) {
                for (int k = 0; k < relativeIndexes.size(); k++) {
                    if (relativeIndexes[k].doc_id == infoAboutWord[j].doc_id) {
                        relativeIndexes[k].rank += infoAboutWord[j].count;
                        isDocIdInRelatives = true;
                    }
                    if (maxRank < relativeIndexes[k].rank) {
                        maxRank = relativeIndexes[k].rank;
                    }
                }
                if (!isDocIdInRelatives) {
                    relativeIndexes.push_back({infoAboutWord[j].doc_id, static_cast<float>(infoAboutWord[j].count)});
                    if (maxRank < relativeIndexes[j].rank) {
                        maxRank = relativeIndexes[j].rank;
                    }
                    isDocIdInRelatives = false;
                }
            }
        }

        for (int j = 1; j < relativeIndexes.size(); j++) {
            for (int i = 0; i < relativeIndexes.size() - j; i++) {
                if (relativeIndexes[i].rank < relativeIndexes[i + 1].rank) {
                    std::swap(relativeIndexes[i].rank, relativeIndexes[i + 1].rank);
                }
            }
        }

        for (int j = 0; j < relativeIndexes.size(); j++) {
            relativeIndexes[j].rank /= maxRank;
        }

        if (!relativeIndexes.empty() and relativeIndexes.size() > maxResponseCount) {
            relativeIndexes.resize(maxResponseCount);
        }
        resultOfSearchForSpecifiedRequests.push_back(relativeIndexes);
    }
    return resultOfSearchForSpecifiedRequests;
}