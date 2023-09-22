#pragma once

#include <vector>
#include <array>
#include <unordered_map>

#include "../Commons/Entities/Entity.h"
#include "QPSTypes.h"

enum class ResultType {
    Invalid,
    Boolean, // future milestones
    Tuples
};

class Result {
private:
    ResultType type;
    bool boolResult;
    SynonymMap synIndices;
    ResultTuples tuples;

public:
    Result();
    ResultType getType();
    void setType(ResultType& ttype);
    void setBoolResult(bool result);
    bool getBoolResult();
    void setSynIndices(SynonymMap & ssynIndices);
    SynonymMap& getSynIndices();
    void setTuples(const std::vector<Entity>& resultEntities);
    void setTuples(const std::vector<std::vector<Entity>>& resultTuples);
    ResultTuples& getTuples();
};
