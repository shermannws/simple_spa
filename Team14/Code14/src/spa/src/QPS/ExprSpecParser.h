#pragma once

#include <string>
#include <stack>
#include <stdexcept>

#include "Tokenizer.h"
#include "QPSTypes.h"

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
     * Returns true if the vector of tokens is a valid Expr
     * @param input vector of Token ptr
     * @return boolean
     */
    void processSubExpr(std::stack<std::shared_ptr<Token>>& operators, std::stack<std::string>& expression);

    Expression extractExpression();

public:
    explicit ExprSpecParser(std::shared_ptr<Tokenizer> tokenizer);
    ExpressionSpec extractExpressionSpec();
};

