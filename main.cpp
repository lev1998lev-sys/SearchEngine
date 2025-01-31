#include <iostream>
#include <nlohmann/json.hpp>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchService.h"
#include <vector>
#include <thread>

using namespace std;

int main() {
    ConverterJSON converter_json;
    InvertedIndex inv_index;
    inv_index.UpdateDocumentBase(converter_json.GetTextDocuments());
    this_thread::sleep_for(chrono::seconds(7));
    SearchServer search_server(&inv_index, converter_json.GetResponsesLimit());
    std::vector<std::vector<RelativeIndex>> proccessReqs = search_server.search(converter_json.GetRequests());
    std::vector<std::vector<std::pair<int,float>>> answers;
    answers.resize(proccessReqs.size());

    for (int i = 0; i < proccessReqs.size(); i++) {
        for (int j = 0; j < proccessReqs[i].size(); j++) {
            answers[i].push_back(std::pair<int, float>(proccessReqs[i][j]));
        }
    }

    converter_json.putAnswers(answers);

    return 0;
}