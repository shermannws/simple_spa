#pragma once

#include <string>
#include <utility>

#include "QPS/Query.h"
#include "Tokenizer.h"
#include "QPS/QueryEntity.h"
#include "ExprSpecParser.h"
#include "QPS/QPSTypes.h"

/**
 * @brief PQLParser class
 */
class PQLParser {
private:
    /**
     * @brief The tokenizer used to tokenize query
     */
    std::shared_ptr<Tokenizer> tokenizer;

    /**
     * @brief The expression-spec parser used to parse expression-spec
     */
    std::shared_ptr<ExprSpecParser> exprSpecParser;

    /**
     * @brief Parses declarations syntactically and extracts the declared entities
     * @return vector of declared entities
     */
    std::vector<std::shared_ptr<QueryEntity>> processDeclarations();

    /**
     * @brief Parses select clause syntactically ad extracts the selected synonym
     * @return the selected synonym
     */
    Synonym processSelectClause();

    /**
     * @brief parses a chain of such that clause and adds the clauses to the query
     */
    void processSuchThatClause(Query& query);

    /**
     * @brief parses a chain of pattern clause and adds the clauses to the query
     */
    void processPatternClause(Query& query);

    /**
     * @brief Returns a SuchThatClause if syntax is valid, otherwise throws a SyntaxException
     * @return clause the shared pointer of SuchThat Clause
     */
    std::shared_ptr<SuchThatClause> extractSuchThatClause();

    /**
    * @brief Validates SuchThatRefType LHS & RHS according to ClauseType
    * @param clause the shared pointer of SuchThatClause to validate
    */
    void validateSuchThatRefType(const std::shared_ptr<SuchThatClause> clause);

    /**
     * @brief Returns a PatternClause if syntax is valid, otherwise throws a SyntaxException
     * @param return the shared pointer of Pattern Clause
     */
    std::shared_ptr<PatternClause> extractPatternClause();

    /**
     * @brief Validates the declarations and stores them in the query object,
     * otherwise throws a Semantic exception in case of an entity redeclaration
     * @param query the query object
     * @param entities the vector of shared pointer to query entities declared
     */
    void setDeclarations(Query& query, const std::vector<std::shared_ptr<QueryEntity>>& entities);

    /**
     * @brief Returns a Token shared pointer if isToken is true, otherwise throws an Exception with errorMsg
     * @param isToken the token boolean check
     * @param errorMsg the error message of the thrown exception
     */
    std::shared_ptr<Token> expect(bool isToken, const std::string& errorMsg);

    /**
     * @brief Returns the next token as Ref if it is Integer, Identity, Wildcard or Synonym,
     * otherwise throws a SyntaxException
     * @return a Ref object
     */
    Ref extractRef();

    /**
    * @brief Returns the next token as QueryEntity of the specified type if it is a valid ident
    * otherwise throws a SyntaxException
    * @param entityType a shared ptr to a Token which represents the query entity type
    * @return a shared ptr to a QueryEntity
    */
    std::shared_ptr<QueryEntity> extractQueryEntity(std::shared_ptr<Token> entityType);

public:
    /**
     * @brief The constructor of PQLParser
     * @param PQLQuery the query in string
     */
    explicit PQLParser(const std::string& PQLQuery);

    /**
     * @brief Parses query in string and returns a Query object
     * @return a new Query object
     */
    Query parse();
};