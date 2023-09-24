#pragma once

/**
 * @brief A struct that represents the hash function for a Relationship
 * @tparam RelationshipType
 * @note This hash function is used by the RelationshipStore class
 */
template <typename RelationshipType>
struct RelationshipHash {
	size_t operator()(const RelationshipType& relationship) const {
		return std::hash<std::string>()(
			*(relationship.getLeftEntity()->getEntityValue()) +
			"," +
			*(relationship.getRightEntity()->getEntityValue()));
	}
};

/**
 * @brief A struct that represents the hash function for a Relationship pointer
 * @tparam RelationshipType
 * @note This hash function is used by the RelationshipStore class
 */
template <typename RelationshipType>
struct RelationshipPtrHash {
	size_t operator()(const std::shared_ptr<RelationshipType> relationshipPtr) const {
		return RelationshipHash<RelationshipType>()(*relationshipPtr.get());
	}
};

/**
 * @brief A struct that represents the comparator for a Relationship
 * @tparam RelationshipType
 * @note This comparator is used by the RelationshipStore class
 */
template <typename RelationshipType>
struct RelationshipPtrComparator {
	bool operator()(
		std::shared_ptr<RelationshipType> const& lhs,
		std::shared_ptr<RelationshipType> const& rhs) const {
		return *lhs == *rhs;
	};
};