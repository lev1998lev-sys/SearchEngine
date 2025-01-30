#ifndef CONVERTERJSON_H
#define CONVERTERJSON_H

#include <nlohmann/json.hpp>

class FieldConfigIsMissing : public std::exception {
public:
    const char* what() const noexcept override;
};

class ConfigurationFileIsMissing : public std::exception {
public:
    const char* what() const noexcept override;
};

class ConverterJSON {
public:
    ConverterJSON() = default;
    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};


#endif