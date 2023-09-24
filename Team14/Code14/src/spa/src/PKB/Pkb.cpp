#include "Pkb.h"
#include "PKB/PkbConcreteReader.h"
#include "PKB/PkbConcreteWriter.h"

Pkb::Pkb() {
    this->assignmentManager = std::make_shared<AssignmentManager>(AssignmentManager());
    this->entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
    this->followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    this->usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    this->modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
    this->parentRelationshipManager = std::make_shared<ParentRelationshipManager>();


    this->pkbReaderManager = std::make_shared<PkbReaderManager>(
            PkbReaderManager(
                    this->assignmentManager,
                    this->entitiesManager,
                    this->followsRelationshipManager,
                    this->usesRelationshipManager,
                    this->modifiesRelationshipManager,
                    this->parentRelationshipManager
            )
    );
    this->pkbWriterManager = std::make_shared<PkbWriterManager>(
            PkbWriterManager(
                    this->assignmentManager,
                    this->entitiesManager,
                    this->followsRelationshipManager,
                    this->usesRelationshipManager,
                    this->modifiesRelationshipManager,
                    this->parentRelationshipManager
            )
    );
};

std::shared_ptr<PkbReader> Pkb::createPkbReader() {
    return std::make_shared<PkbConcreteReader>(this->pkbReaderManager);
};

std::shared_ptr<PkbWriter> Pkb::createPkbWriter() {
    return std::make_shared<PkbConcreteWriter>(this->pkbWriterManager);
};