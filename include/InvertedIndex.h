#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <vector>
#include <map>
#include <string>
#include <iostream>

struct Entry {
    size_t doc_id, count;
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
    std::map<std::string, std::vector<Entry>> freqDictionary;
public:
    InvertedIndex() = default;
    void updateDocumentBase(const std::vector<std::string>& inDocuments);
    std::vector<Entry> getWordCount(const std::string& word) const;
};


#endif
