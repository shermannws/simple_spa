#pragma once

#include "QPS/Clauses/Clause.h"
#include "QPS/Evaluators/Strategies/Strategy.h"
#include "QueryEntity.h"
#include "Ref.h"

/* Represents a function type that retrieves entities from a PkbReader*/
using entityGetterFunc = std::function<std::unordered_set<std::shared_ptr<Entity>>(std::shared_ptr<PkbReader>)>;

/* Represents a function type that creates a Strategy that uses a PkbReader */
using strategyCreatorFunc = std::function<std::shared_ptr<Strategy>(std::shared_ptr<PkbReader>)>;

/**
 * @brief QPSUtil class
 */
class QPSUtil {
public:
    /**
     * @brief An unordered map that maps StringRep of a design entity to its corresponding QueryEntityType
     */
    static std::unordered_map<StringRep, QueryEntityType> designEntities;

    /**
     * @brief An unordered map that maps StringRep to its corresponding ClauseType
     */
    static std::unordered_map<StringRep, ClauseType> repClauseTypeMap;

    /**
     * @brief An unordered map that maps QueryEntityType to the corresponding ClauseType
     */
    static std::unordered_map<QueryEntityType, ClauseType> entityToClauseMap;

    /**
     * @brief An unordered map that maps a pattern clause's ClauseType to the corresponding QueryEntityType
     */
    static std::unordered_map<ClauseType, QueryEntityType> patternClauseToEntityMap;

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
     * @brief An unordered set of QueryEntityTypes that are categorised as stmtRef
     */
    static std::unordered_set<QueryEntityType> stmtRefEntities;

    /**
     * @brief An unordered map of ClauseType and its corresponding strategy creator function
     */
    static std::unordered_map<ClauseType, strategyCreatorFunc> strategyCreatorMap;

    /**
     * @brief An unordered map of query entity type to the corresponding pkb getAll func
     */
    static std::unordered_map<QueryEntityType, entityGetterFunc> entityGetterMap;

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
    static std::unordered_map<AttrName, std::function<std::string(std::shared_ptr<Entity>)>> getValueFunc;

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
    static std::string getAttrName(std::string elem);
};