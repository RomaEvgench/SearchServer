#include "request_queue.h"

using namespace std;

vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentStatus status) {
    return RequestQueue:: AddFindRequest(raw_query, [status](int document_id, DocumentStatus document_status, int rating) 
        {
            return document_status == status;
        });
    }

vector<Document> RequestQueue::AddFindRequest(const string& raw_query) {
    return RequestQueue::AddFindRequest(raw_query, DocumentStatus::ACTUAL);
    }

int RequestQueue::GetNoResultRequests() const {
    int noresult = 0;
    for (auto it = requests_.begin(); it != requests_.end(); ++it) 
    {
        if ((*it).isEmpty) 
        {
            ++noresult;
        }
    }
    return noresult;
}