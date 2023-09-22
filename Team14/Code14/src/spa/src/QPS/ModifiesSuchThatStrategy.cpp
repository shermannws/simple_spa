#include "ModifiesSuchThatStrategy.h"
#include "Commons/Entities/Entity.h"

Result ModifiesSuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const {
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

    if (leftType == RefType::StmtRef) {
        if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Modifies(a,v)
            std::string leftSyn = leftRef.getRep();
            std::string rightSyn = rightRef.getRep();
            tuples = pkbReader->getModifiesStmtPair(stmtMap.at(leftEntityType));

            std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;

        } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Ident) { // Modifies(a,"x")
            std::string syn = leftRef.getRep();
            Variable v = Variable(rightRef.getRep());
            std::vector<Entity> data = pkbReader->getModifiesTypeIdent(stmtMap.at(leftEntityType), v);
            for (const auto& ent : data) {
                std::vector<Entity> tuple_vector {ent};
                tuples.emplace_back(tuple_vector);
            }

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;

        } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Wildcard) { // Modifies(a,_)
            std::string syn = leftRef.getRep();
            std::vector<Entity> data = pkbReader->getModifiesStmt(stmtMap.at(leftEntityType));
            for (const auto& ent : data) {
                std::vector<Entity> tuple_vector {ent};
                tuples.emplace_back(tuple_vector);
            }

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;
        } else if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Modifies(1,v)
            Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
            std::string syn = rightRef.getRep();
            std::vector<Entity> data = pkbReader->getModifiesVar(s);
            for (auto & ent : data) {
                std::vector<Entity> tuple_vector {ent};
                tuples.emplace_back(tuple_vector);
            }
            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

            type = ResultType::Tuples;

        } else if (leftRootType == RootType::Integer && rightRootType == RootType::Ident) { // Modifies(1,"x")
            Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
            Variable v = Variable(rightRef.getRep());
            res.setBoolResult(pkbReader->isStmtModifiesVar(s, v));

            type = ResultType::Boolean;
        }
    }

    res.setType(type);
    res.setTuples(tuples);
    return res;
}