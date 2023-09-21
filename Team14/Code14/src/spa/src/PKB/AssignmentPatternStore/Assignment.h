#pragma once

#include <memory>
#include <vector>

#include "../../Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/HashableKey.h"

class Assignment : public HashableKey {
private:
    std::shared_ptr<Statement> statement;
    std::shared_ptr<Variable> variable;
    std::shared_ptr<std::string> expression;
public:
    Assignment(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable, std::shared_ptr<std::string> expression);
    virtual ~Assignment() = default;

    static Entity getStmtFromAssign(const Assignment& assignment);

    static std::vector<Entity> getStmtVarPairFromAssign(const Assignment& assignment);

    std::shared_ptr<Statement> getStatement() const;
    std::shared_ptr<Variable> getVariable() const;
    std::shared_ptr<std::string> getExpression() const;

    bool operator==(const HashableKey& other) const override;
};

template <>
struct std::hash<Assignment> {
    std::size_t operator()(const Assignment& assignment) const;
};

template <>
struct std::hash<std::shared_ptr<Assignment>> {
    std::size_t operator()(const std::shared_ptr<Assignment> assignmentPtr) const;
};

template<>
struct std::equal_to<std::shared_ptr<Assignment>> {
    bool operator()(std::shared_ptr<Assignment> const& lhs,
                    std::shared_ptr<Assignment> const& rhs) const;
};