#pragma once

#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::string Synonym;

// Query
class QueryEntity;
typedef std::shared_ptr<QueryEntity> EntityPtr;
typedef std::unordered_map<std::string, std::shared_ptr<QueryEntity>> DeclarationMap;

// Refs
typedef std::string StringRep;
enum ExpressionSpecType {
    WildCard,
    PartialMatch,
    ExactMatch
};
typedef std::string Expression;
typedef std::pair<ExpressionSpecType, Expression> ExpressionSpec;

// Result
class Entity;
typedef std::unordered_map<Synonym, int> SynonymMap;
typedef std::list<std::string> ResultList;
typedef std::unordered_set<std::string> ResultSet;
typedef std::string FormattedResult;
typedef std::vector<std::vector<Entity>> ResultTuples;