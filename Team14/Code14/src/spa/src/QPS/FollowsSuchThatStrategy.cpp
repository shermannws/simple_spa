#include "FollowsSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"

Result FollowsSuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const {
    std::shared_ptr<SuchThatClause> suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    Ref leftRef = suchThat->getFirstParam();
    RootType leftRootType = leftRef.getRootType();
    QueryEntityType leftEntityType = leftRef.getEntityType();
    Ref rightRef = suchThat->getSecondParam();
    RootType rightRootType = rightRef.getRootType();
    QueryEntityType rightEntityType = rightRef.getEntityType();
    Result res;
    ResultType type;
    std::vector<std::vector<Entity>> tuples;

    // LHS & RHS ARE STATEMENTS
    // stmts can be syn, _ or int

    // TODO: check EntityType

    // SYNONYMS
    if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Follows(s1,s2)
        if (leftEntityType == QueryEntityType::Stmt && rightEntityType == QueryEntityType::Stmt) {
            std::string leftSyn = leftRef.getRep();
            std::string rightSyn = rightRef.getRep();
            tuples = pkbReader->getAllFollowsStatementPair();

            std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;
        }
    } if (leftRootType == RootType::Synonym && rightRootType == RootType::Integer) { // Follows(s,1)
        if (leftEntityType == QueryEntityType::Stmt) {
            std::string syn = leftRef.getRep();
            Statement s = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
            auto data = pkbReader->getFollowsByStatement(s);
            tuples.emplace_back(data);

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;
        }

    } if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Follows(1,s)
        if (rightEntityType == QueryEntityType::Stmt) {
            std::string syn = rightRef.getRep();
            Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
            auto data = pkbReader->getFollowingStatement(s);
            std::vector<std::shared_ptr<Entity>> v;
            tuples.emplace_back(data);

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;
        }

        // INTEGERS
    } if (leftRootType == RootType::Integer && rightRootType == RootType::Integer) { // Follows(1,2)
        Statement s1 = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
        Statement s2 = Statement(stoi(rightRef.getRep()), StatementType::Stmt);
        bool boolResult = (*pkbReader).getIsFollows(s1, s2);
        res.setBoolResult(boolResult);
        type = ResultType::Boolean;
    }

    // TODO: WILDCARDS
    // WILDCARDS

    res.setType(type);
    res.setTuples(tuples);
    return res;
}
