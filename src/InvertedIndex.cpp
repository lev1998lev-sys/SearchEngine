#include "../InvertedIndex.h"
#include <sstream>
#include <thread>
#include <mutex>

std::mutex commonData;

std::vector<Entry> InvertedIndex::getWordCount(const std::string& word) const {
    if (freqDictionary.find(word) != freqDictionary.end()) {
        return freqDictionary.at(word);
    }
    return std::initializer_list<Entry>();
}

void InvertedIndex::updateDocumentBase(const std::vector<std::string>& inDocuments) {
    std::string currentDoc;
    std::vector<std::thread> docsProccessing;
    freqDictionary.clear();
    for (int i = 0; i < inDocuments.size(); i++) {
        currentDoc = inDocuments[i];
        std::thread indexCurrentDoc([](std::string inDoc, InvertedIndex* inIndex, int indexOfDoc) {
            std::stringstream cleanWord;
            std::string tempWordByWord;
            std::vector<Entry> infoAboutCurrentWord;
            cleanWord << inDoc;
            while (!cleanWord.eof()) {
                std::getline(cleanWord, tempWordByWord, ' ');
                commonData.lock();
                if (!tempWordByWord.empty()) {
                    if (inIndex->freqDictionary.find(tempWordByWord) != inIndex->freqDictionary.end()) {
                        infoAboutCurrentWord = inIndex->freqDictionary.at(tempWordByWord);
                        try {
                            infoAboutCurrentWord.at(indexOfDoc).count += 1;
                        } catch (std::out_of_range& e) {
                            infoAboutCurrentWord.push_back({size_t(indexOfDoc), 1});
                        }
                        inIndex->freqDictionary.at(tempWordByWord) = infoAboutCurrentWord;
                    } else {
                        infoAboutCurrentWord.clear();
                        infoAboutCurrentWord.push_back({size_t(indexOfDoc), 1});
                        inIndex->freqDictionary.insert(std::make_pair(tempWordByWord, infoAboutCurrentWord));
                    }
                }
                commonData.unlock();
            }
            cleanWord.clear();
        }, currentDoc, this, i);
        docsProccessing.push_back(std::move(indexCurrentDoc));
    }
    for (int i = 0; i < docsProccessing.size(); i++) {
        docsProccessing[i].join();
    }
}