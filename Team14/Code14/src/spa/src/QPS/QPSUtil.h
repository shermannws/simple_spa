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
     * @brief An unordered map of query entity type to the corresponding pkb getAll func
     */
    static std::unordered_map<QueryEntityType, std::function<std::vector<Entity>(std::shared_ptr<PkbReader>)>>
            entityGetterMap;

    /**
     * @brief An unordered map that maps QueryEntityType to the corresponding StatementType
     */
    static std::unordered_map<QueryEntityType, StatementType> entityToStmtMap;

    /**
     * @brief An unordered map that maps AttrName type to the valid query entity types;
     */
    static std::unordered_map<AttrName, std::unordered_set<QueryEntityType>> attrNameToTypeMap;

    /**
     * @brief An unordered map of attrName strings to the entity's getValue func based on attrName
     */
    static std::unordered_map<AttrName, std::function<std::string(Entity)>> getValueFunc;

    /**
     * @brief returns the synonym of an element
     * @param elem the element string
     * @return the element itself for synonym elements, the synonym without attrName for attrRef elements
     */
    static Synonym getSyn(std::string elem);

    /**
     * @brief returns the attrName of an element
     * @param elem the element string
     * @return the empty string for synonym elements, the attrName without the synonym for attrRef elements
     */
    static AttrName getAttrName(std::string elem);
};