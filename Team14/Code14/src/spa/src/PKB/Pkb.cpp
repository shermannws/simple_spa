#include "Pkb.h"
#include "PKB/PkbConcreteReader.h"
#include "PKB/PkbConcreteWriter.h"

Pkb::Pkb() {
    this->assignmentManager = std::make_shared<AssignPatternManager>(AssignPatternManager());
    this->entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
    this->followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    this->usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    this->modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
    this->parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
    this->callsRelationshipManager = std::make_shared<CallsRelationshipManager>();
    this->modifiesProcRelationshipManager = std::make_shared<ModifiesProcRelationshipManager>();
    this->usesProcRelationshipManager = std::make_shared<UsesProcRelationshipManager>();
    this->ifPatternManager = std::make_shared<IfPatternManager>();
    this->whilePatternManager = std::make_shared<WhilePatternManager>();
    this->nextRelationshipManager = std::make_shared<NextRelationshipManager>();

    this->pkbReaderManager = std::make_shared<PkbReaderManager>(
            PkbReaderManager(
                    this->assignmentManager,
                    this->entitiesManager,
                    this->followsRelationshipManager,
                    this->usesRelationshipManager,
                    this->modifiesRelationshipManager,
                    this->parentRelationshipManager,
                    this->callsRelationshipManager,
                    this->modifiesProcRelationshipManager,
                    this->usesProcRelationshipManager,
                    this->ifPatternManager,
                    this->whilePatternManager,
                    this->nextRelationshipManager
            )
    );
    this->pkbWriterManager = std::make_shared<PkbWriterManager>(
            PkbWriterManager(
                    this->assignmentManager,
                    this->entitiesManager,
                    this->followsRelationshipManager,
                    this->usesRelationshipManager,
                    this->modifiesRelationshipManager,
                    this->parentRelationshipManager,
                    this->callsRelationshipManager,
                    this->modifiesProcRelationshipManager,
                    this->usesProcRelationshipManager,
                    this->ifPatternManager,
                    this->whilePatternManager,
                    this->nextRelationshipManager
            )
    );
};

std::shared_ptr<PkbReader> Pkb::createPkbReader() {
    return std::make_shared<PkbConcreteReader>(this->pkbReaderManager);
};

std::shared_ptr<PkbWriter> Pkb::createPkbWriter() {
    return std::make_shared<PkbConcreteWriter>(this->pkbWriterManager);
};