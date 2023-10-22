#include "QueryEntity.h"
#include "QPSUtil.h"

#include <string>

QueryEntity::QueryEntity(QueryEntityType type, const Synonym &synonym) : type(type), synonym(synonym) {}

QueryEntity::QueryEntity(const std::shared_ptr<Token> &designEntity, const std::string &synonym) : synonym(synonym) {
    StringRep rep = designEntity->getRep();
    if (QPSUtil::designEntities.find(rep) == QPSUtil::designEntities.end()) {
        throw std::runtime_error("Invalid design entity");
    }
    this->type = QPSUtil::designEntities[rep];
}

bool QueryEntity::operator==(const QueryEntity &other) const {
    return (type == other.type) && (synonym == other.synonym);
}

std::string QueryEntity::getSynonym() { return synonym; }

QueryEntityType QueryEntity::getType() { return type; }
