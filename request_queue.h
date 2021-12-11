#pragma once
#include <deque>
#include "document.h"
#include "search_server.h"



using namespace std;

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server)
        : server_(search_server){ 
    }
    
    template <typename DocumentPredicate>
    vector<Document> AddFindRequest(const string& raw_query, DocumentPredicate document_predicate);
    vector<Document> AddFindRequest(const string& raw_query, DocumentStatus status);
    vector<Document> AddFindRequest(const string& raw_query);
    
    int GetNoResultRequests() const;
    
    private:
    struct QueryResult {
        bool isEmpty;
    };
    
    const SearchServer& server_;
    deque<QueryResult> requests_;
    const static int sec_in_day_ = 1440;
};

//Function With Template 
template <typename DocumentPredicate>
vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentPredicate document_predicate) {
    vector<Document> found = server_.FindTopDocuments(raw_query, document_predicate);
    
    QueryResult result = {(found.empty()) ? (true) : (false)};
    requests_.push_back(result);
    if (requests_.size() > sec_in_day_) 
    {
        requests_.pop_front();
    }

    return found;
}