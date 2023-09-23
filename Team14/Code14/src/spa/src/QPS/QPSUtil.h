#pragma once

#include "QueryEntity.h"
#include "Ref.h"

class QPSUtil {
public:
    static bool isOfStmtType(QueryEntityType entityType);
    static bool isRootOfEntref(RootType rootType);
    static bool isRootOfStmtref(RootType rootType);
};