#include "PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(std::shared_ptr<PkbReader> pkbReader) :pkbReader(pkbReader),
    clauseHandler(std::make_shared<ClauseHandler>(pkbReader)){}

Result PQLEvaluator::Evaluate(Query& query) {

    // TODO iterate through clauses, get Strategy Type from clause type
    // example :
    // clauseHandler->setStrategy(std::make_unique<AssignPatternStrategy>());
    // Result result;
    // clauseHandler->executeQuery(query, result);

   std::shared_ptr<QueryEntity> entity = query.getSelect()[0];
   std::shared_ptr<std::vector<std::shared_ptr<Entity>>> entities = getAll(entity);
   // convert entities to Result obj

    Result result;
    return result;
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PQLEvaluator::getAll(std::shared_ptr<QueryEntity> queryEntity) {
    EntityType entityType = queryEntity->getType();
    switch (entityType) {
        case EntityType::Procedure:
            return pkbReader->getAllProcedures();
        case EntityType::Stmt:
            return pkbReader->getAllStatements();
        case EntityType::Assign:
            return pkbReader->getAllAssign();
        case EntityType::Variable:
            return pkbReader->getAllVariables();
        case EntityType::Constant:
            return pkbReader->getAllConstants();
        default:
            throw std::runtime_error("Not supported entity type in query select clause");
    }
}


