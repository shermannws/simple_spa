#include "UsesSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

Result UsesSuchThatStrategy::evaluateClause(Query& query, std::shared_ptr<PkbReader> pkbReader) const {
    // call pkbReader getter funcs
    // build result
    SuchThatClause clause;
    Ref leftRef = clause.getLeftRef();
    RefType leftType = leftRef.getType();
    RootType leftRootType = leftRef.getRootType();
    Ref rightRef = clause.getRightRef();
    RootType rightRootType = rightRef.getRootType();
    Result res;
    ResultType type;
    std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> tuples;
    std::vector<Entity> entities;

    // TODO: check leftType entRef
    // TODO: check EntityType

    if (leftType == RefType::StmtRef) {
        if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Uses(a,v)
            std::string leftSyn = leftRef.getRep();
            std::string rightSyn = leftRef.getRep();
            std::unordered_map<std::string, std::shared_ptr<Entity>> tmp;
            std::vector<std::vector<std::shared_ptr<Entity>>> data = pkbReader->getAllAssignVariableUses();
            for (const auto& e : data)  {
                tmp.insert({leftSyn, e[0]});
                tmp.insert({rightSyn, e[1]});
            }
            tuples.push_back(tmp);
            type = ResultType::Tuples;

        } if (leftRootType == RootType::Synonym && rightRootType == RootType::Ident) { // Uses(a,"x")
            std::string syn = leftRef.getRep();
            std::unordered_map<std::string, std::shared_ptr<Entity>> tmp;
            std::vector<std::shared_ptr<Entity>> data = pkbReader->getAllAssign(rightRef.getRep());
            for (const auto& e : data) {
                tmp.insert({syn, e});
            }
            tuples.push_back(tmp);
            type = ResultType::Tuples;

        } if (leftRootType == RootType::Synonym && rightRootType == RootType::Wildcard) { // Uses(a,_)
            // TODO not in demo
        }
    }

    res.setType(type);
    res.setTuples(tuples);
    return res;
}