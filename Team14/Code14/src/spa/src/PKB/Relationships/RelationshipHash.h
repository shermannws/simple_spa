#pragma once

template <typename RelationshipType>
struct RelationshipHash {
	size_t operator()(const RelationshipType& relationship) const {
		return std::hash<std::string>()(
			*(relationship.getLeftEntity()->getEntityValue()) +
			"," +
			*(relationship.getRightEntity()->getEntityValue()));
	}
};

template <typename RelationshipType>
struct RelationshipPtrHash {
	size_t operator()(const std::shared_ptr<RelationshipType> relationshipPtr) const {
		return RelationshipHash<RelationshipType>()(*relationshipPtr.get());
	}
};

template <typename RelationshipType>
struct RelationshipPtrComparator {
	bool operator()(
		std::shared_ptr<RelationshipType> const& lhs,
		std::shared_ptr<RelationshipType> const& rhs) const {
		return *lhs == *rhs;
	};
};