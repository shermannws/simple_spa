#include "WithHandler.h"

void WithHandler::handle(const Query &query, std::shared_ptr<Clause> clause) {
    auto with = std::dynamic_pointer_cast<WithClause>(clause);
    if (!with) { return SemanticValHandler::handle(query, clause); }
    Ref &leftRef = with->getFirstParam();
    Ref &rightRef = with->getSecondParam();

    handleRefType(leftRef, rightRef);


    return SemanticValHandler::handle(query, clause);
}

void WithHandler::handleRefType(Ref &leftRef, Ref &rightRef) {
    auto refType = RefType::WithRef;
    leftRef.setType(refType);
    rightRef.setType(refType);

    validateSameType(leftRef, rightRef);

    if (leftRef.isRootType(RootType::AttrRef)) { validateAttrRef(leftRef); }

    if (rightRef.isRootType(RootType::AttrRef)) { validateAttrRef(rightRef); }
}

void WithHandler::validateSameType(Ref &leftRef, Ref &rightRef) {
    auto areBothOfName = leftRef.isOfName() && rightRef.isOfName();
    auto areBothOfInteger = leftRef.isOfInteger() && rightRef.isOfInteger();
    if (!areBothOfName && !areBothOfInteger) { throw SemanticException("Different attribute value types"); }
}

void WithHandler::validateAttrRef(Ref &attrRef) {
    auto entitySet = QPSUtil::attrNameToTypeMap[attrRef.getAttrName()];
    auto entityType = attrRef.getEntityType();
    if (entitySet.find(entityType) == entitySet.end()) { throw SemanticException("Invalid attribute of the synonym"); }
}
