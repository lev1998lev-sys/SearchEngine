#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <vector>
#include <map>
#include <string>
#include <iostream>

struct Entry {
    size_t doc_id, count;
};

class InvertedIndex {
private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
public:
    InvertedIndex() = default;
    void UpdateDocumentBase(std::vector<std::string> input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);
};


#endif
