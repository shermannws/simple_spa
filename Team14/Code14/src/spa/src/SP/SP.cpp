#include <iostream>

#include "SP.h"
#include "SPTokenizer.h"
#include "SPParser.h"
#include "SP/Validators/SyntacticValidator/SyntacticValidator.h"
#include "SP/Validators/SemanticValidator/SemanticValidator.h"
#include "SP/AST/Visitors/EntityExtractorVisitor.h"
#include "SP/AST/Visitors/FollowsExtractorVisitor.h"
#include "SP/AST/Visitors/UsesExtractorVisitor.h"
#include "SP/AST/Visitors/ModifiesExtractorVisitor.h"
#include "SP/AST/Visitors/ParentExtractorVisitor.h"
#include "SP/AST/Visitors/CallsExtractorVisitor.h"
#include "SP/AST/Traverser/Traverser.h"
#include "SP/Errors/SyntaxError.h"
#include "SP/Errors/SemanticError.h"

SP::SP(std::shared_ptr<PkbWriter> pkbWriter) : pkbWriter(pkbWriter) {}

void SP::startSPProcessing(std::string& input) {
    try {
        //Tokenize the string input
        SPTokenizer tokenizer = SPTokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        //Syntactic Validator takes in tokens
        SyntacticValidator syntacticValidator = SyntacticValidator(tokens);
        syntacticValidator.validate();

        //Parse the tokens
        SPParser parser = SPParser();
        std::shared_ptr<ProgramNode> root = parser.parse(tokens);

        //Semantically validate from the root node
        SemanticValidator semanticValidator;
        semanticValidator.validate(root);

        //Instantiate all visitors to be used
        std::shared_ptr<EntityExtractorVisitor> entityExtractor = std::make_shared<EntityExtractorVisitor>(pkbWriter);
        std::shared_ptr<FollowsExtractorVisitor> followsExtractor = std::make_shared<FollowsExtractorVisitor>(pkbWriter);
        std::shared_ptr<UsesExtractorVisitor> usesExtractor = std::make_shared<UsesExtractorVisitor>(pkbWriter);
        std::shared_ptr<ModifiesExtractorVisitor> modifiesExtractor = std::make_shared<ModifiesExtractorVisitor>(pkbWriter);
        std::shared_ptr<ParentExtractorVisitor> parentExtractor = std::make_shared<ParentExtractorVisitor>(pkbWriter);
        std::shared_ptr<CallsExtractorVisitor> callsExtractor = std::make_shared<CallsExtractorVisitor>(pkbWriter);
        std::vector<std::shared_ptr<DesignExtractorVisitor>> visitors = { entityExtractor, followsExtractor, usesExtractor, modifiesExtractor, parentExtractor, callsExtractor };

        //Traverse the AST from root node
        Traverser traverser = Traverser(visitors);
        traverser.traverse(root);
    } catch (const SyntaxError& e) {
        std::cout << "\n" << e.what() << "\n\n" << "Terminating program due to invalid SIMPLE code." << std::endl;
        std::exit(EXIT_FAILURE); // Exit the program with an error code
    } catch (const SemanticError& e) {
        std::cout << "\n" << e.what() << "\n\n" << "Terminating program due to invalid SIMPLE code." << std::endl;
        std::exit(EXIT_FAILURE); // Exit the program with an error code
    }
}