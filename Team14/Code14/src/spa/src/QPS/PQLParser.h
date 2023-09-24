#pragma once

#include <string>
#include <utility>

#include "Query.h"
#include "Tokenizer.h"
#include "QueryEntity.h"
#include "ExprSpecParser.h"

/*
 * @brief PQLParser class
 */
class PQLParser {
private:
    /*
     * @brief The tokenizer used to tokenize query
     */
    std::shared_ptr<Tokenizer> tokenizer;

    /*
     * @brief The expression-spec parser used to parse expression-spec
     */
    std::shared_ptr<ExprSpecParser> exprSpecParser;

    /*
     * @brief Parses declarations syntactically and semantically
     * @param query the Query object
     */
    void processDeclarations(Query& query);

    /*
     * @brief Parses select clause syntactically and semantically
     * @param query the Query object
     */
    void processSelectClause(Query& query);

    /*
     * @brief Parses SuchThatClause syntactically and semantically
     * @param query the Query object
     */
    void processSuchThatClause(Query& query);

    /*
     * @brief Parses PatternClause syntactically and semantically
     * @param query the Query object
     */
    void processPatternClause(Query& query);
    /*
     * @brief Returns a Token shared pointer if isToken is true, otherwise throws an Exception with errorMsg
     * @param isToken the token boolean check
     * @param errorMsg the error message of the thrown exception
     */
    std::shared_ptr<Token> expect(bool isToken, const std::string& errorMsg);

    /*
     * @brief Returns the next token as Ref if it is Integer, Identity, Wildcard or Synonym, otherwise throws a SyntaxException
     * @return a Ref object
     */
    Ref extractRef();

    /*
     * @brief Validates SuchThatClause syntactically, otherwise throws a SyntaxException
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validateSuchThatSyntax(std::shared_ptr<SuchThatClause> clause);

    /*
     * @brief Validates SuchThatClause semantically, otherwise throws a SemanticException
     * @param query the Query object
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validateSuchThatSemantics(Query& query, const std::shared_ptr<SuchThatClause> clause);

    /*
     * @brief Validates SuchThatRefType LHS & RHS according to ClauseType
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validateSuchThatRefType(const std::shared_ptr<SuchThatClause> clause);

    /*
     * @brief Validates PatternClause syntactically, otherwise throws a SyntaxException
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validatePatternSyntax(std::shared_ptr<PatternClause> clause);

    /*
     * @brief Validates PatternClause semantically, otherwise throws a SemanticException
     * @param query the Query object
     * @param clause the shared pointer of PatternClause to validate
     */
    void validatePatternSemantics(Query& query, const std::shared_ptr<PatternClause> clause);

public:
    /*
     * @brief The constructor of PQLParser
     * @param PQLQuery the query in string
     */
    explicit PQLParser(const std::string& PQLQuery);

    /*
     * @brief Parses query in string and returns a Query object
     * @return a new Query object
     */
    Query parse();
};
