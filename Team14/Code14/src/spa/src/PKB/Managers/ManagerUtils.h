#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Commons/Entities/Entity.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "PKB/Commons/ClauseGroup.h"
#include "PKB/EntityStores/EntityStore.h"
#include "PKB/PatternStore/IfPatternStore.h"
#include "PKB/PatternStore/WhilePatternStore.h"
#include "PKB/RelationshipStores/RelationshipStore.h"

/**
 * @brief A class that contains utility functions for the Managers
 * @details A class that contains utility functions for the Managers
 */
class ManagerUtils {
private:
    /**
     * @brief A function that retrieves objects from a set-based store based on a matcher and getter function
     * @tparam E The type of the object to be retrieved
     * @tparam S The type of the store to be retrieved from
     * @tparam R The type of the object stored in the store
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the object matches the criteria
     * @param getter The getter function that returns the object
     * @return An unordered_set of entities
     */
    template<typename E, typename S, typename R>
    static std::unordered_set<E> getFromSetStore(std::shared_ptr<S> store,
                                                 std::function<bool(std::shared_ptr<R>)> matcher,
                                                 std::function<E(std::shared_ptr<R>)> getter);

    /**
     * @brief A function that retrieves objects from a map-based store based on a matcher and getter function
     * @tparam E The type of set-based store used to store the values in the map
     * @tparam S The type of the store to be retrieved from
     * @tparam K The type of the left object stored in the store
     * @tparam V The type of the right object stored in the store
     * @tparam R The type of the object to be retrieved
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the object matches the criteria
     * @param getter The getter function that returns the object
     * @return An unordered_set of entities
     */
    template<typename E, typename S, typename K, typename V, typename R>
    static std::unordered_set<std::shared_ptr<R>>
    getFromMapStore(S &store, std::function<std::shared_ptr<E>(S &, K &)> getter, K &key,
                    std::function<bool(std::shared_ptr<V>)> matcher);


    /**
     * @brief A function that retrieves keys from a map-based store based on a matcher function
     * @tparam K The type of the left object stored in the store
     * @tparam V The type of the right object stored in the store
     * @tparam R The type of the object to be retrieved
     * @param beginItr The iterator pointing to the beginning of the map
     * @param endItr The iterator pointing to the end of the map
     * @param matcher The matcher function that returns a boolean value indicating if the object matches the criteria
     * @return An unordered_set of keys from the map
     */
    template<typename K, typename V, typename R>
    static std::unordered_set<std::shared_ptr<R>>
    getKeys(typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<EntityStore<V>>>::iterator beginItr,
            typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<EntityStore<V>>>::iterator endItr,
            std::function<bool(std::shared_ptr<K>)> matcher);

    /**
     * @brief A function that retrieves keys from a map-based store when no matcher function is required
     * @tparam K The type of the left object stored in the store
     * @tparam V The type of the right object stored in the store
     * @param beginItr The iterator pointing to the beginning of the map
     * @param endItr The iterator pointing to the end of the map
     * @return An unordered_set of keys from the map
     */
    template<typename K, typename V>
    static EntitySet
    getKeysNoMatch(typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<EntityStore<V>>>::iterator beginItr,
                   typename std::unordered_map<std::shared_ptr<K>, std::shared_ptr<EntityStore<V>>>::iterator endItr);

    /**
     * @brief A function that retrieves keys from a map-based store when a matcher function for statement type is
     * required
     * @tparam V The type of the right object stored in the store
     * @param beginItr The iterator pointing to the beginning of the map
     * @param endItr The iterator pointing to the end of the map
     * @param type The type of the statement to be retrieved from the keys
     * @return An unordered_set of keys from the map that matches the statement type
     */
    template<typename V>
    static EntitySet getKeysStmtMatch(
            typename std::unordered_map<std::shared_ptr<Statement>, std::shared_ptr<EntityStore<V>>>::iterator beginItr,
            typename std::unordered_map<std::shared_ptr<Statement>, std::shared_ptr<EntityStore<V>>>::iterator endItr,
            StatementType type);

public:
    /**
     * @brief A map that stores the allowed statement types for each clause group
     */
    static std::unordered_map<ClauseGroup, std::unordered_set<StatementType>> allowedStmtTypesMap;

    /**
     * @brief A function that checks if the statement type is allowed for the clause group
     * @param clauseGroup The clause group to be checked
     * @param stmtType The statement type to be checked
     * @return True if the statement type is allowed for the clause group, false otherwise
     */
    static bool isStmtTypeAllowed(ClauseGroup clauseGroup, StatementType stmtType);

    /**
     * @brief A function that retrieves entities from a set-based store based on a matcher and getter function
     * @tparam S The type of the store to be retrieved from
     * @tparam R The type of the object stored in the store
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the object matches the criteria
     * @param getter The getter function that returns the entity
     * @return An unordered_set of entities
     */
    template<typename S, typename R>
    static EntitySet getEntitiesFromStore(std::shared_ptr<S> store, std::function<bool(std::shared_ptr<R>)> matcher,
                                          std::function<EntityPointer(std::shared_ptr<R>)> getter);

    /**
     * @brief A function that retrieves entities from an set-based entity store based on a matcher and getter function
     * @tparam E The type of the entity to be retrieved
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the entity matches the criteria
     * @param getter The getter function that returns the entity
     * @return An unordered_set of entities
     */
    template<typename E>
    static EntitySet getEntitiesFromEntityStore(std::shared_ptr<EntityStore<E>> store,
                                                std::function<bool(std::shared_ptr<E>)> matcher,
                                                std::function<EntityPointer(std::shared_ptr<E>)> getter);


    /**
     * @brief A function that retrieves entity pairs from a set-based store based on a matcher and getter function
     * @tparam S The type of store to be retrieved from
     * @tparam R The type of the object stored in the store
     * @param store The store to be retrieved from
     * @param matcher The matcher function that returns a boolean value indicating if the object matches the criteria
     * @param getter The getter function that returns the entity pair
     * @return An unordered_set of entity pairs
     */
    template<typename S, typename R>
    static EntityPairSet getEntityPairsFromStore(std::shared_ptr<S> store,
                                                 std::function<bool(std::shared_ptr<R>)> matcher,
                                                 std::function<std::vector<EntityPointer>(std::shared_ptr<R>)> getter);

    /**
     * @brief A function that retrieves right entities based on a left key when no matcher function is required
     * @tparam L The type of the left object stored in the store
     * @tparam R The type of the right object stored in the store
     * @param store The store to be retrieved from
     * @param key The left key to be used to retrieve the right entities
     * @return An unordered_set of right entities
     */
    template<typename L, typename R>
    static EntitySet getRightEntitiesFromLeftKeyNoMatch(RelationshipStore<L, R> &store, L &key);

    /**
     * @brief A function that retrieves left entities based on a right key when no matcher function is required
     * @tparam L The type of the left object stored in the store
     * @tparam R The type of the right object stored in the store
     * @param store The store to be retrieved from
     * @param key The right key to be used to retrieve the left entities
     * @return An unordered_set of left entities
     */
    template<typename L, typename R>
    static EntitySet getLeftEntitiesFromRightKeyNoMatch(RelationshipStore<L, R> &store, R &key);

    /**
     * @brief A function that retrieves left entities based on a right key when no matcher function is required
     * @param store The store to be retrieved from
     * @param key The right key to be used to retrieve the left entities
     * @return An unordered_set of left entities
     */
    static EntitySet getLeftEntitiesFromRightKeyNoMatch(ConditionPatternStore &store, Variable &key);

    /**
     * @brief A function that retrieves right entities based on a left key when a matcher function for statement type is
     * required
     * @tparam L The type of the left object stored in the store
     * @param store The store to be retrieved from
     * @param key The left key to be used to retrieve the right entities
     * @param type The type of the statement to be retrieved from the right entities
     * @return An unordered_set of right entities that matches the statement type
     */
    template<typename L>
    static EntitySet getRightEntitiesFromLeftKeyStmtMatch(RelationshipStore<L, Statement> &store, L &key,
                                                          StatementType type);

    /**
     * @brief A function that retrieves left entities based on a right key when a matcher function for statement type is
     * required
     * @tparam R The type of the right object stored in the store
     * @param store The store to be retrieved from
     * @param key The right key to be used to retrieve the left entities
     * @param type The type of the statement to be retrieved from the left entities
     * @return An unordered_set of left entities that matches the statement type
     */
    template<typename R>
    static EntitySet getLeftEntitiesFromRightKeyStmtMatch(RelationshipStore<Statement, R> &store, R &key,
                                                          StatementType type);

    /**
     * @brief A function that checks if the map-based store contains the key-value pair
     * @tparam L The type of the left object stored in the store
     * @tparam R The type of the right object stored in the store
     * @param store The store to be checked
     * @param key The left key to be checked
     * @param value The right value to be checked
     * @return True if the map-based store contains the key-value pair, false otherwise
     */
    template<typename L, typename R>
    static bool mapContains(RelationshipStore<L, R> &store, L &key, R &value);

    /**
     * @brief A function that retrieves left keys from a double map-based store when no matcher function is required
     * @tparam K The type of the left object stored in the store
     * @tparam V The type of the right object stored in the store
     * @param store The store to be retrieved from
     * @return An unordered_set of left keys from the map
     */
    template<typename K, typename V>
    static EntitySet getLeftKeysNoMatch(RelationshipStore<K, V> &store);

    /**
     * @brief A function that retrieves right keys from a double map-based store when no matcher function is required
     * @tparam K The type of the left object stored in the store
     * @tparam V The type of the right object stored in the store
     * @param store The store to be retrieved from
     * @return An unordered_set of right keys from the map
     */
    template<typename K, typename V>
    static EntitySet getRightKeysNoMatch(RelationshipStore<K, V> &store);

    /**
     * @brief A function that retrieves left keys from a double map-based store when no matcher function is required
     * @param store The store to be retrieved from
     * @return An unordered_set of left keys from the map
     */
    static EntitySet getLeftKeysNoMatch(ConditionPatternStore &store);

    /**
     * @brief A function that retrieves left keys from a double map-based store when a matcher function for statement
     * type is required
     * @tparam V The type of the right object stored in the store
     * @param store The store to be retrieved from
     * @param type The type of the statement to be retrieved from the keys
     * @return An unordered_set of left keys from the map that matches the statement type
     */
    template<typename V>
    static EntitySet getLeftKeysStmtMatch(RelationshipStore<Statement, V> &store, StatementType type);

    /**
     * @brief A function that retrieves right keys from a double map-based store when a matcher function for statement
     * type is required
     * @tparam V The type of the right object stored in the store
     * @param store The store to be retrieved from
     * @param type The type of the statement to be retrieved from the keys
     * @return An unordered_set of right keys from the map that matches the statement type
     */
    template<typename K>
    static EntitySet getRightKeysStmtMatch(RelationshipStore<K, Statement> &store, StatementType type);

    /**
     * @brief A function that retrieves key-value pairs from a map-based store
     * @tparam R The type of object to be returned
     * @tparam S The type of the store to be retrieved from
     * @tparam K The type of the left object stored in the store
     * @tparam V The type of the right object stored in the store
     * @param store The store to be retrieved from
     * @param leftMatcher The matcher function that returns a boolean value indicating if the left object matches the
     * criteria
     * @param rightMatcher The matcher function that returns a boolean value indicating if the right object matches the
     * criteria
     * @return An unordered_set of key-value pairs from the map
     */
    template<typename R, typename S, typename K, typename V>
    static std::unordered_set<std::vector<std::shared_ptr<R>>>
    getPairs(S &store, std::function<bool(std::shared_ptr<K>)> leftMatcher,
             std::function<bool(std::shared_ptr<V>)> rightMatcher);

    /**
     * @brief A function that adds to stmtVarManager (s,v) given the the (s,p) pairs in procStmtStore such that (p,v) is
     * in procVarManager
     * @tparam S The type of the statement variable manager
     * @tparam P The type of the procedure variable manager
     */
    template<typename S, typename P>
    static void addStmtVarFromProcVar(std::shared_ptr<S> stmtVarManager,
                                      std::shared_ptr<RelationshipStore<Procedure, Statement>> procStmtStore,
                                      std::shared_ptr<P> procVarManager);


    /**
     * @brief A function that retrieves left keys from a double map-based store when a matcher function for statement
     * type is required and the left key also appears on the right of the store
     * @tparam K The type of the left and right object stored in the store
     * @param store The store to be retrieved from
     * @param type The type of the statement to be retrieved from the left keys
     * @return An unordered_set of left keys from the map that matches the statement type and also appears on the rhs of
     * the map
     */
    template<typename K>
    static EntitySet getLeftKeysMatchRight(RelationshipStore<K, K> &store,
                                           std::function<bool(std::shared_ptr<K>)> leftMatcher);

    /**
     * @brief A function that helps calculate the transitive closure of a relationship
     * @tparam S The type of the store to be retrieved from
     * @tparam T The type of the object stored in the store
     * @param relationshipStore The store that stores the direct relationships
     * @param starRelationshipStore The store that stores the transitive closure of the indirect relationships
     */
    template<typename S, typename T>
    static void calculateTransitivity(std::shared_ptr<S> relationshipStore, std::shared_ptr<S> starRelationshipStore);
};