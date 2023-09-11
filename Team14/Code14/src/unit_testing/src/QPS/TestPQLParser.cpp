#include "QPS/PQLParser.h"

#include "catch.hpp"

// TODO refactor unit tests using SECTION()

TEST_CASE("single declaration, single Select") {
    std::string input = "stmt s; Select s";
    PQLParser parser(input);
    Query query = parser.parse();
    QueryEntity expectedEntity = QueryEntity(QueryEntityType::Stmt, "s");
    std::shared_ptr<QueryEntity> declarationEntity = query.getEntity("s");
    std::shared_ptr<QueryEntity> selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(query.getEntity("s"));
    REQUIRE(*declarationEntity == expectedEntity);
    REQUIRE(declarationEntity == selectEntity);
}

TEST_CASE("processDeclarations serial declaration") {
    std::string input = "variable v,v1,v2; Select v";
    PQLParser parser(input);
    Query query = parser.parse();
    auto declaration_map = query.getDeclarations();
    std::shared_ptr<QueryEntity> declarationEntity = query.getEntity("v");
    std::shared_ptr<QueryEntity> selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(declaration_map.size()==3);
    REQUIRE(query.getEntity("v"));
    REQUIRE(query.getEntity("v1"));
    REQUIRE(query.getEntity("v2"));
    REQUIRE(declarationEntity == selectEntity);
}

TEST_CASE("processDeclarations multiple declaration") {
    std::string input = "procedure p; stmt s; read re; print pr; assign a; \n call c; while w; if i; variable v; constant k; \n Select c";
    PQLParser parser(input);
    Query query = parser.parse();
    auto declaration_map = query.getDeclarations();
    std::shared_ptr<QueryEntity> declarationEntity = query.getEntity("c");
    std::shared_ptr<QueryEntity> selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(declaration_map.size()==10);
    REQUIRE(query.getEntity("p"));
    REQUIRE(query.getEntity("s"));
    REQUIRE(query.getEntity("re"));
    REQUIRE(query.getEntity("pr"));
    REQUIRE(query.getEntity("a"));
    REQUIRE(query.getEntity("c"));
    REQUIRE(query.getEntity("w"));
    REQUIRE(query.getEntity("i"));
    REQUIRE(query.getEntity("v"));
    REQUIRE(query.getEntity("k"));
    REQUIRE(declarationEntity == selectEntity);
}

TEST_CASE("processDeclarations Errors") {
    std::vector<std::pair<std::string, std::string>> testcases;
    testcases.emplace_back("Select s ", "Expected a declaration but found none");
    testcases.emplace_back("assignment a; ", "Expected a declaration but found none");
    testcases.emplace_back("assign a Select s", "Expected ; but found 'Select'");
    testcases.emplace_back("assign a a1;", "Expected ; but found 'a1'");
    testcases.emplace_back("assign a; print a;", "Trying to redeclare a synonym");
    testcases.emplace_back("assign 1; Select 1", "Invalid synonym '1'");
    testcases.emplace_back("assign -a ; Select -a", "Invalid synonym '-'");
    testcases.emplace_back("stmt", "Expected synonym but found none");
    testcases.emplace_back("stmt ; ",  "Invalid synonym ';'");

    for (const auto& testcase : testcases) {
        PQLParser parser(testcase.first);
        REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
    }
}

TEST_CASE("processSelect Errors") {
    std::vector<std::pair<std::string, std::string>> testcases;
    testcases.emplace_back("stmt s; where s", "Expected Select clause but found 'where'");
    testcases.emplace_back("assign a; Select s", "Undeclared synonym in Select clause");
    testcases.emplace_back("assign a; Select", "Expected synonym but found none");

    for (const auto& testcase : testcases) {
        PQLParser parser(testcase.first);
        REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
    }
}

TEST_CASE("processSuchThatClause") {
    SECTION("Valid Uses query") {
        PQLParser parser("assign a; variable v;\nSelect a such that Uses(a, v)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getLeftRef();
        Ref rightRef = clause.getRightRef();
        REQUIRE(clause.getType() == ClauseType::Uses);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "a");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Variable);
        REQUIRE(rightRef.getRep() == "v");
    }

    SECTION("Valid Uses query") {
        PQLParser parser("assign a;\nSelect a such that Uses(\"main\",\"x\")"); // LHS is procedure
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getLeftRef();
        Ref rightRef = clause.getRightRef();
        REQUIRE(clause.getType() == ClauseType::Uses);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Ident);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "\"main\"");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "\"x\"");
    }

    SECTION("Valid Uses query") {
        PQLParser parser("assign x;\nSelect x such that Uses(x, \"x\")");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getLeftRef();
        Ref rightRef = clause.getRightRef();
        REQUIRE(clause.getType() == ClauseType::Uses);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "x");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "\"x\"");
    }

    SECTION("Valid Follows query") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Follows (s1,s2)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getLeftRef();
        Ref rightRef = clause.getRightRef();
        REQUIRE(clause.getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Follows query") {
        PQLParser parser("stmt s1; assign x;\nSelect x such that Follows(3,x) ");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getLeftRef();
        Ref rightRef = clause.getRightRef();
        REQUIRE(clause.getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "3");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(rightRef.getRep() == "x");
    }

    SECTION("Valid Follows* query") {
        PQLParser parser("stmt s1;\nSelect s1 such that Follows*(_, 1)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getLeftRef();
        Ref rightRef = clause.getRightRef();
        REQUIRE(clause.getType() == ClauseType::FollowsStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "1");
    }

    SECTION("Valid Follows* query") {
        PQLParser parser("stmt x;\nSelect x such that Follows*(_,_)");
        Query query = parser.parse();
        SuchThatClause clause = query.getSuchThat()[0];
        Ref leftRef = clause.getLeftRef();
        Ref rightRef = clause.getRightRef();
        REQUIRE(clause.getType() == ClauseType::FollowsStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Invalid general queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; print d;\nSelect a such",
                               "Invalid query syntax");
        testcases.emplace_back("assign a; print d;\nSelect a such that random(a",
                               "Invalid token, abstraction expected");
        testcases.emplace_back("assign a; print d;\nSelect a such that Follows* ",
                               "No left parenthesis");
        testcases.emplace_back("assign a; print d;\nSelect a such that Uses(a",
                               "No comma");
        testcases.emplace_back("assign a; print d;\nSelect a such that Follows(a, d",
                               "No right parenthesis");

        for (const auto& testcase : testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }

    SECTION("Invalid Uses queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; variable v;\nSelect a such that Uses(_, v)",
                               "Invalid Uses LHS, wildcard found");
        testcases.emplace_back("assign a; variable v;\nSelect a such that Uses(v, a)",
                               "Invalid Uses LHS, invalid entity type found");
        testcases.emplace_back("call a; print d;\nSelect a such that Uses(\"y\", d)",
                               "Invalid Uses RHS, non-variable found");
        testcases.emplace_back("assign a; print d;\nSelect a such that Uses(b, d)",
                               "Invalid Uses LHS, undeclared synonym found");
        testcases.emplace_back("assign a; print d;\nSelect a such that Uses(a, 2)",
                               "Invalid entRef");

        for (const auto& testcase : testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }

    SECTION("Invalid Follow queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("stmt a; variable v;\nSelect v such that Follows(v, a)",
                               "Invalid Follows LHS, non-statement found");
        testcases.emplace_back("procedure a; call v;\nSelect v such that Follows(v, a)",
                               "Invalid Follows RHS, non-statement found");
        testcases.emplace_back("procedure a; call v;\nSelect v such that Follows(hello, a)",
                               "Undeclared synonym found");
        testcases.emplace_back("procedure a; call v;\nSelect a such that Follows(\"hello\", v)",
                               "Invalid stmtRef");
        testcases.emplace_back("assign a; call v;\nSelect a such that Follows(a, \"world\")",
                               "Invalid stmtRef");

        for (const auto& testcase : testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }
}
