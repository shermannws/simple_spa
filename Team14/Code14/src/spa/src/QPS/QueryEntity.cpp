#include "QueryEntity.h"

#include <string>

QueryEntity::QueryEntity(QueryEntityType type, const Synonym &synonym) : type(type), synonym(synonym) {}

QueryEntity::QueryEntity(const std::shared_ptr<Token>& designEntity, const std::string& synonym) : synonym(synonym) {
    if (designEntity->isToken("procedure")) {
        this->type = QueryEntityType::Procedure;
    } else if (designEntity->isToken("stmt")) {
        this->type = QueryEntityType::Stmt;
    } else if (designEntity->isToken("read")) {
        this->type = QueryEntityType::Read;
    } else if (designEntity->isToken("print")) {
        this->type = QueryEntityType::Print;
    } else if (designEntity->isToken("assign")) {
        this->type = QueryEntityType::Assign;
    } else if (designEntity->isToken("while")) {
        this->type = QueryEntityType::While;
    } else if (designEntity->isToken("if")) {
        this->type = QueryEntityType::If;
    } else if (designEntity->isToken("variable")) {
        this->type = QueryEntityType::Variable;
    } else if (designEntity->isToken("constant")) {
        this->type = QueryEntityType::Constant;
    } else if (designEntity->isToken("call")) {
        this->type = QueryEntityType::Call;
    } else {
        throw std::runtime_error("Invalid design entity");
    }
}

bool QueryEntity::operator==(const QueryEntity& other) const {
    return (type == other.type) && (synonym == other.synonym);
}

std::string QueryEntity::getSynonym() {
    return synonym;
}

QueryEntityType QueryEntity::getType() {
    return type;
}
