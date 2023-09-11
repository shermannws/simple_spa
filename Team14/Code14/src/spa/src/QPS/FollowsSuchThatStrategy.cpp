#include "FollowsSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"

Result FollowsSuchThatStrategy::evaluateClause(Query& query, std::shared_ptr<PkbReader> pkbReader) const {
    // call pkbReader getter funcs
    // build result
    SuchThatClause clause;
    Ref leftRef = clause.getLeftRef();
    RootType leftRootType = leftRef.getRootType();
    QueryEntityType leftEntityType = leftRef.getEntityType();
    Ref rightRef = clause.getRightRef();
    RootType rightRootType = rightRef.getRootType();
    QueryEntityType rightEntityType = rightRef.getEntityType();
    Result res;
    ResultType type;
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>> tuples;

    // LHS & RHS ARE STATEMENTS
    // stmts can be syn, _ or int

    // TODO: check EntityType

    // SYNONYMS
    if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Follows(s1,s2)
        if (leftEntityType == QueryEntityType::Stmt && rightEntityType == QueryEntityType::Stmt) {
            std::string leftSyn = leftRef.getRep();
            std::string rightSyn = rightRef.getRep();
            tuples = *((*pkbReader).getAllFollowsStatementPair());

            std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;
        }
    } if (leftRootType == RootType::Synonym && rightRootType == RootType::Integer) { // Follows(s,1)
        if (leftEntityType == QueryEntityType::Stmt) {
            std::string syn = leftRef.getRep();
            std::shared_ptr<Statement> s = std::make_shared<Statement>(stoi(rightRef.getRep()), StatementType::Stmt);
            std::vector<std::shared_ptr<Entity>> v {(*pkbReader).getFollowsByStatement(s)};
            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> data = std::make_shared<std::vector<std::shared_ptr<Entity>>>(v);
            tuples.emplace_back(data);

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;
        }

    } if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Follows(1,s)
        if (rightEntityType == QueryEntityType::Stmt) {
            std::string syn = rightRef.getRep();
            std::shared_ptr<Statement> s = std::make_shared<Statement>(stoi(leftRef.getRep()), StatementType::Stmt);
            std::vector<std::shared_ptr<Entity>> v {(*pkbReader).getFollowingStatement(s)};
            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> data = std::make_shared<std::vector<std::shared_ptr<Entity>>>(v);
            tuples.emplace_back(data);

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;
        }

    // INTEGERS
    } if (leftRootType == RootType::Integer && rightRootType == RootType::Integer) { // Follows(1,2)
        std::shared_ptr<Statement> s1 = std::make_shared<Statement>(stoi(leftRef.getRep()), StatementType::Stmt);
        std::shared_ptr<Statement> s2 = std::make_shared<Statement>(stoi(rightRef.getRep()), StatementType::Stmt);
        bool boolResult = (*pkbReader).getIsFollows(s1, s2);
        res.setBoolResult(boolResult);
        type = ResultType::Boolean;
    }

    // TODO: WILDCARDS
    // WILDCARDS


    return res;
}