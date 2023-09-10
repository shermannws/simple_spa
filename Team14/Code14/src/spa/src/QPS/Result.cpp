#include "Result.h"

Result::Result() : type(ResultType::Invalid), boolResult(false) {
    tuples = std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>>();
}

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

void Result::setTuples(std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>>& ttuples) {
tuples = ttuples;
}

std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> Result::getTuples() {
    return tuples;
}