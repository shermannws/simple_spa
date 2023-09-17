#include "ParentStarSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"

Result ParentStarSuchThatStrategy::evaluateClause(Clause& clause, std::shared_ptr<PkbReader> pkbReader) const {
    auto& suchThat = dynamic_cast<SuchThatClause&>(clause);
    Ref leftRef = suchThat.getFirstParam();
    RootType leftRootType = leftRef.getRootType();
    QueryEntityType leftEntityType = leftRef.getEntityType();
    Ref rightRef = suchThat.getSecondParam();
    RootType rightRootType = rightRef.getRootType();
    QueryEntityType rightEntityType = rightRef.getEntityType();
    Result res;
    ResultType type;
    std::vector<std::vector<Entity>> tuples;

    if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Parent*(s1,s2)
        std::string leftSyn = leftRef.getRep();
        std::string rightSyn = rightRef.getRep();
        tuples = pkbReader->getParentStarPair(stmtMap.at(leftEntityType), stmtMap.at(rightEntityType));

        std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;
    } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Integer) { // Parent*(s,1)
        std::string syn = leftRef.getRep();
        Statement s = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        auto data = pkbReader->getParentStarTypeStmt(stmtMap.at(leftEntityType), s);
        for (const auto& ent : data) {
            std::vector<Entity> tuple_vector {ent};
            tuples.emplace_back(tuple_vector);
        }

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;

    } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Wildcard) { // Parent*(s,_)
        std::string syn = leftRef.getRep();
        auto data = pkbReader->getParentStarTypeWildcard(stmtMap.at(leftEntityType));
        for (const auto& ent : data) {
            std::vector<Entity> tuple_vector {ent};
            tuples.emplace_back(tuple_vector);
        }

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Parent*(1,s)
        std::string syn = rightRef.getRep();
        Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        auto data = pkbReader->getParentStarStmtType(s, stmtMap.at(rightEntityType));
        for (const auto& ent : data) {
            std::vector<Entity> tuple_vector {ent};
            tuples.emplace_back(tuple_vector);
        }

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Synonym) { // Parent*(_,s)
        std::string syn = rightRef.getRep();
        auto data = pkbReader->getParentStarWildcardType(stmtMap.at(rightEntityType));
        for (const auto& ent : data) {
            std::vector<Entity> tuple_vector {ent};
            tuples.emplace_back(tuple_vector);
        }

        std::unordered_map<std::string, int> indices{{syn, 0}};
        res.setSynIndices(indices);

        type = ResultType::Tuples;

    } else if (leftRootType == RootType::Integer && rightRootType == RootType::Integer) { // Parent*(1,2)
        Statement s1 = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        res.setBoolResult(pkbReader->isParentStar(s1, s2));
        type = ResultType::Boolean;

    } else if (leftRootType == RootType::Wildcard && rightRootType == RootType::Wildcard) { // Parent*(_,_)
        res.setBoolResult(pkbReader->hasParentStar());
        type = ResultType::Boolean;

    }

    res.setType(type);
    res.setTuples(tuples);
    return res;
}