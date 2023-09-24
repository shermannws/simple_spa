#pragma once

#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/* Type alias for a string representing a synonym of an entity*/
typedef std::string Synonym;

// Query typedefs
class QueryEntity;
/* Type alias for a shared pointer to QueryEntity */
typedef std::shared_ptr<QueryEntity> EntityPtr;
/* Type alias for an unordered map of string to shared pointer to QueryEntity */
typedef std::unordered_map<std::string, std::shared_ptr<QueryEntity>> DeclarationMap;


/* Type alias for a string representation of a stmtRef or entRef */
typedef std::string StringRep;


/* enum class for the valid types of expr-spec */
enum ExpressionSpecType {
    Wildcard,
    PartialMatch,
    ExactMatch
};
/* Type alias for a string representing an expression */
typedef std::string Expression;
/* Type alias for a pair of ExpressionSpecType and Expression representing an expr-spec */
typedef std::pair<ExpressionSpecType, Expression> ExpressionSpec;

// Result typedefs
class Entity;
/* Type alias for an unordered map representing synonym-to-index mapping for a Result table header*/
typedef std::unordered_map<Synonym, int> SynonymMap;
/* Type alias for a list of strings representing the formatted result */
typedef std::list<std::string> ResultList;
/* Type alias for an unordered set of strings representing a set of results */
typedef std::unordered_set<std::string> ResultSet;
/* Type alias for a string representing a formatted result */
typedef std::string FormattedResult;
/* Type alias for a vector of vectors of Entities, representing rows of tuples in a result table */
typedef std::vector<std::vector<Entity>> ResultTuples;