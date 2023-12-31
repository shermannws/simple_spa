#pragma once

#include <string>
#include <utility>

#include "ExprSpecParser.h"
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
     * @param query The query with declarations to parse
     * @return a vector of Synonyms declared
     */
    std::vector<Synonym> parseDeclarations(Query &query);

    /**
     * @brief parses result clause and adds the selected synonyms to the query object
     * @param query The query with result clause to parse
     */
    void parseResultClause(Query &query);

    /**
     * @brief parses a tuple result clause and adds the tuple elements to the query
     * @param query The query with tuple in result clause to process
     */
    void processTuple(Query &query);

    /**
     * @brief parses a single element of result clause and adds the element to the query
     * @query The query with element in result clause to process
     */
    void processElem(Query &query);

    /**
     * @brief parses the chain of constraint clause and adds the clauses to the query object
     * @query The query with clauses to parse
     */
    void parseClauses(Query &query);

    /**
     * @brief parses a chain of such that clause and adds the clauses to the query
     * @query The query with SuchThatClause to parse
     */
    void processSuchThatClause(Query &query);

    /**
     * @brief parses a chain of pattern clause and adds the clauses to the query
     * @query The query with PatternClause to parse
     */
    void processPatternClause(Query &query);

    /**
     * @brief parses a chain of with clause and adds the clauses to the query
     * @query The query with WithClause to parse
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
     * @param leftRef The leftRef of the WithClause to validate
     * @param rightRef The rightRef of the WithClause to validate
     */
    void validateWithRefType(Ref &leftRef, Ref &rightRef);

    /**
     * @brief Validates Pattern Clause structure according to the existence of thirdParam
     * @param clause The shared pointer of PatternClause to validate
     */
    void validatePatternStructure(const std::shared_ptr<PatternClause> clause);

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