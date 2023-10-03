#pragma once

#include "QueryEntity.h"
#include "Ref.h"
#include "QPS/Clauses/Clause.h"
#include "QPS/Evaluators/Strategies/Strategy.h"

/**
 * @brief QPSUtil class
 */
class QPSUtil {
public:
    static std::unordered_set<ClauseType> stmtrefProcVarClauseTypes;

    static std::unordered_map<QueryEntityType, RefType> entityRefMap;

    static std::unordered_set<ClauseType> stmtrefClauseTypes;

    static std::unordered_set<QueryEntityType> stmtRefEntities;
    /**
     * @brief A map of ClauseType and its corresponding strategy creator function
     */
    static std::unordered_map<ClauseType, std::function<std::shared_ptr<Strategy>(std::shared_ptr<PkbReader>)>> strategyCreatorMap;
};