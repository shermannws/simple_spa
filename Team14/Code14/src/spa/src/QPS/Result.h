#pragma once

#include <vector>
#include <array>

#include "../Commons/Entities/Entity.h"

enum class ResultType {
    Invalid,
    Boolean, // future milestones
    Tuples
};

class Result {
private:
    ResultType type;
    bool boolResult;
    std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> tuples;

public:
    Result();
    ResultType getType();
    void setType(ResultType& ttype);
    void setBoolResult(bool result);
    bool getBoolResult();
    void setTuples(std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>>& ttuples);
    std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> getTuples();

};
