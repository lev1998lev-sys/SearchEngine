#include "ConverterJSON.h"
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

const char* FieldConfigIsMissing::what() const noexcept {
    return "config file is empty";
}

const char* ConfigurationFileIsMissing::what() const noexcept {
    return "config file is missing";
}

std::vector<std::string> ConverterJSON::getTextDocuments() const {
    std::ifstream readConfigFile("config.json");
    std::vector<std::string> textsFromFiles;
    nlohmann::json configFile;
    if (!readConfigFile.is_open()) {
        throw ConfigurationFileIsMissing();
    }
    readConfigFile >> configFile;
    if (configFile.find("config") == configFile.end()) {
        throw FieldConfigIsMissing();
    }
    readConfigFile.close();
    nlohmann::json filesFromConfigFile = configFile.at("files");
    textsFromFiles.resize(filesFromConfigFile.size());
    for (int i = 0; i < filesFromConfigFile.size(); i++) {
        readConfigFile.open(filesFromConfigFile.at(i));
        if (readConfigFile.is_open()) {
            std::getline(readConfigFile, textsFromFiles[i], '\0');
        }
        if (!limitNumberOfWords(textsFromFiles[i], 0, 1000, 100)) {
            return {};
        }
        readConfigFile.close();
    }
    return textsFromFiles;
}

int ConverterJSON::getResponsesLimit() const {
    std::ifstream readConfigFile("config.json");
    nlohmann::json configFile;
    readConfigFile >> configFile;
    readConfigFile.close();
    if (!configFile.at("config").contains("max_responses")) {
        return 5;
    }
    auto maxResponses = configFile.at("config").at("max_responses");
    return maxResponses;
}

std::vector<std::string> ConverterJSON::getRequests() const {
    std::ifstream readRequestFile("requests.json");
    if (!readRequestFile.is_open()) {
        return std::initializer_list<std::string>({});
    }
    std::vector<std::string> requestsFromFile;
    nlohmann::json requestsFile;
    readRequestFile >> requestsFile;
    readRequestFile.close();
    nlohmann::json requestsFromReqFile = requestsFile.at("requests");
    for (int i = 0; i < requestsFromReqFile.size(); i++) {
        requestsFromFile.push_back(requestsFromReqFile.at(i));
        if (!limitNumberOfWords(requestsFromFile.back(), 1, 10, 0)) {
            return {};
        }
    }
    return requestsFromFile;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>>& inAnswers) {
    nlohmann::json answersJson;
    nlohmann::json tempRelevance;
    for (int i = 0; i < inAnswers.size(); i++) {
        std::stringstream formattedReqNumber;;
        std::stringstream formattedRank;
        formattedReqNumber << std::setfill('0') << std::setw(3) << i + 1;
        std::string requestNumber = "request" + formattedReqNumber.str();
        if (inAnswers[i].size() > 1) {
            answersJson[requestNumber].push_back(nlohmann::json::object_t::value_type("result", true));
            int maxResponseToRequest = getResponsesLimit();
            answersJson[requestNumber]["relevance"] = nlohmann::json::object();
            for (int j = 0; j < inAnswers[i].size() and j < maxResponseToRequest; j++) {
                formattedRank << std::setprecision(4) << std::fixed << inAnswers[i][j].rank;
                std::string tempDocId = "docid_" + std::to_string(inAnswers[i][j].doc_id);
                answersJson[requestNumber]["relevance"].push_back(nlohmann::json::object_t::value_type(tempDocId, std::stod(formattedRank.str())));
                formattedRank.seekp(0);
            }
        } else if (inAnswers[i].size() == 1) {
            formattedRank << std::setprecision(4) << std::fixed << inAnswers[i][0].rank;
            answersJson[requestNumber].push_back(nlohmann::json::object_t::value_type("result", true));
            answersJson[requestNumber].push_back(nlohmann::json::object_t::value_type("docid_0", std::stod(formattedRank.str())));
            formattedRank.seekp(0);
        } else {
            answersJson[requestNumber].push_back(nlohmann::json::object_t::value_type("result", false));
        }
    }
    std::ofstream outAnswersFile("answers.json");
    outAnswersFile << answersJson;
    outAnswersFile.close();
}

bool ConverterJSON::limitNumberOfWords(std::string& inSentence, int minAmountOfWords, int maxAmountOfWords, int amountOfSymbols) const {
    std::stringstream cleanWord;
    std::string tempCurrentWord;
    int tempAmountOfWords = 0;
    cleanWord << inSentence;
    while (!cleanWord.eof()) {
        std::getline(cleanWord, tempCurrentWord, ' ');
        if (amountOfSymbols > 0) {
            if (tempCurrentWord.length() > amountOfSymbols) {
                return false;
            }
        }
        if (!tempCurrentWord.empty()) {
            tempAmountOfWords += 1;
        }
    }
    if (tempAmountOfWords < minAmountOfWords or tempAmountOfWords > maxAmountOfWords) {
        return false;
    }
    return true;
}
