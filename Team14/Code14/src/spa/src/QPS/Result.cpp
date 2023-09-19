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

void Result::setTuples(const std::vector<std::vector<Entity>>& ttuples) {
    tuples = ttuples;
}

std::vector<std::vector<Entity>> Result::getTuples() {
    return tuples;
}

std::unordered_map<std::string, int> Result::getSynIndices() {
    return synIndices;
}

void Result::setSynIndices(std::unordered_map<std::string, int> &ssynIndices) {
    synIndices = ssynIndices;
}
