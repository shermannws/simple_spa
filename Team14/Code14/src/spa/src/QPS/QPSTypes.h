#pragma once

#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::string Synonym;

// Refs
typedef std::string Expression;

// Result
typedef std::unordered_map<Synonym, int> SynonymMap;
typedef std::list<std::string> ResultList;
typedef std::unordered_set<std::string> ResultSet;
typedef std::string FormattedResult;