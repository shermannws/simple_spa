#pragma once

#include <string>

typedef std::string ProcedureName;
typedef int StatementNumber;
typedef std::string FormattedExpression;

class AppConstants {
public:
    // Entities
    inline static const std::string STRING_PROCEDURE = "procedure";
    inline static const std::string STRING_STATEMENT = "stmt";
    inline static const std::string STRING_READ = "read";
    inline static const std::string STRING_PRINT = "print";
    inline static const std::string STRING_ASSIGN = "assign";
    inline static const std::string STRING_CALL = "call";
    inline static const std::string STRING_WHILE = "while";
    inline static const std::string STRING_IF = "if";
    inline static const std::string STRING_THEN = "then";
    inline static const std::string STRING_ELSE = "else";
    inline static const std::string STRING_VARIABLE = "variable";
    inline static const std::string STRING_CONSTANT = "constant";


    inline static const std::string STRING_INTEGER_REGEX = "^[0-9]+$";

    inline static const std::string STRING_GREATER_THAN = ">";
    inline static const std::string STRING_LESS_THAN = "<";
    inline static const std::string STRING_GREATER_EQUAL = ">=";
    inline static const std::string STRING_LESS_EQUAL = "<=";
    inline static const std::string STRING_DOUBLE_EQUAL = "==";
    inline static const std::string STRING_NOT_EQUAL = "!=";
    inline static const std::string STRING_NOT = "!";
    inline static const std::string STRING_AND = "&&";
    inline static const std::string STRING_OR = "||";
    inline static const std::string STRING_EQUAL = "=";
    inline static const std::string STRING_PLUS = "+";
    inline static const std::string STRING_MINUS = "-";
    inline static const std::string STRING_TIMES = "*";
    inline static const std::string STRING_DIVIDE = "/";
    inline static const std::string STRING_MODULO = "%";
    inline static const std::string STRING_OPEN_ROUND_PARENTHESIS = "(";
    inline static const std::string STRING_CLOSE_ROUND_PARENTHESIS = ")";
    inline static const std::string STRING_OPEN_CURLY_PARENTHESIS = "{";
    inline static const std::string STRING_CLOSE_CURLY_PARENTHESIS = "}";
    inline static const std::string STRING_SEMICOLON = ";";

    inline static const char CHAR_GREATER_THAN = '>';
    inline static const char CHAR_LESS_THAN = '<';
    inline static const char CHAR_NOT = '!';
    inline static const char CHAR_AMPERSAND = '&';
    inline static const char CHAR_VERTICAL_BAR = '|';
    inline static const char CHAR_EQUAL = '=';
    inline static const char CHAR_PLUS = '+';
    inline static const char CHAR_MINUS = '-';
    inline static const char CHAR_TIMES = '*';
    inline static const char CHAR_DIVIDE = '/';
    inline static const char CHAR_MODULO = '%';
    inline static const char CHAR_OPEN_ROUND_PARENTHESIS = '(';
    inline static const char CHAR_CLOSE_ROUND_PARENTHESIS = ')';
    inline static const char CHAR_OPEN_CURLY_PARENTHESIS = '{';
    inline static const char CHAR_CLOSE_CURLY_PARENTHESIS = '}';
    inline static const char CHAR_SEMICOLON = ';';
};
