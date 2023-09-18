#include "AssignPatternStrategy.h"

Result AssignPatternStrategy::evaluateClause(Clause& clause, std::shared_ptr<PkbReader> pkbReader) const {
    auto& patternClause = dynamic_cast<PatternClause&>(clause);
    Ref firstArg = patternClause.getFirstParam();
    ExpressionSpec secondArg = patternClause.getSecondParam();

    Result result;
    ResultType type = ResultType::Tuples;
    result.setType(type);
    std::unordered_map<std::string, int> columns {{patternClause.getSyn(), 0}};


    if (firstArg.getRootType() == RootType::Wildcard) { // first arg is wildcard
        result.setSynIndices(columns); // no more columns in result table
        if (secondArg.first == ExpressionSpecType::Wildcard) {
            //get All Assign
        } else {
            //get Matching Assign(Expression, isExact)
        }
    } else if (firstArg.getRootType() == RootType::Synonym) { //Variable synonym
        columns.insert({firstArg.getRep(), 1});
        result.setSynIndices(columns);
        if (secondArg.first == ExpressionSpecType::Wildcard) {
            //get All Assign by LHSType (TypeConstraint)
        } else {
            //get Matching Assign by LHSType (TypeConstraint, Expression, isExact)
        }
    } else { // first arg is character strings (ident)
        result.setSynIndices(columns);
        if (secondArg.first == ExpressionSpecType::Wildcard) {
            //get All Assign by LHSExpression (firstArg.StringRep)
        } else {
            //get Matching Assign by LHSExpression (firstArg.StringRep, Expression, isExact)
        }
    }

//    std::vector<std::vector<Entity>> mappedEntities;
//        for (const auto& entity : entities) {
//            std::vector<Entity> mappedEntity {entity};
//            mappedEntities.push_back(mappedEntity);
//        }
//        result.setTuples(mappedEntities);

    return result;
}