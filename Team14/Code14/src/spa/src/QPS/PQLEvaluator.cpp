
#include "PQLEvaluator.h"
#include "QueryEntity.h"

#include <numeric>

PQLEvaluator::PQLEvaluator() {}


std::list<std::string> PQLEvaluator::formatResult(Query& query, Result& result) {
    std::vector<std::shared_ptr<QueryEntity>> selects = query.getSelect();
    std::list<std::string> results;
    // TODO: add formatter for ResultType::Boolean

    if (result.getType() == ResultType::Tuples) {
        for (auto & tuple : result.getTuples()) {
            std::vector<std::string> tmp;
            for (auto & entity : selects) { // order ans according to select
                std::string syn = entity->getSynonym();
                if (tuple.find(syn) != tuple.end()) { // check if synonym is in tuple
                    std::string value = *(tuple.at(syn)->getEntityValue());
                    tmp.push_back(value);
                }
            }
            std::string concat = std::accumulate(tmp.begin(), tmp.end(), std::string(),
                                             [](std::string& a, const std::string& b) {
            return a += (a.empty() ? "" : " ") + b;
            });
            if (!concat.empty()) {
                results.push_back(concat);
            }
        }
    }
    return results;
}
