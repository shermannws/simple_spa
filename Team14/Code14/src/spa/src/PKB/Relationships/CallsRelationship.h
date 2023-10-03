#pragma once

#include "Relationship.h"
#include "RelationshipType.h"
#include "Commons/Entities/Procedure.h"

/**
 * @brief A class that represents the Calls relationship between two Procedure objects
 * @details A class that represents the Calls relationship between two Procedure objects
 */
class CallsRelationship : public Relationship<Procedure, Procedure> {
private:
    /**
     * @brief A boolean value that indicates if the Procedure relationship is direct
     * @details Two procedure are directly Calls if the first procedure is the procedure immediately before the second procedure
     */
    bool direct;
public:
    /**
     * @brief RelationshipType of CallsRelationship
     */
    static RelationshipType relationshipType;

    /**
     * @brief Construct a new CallsRelationship object
     * @param leftEntity The former procedure of the Calls relationship
     * @param rightEntity The latter procedure of the Calls relationship
     * @param isDirect A boolean value that indicates if the Calls relationship is direct
     * @return A new CallsRelationship object
     */
    CallsRelationship(const std::shared_ptr<Procedure> leftEntity,
        const std::shared_ptr<Procedure> rightEntity, bool isDirect);

    /**
     * @brief Returns a boolean value that indicates if the Calls relationship is direct
     * @return True if the Calls relationship is direct, else false
     */
    bool isDirect() const;
};