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

std::vector<std::string> ConverterJSON::GetTextDocuments() {
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
        readConfigFile.close();
    }
    return textsFromFiles;
}

int ConverterJSON::GetResponsesLimit() {
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

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream readRequestFile("requests.json");
    std::vector<std::string> requestsFromFile;
    nlohmann::json requestsFile;
    readRequestFile >> requestsFile;
    readRequestFile.close();
    nlohmann::json requestsFromReqFile = requestsFile.at("requests");
    for (int i = 0; i < requestsFromReqFile.size(); i++) {
        requestsFromFile.push_back(requestsFromReqFile.at(i));
    }
    return requestsFromFile;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
    nlohmann::json answersJson;
    nlohmann::json tempRelevance;
    for (int i = 0; i < answers.size(); i++) {
        std::ostringstream os;
        os << std::setfill('0') << std::setw(3) << i + 1;
        std::string requestNumber = "request" + os.str();
        os.seekp(0);
        if (answers[i].size() > 1) {
            answersJson[requestNumber].push_back(nlohmann::json::object_t::value_type("result", true));
            int maxResponseToRequest = GetResponsesLimit();
            answersJson[requestNumber]["relevance"] = nlohmann::json::object();
            for (int j = 0; j < answers[i].size() and j < maxResponseToRequest; j++) {
                std::string tempDocId = "docid_" + std::to_string(answers[i][j].first);
                answersJson[requestNumber]["relevance"].push_back(nlohmann::json::object_t::value_type(tempDocId, answers[i][j].second));
            }
        } else if (answers[i].size() == 1) {
            answersJson[requestNumber].push_back(nlohmann::json::object_t::value_type("result", true));
            answersJson[requestNumber].push_back(nlohmann::json::object_t::value_type("docid_0", answers[i][0].second));
        } else {
            answersJson[requestNumber].push_back(nlohmann::json::object_t::value_type("result", false));
        }
    }
    std::ofstream outAnswersFile("answers.json");
    outAnswersFile << answersJson;
    outAnswersFile.close();
}