#include "QPS.h"

#include <utility>
#include "QPS/PQLParser.h"
#include "QPS/PQLEvaluator.h"
#include "Exception/SemanticException.h"
#include "Exception/SyntaxException.h"

void QPS::evaluate(std::shared_ptr<PkbReader> pkbReader, std::string& query, std::list<std::string>& results) {
    try {
        PQLParser parser(query);
        Query queryObj = parser.parse();
        PQLEvaluator evaluator = PQLEvaluator(std::move(pkbReader));
        Result resultObj = evaluator.evaluate(queryObj);
        results = evaluator.formatResult(queryObj, resultObj);
    } catch (SyntaxException& e) {
        results.emplace_back("SyntaxError");
    } catch (SemanticException& e) {
        results.emplace_back("SemanticError");
    }

}