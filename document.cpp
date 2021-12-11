#include "document.h"

Document::Document(int id, double relevance, int rating)
    : id(id)
    , relevance(relevance)
    , rating(rating) 
{
}

std::ostream& operator<<(std::ostream& out, const Document& document) 
{
    out << "{ "
        << "document_id = " << document.id << ", "
        << "relevance = " << document.relevance << ", "
        << "rating = " << document.rating << " }";
    return out;
}
