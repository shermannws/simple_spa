#include "Relationship.h"
#include "UsesRelationship.h"
#include "FollowsRelationship.h"


namespace std {
	template <typename RelationshipType>
	struct RelationshipHash {
		size_t operator()(const RelationshipType& relationship) const {
			return hash<string>()(
				*(relationship.getLeftEntity()->getEntityValue()) +
				"," +
				*(relationship.getRightEntity()->getEntityValue()));
		}
	};

	template <typename RelationshipType>
	struct RelationshipPtrHash {
		size_t operator()(const shared_ptr<RelationshipType> relationshipPtr) const {
			return RelationshipHash<RelationshipType>()(*relationshipPtr.get());
		}
	};

	template <typename RelationshipType>
	struct RelationshipPtrComparator {
		bool operator()(
			shared_ptr<RelationshipType> const& lhs,
			shared_ptr<RelationshipType> const& rhs) const {
			return *lhs == *rhs;
		};
	};
}

// Specialization for UsesRelationship
template <>
struct std::hash<UsesRelationship> : public std::RelationshipHash<UsesRelationship> {};

template <>
struct std::hash<std::shared_ptr<UsesRelationship>> : public std::RelationshipPtrHash<UsesRelationship> {};

template <>
struct std::equal_to< std::shared_ptr<UsesRelationship>> : public std::RelationshipPtrComparator<UsesRelationship> {};


// Specialization for FollowsRelationship
template <>
struct std::hash<FollowsRelationship> : public std::RelationshipHash<FollowsRelationship> {};

template <>
struct std::hash<std::shared_ptr<FollowsRelationship>> : public std::RelationshipPtrHash<FollowsRelationship> {};

template <>
struct std::equal_to< std::shared_ptr<FollowsRelationship>> : public std::RelationshipPtrComparator<FollowsRelationship> {};