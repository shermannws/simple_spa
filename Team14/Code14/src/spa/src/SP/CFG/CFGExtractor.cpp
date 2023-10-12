#include <utility>

#include "CFGExtractor.h"

CFGExtractor::CFGExtractor(std::shared_ptr<PkbWriter> pkbWriter) : pkbWriter(std::move(pkbWriter)) {}

void CFGExtractor::extractRelationships(
        const std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> &cfgs) {
    saveCFGToPKB(cfgs);
    extractNextRelationships(cfgs);
}

void CFGExtractor::saveCFGToPKB(
        const std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> &cfgs) {
    // TODO: Call pkbWriter to save CFG
}

void CFGExtractor::extractNextRelationships(
        const std::unordered_map<ProcedureName, std::unordered_map<Statement, std::shared_ptr<CFGNode>>> &cfgs) {
    // TODO: Implement
}