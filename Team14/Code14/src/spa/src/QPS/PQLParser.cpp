#include "PQLParser.h"


#include <string>

PQLParser::PQLParser(const std::string& str) {
    this->tokenizer = std::make_shared<Tokenizer>(str);
}

Query PQLParser::parse(){
    Query query = Query();
    processDeclarations(query);
    processSelectClause(query);
    return query;
}

void PQLParser::processDeclarations(Query& query) {
    while(tokenizer->peekToken()->isDesignEntity()) {
        std::shared_ptr<Token> designEntity = tokenizer->popToken();
        EntityType currentType;
        if (designEntity->isToken("procedure")) {
            currentType = EntityType::PROCEDURE;
        } else if (designEntity->isToken("stmt")) {
            currentType = EntityType::STMT;
        } else if (designEntity->isToken("read")) {
            currentType = EntityType::READ;
        } else if (designEntity->isToken("print")) {
            currentType = EntityType::PRINT;
        } else if (designEntity->isToken("assign")) {
            currentType = EntityType::ASSIGN;
        } else if (designEntity->isToken("call")) {
            currentType = EntityType::CALL;
        } else if (designEntity->isToken("while")) {
            currentType = EntityType::WHILE;
        } else if (designEntity->isToken("if")) {
            currentType = EntityType::IF;
        } else if (designEntity->isToken("variable")) {
            currentType = EntityType::VARIABLE;
        } else if (designEntity->isToken("constant")) {
            currentType = EntityType::CONSTANT;
        }

        std::shared_ptr<Token> synonym = tokenizer->popToken();
        if (!synonym->isIdent()) {
            throw std::runtime_error("Invalid synonym ...");
        }
        std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(currentType, synonym->getRep());
        query.addDeclaration(newEntity);

        while(tokenizer->peekToken()->isToken(TokenType::COMMA)) {
            tokenizer->popToken(); //consume comma
            synonym = tokenizer->popToken();
            if (!synonym->isIdent()) {
                throw std::runtime_error("Invalid synonym ...");
            }
            newEntity = std::make_shared<Entity>(currentType, synonym->getRep());
            query.addDeclaration(newEntity);
        }

        // consume semicolon
        std::shared_ptr<Token> endToken = tokenizer->popToken();
        if (!endToken->isToken(TokenType::SEMICOLON)) {
            throw std::runtime_error("Expected ; token but found ...");
        }
    }

    // if no design entity return err
    if (!query.hasDeclarations()) {
        throw std::runtime_error("Expected a declaration but found none");
    }
}

void PQLParser::processSelectClause(Query& query) {
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isSelectToken()) {
        throw std::runtime_error("Expected Select clause but found ...");
    }
    next = tokenizer->popToken();

    std::shared_ptr<Entity> entity = query.getEntity(next->getRep());
    if (!entity) {
        throw std::runtime_error("Undeclared synonym in Select clause");
    }
    query.addSelect(entity);

    // TODO support for multiple synonyms
}

