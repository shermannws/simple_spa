#pragma once

#include <memory>
#include <vector>

#include "../../Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/HashableKey.h"
#include "PKB/PkbTypes.h"

/**
 * @brief A class that represents an assignment statement
 * @details A class that represents an assignment statement
 */
class Assignment : public HashableKey {
private:
    /**
     * @brief The statement that is an assignment statement
     */
    std::shared_ptr<Statement> statement;

    /**
     * @brief The variable that is being assigned to
     */
    std::shared_ptr<Variable> variable;

    /**
     * @brief The expression that is being assigned to the variable
     */
    std::shared_ptr<Expression> expression;

public:
    /**
     * @brief Construct a new Assignment object
     * @param statement The statement that is an assignment statement
     * @param variable The variable that is being assigned to
     * @param expression The expression that is being assigned to the variable
     * @return A new Assignment object
     */
    Assignment(std::shared_ptr<Statement> statement, std::shared_ptr<Variable> variable,
               std::shared_ptr<Expression> expression);

    /**
     * @brief Destroy the Assignment object
     * @return None
     * @note Default destructor
     */
    virtual ~Assignment() = default;

    /**
     * @brief Returns the Statement object from the Assignment object
     * @param assignment The Assignment object
     * @return The Statement object that represents the assignment statement
     */
    static EntityPointer getStmtFromAssign(const std::shared_ptr<Assignment> assignment);

    /**
     * @brief Returns the Statement and Variable Pair as a vector from the Assignment object
     * @param assignment The Assignment object
     * @return A vector containing the Statement and Variable objects of the Assignment object
     * @note The Statement object is at index 0 and the Variable object is at index 1
     */
    static std::vector<EntityPointer> getStmtVarPairFromAssign(const std::shared_ptr<Assignment> assignment);

    /**
     * @brief Returns the Statement object from the Assignment object
     * @param None
     * @return The Statement object that represents the assignment statement
     */
    std::shared_ptr<Statement> getStatement() const;

    /**
     * @brief Returns the Variable object from the Assignment object
     * @param None
     * @return The Variable object that represents the variable being assigned to
     */
    std::shared_ptr<Variable> getVariable() const;

    /**
     * @brief Returns the Expression from the Assignment object
     * @return The Expression that represents the expression being assigned to the variable
     */
    std::shared_ptr<Expression> getExpression() const;

    /**
     * @brief Returns true if the Assignment object is equal to the other Assignment object, false otherwise
     * @param other The other Assignment object to compare against
     * @return True if the Assignment object is equal to the other Assignment object, false otherwise
     */
    bool operator==(const HashableKey &other) const override;
};

template<>
struct std::hash<Assignment> {
    std::size_t operator()(const Assignment &assignment) const;
};

template<>
struct std::hash<std::shared_ptr<Assignment>> {
    std::size_t operator()(const std::shared_ptr<Assignment> assignmentPtr) const;
};

template<>
struct std::equal_to<std::shared_ptr<Assignment>> {
    bool operator()(std::shared_ptr<Assignment> const &lhs, std::shared_ptr<Assignment> const &rhs) const;
};