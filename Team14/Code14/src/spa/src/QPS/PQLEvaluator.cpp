
#include "PQLEvaluator.h"
#include "QueryEntity.h"

#include <numeric>

PQLEvaluator::PQLEvaluator() {}

std::list<std::string> PQLEvaluator::formatResult(Query& query, Result& result) {
    std::vector<std::shared_ptr<QueryEntity>> selects = query.getSelect();
    std::list<std::string> results;
    // TODO: add formatter for ResultType::Boolean

    if (result.getType() == ResultType::Tuples) {
        for (auto & tuple_ptr : result.getTuples()) { // tuple_ptr is std::shared_ptr<std::vector<std::shared_ptr<Entity>>>
            std::vector<std::string> tmp;
            for (auto & entity : selects) {
                std::string syn = entity->getSynonym();
                std::unordered_map<std::string, int> indicesMap = result.getSynIndices();
                if (indicesMap.find(syn) != indicesMap.end()) {
                    int idx = indicesMap.at(syn);
                    std::string value = (*(*tuple_ptr)[idx]->getEntityValue());
                    tmp.push_back(value);
                }
            }
            std::string concat = std::accumulate(tmp.begin(), tmp.end(), std::string(),
                                                 [](std::string& a, const std::string& b) {
                                                     return a += (a.empty() ? "" : " ") + b;
                                                 }); // handles formatting of more than two variables in select clause
            if (!concat.empty()) {
                results.push_back(concat);
            }
        }
    }
    return results;
}
