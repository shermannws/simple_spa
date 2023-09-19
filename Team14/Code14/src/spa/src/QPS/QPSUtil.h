#pragma once

#include "QueryEntity.h"

class QPSUtil {
public:
    static bool isOfStmtType(QueryEntityType entityType);
    static bool isOfUsesStmtType(QueryEntityType entityType);
    static bool isOfModifiesStmtType(QueryEntityType entityType);
};