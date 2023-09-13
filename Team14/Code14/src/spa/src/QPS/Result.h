#pragma once

#include <vector>
#include <array>
#include <unordered_map>

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
    std::unordered_map<std::string, int> synIndices;
    std::vector<std::vector<Entity>> tuples;

public:
    Result();
    ResultType getType();
    void setType(ResultType& ttype);
    void setBoolResult(bool result);
    bool getBoolResult();
    void setSynIndices(std::unordered_map<std::string, int>& ssynIndices);
    std::unordered_map<std::string, int> getSynIndices();
    void setTuples(std::vector<std::vector<Entity>>& ttuples);
    std::vector<std::vector<Entity>> getTuples();

};
