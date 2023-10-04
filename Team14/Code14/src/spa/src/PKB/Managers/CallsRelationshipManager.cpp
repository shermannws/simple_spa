 #include "CallsRelationshipManager.h"

 CallsRelationshipManager::CallsRelationshipManager() : ProcToProcRelationshipManager<CallsRelationshipStore, CallsRelationship>() {};

 void CallsRelationshipManager::storeCallsRelationship(std::shared_ptr<Procedure> procedure1, std::shared_ptr<Procedure> procedure2, bool isDirect) {
	 this->storeRelationship(procedure1, procedure2, isDirect);
 };

 std::vector<std::vector<Entity>> CallsRelationshipManager::getCallsPair(bool requireDirect) const {
	 return this->getRelationshipPair(requireDirect);
 };

 std::vector<Entity> CallsRelationshipManager::getCallsFormer(Procedure& latterProcedure, bool requireDirect) const {
	 return this->getRelationshipFormer(latterProcedure, requireDirect);
 };

 std::vector<Entity> CallsRelationshipManager::getCallsFormer() const {
	 return this->getRelationshipFormer();
 };

 std::vector<Entity> CallsRelationshipManager::getCallsLatter(Procedure& formerProcedure, bool requireDirect) const {
	 return this->getRelationshipLatter(formerProcedure, requireDirect);
 };

 std::vector<Entity> CallsRelationshipManager::getCallsLatter() const {
	 return this->getRelationshipLatter();
 };

 bool CallsRelationshipManager::isCalls(Procedure& procedure1, Procedure& procedure2, bool requireDirect) const {
	 return this->isRelationship(procedure1, procedure2, requireDirect);
 };

 bool CallsRelationshipManager::hasCalls() const {
	 return this->hasRelationship();
 };

 bool CallsRelationshipManager::hasLatterProc(Procedure& formerProcedure) const {
	 return this->isFormer(formerProcedure);
 };

 bool CallsRelationshipManager::hasFormerProc(Procedure& latterProcedure) const {
	 return this->isLatter(latterProcedure);
 };
