#include <string>
#include <stdexcept>

#include "PQLParser.h"

PQLParser::PQLParser(const std::string& str) : tokenizer(std::make_shared<Tokenizer>(str)){}

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
            currentType = EntityType::Procedure;
        } else if (designEntity->isToken("stmt")) {
            currentType = EntityType::Stmt;
        } else if (designEntity->isToken("read")) {
            currentType = EntityType::Read;
        } else if (designEntity->isToken("print")) {
            currentType = EntityType::Print;
        } else if (designEntity->isToken("assign")) {
            currentType = EntityType::Assign;
        } else if (designEntity->isToken("call")) {
            currentType = EntityType::Call;
        } else if (designEntity->isToken("while")) {
            currentType = EntityType::While;
        } else if (designEntity->isToken("if")) {
            currentType = EntityType::If;
        } else if (designEntity->isToken("variable")) {
            currentType = EntityType::Variable;
        } else if (designEntity->isToken("constant")) {
            currentType = EntityType::Constant;
        }

        std::shared_ptr<Token> synonym = tokenizer->popToken();
        if (!synonym->isIdent()) {
            if (synonym->isToken(TokenType::Empty)) {
                throw std::runtime_error("Expected synonym but found none");
            }
            throw std::runtime_error("Invalid synonym '" + synonym->getRep() + "'");
        }
        std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(currentType, synonym->getRep());
        query.addDeclaration(newEntity);

        while(tokenizer->peekToken()->isToken(TokenType::Comma)) {
            tokenizer->popToken(); //consume comma
            synonym = tokenizer->popToken();
            if (!synonym->isIdent()) {
                if (synonym->isToken(TokenType::Empty)) {
                    throw std::runtime_error("Expected synonym but found none");
                }
                throw std::runtime_error("Invalid synonym '" + synonym->getRep() + "'");
            }
            newEntity = std::make_shared<Entity>(currentType, synonym->getRep());
            query.addDeclaration(newEntity);
        }

        // consume semicolon
        std::shared_ptr<Token> endToken = tokenizer->popToken();
        if (!endToken->isToken(TokenType::Semicolon)) {
            throw std::runtime_error("Expected ; but found '" + endToken->getRep() + + "'");
        }
    }

    // if no design entity return err
    if (!query.hasDeclarations()) {
        throw std::runtime_error("Expected a declaration but found none");
    }
}

void PQLParser::processSelectClause(Query& query) {
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken("Select")) {
        throw std::runtime_error("Expected Select clause but found '" + next->getRep() + "'");
    }
    next = tokenizer->popToken();

    if (next->isToken(TokenType::Empty)) {
        throw std::runtime_error("Expected synonym but found none");
    }

    std::shared_ptr<Entity> entity = query.getEntity(next->getRep());
    if (!entity) {
        throw std::runtime_error("Undeclared synonym in Select clause");
    }
    query.addSelect(entity);

    // TODO support for multiple synonyms
}

