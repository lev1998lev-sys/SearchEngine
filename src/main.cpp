#include "SearchService.h"

int main(int argc, char* argv[]) {
    SearchServer* searchService = new SearchServer();
    searchService->proccessRequests();
    delete searchService;
    searchService = nullptr;
    return 0;
}