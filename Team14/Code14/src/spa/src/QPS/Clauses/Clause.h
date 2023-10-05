#pragma once

#include "QPS/QueryEntity.h"
#include "QPS/Ref.h"
#include <string>

/**
 * @brief The enum class of ClassType
 */
enum class ClauseType {
    Uses,
    Modifies,
    Follows,
    FollowsStar,
    Parent,
    ParentStar,
    Assign,
    Invalid
};

/**
 * @brief Clause class
 */
class Clause {
protected:
    /**
     * @brief The ClauseType of the Clause
     */
    ClauseType type;

    /**
     * @brief The first parameter of the Clause in Ref
     */
    Ref firstParam;
public:
    /**
     * @brief The constructor of Clause
     */
    explicit Clause();

    /**
     * @brief The destructor of Clause
     */
    virtual ~Clause() = default;

    /**
     * @brief The setter of the ClauseType of the Clause
     * @param clauseType The ClauseType of the Clause
     */
    void setType(ClauseType clauseType);

    /**
     * @brief The getter of the ClauseType of the Clause
     * @return The ClauseType of the Clause
     */
    ClauseType getType();

    /**
     * @brief The setter of the first parameter of the Clause
     * @param ref The Ref reference of the first parameter
     */
    void setFirstParam(Ref& ref);

    /**
     * @brief The getter of the first parameter of the Clause
     * @return The Ref reference of the first parameter
     */
    Ref& getFirstParam();
};
