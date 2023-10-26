#pragma once

#include <string>
#include <unordered_set>

typedef std::string ProcedureName;
typedef std::string VariableName;
typedef int StatementNumber;
typedef std::string ConstantValue;
typedef std::string FormattedExpression;
typedef std::string EntityValue;
typedef std::string AttrValue;

class AppConstants {
public:
    inline static const std::string STRING_EMPTY = "";
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

    // ClauseTypes
    inline static const std::string STRING_USES = "Uses";
    inline static const std::string STRING_MODIFIES = "Modifies";
    inline static const std::string STRING_FOLLOWS = "Follows";
    inline static const std::string STRING_FOLLOWSSTAR = "Follows*";
    inline static const std::string STRING_PARENT = "Parent";
    inline static const std::string STRING_PARENTSTAR = "Parent*";
    inline static const std::string STRING_CALLS = "Calls";
    inline static const std::string STRING_CALLSSTAR = "Calls*";
    inline static const std::string STRING_NEXT = "Next";
    inline static const std::string STRING_NEXTSTAR = "Next*";
    inline static const std::string STRING_AFFECTS = "Affects";

    // AttrNames
    inline static const std::string STRING_PROCNAME = "procName";
    inline static const std::string STRING_VARNAME = "varName";
    inline static const std::string STRING_VALUE = "value";
    inline static const std::string STRING_STMTNO = "stmt#";

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
    inline static const std::string STRING_COMMA = ",";
    inline static const std::string STRING_QUOTE = "\"";
    inline static const std::string STRING_UNDERSCORE = "_";
    inline static const std::string STRING_DOT = ".";
    inline static const std::string STRING_LTUPLE = "<";
    inline static const std::string STRING_RTUPLE = ">";


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

    inline static const std::unordered_set<char> MATH_SPECIAL_CHAR_SET = {CHAR_PLUS,
                                                                          CHAR_MINUS,
                                                                          CHAR_TIMES,
                                                                          CHAR_DIVIDE,
                                                                          CHAR_MODULO,
                                                                          CHAR_OPEN_ROUND_PARENTHESIS,
                                                                          CHAR_CLOSE_ROUND_PARENTHESIS};

    inline static const std::unordered_set<std::string> TERM_ARITHMETIC_OPERATOR_STRING_SET = {
            STRING_TIMES, STRING_DIVIDE, STRING_MODULO};

    inline static const std::unordered_set<std::string> EXPR_ARITHMETIC_OPERATOR_STRING_SET = {STRING_PLUS,
                                                                                               STRING_MINUS};

    inline static const StatementNumber INITIAL_STATEMENT_NUMBER = 1;
    inline static const StatementNumber DUMMY_CFGNODE_STATEMENT_NUMBER = -1;
};
