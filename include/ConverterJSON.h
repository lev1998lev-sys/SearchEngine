#ifndef CONVERTERJSON_H
#define CONVERTERJSON_H

#include <nlohmann/json.hpp>
#include "SearchService.h"

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
    std::vector<std::string> getTextDocuments() const;
    int getResponsesLimit() const;
    std::vector<std::string> getRequests() const;
    void putAnswers(std::vector<std::vector<struct RelativeIndex>>& inAnswers);
    bool limitNumberOfWords(std::string& inSentence, int minAmountOfWords, int maxAmountOfWords, int amountOfSymbols) const;
};

#endif