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

void Result::setTuples(const std::vector<ResultTuple>& ttuples) {
    tuples = ttuples;
}

std::vector<ResultTuple> Result::getTuples() {
    return tuples;
}

SynonymMap Result::getSynIndices() {
    return synIndices;
}

void Result::setSynIndices(SynonymMap &ssynIndices) {
    synIndices = ssynIndices;
}
