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
    Invalid,
};

/**
 * @brief The enum class of RootType
 */
enum class RootType {
    Integer, // StmtRef
    Wildcard, // StmtRef & EntRef
    Synonym, // StmtRef & EntRef
    Ident, // EntRef
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

    /*
     * @brief The getter of the string representation of the Ref
     * @return The StringRep of the Ref
     */
    StringRep getRep();

    /*
     * @brief The getter of the RefType of the Ref
     * @return The RefType of the Ref
     */
    RefType getType();

    /*
     * @brief The getter of the RoofType of the Ref
     * @param The RootType of the Ref
     */
    RootType getRootType();

    /*
     * @brief The getter of the QueryEntityType of the Ref
     * @param The QueryEntityType of the Ref
     */
    QueryEntityType getEntityType();

    /*
     * @brief The setter of the string representation of the Ref
     * @param rrep The StringRep reference
     */
    void setRep(StringRep& rrep);

    /*
     * @brief The setter of the RefType of the Ref
     * @param rrefType The RefType reference
     */
    void setType(RefType& rrefType);

    /*
     * @brief The setter of the RootType of the Ref
     * @param rrootType The RootType reference
     */
    void setRootType(RootType& rrootType);

    /*
     * @brief The setter of the QueryEntityType of the Ref
     * @param eentityType The QueryEntityType reference
     */
    void setEntityType(QueryEntityType& eentityType);

};
