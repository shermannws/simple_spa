#include "Assignment.h"

Assignment::Assignment(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable,
                       std::shared_ptr<Expression> expression)
    : statement(statement), variable(variable), expression(expression) {}

std::shared_ptr<Statement> Assignment::getStatement() const { return statement; }

std::shared_ptr<Variable> Assignment::getVariable() const { return variable; }

std::shared_ptr<Expression> Assignment::getExpression() const { return expression; }

bool Assignment::operator==(const Assignment &other) const { return this->getStatement() == other.getStatement(); }

EntityPointer Assignment::getStmtFromAssign(const std::shared_ptr<Assignment> assignment) {
    return assignment->getStatement();
}

std::vector<EntityPointer> Assignment::getStmtVarPairFromAssign(const std::shared_ptr<Assignment> assignment) {
    return {assignment->getStatement(), assignment->getVariable()};
}

std::size_t std::hash<std::shared_ptr<Assignment>>::operator()(const std::shared_ptr<Assignment> assignmentPtr) const {
    return std::hash<std::shared_ptr<Entity>>()(assignmentPtr->getStatement());
}

bool std::equal_to<std::shared_ptr<Assignment>>::operator()(std::shared_ptr<Assignment> const &lhs,
                                                            std::shared_ptr<Assignment> const &rhs) const {
    return *lhs == *rhs;
}