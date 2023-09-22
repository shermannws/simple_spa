#pragma once

#include <string>
#include <stack>
#include <stdexcept>

#include "Tokenizer.h"
#include "QPSTypes.h"

class ExprSpecParser {
private:
    std::shared_ptr<Tokenizer> tokenizer;

    bool isExpr(std::vector<std::shared_ptr<Token>>& input, size_t& index);
    bool isTerm(std::vector<std::shared_ptr<Token>>& input, size_t& index);
    bool isFactor(std::vector<std::shared_ptr<Token>>& input, size_t& index);
    bool validateExprSyntax(std::vector<std::shared_ptr<Token>>& input);
    void processSubExpr(std::stack<std::shared_ptr<Token>>& operators, std::stack<std::string>& expression);
    Expression extractExpression();

public:
    explicit ExprSpecParser(std::shared_ptr<Tokenizer> tokenizer);
    ExpressionSpec extractExpressionSpec();
};

