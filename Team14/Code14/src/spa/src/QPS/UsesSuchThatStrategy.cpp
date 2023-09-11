#include "UsesSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

Result UsesSuchThatStrategy::evaluateClause(Query& query, std::shared_ptr<PkbReader> pkbReader) const {
    SuchThatClause clause = query.getSuchThat()[0];
    Ref leftRef = clause.getLeftRef();
    RefType leftType = leftRef.getType();
    RootType leftRootType = leftRef.getRootType();
    Ref rightRef = clause.getRightRef();
    RootType rightRootType = rightRef.getRootType();
    Result res;
    ResultType type;
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>> tuples;

    // TODO: check leftType entRef
    // TODO: check EntityType

    if (leftType == RefType::StmtRef) {
        if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Uses(a,v)
            std::string leftSyn = leftRef.getRep();
            std::string rightSyn = rightRef.getRep();
            tuples = *((*pkbReader).getAllUsesAssignVariablePair());

            std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;

        } if (leftRootType == RootType::Synonym && rightRootType == RootType::Ident) { // Uses(a,"x")
            std::string syn = leftRef.getRep();
            std::unordered_map<std::string, std::shared_ptr<Entity>> tmp;
            std::shared_ptr<Variable> v = std::make_shared<Variable>(rightRef.getRep());
            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> data = (*pkbReader).getAllUsesAssignByVariable(v); // TODO: to change to new method name with "Uses" inside
            tuples.emplace_back(data);

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;

        } if (leftRootType == RootType::Synonym && rightRootType == RootType::Wildcard) { // Uses(a,_)
            // TODO not in demo
        }
    }

    res.setType(type);
    res.setTuples(tuples);
    return res;
}