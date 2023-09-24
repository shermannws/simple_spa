#include <string>

#include "catch.hpp"
#include "SP/SyntacticValidator.h"
#include "SP/SPTokenizer.h"

TEST_CASE("SyntacticValidator - Valid syntax") {

    SECTION("Single Read statement")  {
        std::string input = "procedure testProcedure {read num1;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Single Print statement")  {
        std::string input = "procedure testProcedure {print num1;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Two different statement")  {
        std::string input = "procedure testProcedure {read num1; print num2;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Single Assign statement")  {
        std::string input = "procedure testProcedure {x = 1;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Assign statement with expr")  {
        std::string input = "procedure testProcedure {x = 1 + 1;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Assign statement with complex expr")  {
        std::string input = "procedure testProcedure {x = a + b - 1 * d / 5 % f;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Assign statement with parentheses")  {
        std::string input = "procedure testProcedure {x = (1 + 1);}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Assign statement with parentheses 2")  {
        std::string input = "procedure testProcedure {x = (1 * 1) + 1;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Assign statement with nested parentheses")  {
        std::string input = "procedure testProcedure {x = (1 * (1)) + 1;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }
}

TEST_CASE("SyntacticValidator - Invalid syntax") {

    SECTION("Empty Procedure") {
        std::string input = "procedure testProcedure {}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(),
                            "Syntax error: StmtLst cannot be empty");
    }

    SECTION("Empty Procedure 2") {
        std::string input = "procedure testProcedure {}read num1;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(),
                            "Syntax error: StmtLst cannot be empty");
    }

    SECTION("No procedure terminal") {
        std::string input = "wrongProcedure test {}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(),
                            "Syntax error: Expected 'procedure'");
    }

    SECTION("Expecting next procedure") {
        std::string input = "procedure testProcedure {read num2;} read num1;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(),
                            "Syntax error: Expected 'procedure'");
    }

    SECTION("Invalid statement") {
        std::string input = "procedure testProcedure {num1}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(),
                            "Syntax error: Invalid Stmt");
    }

    SECTION("Invalid expr") {
        std::string input = "procedure testProcedure {x = ((1 * 1)) + (1;}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(),
                            "Syntax error: Expected TokenType CloseRoundParenthesis");
    }
}

TEST_CASE("SyntacticValidator - Valid IF syntax") {
    SECTION("basic if syntax")  {
        std::string input = "procedure testWhile {if (0 == 1) then { count = count + 1; } else { call readx ;}}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("longer if syntax")  {
        std::string input = "procedure testWhile {if (((x != 0) && (y != 0)) || (term > term2)) then { count = count + 1; } else { call readx ;}}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }
}

TEST_CASE("SyntacticValidator - Valid WHILE syntax RELATIONAL expr") {
    SECTION("single relational expr") {
        std::string input = "procedure testWhile {while (k > r) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("single relational expr with brackets") {
        std::string input = "procedure testWhile {while ( (k) < (r) ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("single relational expr with expr") {
        std::string input = "procedure testWhile {while ( k + 1 >= r - g ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("single relational expr with expr and brackets") {
        std::string input = "procedure testWhile {while ( (k * 1) <= (r / g) ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("single relational expr with LHS brackets") {
        std::string input = "procedure testWhile {while ( (A + B) + C > D) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("single relational expr with expr and nested brackets") {
        std::string input = "procedure testWhile {while ( ((k) % (1)) == (r / g) ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("single relational expr with expr and nested brackets  2") {
        std::string input = "procedure testWhile {while ( ((k - (a + b)) % (1)) != (r / g) ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }
}

TEST_CASE("SyntacticValidator - Invalid WHILE syntax RELATIONAL expr") {
    SECTION("Nested single relational expr") {
        std::string input = "procedure testWhile {while ((a > b)) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(), "Syntax error: Invalid nesting in conditional expression" );
    }

    SECTION("Invalid nesting on RHS") {
        std::string input = "procedure testWhile {while ( ((a) > (b)) && ((a<b))    ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(), "Syntax error: Invalid nesting in conditional expression");
    }

    SECTION("Invalid expression on LHS") {
        std::string input = "procedure testWhile {while ( ((k - (a + b)) % (1)) z!= (r / g) ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(), "Syntax error: Missing / wrong operator");
    }
}

TEST_CASE("SyntacticValidator - Valid WHILE syntax CONDITIONAL expr") {
    SECTION("NOT conditional expr"){
        std::string input = "procedure testWhile {while ( !(a>b)  ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("AND conditional expr") {
        std::string input = "procedure testWhile {while ( (a<b) && (a>b) ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("AND conditional expr") {
        std::string input = "procedure testWhile {while ( (a<=b) || (a>=b) ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("NOT conditional expr, nested"){
        std::string input = "procedure testWhile {while ( !( !(  !(a>b) )  ) ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("AND conditional expr, nested"){
        std::string input = "procedure testWhile {while ( !( !(  !(a>b) )  ) ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Complex nested expr") {
        std::string input = "procedure testWhile {while (     (((k + 0)>(r)) || (b != a)) && (!(a != 0))      ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

    SECTION("Complex nested expr 2") {
        std::string input = "procedure testWhile {while (     ! (((k + 0)>(r)) || (b != a))     ) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_NOTHROW(validator.validate());
    }

}

TEST_CASE("SyntacticValidator - Invalid WHILE syntax CONDITIONAL expr") {
    SECTION("invalid not expression"){
        std::string input = "procedure testWhile {while (!a) { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(), "Syntax Error: Expected rel_expr in Relation Expression");
    }

    SECTION("invalid expression"){
        std::string input = "procedure testWhile {while ( ((A > B)) && (C < D) )  { a = r; }}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        SyntacticValidator validator(tokens);
        REQUIRE_THROWS_WITH(validator.validate(), "Syntax error: Invalid nesting in conditional expression");
    }
}

