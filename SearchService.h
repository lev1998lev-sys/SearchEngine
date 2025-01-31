#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include "InvertedIndex.h"
#include <vector>
#include <string>
#include <map>

#include "ConverterJSON.h"

struct RelativeIndex{
    size_t doc_id;
    float rank;
    explicit operator std::pair<int, float>() {
        return std::make_pair(doc_id, rank);
    }
};

class SearchServer {
public:
    SearchServer(InvertedIndex* idx, int inMaxResponseCount) : _index(idx), maxResponseCount(inMaxResponseCount) {};

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
private:
    InvertedIndex* _index;
    int maxResponseCount;
};



#endif
