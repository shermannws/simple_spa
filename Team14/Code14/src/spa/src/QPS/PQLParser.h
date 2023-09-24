#pragma once

#include <string>
#include <utility>

#include "Query.h"
#include "Tokenizer.h"
#include "QueryEntity.h"
#include "ExprSpecParser.h"
#include "QPSTypes.h"

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
    Synonym processSelectClause(Query& query);

    /**
     * @brief parses the query for any such that clause and extracts the related
     * information into a such that clause object
     * @param query the Query object
     * @return a shared pointer to the pattern clause
     */
    std::shared_ptr<SuchThatClause> processSuchThatClause(Query& query);

    /**
     * @brief parses the query for any pattern clause and extracts the related
     * information into a pattern clause object
     * @param query the Query object
     * @return a shared pointer to the pattern clause
     */
    std::shared_ptr<PatternClause> processPatternClause(Query& query);

    /**
     * @brief Validates SuchThatClause syntactically, otherwise throws a SyntaxException
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validateSuchThatSyntax(std::shared_ptr<SuchThatClause> clause);

    /**
    * @brief Validates SuchThatRefType LHS & RHS according to ClauseType
    * @param clause the shared pointer of SuchThatClause to validate
    */
    void validateSuchThatRefType(const std::shared_ptr<SuchThatClause> clause);

    /**
     * @brief Validates PatternClause syntactically, otherwise throws a SyntaxException
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validatePatternSyntax(std::shared_ptr<PatternClause> clause);

    /**
     * @brief Validates the declarations and stores them in the query object,
     * otherwise throws a Semantic exception in case of an entity redeclaration
     * @param query the query object
     * @param entities the vector of shared pointer to query entities declared
     */
    void validateDeclarations(Query& query, const std::vector<std::shared_ptr<QueryEntity>>& entities);

    /**
     * @brief Validates the selected entity and stores them in the query object,
     * otherwise throws a Semantic exception if not valid
     * @param query the query object
     * @param syn the synonym selected in the query
     */
    void validateSelectSemantics(Query& query, const Synonym& syn);

    /**
     * @brief Validates SuchThatClause semantically, and stores it in the query object
     * otherwise throws a SemanticException
     * @param query the Query object
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validateSuchThatSemantics(Query& query, const std::shared_ptr<SuchThatClause> clause);

    /**
     * @brief Validates PatternClause semantically, and stores it in the query object
     * otherwise throws a SemanticException
     * @param query the Query object
     * @param clause the shared pointer of PatternClause to validate
     */
    void validatePatternSemantics(Query& query, const std::shared_ptr<PatternClause> clause);

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