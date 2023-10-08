 #include "CallsRelationshipManager.h"

 CallsRelationshipManager::CallsRelationshipManager() : ProcToProcRelationshipManager() {};

 void CallsRelationshipManager::calculateCallsStar() {
	 this->calculateTransitiveRelationship();
 };

 std::shared_ptr<EntityStore<Procedure>> CallsRelationshipManager::getCallsFormerAsProcedure(Procedure& latterProcedure) const {
	 return this->getRelationshipFormerStarAsProcedure(latterProcedure);
 };
