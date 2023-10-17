#pragma once

#include <string>
#include <stdexcept>

#include "QPS/Parsers/Token.h"
#include "QPSTypes.h"

/**
 * Enum class representing all valid query entity types
 */
enum class QueryEntityType {
    Procedure,
    Stmt,
    Read,
    Print,
    Assign,
    Call,
    While,
    If,
    Variable,
    Constant,
    Invalid
};

/**
 * @brief QueryEntity is a design entity declared in PQL queries
 */
class QueryEntity {
private:
    /**
     * @brief The synonym of the query entity
     */
    Synonym synonym;

    /**
     * @brief The Type of the Query Entity of enum type `QueryEntityType`
     */
    QueryEntityType type;

public:
    /**
     * @brief Constructor for QueryEntity
     * @param type type of query entity
     * @param synonym synonym representing the query entity
     */
    explicit QueryEntity(QueryEntityType type, const Synonym &synonym);

    /**
     * @brief Factory method that constructs a Query Entity based on a design Entity token
     * @param designEntity token representing the query entity type string
     * @param synonym the synonym of the query entity created
     */
    QueryEntity(const std::shared_ptr<Token>& designEntity, const Synonym &synonym);

    /**
     * @brief returns true if query entity is equal to the other query entity object, else returns false
     * @param other query entity object
     * @return boolean
     */
    bool operator==(const QueryEntity& other) const;

    /**
     * @brief gets the synonym representing the query entity
     * @return the string representation of the query entity
     */
    Synonym getSynonym();

    /**
     * @brief gets the type of the query entity
     * @return query entity type of the query entity
     */
    QueryEntityType getType();
};
