#pragma once

#include "../../Commons/HashableKey.h"
#include "../../Commons/Entities/Entity.h"
#include "RelationshipType.h"

class Relationship: public HashableKey {
private:
	RelationshipType relationshipType;
	std::shared_ptr<Entity> leftEntity;
	std::shared_ptr<Entity> rightEntity;

public:
	/*!
	 * Constructor for Relationship class
	 */
	Relationship(const RelationshipType relationshipType,
		const std::shared_ptr<Entity> leftEntity,
		const std::shared_ptr<Entity> rightEntity);

	/*!
	 * Returns the left Entity in a Relationship
	 */
	std::shared_ptr<Entity> getLeftEntity() const;

	/*!
	 * Returns the right Entity in a Relationship
	 */
    std::shared_ptr<Entity> getRightEntity() const;

	/*!
	 * Overriden == operator for comparison between Relationship
	 */
	bool operator==(const HashableKey& other) const override;
};

template <>
struct std::hash<Relationship> {
	std::size_t operator()(const Relationship& relationship) const;
};

template <>
struct std::hash<std::shared_ptr<Relationship>> {
	std::size_t operator()(const std::shared_ptr<Relationship> relationshipPtr) const;
};

template<>
struct std::equal_to<std::shared_ptr<Relationship>> {
	bool operator()(std::shared_ptr<Relationship> const& lhs,
		std::shared_ptr<Relationship> const& rhs) const;
};