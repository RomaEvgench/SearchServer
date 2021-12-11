
#include "search_server.h"
#include "paginator.h"
#include "request_queue.h"
#include "read_input_functions.h"
#include "log_duration.h"
#include "string_processing.h"
#include "remove_duplicates.h"
//#include "test_example_functions.h"
#include "document.h"
#include <execution>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

int main() {
    SearchServer search_server("и в на"s);

    search_server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, {7, 2, 7});
    search_server.AddDocument(2, "пушистый пёс и модный ошейник"s, DocumentStatus::ACTUAL, {1, 2, 3});
    search_server.AddDocument(3, "большой кот модный ошейник "s, DocumentStatus::ACTUAL, {1, 2, 8});
    search_server.AddDocument(4, "большой пёс скворец евгений"s, DocumentStatus::ACTUAL, {1, 3, 2});
    search_server.AddDocument(5, "большой пёс скворец василий"s, DocumentStatus::ACTUAL, {1, 1, 1});

    const auto search_results = search_server.FindTopDocuments("пушистый пёс"s);
    int page_size = 2;
    const auto pages = Paginate(search_results, page_size);

    // Выводим найденные документы по страницам
    for (auto page = pages.begin(); page != pages.end(); ++page) {
        cout << *page << endl;
        cout << "Разрыв страницы"s << endl;
    }
}