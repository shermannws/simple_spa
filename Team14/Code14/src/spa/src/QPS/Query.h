#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include <vector>

#include "Entity.h"

class Query {
public:
    Query();

    void add_declaration();
    void add_such_that();
    void add_pattern();

private:
    std::vector<Entity> declarations;

};

#endif //SPA_QUERY_H


