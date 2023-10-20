#include "WithStrategy.h"
#include "QPS/Clauses/WithClause.h"
#include "QPS/QPSUtil.h"

WithStrategy::WithStrategy(std::shared_ptr<PkbReader> pkbReader) : pkbReader(std::move(pkbReader)) {}

std::shared_ptr<Result> WithStrategy::evaluateClause(std::shared_ptr<Clause> clause) const {
    std::shared_ptr<WithClause> with = std::dynamic_pointer_cast<WithClause>(clause);
    Ref leftRef = with->getFirstParam();
    Ref rightRef = with->getSecondParam();
    bool isLeftAttrRef = leftRef.isRootType(RootType::AttrRef);
    bool isRightAttrRef = rightRef.isRootType(RootType::AttrRef);

    if (isLeftAttrRef && isRightAttrRef) { return evaluateSynSyn(leftRef, rightRef); }
    if (isLeftAttrRef) { return evaluateSynAny(leftRef, rightRef); }
    if (isRightAttrRef) { return evaluateSynAny(rightRef, leftRef); }
    return evaluateBoolean(leftRef, rightRef);
}

std::shared_ptr<Result> WithStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto leftEntityType = leftRef.getEntityType();
    auto rightEntityType = rightRef.getEntityType();
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();

    if (leftRef == rightRef) {// same attr ref
        res->setTuples(QPSUtil::entityGetterMap[leftEntityType](pkbReader));
    } else {// different synonyms
        auto tuples = join(QPSUtil::entityGetterMap[leftEntityType](pkbReader), leftRef.getAttrName(),
                           QPSUtil::entityGetterMap[rightEntityType](pkbReader), rightRef.getAttrName());
        res->setTuples(tuples);
    }
    return res;
}

std::shared_ptr<Result> WithStrategy::evaluateSynAny(Ref &synRef, Ref &anyRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto synEntityType = synRef.getEntityType();
    auto tuples = filter(QPSUtil::entityGetterMap[synEntityType](pkbReader), synRef.getAttrName(), anyRef.getRep());
    res->setTuples(tuples);
    return res;
}

std::shared_ptr<Result> WithStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    auto leftRep = leftRef.getRep();
    auto rightRep = rightRef.getRep();
    res->setBoolResult(leftRep == rightRep);
    return res;
}

std::vector<std::vector<Entity>> WithStrategy::join(std::vector<Entity> v1, AttrName a1, std::vector<Entity> v2,
                                                    AttrName a2) const {
    std::vector<std::vector<Entity>> res;

    for (const auto &e1: v1) {
        for (const auto &e2: v2) {
            if (QPSUtil::getValueFunc[a1](e1) == QPSUtil::getValueFunc[a2](e2)) {
                res.push_back({e1, e2});
            }
        }
    }

    return res;
}

std::vector<Entity> WithStrategy::filter(std::vector<Entity> v, AttrName a, StringRep rep) const {
    std::vector<Entity> res;
    for (const auto &e: v) {
        if (QPSUtil::getValueFunc[a](e) == rep) { res.push_back(e); }
    }

    return res;
}
