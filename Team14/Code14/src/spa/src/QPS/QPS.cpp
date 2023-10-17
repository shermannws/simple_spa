#include "QPS.h"

#include "Exceptions/SemanticException.h"
#include "Exceptions/SyntaxException.h"
#include "QPS/Evaluators/PQLEvaluator.h"
#include "QPS/Parsers/PQLParser.h"
#include <utility>

QPS::QPS(std::shared_ptr<PkbReader> pkbReader) : pkbReader(std::move(pkbReader)) {}

void QPS::evaluate(std::string &query, std::list<std::string> &results) {
    try {
        PQLParser parser(query);
        Query queryObj = parser.parse();
        PQLEvaluator evaluator = PQLEvaluator(pkbReader);
        Result resultObj = evaluator.evaluate(queryObj);
        results = evaluator.formatResult(queryObj, resultObj);
    } catch (SyntaxException &e) { results.emplace_back("SyntaxError"); } catch (SemanticException &e) {
        results.emplace_back("SemanticError");
    }
}