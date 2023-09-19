#pragma once

#include "QPSUtil.h"

bool QPSUtil::isOfStmtType(QueryEntityType entityType) {
    return entityType == QueryEntityType::Stmt || entityType == QueryEntityType::Assign
           || entityType == QueryEntityType::Print || entityType == QueryEntityType::If
           || entityType == QueryEntityType::While || entityType == QueryEntityType::Call
           || entityType == QueryEntityType::Read;
}

bool QPSUtil::isOfUsesStmtType(QueryEntityType entityType) {
    return entityType == QueryEntityType::Stmt || entityType == QueryEntityType::Assign
           || entityType == QueryEntityType::Print || entityType == QueryEntityType::If
           || entityType == QueryEntityType::While || entityType == QueryEntityType::Call;
}

bool QPSUtil::isOfModifiesStmtType(QueryEntityType entityType) {
    return entityType == QueryEntityType::Stmt || entityType == QueryEntityType::Assign
           || entityType == QueryEntityType::Read || entityType == QueryEntityType::If
           || entityType == QueryEntityType::While || entityType == QueryEntityType::Call;
}