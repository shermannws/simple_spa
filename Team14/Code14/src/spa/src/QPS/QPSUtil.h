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
    static std::unordered_map<StringRep, ClauseType> repClauseTypeMap;
    /**
     * @brief An unordered map that maps a string to TokenType
     */
    static std::unordered_map<std::string, TokenType> strToTokenTypeMap;

    /**
     * @brief An unordered map that maps a string to AttrName
     */
    static std::unordered_map<std::string, AttrName> strToAttrNameMap;

    /**
     * @brief An unordered map that maps QueryEntityType to the corresponding RefType
     */
    static std::unordered_map<QueryEntityType, RefType> entityRefMap;

    /**
     * @brief An unordered map that maps ClauseType to ClauseArgType;
     */
    static std::unordered_map<ClauseType, ClauseArgType> typeToArgTypeMap;

    /**
     * @brief An unordered map that maps QueryEntityType to the set of valid AttrNames
     */
    static std::unordered_map<QueryEntityType, std::unordered_set<AttrName>> entityToAttrNamesMap;

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

    /**
     * @brief An unordered map that maps QueryEntityType to the corresponding function to get the entity from PkbReader
     */
    static std::unordered_map<QueryEntityType, std::function<std::vector<Entity>(std::shared_ptr<PkbReader>)>> entityToGetterMap;
};