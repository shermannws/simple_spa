#include "Result.h"

Result::Result() : type(ResultType::Invalid), boolResult(false) {}

ResultType Result::getType() {
    return type;
}

void Result::setType(ResultType& ttype) {
    type = ttype;
}

void Result::setBoolResult(bool result) {
    boolResult = result;
}
bool Result::getBoolResult() {
    return boolResult;
}

void Result::setTuples(const std::vector<std::vector<Entity>>& resultTuples) {
    tuples = resultTuples;
}

void Result::setTuples(const std::vector<Entity>& resultEntities) {
    for (const Entity& entity : resultEntities) {
        tuples.push_back(std::vector<Entity>{entity});
    }
}

ResultTuples& Result::getTuples() {
    return tuples;
}

SynonymMap& Result::getSynIndices() {
    return synIndices;
}

void Result::setSynIndices(SynonymMap &ssynIndices) {
    synIndices = ssynIndices;
}
