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

    if (leftType == RefType::StmtRef) {
        if (leftRootType == RootType::Synonym && rightRootType == RootType::Synonym) { // Uses(a,v)
            std::string leftSyn = leftRef.getRep();
            std::string rightSyn = rightRef.getRep();
            res.setTuples(pkbReader->getUsesStmtPair(stmtMap.at(leftEntityType)));

            std::unordered_map<std::string, int> indices {{leftSyn, 0}, {rightSyn, 1}};
            res.setSynIndices(indices);

        } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Ident) { // Uses(a,"x")
            std::string syn = leftRef.getRep();
            Variable v = Variable(rightRef.getRep());
            res.setTuples(pkbReader->getUsesTypeIdent(stmtMap.at(leftEntityType), v));

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

        } else if (leftRootType == RootType::Synonym && rightRootType == RootType::Wildcard) { // Uses(a,_)
            std::string syn = leftRef.getRep();
            res.setTuples(pkbReader->getUsesStmt(stmtMap.at(leftEntityType)));

            std::unordered_map<std::string, int> indices {{syn, 0}};
            res.setSynIndices(indices);

        } else if (leftRootType == RootType::Integer && rightRootType == RootType::Synonym) { // Uses(1,v)
            Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
            std::string syn = rightRef.getRep();
            res.setTuples(pkbReader->getUsesVar(s));
            std::unordered_map<std::string, int> indices{{syn, 0}};
            res.setSynIndices(indices);

        } else if (leftRootType == RootType::Integer && rightRootType == RootType::Wildcard) { // Uses(1,_)
            Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
            res.setBoolResult(pkbReader->hasUses(s));

        } else if (leftRootType == RootType::Integer && rightRootType == RootType::Ident) { // Uses(1,"x")
            Statement s = Statement(stoi(leftRef.getRep()), StatementType::Stmt);
            Variable v = Variable(rightRef.getRep());
            res.setBoolResult(pkbReader->isStmtUsesVar(s, v));
        }
    }

    return res;
}
