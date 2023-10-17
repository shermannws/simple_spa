#pragma once

#include "QPS/Clauses/Clause.h"
#include "QPS/Evaluators/Strategies/Strategy.h"
#include "QueryEntity.h"
#include "Ref.h"

/**
 * @brief QPSUtil class
 */
class QPSUtil {
public:
    /**
     * @brief An unordered map that maps StringRep to the corresponding ClauseType
     */
    static std::unordered_map<StringRep, ClauseType> repClauseTypeMap;

    /**
     * @brief An unordered map that maps QueryEntityType to the corresponding ClauseType
     */
    static std::unordered_map<QueryEntityType, ClauseType> entityToClauseMap;

    /**
     * @brief An unordered map that maps QueryEntityType to the corresponding RefType
     */
    static std::unordered_map<QueryEntityType, RefType> entityRefMap;

    /**
     * @brief An unordered map that maps ClauseType to ClauseArgType;
     */
    static std::unordered_map<ClauseType, ClauseArgType> typeToArgTypeMap;

    /**
     * @brief An unordered set of QueryEntityTypes that are categorised as stmtRef
     */
    static std::unordered_set<QueryEntityType> stmtRefEntities;

    /**
     * @brief An unordered map of ClauseType and its corresponding strategy creator function
     */
    static std::unordered_map<ClauseType, std::function<std::shared_ptr<Strategy>(std::shared_ptr<PkbReader>)>>
            strategyCreatorMap;

    /**
     * @brief An unordered map that maps QueryEntityType to the corresponding StatementType
     */
    static std::unordered_map<QueryEntityType, StatementType> entityToStmtMap;
};