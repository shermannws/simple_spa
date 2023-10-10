#pragma once

#include <string>

#include "QueryEntity.h"
#include "QPSTypes.h"

/**
 * @brief The enum class of RefType
 */
enum class RefType {
    StmtRef,
    EntRef,
    WithRef,
    Invalid,
};

/**
 * @brief The enum class of RootType
 */
enum class RootType {
    Integer, // StmtRef & WithRef
    Wildcard, // StmtRef & EntRef
    Synonym, // StmtRef & EntRef
    Ident, // EntRef & WithRef
    AttrRef, // WithRef
    Invalid
};

/**
 * @brief Ref class
 */
class Ref {
private:
    /**
     * @brief The string representation of the Ref
     */
    StringRep rep;

    std::string attrName; // if any

    /**
     * @brief The RefType of the Ref
     */
    RefType type;

    /**
     * @brief The RootType of the Ref
     */
    RootType rootType;

    /**
     * @brief The QueryEntityType of the Ref
     */
    QueryEntityType entityType;
public:
    /**
     * @brief The constructor of Ref
     */
    explicit Ref();

    /**
     * @brief The getter of the string representation of the Ref
     * @return The StringRep of the Ref
     */
    StringRep getRep() const;

    std::string getAttrName() const;

    /**
     * @brief The getter of the RefType of the Ref
     * @return The RefType of the Ref
     */
    RefType getType() const;

    /**
     * @brief The getter of the RoofType of the Ref
     * @param The RootType of the Ref
     */
    RootType getRootType() const;

    /**
     * @brief The getter of the QueryEntityType of the Ref
     * @param The QueryEntityType of the Ref
     */
    QueryEntityType getEntityType() const;

    /**
     * @brief The setter of the string representation of the Ref
     * @param rrep The StringRep reference
     */
    void setRep(StringRep& rrep);

    void setAttrName(std::string name);

    /**
     * @brief The setter of the RefType of the Ref
     * @param rrefType The RefType reference
     */
    void setType(RefType& rrefType);

    /**
     * @brief The setter of the RootType of the Ref
     * @param rrootType The RootType reference
     */
    void setRootType(RootType& rrootType);

    /**
     * @brief The setter of the QueryEntityType of the Ref
     * @param eentityType The QueryEntityType reference
     */
    void setEntityType(QueryEntityType& eentityType);

    /**
     * @brief Checks if the RootType of the Ref is rrootType
     * @param rrootType The RootType to compare with
     * @return Returns true if the rootType is rrootType, otherwise false
     */
    bool isRootType(RootType rrootType);

    /**
     * Checks if the rootType of the Ref is of stmtRef
     * @return Returns true if the rootType is of stmtRef, otherwise false
     */
    bool isOfStmtRef();

    /**
     * Checks if the rootType of the Ref is of entRef
     * @return Returns true if the rootType is of entRef, otherwise false
     */
    bool isOfEntRef();

    /**
     * Checks if the rootType of the Ref is of WithRef
     * @return Returns true if the rootType is of WithRef, otherwise false
     */
    bool isOfWithRef();

    /**
     * @brief Checks if this Ref is equal to other by comparing their rep, type, rootType and entityType
     * @param other query entity object
     * @return Returns true if this == other, otherwise false
     */
    bool operator==(const Ref& other) const;
};
