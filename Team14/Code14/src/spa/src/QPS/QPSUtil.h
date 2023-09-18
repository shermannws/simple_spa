#pragma once

#include "QPSTypes.h"

class QPSUtil {
public:
    static bool IsExpr(const std::string& s);
    static bool IsTerm(const std::string& s);
    static bool IsFactor(const std::string& s);
    static bool IsVarName(const std::string& s);
    static bool IsConstValue(const std::string& s);
};
