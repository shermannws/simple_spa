#include "Result.h"

Result::Result() : type(ResultType::Invalid), bool_result(false) {
    tuples = std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>>();
}

ResultType Result::getType() {
    return type;
}

void Result::setType(ResultType& ttype) {
    type = ttype;
}

void Result::setBoolResult(bool result) {
    bool_result = result;
}
bool Result::getBoolResult() {
    return bool_result;
}

void Result::setTuples(std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>>& ttuples) {
    tuples = ttuples;
}

std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> Result::getTuples() {
    return tuples;
}