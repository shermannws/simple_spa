#include "QPSTestUtil.h"

std::shared_ptr<SuchThatClause> QPSTestUtil::createSuchThatClause(ClauseType type,
                                                            RefType t1, RootType r1, QueryEntityType e1, std::string rep1,
                                                            RefType t2, RootType r2, QueryEntityType e2, std::string rep2) {
    auto clause = std::make_shared<SuchThatClause>();
    clause->setType(type);
    auto p1 = Ref();
    p1.setType(t1);
    p1.setRootType(r1);
    p1.setEntityType(e1);
    p1.setRep(rep1);
    clause->setFirstParam(p1);
    auto p2 = Ref();
    p2.setType(t2);
    p2.setRootType(r2);
    p2.setEntityType(e2);
    p2.setRep(rep2);
    clause->setSecondParam(p2);
    return clause;
}


std::shared_ptr<PatternClause> QPSTestUtil::createPatternClause(ClauseType type, Synonym syn,
                                                           RootType r1, std::string rep1,
                                                           ExpressionSpecType t2, Expression rep2) {
    auto clause = std::make_shared<PatternClause>();
    clause->setType(type);
    clause->setSyn(syn);
    auto p1 = Ref();
    auto refType = RefType::EntRef;
    p1.setType(refType);
    if (r1 == RootType::Synonym) {
        auto entityType = QueryEntityType::Variable;
        p1.setEntityType(entityType);
    }
    p1.setRootType(r1);
    p1.setRep(rep1);
    clause->setFirstParam(p1);
    auto p2 = ExpressionSpec (t2, rep2);
    clause->setSecondParam(p2);
    return clause;
}