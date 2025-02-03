#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include "InvertedIndex.h"
#include "ConverterJSON.h"
#include <vector>
#include <string>

struct RelativeIndex{
    size_t doc_id;
    float rank;
    explicit operator std::pair<int, float>() {
        return std::make_pair(doc_id, rank);
    }
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
    class ConverterJSON* currentConverter;
    class InvertedIndex* currentIndex;
public:
    SearchServer();
    ~SearchServer();
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& inRequests) const;
    void proccessRequests() const;
};

#endif
