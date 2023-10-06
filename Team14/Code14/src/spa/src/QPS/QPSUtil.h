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
    /**
     * @brief An unordered set of clause types that follow the pattern (stmtref/proc, var)
     */
    static std::unordered_set<ClauseType> stmtrefProcVarClauseTypes;

    /**
     * @brief An unordered map that maps QueryEntityType to the corresponding RefType
     */
    static std::unordered_map<QueryEntityType, RefType> entityRefMap;

    /**
     * @brief An unordered set of clause types that follow the pattern (stmtref, stmtref)
     */
    static std::unordered_set<ClauseType> stmtrefClauseTypes;

    /**
     * @brief An unordered set of QueryEntityTypes that are categorised as stmtRef
     */
    static std::unordered_set<QueryEntityType> stmtRefEntities;

    /**
     * @brief An unordered map of ClauseType and its corresponding strategy creator function
     */
    static std::unordered_map<ClauseType, std::function<std::shared_ptr<Strategy>(std::shared_ptr<PkbReader>)>> strategyCreatorMap;

    /**
     * @brief An unordered map that maps QueryEntityType to the corresponding StatementType
     */
    static std::unordered_map<QueryEntityType, StatementType> entityToStmtMap;
};