
#include "QueryEvaluator.h"
#include "QueryEntity.h"

#include <numeric>

QueryEvaluator::QueryEvaluator() {}

std::list<std::string> QueryEvaluator::formatResult(Query& query, Result& result) {
    std::vector<std::shared_ptr<QueryEntity>> selects = query.getSelect();
    std::list<std::string> results;
    if (result.getType() == ResultType::Tuples) {
        for (auto & tuple : result.getTuples()) {
            std::vector<std::string> tmp;
            for (auto & entity : selects) { // order ans according to select
                std::string syn = entity->getSynonym();
                if (tuple.find(syn) != tuple.end()) { // check if synonym is in tuple
                    tmp.push_back(*(tuple.at(syn)->getEntityValue()));
                }
            }
            std::string concat = std::accumulate(tmp.begin(), tmp.end(), std::string(),
                                             [](std::string& a, const std::string& b) {
            return a += (a.empty() ? "" : " ") + b;
            });
            results.push_back(concat);
        }
    }
    return results;
}
