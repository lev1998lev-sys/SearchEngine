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
    const vector<string> docs = {
        "london is the capital of great britain",
        "paris is the capital of france",
        "berlin is the capital of germany",
        "rome is the capital of italy",
        "madrid is the capital of spain",
        "lisboa is the capital of portugal",
        "bern is the capital of switzerland",
        "moscow is the capital of russia",
        "kiev is the capital of ukraine",
        "minsk is the capital of belarus",
        "astana is the capital of kazakhstan",
        "beijing is the capital of china",
        "tokyo is the capital of japan",
        "bangkok is the capital of thailand",
        "welcome to moscow the capital of russia the third rome",
        "amsterdam is the capital of netherlands",
        "helsinki is the capital of finland",
        "oslo is the capital of norway",
        "stockholm is the capital of sweden",
         "riga is the capital of latvia",
         "tallinn is the capital of estonia",
         "warsaw is the capital of poland",
 };
    InvertedIndex inv_index;
    inv_index.UpdateDocumentBase(docs);
    this_thread::sleep_for(chrono::seconds(7));
    SearchServer search_server(inv_index);
    std::vector<RelativeIndex> proccessReq = search_server.proccessRequest("moscow is the capital of russia");

    cout << endl;
    cout << endl;
    for (auto& elem: proccessReq) {
        cout << "Doc id: " << elem.doc_id << " rank: " << elem.rank << endl;
    }

    /*
    for (auto it = freqDictionary.begin(); it != freqDictionary.end(); it++) {
        cout << "word: " << it->first << endl;
        for (int j = 0; j < it->second.size(); j++) {
            cout << "doc id: " << it->second[j].doc_id << " count: " << it->second[j].count << endl;
        }
        cout << endl;
    }*/
    return 0;
}