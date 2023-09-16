#pragma once

#include <vector>
#include <array>
#include <unordered_map>

#include "../Commons/Entities/Entity.h"
#include "QPSTypes.h"

typedef std::vector<Entity> ResultTuple;

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
    std::vector<ResultTuple> tuples;

public:
    Result();
    ResultType getType();
    void setType(ResultType& ttype);
    void setBoolResult(bool result);
    bool getBoolResult();
    void setSynIndices(SynonymMap & ssynIndices);
    SynonymMap getSynIndices();
    void setTuples(const std::vector<ResultTuple>& ttuples);
    std::vector<ResultTuple> getTuples();

};
