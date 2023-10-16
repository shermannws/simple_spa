#include "Result.h"

Result::Result() : type(ResultType::Invalid), boolResult(false) {}

Result::Result(bool value) : type(ResultType::Boolean), boolResult(false) {}

ResultType Result::getType() { return type; }

void Result::setType(std::vector<Synonym> synonyms) {
    if (synonyms.empty()) {
        type = ResultType::Boolean;
    } else {
        type = ResultType::Tuples;
    }

    int i = 0;
    for (const auto &syn: synonyms) {
        synIndices[syn] = i;
        i++;
    }
}

void Result::setBoolResult(bool result) { boolResult = result; }
bool Result::getBoolResult() { return boolResult; }

void Result::setTuples(const std::vector<std::vector<Entity>> &resultTuples) {
    tuples = resultTuples;
}

void Result::setTuples(const std::vector<Entity> &resultEntities) {
    for (const Entity &entity: resultEntities) {
        tuples.push_back(std::vector<Entity>{entity});
    }
}

ResultTuples &Result::getTuples() { return tuples; }

SynonymMap &Result::getSynIndices() { return synIndices; }

bool Result::isTrue() { return (type == ResultType::Boolean && boolResult); }

bool Result::isFalse() { return (type == ResultType::Boolean && !boolResult); }

bool Result::isEmpty() {
    return (type == ResultType::Tuples && tuples.empty());
}

bool Result::isInvalid() { return type == ResultType::Invalid; }
