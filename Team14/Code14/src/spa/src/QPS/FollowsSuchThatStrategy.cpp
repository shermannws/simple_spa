#include "FollowsSuchThatStrategy.h"
#include "Commons/Entities/Statement.h"

Result FollowsSuchThatStrategy::evaluateClause(Query& query, std::shared_ptr<PkbReader> pkbReader) const {
    // call pkbReader getter funcs
    // build result
    SuchThatClause clause;
    Ref leftRef = clause.getLeftRef();
    RootType leftRootType = leftRef.getRootType();
    EntityType leftEntityType = leftRef.getEntityType();
    Ref rightRef = clause.getRightRef();
    RootType rightRootType = rightRef.getRootType();
    EntityType rightEntityType = rightRef.getEntityType();
    Result res;
    ResultType type;
    std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> tuples;
    std::vector<Entity> entities;

    // LHS & RHS ARE STATEMENTS
    // stmts can be syn, _ or int

    // TODO: check EntityType

    // SYNONYMS
    if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Follows(s1,s2)
        if (leftEntityType == EntityType::Stmt && rightEntityType == EntityType::Stmt) {
            std::string leftSyn = leftRef.getRep();
            std::string rightSyn = leftRef.getRep();
            std::unordered_map<std::string, std::shared_ptr<Entity>> tmp;
            std::vector<std::vector<std::shared_ptr<Entity>>> data = pkbReader->getAllStatementFollows();
            for (const auto& e : data)  {
                tmp.insert({leftSyn, e[0]});
                tmp.insert({rightSyn, e[1]});
            }
            tuples.push_back(tmp);
            type = ResultType::Tuples;
        }
    } if (leftRootType == RootType::Synonym && rightRootType == RootType::Integer) { // Follows(s,1)
        if (leftEntityType == EntityType::Stmt) {
            std::string syn = leftRef.getRep();
            std::unordered_map<std::string, std::shared_ptr<Entity>> tmp;
            std::vector<std::shared_ptr<Entity>> data = pkbReader->getAllFollower(Statement(rightRef.getRep()));
            for (const auto& e : data) {
                tmp.insert({syn, e});
            }
            tuples.push_back(tmp);
            type = ResultType::Tuples;
        }

    } if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Follows(1,s)
        if (rightEntityType == EntityType::Stmt) {
            std::string syn = rightRef.getRep();
            std::unordered_map<std::string, std::shared_ptr<Entity>> tmp;
            std::vector<std::shared_ptr<Entity>> data = pkbReader->getAllFollowedBy(Statement(leftRef.getRep()));
            for (const auto& e : data) {
                tmp.insert({syn, e});
            }
            tuples.push_back(tmp);
            type = ResultType::Tuples;
        }

    // INTEGERS
    } if (leftRootType == RootType::Integer && rightRootType == RootType::Integer) { // Follows(1,2)
        res.setBoolResult(pkbReader->getFollows(Statement(leftRef.getRep()), Statement(rightRef.getRep())));
        type = ResultType::Boolean;
    }

    // TODO: WILDCARDS
    // WILDCARDS


    return res;
}