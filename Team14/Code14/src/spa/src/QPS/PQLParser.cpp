
#include <string>
#include <stdexcept>

#include "PQLParser.h"
#include "Tokenizer.h"
#include "SuchThatClause.h"
#include "QPS/SemanticValHandler/SynonymHandler.h"
#include "QPS/SemanticValHandler/StmtrefStmtrefHandler.h"
#include "QPS/SemanticValHandler/StmtrefEntrefHandler.h"
#include "QPSUtil.h"


PQLParser::PQLParser(const std::string& str) : tokenizer(std::make_shared<Tokenizer>(str)){}

Query PQLParser::parse(){
    Query query = Query();
    processDeclarations(query);
    processSelectClause(query);
    processSuchThatClause(query);
    processPatternClause(query);

    expect(tokenizer->peekToken()->isToken(TokenType::Empty), "Invalid query syntax");
    return query;
}

void PQLParser::processDeclarations(Query& query) {
    while(tokenizer->peekToken()->isDesignEntity()) {
        std::shared_ptr<Token> designEntity = tokenizer->popToken();
        QueryEntityType currentType;
        if (designEntity->isToken("procedure")) {
            currentType = QueryEntityType::Procedure;
        } else if (designEntity->isToken("stmt")) {
            currentType = QueryEntityType::Stmt;
        } else if (designEntity->isToken("read")) {
            currentType = QueryEntityType::Read;
        } else if (designEntity->isToken("print")) {
            currentType = QueryEntityType::Print;
        } else if (designEntity->isToken("assign")) {
            currentType = QueryEntityType::Assign;
        } else if (designEntity->isToken("call")) {
            currentType = QueryEntityType::Call;
        } else if (designEntity->isToken("while")) {
            currentType = QueryEntityType::While;
        } else if (designEntity->isToken("if")) {
            currentType = QueryEntityType::If;
        } else if (designEntity->isToken("variable")) {
            currentType = QueryEntityType::Variable;
        } else if (designEntity->isToken("constant")) {
            currentType = QueryEntityType::Constant;
        }

        std::shared_ptr<Token> synonym = tokenizer->popToken();
        if (!synonym->isIdent()) {
            if (synonym->isToken(TokenType::Empty)) {
                throw std::runtime_error("Expected synonym but found none");
            }
            throw std::runtime_error("Invalid synonym '" + synonym->getRep() + "'");
        }
        std::shared_ptr<QueryEntity> newEntity = std::make_shared<QueryEntity>(currentType, synonym->getRep());
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
            newEntity = std::make_shared<QueryEntity>(currentType, synonym->getRep());
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

    std::shared_ptr<QueryEntity> entity = query.getEntity(next->getRep());
    if (!entity) {
        throw std::runtime_error("Undeclared synonym in Select clause");
    }
    query.addSelect(entity);

    // TODO support for multiple synonyms
}

void PQLParser::processSuchThatClause(Query& query) {
    // handle optional
    std::shared_ptr<Token> suchThatToken = tokenizer->peekToken();
    try {
        expect(suchThatToken->isToken("such that"), "No such that");
    } catch (...) {
        return;
    }
    std::shared_ptr<Token> absToken = tokenizer->popToken();
    std::shared_ptr<SuchThatClause> clause = std::make_shared<SuchThatClause>(absToken);
    validateSuchThatSyntax(clause);
    validateSuchThatSemantics(query, clause);
    query.addSuchThat(clause);
}

void PQLParser::validateSuchThatSyntax(const std::shared_ptr<SuchThatClause>& clause) {
    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw std::runtime_error("No left parenthesis");
    }

    Ref leftRef = extractRef();
    clause->setFirstParam(leftRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) {
        throw std::runtime_error("No comma");
    }

    Ref rightRef = extractRef();
    clause->setSecondParam(rightRef);

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Rparenthesis)) {
        throw std::runtime_error("No right parenthesis");
    }

    validateSuchThatRefType(clause);
}

void PQLParser::validateSuchThatRefType(const std::shared_ptr<SuchThatClause>& clause) {
    ClauseType type = clause->getType();
    Ref& leftRef = clause->getFirstParam();
    Ref& rightRef = clause->getSecondParam();
    RootType leftRootType = leftRef.getRootType();
    RootType rightRootType = rightRef.getRootType();

    switch (type) {
    case ClauseType::Uses:
    case ClauseType::Modifies:
        // check right
        if (!QPSUtil::isRootOfEntref(rightRootType)) {
            throw std::runtime_error("Invalid RHS, entRef expected");
        }
        break;
    case ClauseType::Follows:
    case ClauseType::FollowsStar:
    case ClauseType::Parent:
    case ClauseType::ParentStar:
        // check left
        if (!QPSUtil::isRootOfStmtref(leftRootType)) {
            throw std::runtime_error("Invalid LHS, stmtRef expected");
        }
        // check right
        if (!QPSUtil::isRootOfStmtref(rightRootType)) {
            throw std::runtime_error("Invalid RHS, stmtRef expected");
        }
        break;
    default:
        throw std::runtime_error("Invalid ClauseType in Such That Clause");
    }
}

// TODO: generalise this to cater both such that & pattern clauses
void PQLParser::validateSuchThatSemantics(Query& query, const std::shared_ptr<SuchThatClause>& clause) {
    std::shared_ptr<SynonymHandler> synonymHandler = std::make_shared<SynonymHandler>();
    std::shared_ptr<StmtrefStmtrefHandler> stmtrefHandler = std::make_shared<StmtrefStmtrefHandler>();
    std::shared_ptr<StmtrefEntrefHandler> stmtEntHandler = std::make_shared<StmtrefEntrefHandler>();
    synonymHandler->setNext(stmtrefHandler)->setNext(stmtEntHandler);
    synonymHandler->handle(query, clause);
}

void PQLParser::processPatternClause(Query& query) {
    std::shared_ptr<Token> patternToken = tokenizer->peekToken();
    try {
        expect(patternToken->isToken("pattern"), "No pattern");
    } catch (...) {
        return;
    }

    std::shared_ptr<Token> patternSyn = tokenizer->popToken();
    std::shared_ptr<QueryEntity> entity = query.getEntity(patternSyn->getRep());
    if (!entity) {
        throw std::runtime_error("Undeclared synonym in pattern clause");
    } else if (entity->getType() != QueryEntityType::Assign) {
        throw std::runtime_error("Unsupported pattern clause, expected an assignment");
    }

    std::shared_ptr<Token> next = tokenizer->popToken();
    if (!next->isToken(TokenType::Lparenthesis)) {
        throw std::runtime_error("Expected Lparenthesis");
    }

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Underscore)) {
        throw std::runtime_error("Expected wildcard as first arg");
    }

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Comma)) {
        throw std::runtime_error("Expected comma ");
    }

    next = tokenizer->popToken();
    if (!next->isToken(TokenType::Underscore)) {
        throw std::runtime_error("Expected wildcard as second arg");
    }

    Ref wildcard;
    std::string rep = next->getRep();
    RefType ent = RefType::EntRef;
    RootType root = RootType::Wildcard;
    wildcard.setRep(rep);
    wildcard.setRootType(root);
    wildcard.setType(ent);

    next = tokenizer->popToken();
    expect(next->isToken(TokenType::Rparenthesis), "Expected right parenthesis");

    std::shared_ptr<PatternClause> clause = std::make_shared<PatternClause>();
    clause->setType(ClauseType::Assign);
    clause->setEntity(entity);
    clause->setFirstParam(wildcard);
    clause->setSecondParam(wildcard);
    query.addPattern(clause);
}

Ref PQLParser::extractRef() {
    Ref ref;
    RootType rootType;
    std::string refString;
    std::shared_ptr<Token> curr = tokenizer->peekToken();
    if (curr->isInteger()) { // INTEGER
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Integer;
    } else if (curr->isToken(TokenType::Quote)) { // IDENTITY
        tokenizer->popToken();
        std::shared_ptr<Token> syn = tokenizer->peekToken();
        expect(syn->isIdent(), "Identity invalid");
        std::string right_quote = tokenizer->peekToken()->getRep();
        expect(tokenizer->peekToken()->isToken(TokenType::Quote), "No right quote");

        refString = syn->getRep();
        rootType = RootType::Ident;
    } else if (curr->isToken(TokenType::Underscore)) { // WILDCARD
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Wildcard;
    } else if (curr->isToken(TokenType::Word) && curr->isIdent()) { // SYNONYM
        refString = tokenizer->popToken()->getRep();
        rootType = RootType::Synonym;
    } else {
        throw std::runtime_error("Invalid stmtRef");
    }

    ref.setRep(refString);
    ref.setRootType(rootType);
    return ref;
}

std::shared_ptr<Token> PQLParser::expect(bool isToken, const std::string& errorMsg) {
    if (!isToken) {
        throw std::runtime_error(errorMsg);
    }
    return tokenizer->popToken();
}
