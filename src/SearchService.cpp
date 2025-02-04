#include "SearchService.h"
#include <sstream>
#include <unordered_set>
#include <vector>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& inRequests) const {
    std::vector<std::vector<RelativeIndex>> resultOfSearchForSpecifiedRequests;
    for (int i = 0; i < inRequests.size(); i++) {
        std::stringstream cleanWord;
        std::string currentWord;
        std::vector<Entry> infoAboutWord;
        std::vector<RelativeIndex> relativeIndexes;
        float maxRank = 0.0;
        std::unordered_set<std::string> listOfUniqueWords;
        cleanWord << inRequests[i];
        while (!cleanWord.eof()) {
            std::getline(cleanWord, currentWord, ' ');
            if (!currentWord.empty()) {
                listOfUniqueWords.insert(currentWord);
            }
        }

        for (auto& word : listOfUniqueWords) {
            infoAboutWord = currentIndex->getWordCount(word);
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
            for (int k = 0; k < relativeIndexes.size() - k; k++) {
                if (relativeIndexes[k].rank < relativeIndexes[k + 1].rank) {
                    std::swap(relativeIndexes[k], relativeIndexes[k + 1]);
                }
            }
        }

        for (int j = 0; j < relativeIndexes.size(); j++) {
            relativeIndexes[j].rank /= maxRank;
        }

        resultOfSearchForSpecifiedRequests.push_back(relativeIndexes);
    }
    return resultOfSearchForSpecifiedRequests;
}

SearchServer::SearchServer() {
    currentConverter = new ConverterJSON();
    currentIndex = new InvertedIndex();
    std::vector<std::string> tempInputDocs = currentConverter->getTextDocuments();
    currentIndex->updateDocumentBase(tempInputDocs);
}

SearchServer::SearchServer(const std::vector<std::string>& inDocuments) {
    currentConverter = new ConverterJSON();
    currentIndex = new InvertedIndex();
    currentIndex->updateDocumentBase(inDocuments);
}



SearchServer::~SearchServer() {
    delete currentConverter;
    currentConverter = nullptr;
    delete currentIndex;
    currentIndex = nullptr;
}

void SearchServer::proccessRequests() const {
    std::vector<std::string> tempInRequests = currentConverter->getRequests();
    std::vector<std::vector<RelativeIndex>> resultOfRequests = search(tempInRequests);
    currentConverter->putAnswers(resultOfRequests);
}
