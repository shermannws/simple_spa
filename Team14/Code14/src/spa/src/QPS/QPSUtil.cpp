#include "QPSUtil.h"

#include <regex>

bool QPSUtil::IsExpr(const std::string& s){
    size_t operatorPos = std::string::npos;
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == '+' || s[i] == '-') {
            operatorPos = i;
            break;
        }
    }

    if (operatorPos == s.length() - 1){ // if operator found but at last index of string
        return false;
    }

    return operatorPos == std::string::npos && IsTerm(s) // operator not found
           || IsExpr(s.substr(0,operatorPos)) && IsTerm(s.substr(operatorPos + 1, s.length()));
}

bool QPSUtil::IsTerm(const std::string& s) {
    size_t operatorPos = std::string::npos;
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == '*' || s[i] == '/' || s[i] == '%') {
            operatorPos = i;
            break;
        }
    }

    if (operatorPos == s.length() - 1){ // if operator found but at last index of string
        return false;
    }

    return operatorPos == std::string::npos && IsFactor(s) // operator not found
        || IsTerm(s.substr(0,operatorPos)) && IsFactor(s.substr(operatorPos + 1, s.length()));
}

bool QPSUtil::IsFactor(const std::string& s) {
    return IsVarName(s)
        || IsConstValue(s)
        || s.front() == '(' && s.back() == ')' && IsExpr(s.substr(1, s.length() - 2));

}

bool QPSUtil::IsVarName(const std::string& s) {
    std::regex pattern("[a-zA-Z][a-zA-Z0-9]*");
    return std::regex_match(s, pattern);
}

bool QPSUtil::IsConstValue(const std::string& s){
    std::regex pattern("^(0|[1-9]\\d*)$");
    return std::regex_match(s, pattern);
}
