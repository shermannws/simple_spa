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

    /**
     * @brief An unordered map that maps AttrName type to the valid query entity types;
     */
    static std::unordered_map<AttrName, std::unordered_set<QueryEntityType>> attrNameToTypeMap;

//    /**
//     * @brief An unordered map of attrName and stmt types that requires returning attrValue instead of Entity value;
//     */
//    static std::unordered_map<AttrName, std::unordered_set<StatementType>> getValueFunc;

    static std::unordered_map<AttrName, std::function<std::string(Entity)>> getValueFunc;

    static Synonym getSyn(std::string elem);

    static AttrName getAttrName(std::string elem);

    //bool isAttrRef(std::string elem, Entity& entity);

};