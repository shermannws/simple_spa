#include "Result.h"

Result::Result() : type(ResultType::Invalid), boolResult(false) {}

ResultType Result::getType() {
    return type;
}

void Result::setType(std::vector<Synonym> synonyms) {
    if (synonyms.empty()) {
        type = ResultType::Boolean;
    } else {
        type = ResultType::Tuples;
    }

    int i = 0;
    for (const auto& syn: synonyms) {
        synIndices[syn] = i;
        i++;
    }
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

void Result::setSynIndices(SynonymMap &synIndices) {
    this->synIndices = synIndices;
}
