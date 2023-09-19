#include "UsesSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

Result UsesSuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const {
    std::shared_ptr<SuchThatClause> suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    Ref leftRef = suchThat->getFirstParam();
    RefType leftType = leftRef.getType();
    RootType leftRootType = leftRef.getRootType();
    Ref rightRef = suchThat->getSecondParam();
    RootType rightRootType = rightRef.getRootType();
    Result res;
    ResultType type;
    std::vector<std::vector<Entity>> tuples;

    // TODO: check leftType entRef
    // TODO: check EntityType

    if (leftType == RefType::StmtRef) {
        if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Uses(a,v)
            std::string leftSyn = leftRef.getRep();
            std::string rightSyn = rightRef.getRep();
            tuples = pkbReader->getAllUsesAssignVariablePair();

            std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;

        } if (leftRootType == RootType::Synonym && rightRootType == RootType::Ident) { // Uses(a,"x")
            std::string syn = leftRef.getRep();
            Variable v = Variable(rightRef.getRep());
            std::vector<Entity> data = (*pkbReader).getAllUsesAssignByVariable(v);
            for (auto & ent : data) {
                std::vector<Entity> tuple_vector {ent};
                tuples.emplace_back(tuple_vector);
            }

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
