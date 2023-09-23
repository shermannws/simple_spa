#pragma once

#include "QPSUtil.h"

bool QPSUtil::isOfStmtType(QueryEntityType entityType) {
    return entityType == QueryEntityType::Stmt || entityType == QueryEntityType::Assign
           || entityType == QueryEntityType::Print || entityType == QueryEntityType::If
           || entityType == QueryEntityType::While || entityType == QueryEntityType::Read;
//            entityType == QueryEntityType::Call; // TODO: to uncomment after Milestone 1
}

bool QPSUtil::isRootOfEntref(RootType rootType) {
    return rootType == RootType::Synonym || rootType == RootType::Wildcard
           || rootType == RootType::Ident;
}

bool QPSUtil::isRootOfStmtref(RootType rootType) {
    return rootType == RootType::Synonym || rootType == RootType::Wildcard
           || rootType == RootType::Integer;
}


