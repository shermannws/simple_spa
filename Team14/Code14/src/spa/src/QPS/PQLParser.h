#ifndef SPA_PQLPARSER_H
#define SPA_PQLPARSER_H

#include <string>

#include "Query.h"

class PQLParser {
public:
    explicit PQLParser(const std::string& str) : pql(str) {}
    Query parse();

private:
    std::string pql;
    void process_declaration(Query& query);
    void process_select_clause(Query& query);
    void process_such_that_clause(Query& query);
    void process_pattern_clause(Query& query);
};

#endif //SPA_PQLPARSER_H