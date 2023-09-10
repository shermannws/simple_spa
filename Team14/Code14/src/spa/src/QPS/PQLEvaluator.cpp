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
   std::vector<Entity> results = getAll(entity);
   // print results

    Result result;
    return result;
}

std::vector<Entity> PQLEvaluator::getAll(std::shared_ptr<QueryEntity> queryEntity) {
    if (queryEntity->getType() == EntityType::Procedure) {
        return pkbReader->getAllProcedures();
    } else if (queryEntity->getType() == EntityType::Stmt) {
        return pkbReader->getAllStatements();
    } else if (queryEntity->getType() == EntityType::Assign) {
        return pkbReader->getAllAssign();
    } else if (queryEntity->getType() == EntityType::Variable) {
        return pkbReader->getAllVariables();
    } else if (queryEntity->getType() == EntityType::Constant) {
        return pkbReader->getAllConstants();
    }

}


