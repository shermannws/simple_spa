#include "SPParser.h"

//SPParser::SPParser() {
//    statementToParserMap["assign"] = &parseAssignStatement;
//    statementToParserMap["read"];
//    statementToParserMap["print"];
//}

std::shared_ptr<ProgramNode> SPParser::parse(std::vector<SPToken> tokens) {
    std::deque<SPToken> tokensQueue(tokens.begin(), tokens.end());
    int runningStatementNumber = 1;
    std::shared_ptr<ProgramNode> programNode = std::make_shared<ProgramNode>();
    while (!tokensQueue.empty()) {
        programNode->procedures.push_back(parseProcedure(tokensQueue));
    }
    return programNode;
}

std::shared_ptr<ProcedureNode> SPParser::parseProcedure(std::deque<SPToken>& tokens) {
    assert(tokens.front().getValue() == "procedure" && tokens.front().getType() == TokenType::NAME);
    tokens.pop_front(); // consume "procedure" keyword

    assert(tokens.front().getType() == TokenType::NAME);
    std::shared_ptr<ProcedureNode> procedureNode = std::make_shared<ProcedureNode>();
    procedureNode->procedureName = tokens.front().getValue();
    tokens.pop_front();

    assert(tokens.front().getType() == TokenType::OPEN_CURLY_PARAN);
    tokens.pop_front(); // consume "{"
    procedureNode->statementList = parseStatementList(tokens);
    assert(tokens.front().getType() == TokenType::CLOSE_CURLY_PARAN);
    tokens.pop_front(); // consume "}"

    return procedureNode;
}

std::shared_ptr<StatementListNode> SPParser::parseStatementList(std::deque<SPToken>& tokens) {
    std::shared_ptr<StatementListNode> statementListNode = std::make_shared<StatementListNode>();
    assert(tokens.front().getType() == TokenType::NAME &&
           (tokens.front().getValue() == "assign" ||
           tokens.front().getValue() == "read" ||
           tokens.front().getValue() == "print"));
    while (tokens.front().getType() != TokenType::CLOSE_CURLY_PARAN) {
        if (tokens.front().getValue() == "assign") {
            statementListNode->statements.push_back(parseAssignStatement(tokens));
        } else if (tokens.front().getValue() == "read") {
            statementListNode->statements.push_back(parseReadStatement(tokens));
        } else if (tokens.front().getValue() == "print") {
            statementListNode->statements.push_back(parsePrintStatement(tokens));
        }
    }
    return statementListNode;
}

std::shared_ptr<AssignNode> SPParser::parseAssignStatement(std::deque<SPToken>& tokens) {

}

std::shared_ptr<ReadNode> SPParser::parseReadStatement(std::deque<SPToken>& tokens) {

}

std::shared_ptr<PrintNode> SPParser::parsePrintStatement(std::deque<SPToken>& tokens) {

}