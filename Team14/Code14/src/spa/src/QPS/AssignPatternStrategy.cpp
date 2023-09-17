#include <stdexcept>

#include "AssignPatternStrategy.h"

Result AssignPatternStrategy::evaluateClause(Clause& clause, std::shared_ptr<PkbReader> pkbReader) const {
    auto& patternClause = dynamic_cast<PatternClause&>(clause);
//    Ref first = patternClause.getFirstParam();
//    Ref second = patternClause.getSecondParam();
    Result result;
//    if (first.getRootType() == RootType::Wildcard && second.getRootType() == RootType::Wildcard) {
//        // build result
//        ResultType type = ResultType::Tuples;
//        result.setType(type);
//        std::unordered_map<std::string, int> map {{patternClause.getEntity()->getSynonym(), 0}};
//        result.setSynIndices(map);
//        auto entities = pkbReader->getAllAssign();
//        std::vector<std::vector<Entity>> mappedEntities;
//        for (const auto& entity : entities) {
//            std::vector<Entity> mappedEntity {entity};
//            mappedEntities.push_back(mappedEntity);
//        }
//        result.setTuples(mappedEntities);
//    } else {
//        throw std::runtime_error("Unsupported evaluation of pattern clause");
//    }
    return result;
}