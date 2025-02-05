#include "SearchService.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<SearchServer> searchService = std::make_unique<SearchServer>();
    searchService->proccessRequests();
    return 0;
}