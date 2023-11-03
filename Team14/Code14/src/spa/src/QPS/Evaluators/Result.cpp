#include "Result.h"

Result::Result() : type(ResultType::Invalid), boolResult(false) {}

Result::Result(bool value) : type(ResultType::Boolean), boolResult(value) {}

Result::Result(std::vector<Synonym> synonyms) : boolResult(false) { this->setType(synonyms); }

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

void Result::setTuples(const std::unordered_set<ResultTuple> &resultTuples) { tuples = resultTuples; }


void Result::setTuples(const std::unordered_set<std::shared_ptr<Entity>> &resultEntities) {
    for (const auto &entity: resultEntities) { tuples.insert(ResultTuple{entity}); }
}

ResultTuples &Result::getTuples() { return tuples; }

SynonymMap &Result::getSynIndices() { return synIndices; }

std::vector<Synonym> Result::getHeader() {
    std::vector<Synonym> synonyms(synIndices.size());
    for (const auto &pair: synIndices) { synonyms[pair.second] = pair.first; }
    return synonyms;
}


bool Result::isTrue() { return (type == ResultType::Boolean && boolResult); }

bool Result::isFalse() { return (type == ResultType::Boolean && !boolResult); }

bool Result::isEmpty() { return (type == ResultType::Tuples && tuples.empty()); }

bool Result::isInvalid() { return type == ResultType::Invalid; }
