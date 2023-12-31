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
    Next,
    NextStar,
    Calls,
    CallsStar,
    Affects,
    Assign,
    While,
    If,
    With,
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
     * @brief true if clause is negated
     */
    bool negation;

    /**
     * @brief The first parameter of the Clause in Ref
     */
    Ref firstParam;

    /**
     * @brief A virtual function to implement in subclasses, returns true if all the fields are equal
     * @param other The other Clause to compare
     * @return true if the two Clauses are equal
     */
    virtual bool isEqual(const Clause &other) const = 0;

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
     * @brief The setter of the clause negation
     * @param isNegated value of the negation of the clause
     */
    void setNegation(bool isNegated);

    /**
     * @brief returns true if clause contains 'not' otherwise false
     * @return true if clause is a negation clause
     */
    bool isNegation();

    /**
     * @brief The setter of the first parameter of the Clause
     * @param ref The Ref reference of the first parameter
     */
    void setFirstParam(Ref &ref);

    /**
     * @brief The getter of the first parameter of the Clause
     * @return The Ref reference of the first parameter
     */
    Ref &getFirstParam();

    /**
     * @brief returns the list of synonyms present in the clause, used for
     * defining the corresponding Result table header of the clause
     * @return vector of Synonyms
     */
    virtual std::vector<Synonym> getSynonyms() const = 0;

    /**
     * @brief Returns true if the Clause object is equal to the other Clause object, false otherwise
     * @param other The other Clause object to compare against
     * @return True if the Clause object is equal to the other Clause object
     */
    bool operator==(const Clause &other) const;
};

/**
 * @brief An equal function for shared_ptr of Clause objects
 */
template<>
struct std::equal_to<std::shared_ptr<Clause>> {
    bool operator()(std::shared_ptr<Clause> const &lhs, std::shared_ptr<Clause> const &rhs) const;
};
