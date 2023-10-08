#include "Result.h"

Result::Result() : type(ResultType::Invalid), boolResult(false) {}

ResultType Result::getType() {
    return type;
}

void Result::setType(ResultType& type) {
    this->type = type;
}

void Result::setBoolResult(bool result) {
    boolResult = result;
}
bool Result::getBoolResult() {
    return boolResult;
}

void Result::setTuples(const std::vector<std::vector<Entity>>& resultTuples) {
    type = ResultType::Tuples;
    tuples = resultTuples;
}

void Result::setTuples(const std::vector<Entity>& resultEntities) {
    type = ResultType::Tuples;
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

void Result::setSynIndices(std::vector<Synonym> synonyms) {
    int i = 0;
    for (const auto& syn: synonyms) {
        synIndices[syn] = i;
        i++;
    }

    if (synIndices.empty()) {
        type = ResultType::Boolean;
    } else {
        type = ResultType::Tuples;
    }
}

void Result::setSynIndices(SynonymMap &synIndices) {
    this->synIndices = synIndices;
}
