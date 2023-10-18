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
    if (!((leftRef.isOfName() && rightRef.isOfName()) || (leftRef.isOfInteger() && rightRef.isOfInteger()))) {
        throw SemanticException("Different attribute value types");
    }

    if (leftRef.isRootType(RootType::AttrRef)) {
        auto attrNameSet = QPSUtil::entityToAttrNamesMap[leftRef.getEntityType()];
        if (attrNameSet.find(leftRef.getAttrName()) == attrNameSet.end()) {
            throw SemanticException("Invalid attribute of the synonym");
        }
    }

    if (rightRef.isRootType(RootType::AttrRef)) {
        auto attrNameSet = QPSUtil::entityToAttrNamesMap[rightRef.getEntityType()];
        if (attrNameSet.find(rightRef.getAttrName()) == attrNameSet.end()) {
            throw SemanticException("Invalid attribute of the synonym");
        }
    }
}
