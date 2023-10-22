#include <iostream>
#include <utility>

#include "SP.h"
#include "SP/AST/Traverser/Traverser.h"
#include "SP/AST/Visitors/CallsExtractorVisitor.h"
#include "SP/AST/Visitors/EntityExtractorVisitor.h"
#include "SP/AST/Visitors/FollowsExtractorVisitor.h"
#include "SP/AST/Visitors/ModifiesExtractorVisitor.h"
#include "SP/AST/Visitors/ParentExtractorVisitor.h"
#include "SP/AST/Visitors/PatternExtractorVisitor.h"
#include "SP/AST/Visitors/UsesExtractorVisitor.h"
#include "SP/CFG/CFGBuilder.h"
#include "SP/CFG/CFGExtractor.h"
#include "SP/Errors/SemanticError.h"
#include "SP/Errors/SyntaxError.h"
#include "SP/Validators/SemanticValidator/SemanticValidator.h"
#include "SP/Validators/SyntacticValidator/SyntacticValidator.h"
#include "SPParser.h"
#include "SPTokenizer.h"

SP::SP(std::shared_ptr<PkbWriter> pkbWriter) : pkbWriter(std::move(pkbWriter)) {}

void SP::startSPProcessing(std::string &input) {
    try {
        // Tokenize the string input
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        // Syntactic Validator takes in tokens
        SyntacticValidator syntacticValidator(tokens);
        syntacticValidator.validate();

        // Parse the tokens
        SPParser parser;
        std::shared_ptr<ProgramNode> root = parser.parse(tokens);

        // Semantically validate from the root node
        SemanticValidator semanticValidator;
        semanticValidator.validate(root);

        // Instantiate all visitors to be used
        std::shared_ptr<EntityExtractorVisitor> entityExtractor = std::make_shared<EntityExtractorVisitor>(pkbWriter);
        std::shared_ptr<FollowsExtractorVisitor> followsExtractor =
                std::make_shared<FollowsExtractorVisitor>(pkbWriter);
        std::shared_ptr<UsesExtractorVisitor> usesExtractor = std::make_shared<UsesExtractorVisitor>(pkbWriter);
        std::shared_ptr<ModifiesExtractorVisitor> modifiesExtractor =
                std::make_shared<ModifiesExtractorVisitor>(pkbWriter);
        std::shared_ptr<ParentExtractorVisitor> parentExtractor = std::make_shared<ParentExtractorVisitor>(pkbWriter);
        std::shared_ptr<CallsExtractorVisitor> callsExtractor = std::make_shared<CallsExtractorVisitor>(pkbWriter);
        std::shared_ptr<PatternExtractorVisitor> patternExtractor =
                std::make_shared<PatternExtractorVisitor>(pkbWriter);
        std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors = {
                entityExtractor, followsExtractor, usesExtractor,   modifiesExtractor,
                parentExtractor, callsExtractor,   patternExtractor};

        // Traverse the AST from root node
        Traverser traverser(visitors);
        traverser.traverse(root);

        // Trigger PKB to do transitivity calculations
        pkbWriter->triggerTransitiveCalc();

        // Build CFGs
        auto cfgMap = CFGBuilder::buildAllCFG(root);

        // Handle CFG-related relationships and save CFG to PKB
        CFGExtractor cfgExtractor(pkbWriter);
        cfgExtractor.extractRelationships(cfgMap);
    } catch (const SyntaxError &e) {
        std::cout << "\n"
                  << e.what() << "\n\n"
                  << "Terminating program due to invalid SIMPLE code." << std::endl;
        std::exit(EXIT_FAILURE);// Exit the program with an error code
    } catch (const SemanticError &e) {
        std::cout << "\n"
                  << e.what() << "\n\n"
                  << "Terminating program due to invalid SIMPLE code." << std::endl;
        std::exit(EXIT_FAILURE);// Exit the program with an error code
    }
}