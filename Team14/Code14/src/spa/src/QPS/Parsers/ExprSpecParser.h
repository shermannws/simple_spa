#pragma once

#include <string>
#include <stack>
#include <stdexcept>

#include "Tokenizer.h"
#include "QPS/QPSTypes.h"

/**
 * @class ExprSpecParser handles parsing of expr-spec in PQL queries
 */
class ExprSpecParser {
private:
    /**
     * @brief The tokenizer that produces the stream of tokens
     */
    std::shared_ptr<Tokenizer> tokenizer;

    /**
     * Returns true if the vector of tokens is a valid expr
     * @param input vector of Token ptr
     * @param index starting index of vector that needs to be validated
     * @return boolean
     */
    bool isExpr(std::vector<std::shared_ptr<Token>>& input, size_t& index);

    /**
     * Returns true if the vector of tokens is a valid term
     * @param input vector of Token ptr
     * @param index starting index of vector that needs to be validated
     * @return boolean
     */
    bool isTerm(std::vector<std::shared_ptr<Token>>& input, size_t& index);

    /**
     * Returns true if the vector of tokens is a valid factor
     * @param input vector of Token ptr
     * @param index starting index of vector that needs to be validated
     * @return boolean
     */
    bool isFactor(std::vector<std::shared_ptr<Token>>& input, size_t& index);

    /**
     * Returns true if the vector of tokens is a valid Expr
     * @param input vector of Token ptr
     * @return boolean
     */
    bool validateExprSyntax(std::vector<std::shared_ptr<Token>>& input);

    /**
     * Processes the next operator's subexpression and pushes the subexpression to the expression stack
     * @param operators stack
     * @param expression stack of strings of expression
     */
    void processSubExpr(std::stack<std::shared_ptr<Token>>& operators, std::stack<std::string>& expression);

    /**
     * Extracts a valid expression from token stream, throws error if not found
     * @return the expression as a string
     */
    Expression extractExpression();

public:
    explicit ExprSpecParser(std::shared_ptr<Tokenizer> tokenizer);

    /**
     * Extracts a valid expr-spec from token stream, throws error if no valid expr spec
     * @return the expr-spec as a pair of Expression and expr-spec type
     */
    ExpressionSpec extractExpressionSpec();
};

