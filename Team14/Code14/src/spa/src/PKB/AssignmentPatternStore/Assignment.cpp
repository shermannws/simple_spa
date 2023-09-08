#include "Assignment.h"

Assignment::Assignment(
        std::shared_ptr<Statement> statement,
        std::shared_ptr<Variable> variable,
        std::shared_ptr<std::string> expression
        ) {
    this->statement = statement;
    this->variable = variable;
    this->expression = expression;
}

std::shared_ptr<Statement> Assignment::getStatement() const {
    return statement;
}

std::shared_ptr<Variable> Assignment::getVariable() const {
    return variable;
}

std::shared_ptr<std::string> Assignment::getExpression() const {
    return expression;
}

bool Assignment::operator==(const HashableKey& other) const {
    if (const Assignment* otherKey = dynamic_cast<const Assignment*>(&other)) {
        return *this->getStatement() == *otherKey->getStatement();
    }
    return false;
}

std::size_t std::hash<Assignment>::operator()(const Assignment& assignment) const {
    return std::hash<Entity>()(*assignment.getStatement());
}

std::size_t std::hash<std::shared_ptr<Assignment>>::operator()(const std::shared_ptr<Assignment> assignmentPtr) const {
    return std::hash<Assignment>()(*assignmentPtr);
}

bool std::equal_to<std::shared_ptr<Assignment>>::operator()(
        std::shared_ptr<Assignment> const& lhs,
        std::shared_ptr<Assignment> const& rhs) const {
    return *lhs == *rhs;
}