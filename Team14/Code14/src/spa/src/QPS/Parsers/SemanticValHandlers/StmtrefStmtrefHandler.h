#pragma once

#include "SemanticValHandler.h"

/**
 * StmtrefStmtrefHandler class that extends from SemanticValHandler
 */
class StmtrefStmtrefHandler : public SemanticValHandler {
private:
    std::unordered_set<ClauseType> clauseTypes {
        ClauseType::Follows, ClauseType::FollowsStar,
        ClauseType::Parent, ClauseType::ParentStar
    };

public:
    /**
     * @brief Handles (stmtRef,stmtRef) semantic validation of the Clause in the Clause
     * @param query The Query object
     * @param clause The shared pointer of the Clause
     */
    void handle(Query &query, std::shared_ptr<Clause> clause) override;

    void handleRefType(Ref& leftRef, Ref& rightRef);

};
