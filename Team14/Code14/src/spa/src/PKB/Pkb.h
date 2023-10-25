#pragma once

#include <memory>

#include "PKB/Managers/AssignPatternManager.h"
#include "PKB/Managers/CFGManager.h"
#include "PKB/Managers/CallsRelationshipManager.h"
#include "PKB/Managers/EntitiesManager.h"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Managers/IfPatternManager.h"
#include "PKB/Managers/ModifiesProcRelationshipManager.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/NextRelationshipManager.h"
#include "PKB/Managers/ParentRelationshipManager.h"
#include "PKB/Managers/PkbReaderManager.h"
#include "PKB/Managers/PkbWriterManager.h"
#include "PKB/Managers/UsesProcRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/Managers/WhilePatternManager.h"
#include "PKB/Managers/AffectsRelationshipManager.h"
#include "PKB/PkbReader.h"
#include "PKB/PkbWriter.h"

/**
 * @brief The main class of the PKB
 * @details The main class of the PKB
 */
class Pkb {
private:
    /**
     * @brief The AssignPatternManager of the PKB
     */
    std::shared_ptr<AssignPatternManager> assignmentManager;

    /**
     * @brief The EntitiesManager of the PKB
     */
    std::shared_ptr<EntitiesManager> entitiesManager;

    /**
     * @brief The FollowsRelationshipManager of the PKB
     */
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager;

    /**
     * @brief The FollowsRelationshipManager of the PKB
     */
    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager;

    /**
     * @brief The ModifiesRelationshipManager of the PKB
     */
    std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager;

    /**
     * @brief The ParentRelationshipManager of the PKB
     */
    std::shared_ptr<ParentRelationshipManager> parentRelationshipManager;

    /**
     * @brief The CallsRelationshipManager of the PKB
     */
    std::shared_ptr<CallsRelationshipManager> callsRelationshipManager;

    /**
     * @brief The ModifiesProcRelationshipManager of the PKB
     */
    std::shared_ptr<ModifiesProcRelationshipManager> modifiesProcRelationshipManager;

    /**
     * @brief The UsesProcRelationshipManager of the PKB
     */
    std::shared_ptr<UsesProcRelationshipManager> usesProcRelationshipManager;

    /**
     * @brief The IfPatternManager of the PKB
     */
    std::shared_ptr<IfPatternManager> ifPatternManager;

    /**
     * @brief The WhilePatternManager of the PKB
     */
    std::shared_ptr<WhilePatternManager> whilePatternManager;

    /**
     * @brief The PkbReaderManager of the PKB
     */
    std::shared_ptr<PkbReaderManager> pkbReaderManager;

    /**
     * @brief The PkbWriterManager of the PKB
     */
    std::shared_ptr<PkbWriterManager> pkbWriterManager;

    /**
     * @brief The NextRelationshipManager of the PKB
     */
    std::shared_ptr<NextRelationshipManager> nextRelationshipManager;

    /**
     * @brief The CFGManager of the PKB
     */
    std::shared_ptr<CFGManager> cfgManager;

    /**
     * @brief The AffectsManager of the PKB
     */
    std::shared_ptr<AffectsRelationshipManager> affectsRelationshipManager;

public:
    /**
     * @brief Construct a new Pkb object
     * @return A new Pkb object
     */
    Pkb();

    /**
     * @brief Create a PkbReader object
     * @return A PkbReader object
     */
    std::shared_ptr<PkbReader> createPkbReader();

    /**
     * @brief Create a PkbWriter object
     * @return A PkbWriter object
     */
    std::shared_ptr<PkbWriter> createPkbWriter();
};