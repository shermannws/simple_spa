#pragma once

#include <string>
#include <utility>

#include "ExprSpecParser.h"
#include "QPS/QPSTypes.h"
#include "QPS/Query.h"
#include "QPS/QueryEntity.h"
#include "Tokenizer.h"

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
     * @brief parses declarations and adds the declared entities to the query object
     */
    std::vector<Synonym> parseDeclarations(Query &query);

    /**
     * @brief parses result clause and adds the selected synonyms to the query object
     */
    Synonym parseResultClause(Query &query);

    /**
     * @brief parses the chain of constraint clause and adds the clauses to the query object
     */
    void parseClauses(Query &query);

    /**
     * @brief parses a chain of such that clause and adds the clauses to the query
     */
    void processSuchThatClause(Query &query);

    /**
     * @brief parses a chain of pattern clause and adds the clauses to the query
     */
    void processPatternClause(Query &query);

    /**
     * @brief parses a chain of with clause and adds the clauses to the query
     */
    void processWithClause(Query &query);

    /**
     * @brief Returns a SuchThatClause if syntax is valid, otherwise throws a SyntaxException
     * @return clause the shared pointer of SuchThat Clause
     */
    std::shared_ptr<SuchThatClause> extractSuchThatClause();

    /**
     * @brief Returns a PatternClause if syntax is valid, otherwise throws a SyntaxException
     * @param return the shared pointer of Pattern Clause
     */
    std::shared_ptr<PatternClause> extractPatternClause();

    /**
     * @brief Returns a WithClause if syntax is valid, otherwise throws a SyntaxException
     * @param return the shared pointer of Pattern Clause
     */
    std::shared_ptr<WithClause> extractWithClause();

    /**
     * @brief Validates SuchThatRefType LHS & RHS according to ClauseType
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validateSuchThatRefType(const std::shared_ptr<SuchThatClause> clause);

    /**
     * @brief Validates WithClauseRefType LHS & RHS according to ClauseType
     * @param clause the shared pointer of WithClause to validate
     */
    void validateWithRefType(Ref &leftRef, Ref &rightRef);

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

    /**
     * @brief Returns a Token shared pointer if isToken is true, otherwise throws an Exception with errorMsg
     * @param isToken the token boolean check
     * @param errorMsg the error message of the thrown exception
     */
    std::shared_ptr<Token> expect(bool isToken, const std::string &errorMsg);

public:
    /**
     * @brief The constructor of PQLParser
     * @param PQLQuery the query in string
     */
    explicit PQLParser(const std::string &PQLQuery);

    /**
     * @brief Parses query in string and returns a Query object
     * @return a new Query object
     */
    Query parse();
};