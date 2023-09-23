#include "UsesSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

Result UsesSuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const {
    std::shared_ptr<SuchThatClause> suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    Ref leftRef = suchThat->getFirstParam();
    RefType leftType = leftRef.getType();
    QueryEntityType leftEntityType = leftRef.getEntityType();
    RootType leftRootType = leftRef.getRootType();
    Ref rightRef = suchThat->getSecondParam();
    RootType rightRootType = rightRef.getRootType();
    Result res;
    ResultType type;
    std::vector<std::vector<Entity>> tuples;

    // TODO: add leftType entRef in the future

    // TODO: CHANGE RETURN TYPE !!!!!

    if (leftType == RefType::StmtRef) {
        if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Uses(a,v)
            std::string leftSyn = leftRef.getRep();
            std::string rightSyn = rightRef.getRep();
            tuples = pkbReader->getUsesStmtPair(stmtMap.at(leftEntityType));

            std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;

        } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Ident) { // Uses(a,"x")
            std::string syn = leftRef.getRep();
            Variable v = Variable(rightRef.getRep());
            std::vector<Entity> data = pkbReader->getUsesTypeIdent(stmtMap.at(leftEntityType), v);

            for (const auto& ent : data) {
                std::vector<Entity> tuple_vector {ent};
                tuples.emplace_back(tuple_vector);
            }

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;

        } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Wildcard) { // Uses(a,_)
            std::string syn = leftRef.getRep();
            std::vector<Entity> data = pkbReader->getUsesStmt(stmtMap.at(leftEntityType));

            for (const auto& ent : data) {
                std::vector<Entity> tuple_vector {ent};
                tuples.emplace_back(tuple_vector);
            }

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;
        } else if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Uses(1,v)
            Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
            std::string syn = rightRef.getRep();

            std::vector<Entity> data = pkbReader->getUsesVar(s);
            for (auto & ent : data) {
                std::vector<Entity> tuple_vector {ent};
                tuples.emplace_back(tuple_vector);
            }
            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;

        } else if (leftRootType == RootType::Integer && rightRootType == RootType::Ident) { // Uses(1,"x")
            Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
            Variable v = Variable(rightRef.getRep());
            bool boolResult = pkbReader->isStmtUsesVar(s, v);
            res.setBoolResult(boolResult);

            type = ResultType::Boolean;
        }
    }

    res.setType(type);
    res.setTuples(tuples);
    return res;
}
