#include "InvertedIndex.h"
#include <sstream>
#include <thread>
#include <mutex>

std::mutex commonData;
/*
std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::stringstream cleanWord;
    std::vector<Entry> infoAboutWord;
    std::string tempWordByWord;
    for (int i = 0; i < docs.size(); i++) {
        cleanWord << docs[i];
        while (!cleanWord.eof()) {
            getline(cleanWord, tempWordByWord, ' ');
            if (!tempWordByWord.empty() and tempWordByWord == word) {
                try {
                    if (infoAboutWord.at(i).doc_id == i) {
                        infoAboutWord[i].count += 1;
                    }
                } catch (std::out_of_range& e) {
                    infoAboutWord.push_back({size_t(i), 1});
                }
            }
        }
        cleanWord.clear();
    }
    return infoAboutWord;
}
*/

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    if (freq_dictionary.find(word) != freq_dictionary.end()) {
        return freq_dictionary.at(word);
    }
    return {};
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    std::string currentDoc;
    std::vector<std::thread> docsProccessing;
    freq_dictionary.clear();
    for (int i = 0; i < input_docs.size(); i++) {
        docs.push_back(input_docs[i]);
        currentDoc = input_docs[i];
        std::thread indexCurrentDoc([](std::string inDoc, InvertedIndex* inIndex, int indexOfDoc) {
            std::stringstream cleanWord;
            std::string tempWordByWord;
            std::vector<Entry> infoAboutCurrentWord;
            cleanWord << inDoc;
            while (!cleanWord.eof()) {
                std::getline(cleanWord, tempWordByWord, ' ');
                commonData.lock();
                if (!tempWordByWord.empty()) {
                    if (inIndex->freq_dictionary.find(tempWordByWord) != inIndex->freq_dictionary.end()) {
                        infoAboutCurrentWord = inIndex->freq_dictionary.at(tempWordByWord);
                        try {
                            infoAboutCurrentWord.at(indexOfDoc).count += 1;
                        } catch (std::out_of_range& e) {
                            infoAboutCurrentWord.push_back({size_t(indexOfDoc), 1});
                        }
                        inIndex->freq_dictionary.at(tempWordByWord) = infoAboutCurrentWord;
                    } else {
                        infoAboutCurrentWord.clear();
                        infoAboutCurrentWord.push_back({size_t(indexOfDoc), 1});
                        inIndex->freq_dictionary.insert(std::make_pair(tempWordByWord, infoAboutCurrentWord));
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