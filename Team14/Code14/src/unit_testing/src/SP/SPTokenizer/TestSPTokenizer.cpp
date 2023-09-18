
#include "SP/SPTokenizer.h"
#include "Commons/AppConstants.h"

#include <string>
#include "catch.hpp"

TEST_CASE("SPTokenizer - Valid Tokens") {

    SECTION("Name token") {
        std::string input = "var1 var2 var3 var4";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 4);

        // check each token individually using .at() method
        REQUIRE(tokens.at(0).getType() == TokenType::Name);
        REQUIRE(tokens.at(0).getValue() == "var1");
        REQUIRE(tokens.at(1).getValue() == "var2");
        REQUIRE(tokens.at(2).getValue() == "var3");
        REQUIRE(tokens.at(3).getValue() == "var4");
    }

    SECTION("Name token with whitespace") {
        std::string input = "var1   var2";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 2);

        // check each token individually using .at() method
        REQUIRE(tokens.at(0).getType() == TokenType::Name);
        REQUIRE(tokens.at(0).getValue() == "var1");
        REQUIRE(tokens.at(1).getValue() == "var2");
    }

    SECTION("Name and Integer tokens") {
        std::string input = "var1 123 var2 456";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 4);

        // check each token individually using .at() method
        REQUIRE(tokens.at(0).getType() == TokenType::Name);
        REQUIRE(tokens.at(0).getValue() == "var1");
        REQUIRE(tokens.at(1).getType() == TokenType::Integer);
        REQUIRE(tokens.at(1).getValue() == "123");
        REQUIRE(tokens.at(2).getType() == TokenType::Name);
        REQUIRE(tokens.at(2).getValue() == "var2");
        REQUIRE(tokens.at(3).getType() == TokenType::Integer);
        REQUIRE(tokens.at(3).getValue() == "456");
    }

    SECTION("Name and Integer with white space") {
        std::string input = "1 2 3 456 001 100 100000 1x10";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 9);
    }

    SECTION("Parenthesis test") {
        std::string input = "( hello world ) {1} {{}}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();

        REQUIRE(tokens.size() == 11);

    }

    SECTION("Semicolon and Equals test") {
        std::string input = "(=);{abc 123xyz}";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
    }

    SECTION("Arithmetic test") {
        std::string input = "1+2-3*4/5%6";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
    }

    SECTION("Conditional Not test") {
        std::string input = "!(var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(0).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(0).getValue() == AppConstants::STRING_NOT);
    }

    SECTION("Conditional Not complex test") {
        std::string input = "! (var1) !    (var2) ! 1+2-3*4 ";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(0).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(0).getValue() == AppConstants::STRING_NOT);
        REQUIRE(tokens.at(4).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(4).getValue() == AppConstants::STRING_NOT);
        REQUIRE(tokens.at(8).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(8).getValue() == AppConstants::STRING_NOT);
    }

    SECTION("Conditional And test") {
        std::string input = "(var2)&&(var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(3).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(3).getValue() == AppConstants::STRING_AND);
    }

    SECTION("Conditional Or test") {
        std::string input = "(var2)||(var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(3).getType() == TokenType::ConditionalOperator);
        REQUIRE(tokens.at(3).getValue() == AppConstants::STRING_OR);
    }
}

TEST_CASE("Relational operator test") {

    SECTION("Greater than test 1") {
    std::string input = "(var2 > var1)";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();
    REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
    REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_GREATER_THAN);
    }

    SECTION("Greater than test 2") {
    std::string input = "(var2>var1)";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();
    REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
    REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_GREATER_THAN);
    }

    SECTION("Less than test 1") {
    std::string input = "(var2 < var1)";
    SPTokenizer tokenizer(input);
    std::vector<SPToken> tokens = tokenizer.tokenize();
    REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
    REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_LESS_THAN);
    }

    SECTION("Less than test 2") {
        std::string input = "(var2<var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_LESS_THAN);
    }

    SECTION("Less than equal to test 1") {
        std::string input = "(var2 <= var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_LESS_EQUAL);
    }

    SECTION("Less than equal to test 2") {
        std::string input = "(var2<=var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_LESS_EQUAL);
    }

    SECTION("Greater than equal to test 1") {
        std::string input = "(var2 >= var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_GREATER_EQUAL);
    }

    SECTION("Less than equal to test 2") {
        std::string input = "(var2>=var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_GREATER_EQUAL);
    }

    SECTION("Complex Conditional") {
        std::string input = "((var2 * 5) >= var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(6).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(6).getValue() == AppConstants::STRING_GREATER_EQUAL);
    }

    SECTION("Equal") {
        std::string input = "(var2==var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_DOUBLE_EQUAL);
    }


    SECTION("Not Equal") {
        std::string input = "(var2!=var1)";
        SPTokenizer tokenizer(input);
        std::vector<SPToken> tokens = tokenizer.tokenize();
        REQUIRE(tokens.at(2).getType() == TokenType::RelationalOperator);
        REQUIRE(tokens.at(2).getValue() == AppConstants::STRING_NOT_EQUAL);
    }
}




//TEST_CASE("File Reading Test", "[file]") {
//    std::string fileContent;
//    std::string filePath = "../../../tests/positive_source/Test_source1.txt";
//    std::ifstream inputFile(filePath);
//
//    if (inputFile.is_open()) {
//        std::string line;
//        while (std::getline(inputFile, line)) {
//            fileContent += line + '\n';
//        }
//        inputFile.close();
//    } else {
//        FAIL("Failed to open file");
//    }
//
//    SPTokenizer tokenizer(fileContent);
//    std::vector<SPToken> tokens = tokenizer.tokenize();

    // Perform assertions to check the file content
//    REQUIRE(fileContent == "procedure computeAverage {\n"
//                           "    read num1;\n"
//                           "    read num2;\n"
//                           "    read num3;\n"
//                           "\n"
//                           "    sum = num1 + num2 + num3;\n"
//                           "    ave = sum / 3;\n"
//                           "\n"
//                           "    print ave;\n"
//                           "}");
//}
