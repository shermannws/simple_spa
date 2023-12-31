#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "QPS/Exceptions/SemanticException.h"
#include "QPS/Exceptions/SyntaxException.h"
#include "QPS/Parsers/PQLParser.h"
#include "QPSTestUtil.h"

#include "catch.hpp"


TEST_CASE_METHOD(UnitTestFixture, "single declaration, single Select") {
    std::string input = "stmt s; Select s";
    PQLParser parser(input);
    Query query = parser.parse();
    QueryEntity expectedEntity = QueryEntity(QueryEntityType::Stmt, "s");
    std::shared_ptr<QueryEntity> declarationEntity = query.getEntity("s");
    Synonym selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(query.getEntity("s"));
    REQUIRE(*declarationEntity == expectedEntity);
    REQUIRE(declarationEntity == query.getEntity(selectEntity));
}

TEST_CASE_METHOD(UnitTestFixture, "processDeclarations serial declaration") {
    std::string input = "variable v,v1,v2; Select v";
    PQLParser parser(input);
    Query query = parser.parse();
    auto declaration_map = query.getDeclarations();
    std::shared_ptr<QueryEntity> declarationEntity = query.getEntity("v");
    Synonym selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(declaration_map.size() == 3);
    REQUIRE(query.getEntity("v"));
    REQUIRE(query.getEntity("v1"));
    REQUIRE(query.getEntity("v2"));
    REQUIRE(declarationEntity == query.getEntity(selectEntity));
}

TEST_CASE_METHOD(UnitTestFixture, "processDeclarations multiple declaration") {
    std::string input =
            "procedure p; stmt s; read re; print pr; assign a; \n while w; if i; variable v; constant k; \n Select p";
    PQLParser parser(input);
    Query query = parser.parse();
    auto declaration_map = query.getDeclarations();
    std::shared_ptr<QueryEntity> declarationEntity = query.getEntity("p");
    Synonym selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(declaration_map.size() == 9);
    REQUIRE(query.getEntity("p"));
    REQUIRE(query.getEntity("s"));
    REQUIRE(query.getEntity("re"));
    REQUIRE(query.getEntity("pr"));
    REQUIRE(query.getEntity("a"));
    REQUIRE(query.getEntity("w"));
    REQUIRE(query.getEntity("i"));
    REQUIRE(query.getEntity("v"));
    REQUIRE(query.getEntity("k"));
    REQUIRE(declarationEntity == query.getEntity(selectEntity));
}

TEST_CASE_METHOD(UnitTestFixture, "processDeclarations Errors") {
    SECTION("SyntaxExceptions") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assignment a; Select a", "Expected Select clause but found 'assignment'");
        testcases.emplace_back("assign a Select s", "Expected ; but found 'Select'");
        testcases.emplace_back("assign a a1; Select a1", "Expected ; but found 'a1'");
        testcases.emplace_back("assign a;", "Expected Select clause but found ''");
        testcases.emplace_back("assign 1; Select 1", "Invalid synonym");
        testcases.emplace_back("assign -a ; Select -a", "Invalid synonym");
        testcases.emplace_back("stmt", "Invalid synonym");
        testcases.emplace_back("stmt ; ", "Invalid synonym");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }
    }

    SECTION("SemanticExceptions") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("Select s ", "Undeclared synonym in Select clause");
        testcases.emplace_back("stmt s; assign s; Select s ", "Trying to redeclare a synonym");
        testcases.emplace_back("Select s ", "Undeclared synonym in Select clause");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SemanticException);
        }

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
        }
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSelect Errors") {
    SECTION("SyntaxException") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("stmt s; where s", "Expected Select clause but found 'where'");
        testcases.emplace_back("assign a; Select", "Invalid synonym syntax");
        testcases.emplace_back("assign a; Select a;", "Invalid synonym syntax");
        testcases.emplace_back("assign a; Select -a", "Invalid synonym syntax");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }
    }
    SECTION("SemanticException") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; Select s", "Undeclared synonym in Select clause");
        testcases.emplace_back("assign Synonym; Select synonym", "Undeclared synonym in Select clause");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SemanticException);
        }
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Uses") {
    SECTION("Valid Uses query") {
        PQLParser parser("assign a; variable v;\nSelect a such that Uses(a, v)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Uses);
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
        PQLParser parser("assign x;\nSelect x such that Uses(x, \"x\")");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Uses);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "x");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "x");
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Modifies") {
    SECTION("Valid Modifies(s,v) query") {
        PQLParser parser("stmt s; variable v; \nSelect v such that Modifies(s,v)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(leftRef.getRep() == "s");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Variable);
        REQUIRE(rightRef.getRep() == "v");
    }

    SECTION("Valid Modifies(s,ident) query") {
        PQLParser parser("read re; \nSelect re such that Modifies(re,\"variable\")");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(leftRef.getRep() == "re");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "variable");
    }

    SECTION("Valid Modifies(integer,v) query") {
        PQLParser parser("variable l; \nSelect l such that Modifies(3,l)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "3");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Variable);
        REQUIRE(rightRef.getRep() == "l");
    }

    SECTION("Valid Modifies(integer,ident) query") {
        PQLParser parser("stmt s; \nSelect s such that Modifies(1,\"hello\")");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "hello");
    }

    SECTION("Valid Modifies(s,_) query") {
        PQLParser parser("assign a; \nSelect a such that Modifies(a,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "a");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Modifies(integer,_) query") {
        PQLParser parser("assign a; \nSelect a such that Modifies(5,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Modifies);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "5");
        REQUIRE(rightRef.getType() == RefType::EntRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Follows") {
    SECTION("Valid Follows(s1,s2)") {
        PQLParser parser("stmt s1, s2;\nSelect s1 such that Follows (s1,s2)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Follows(s,integer)") {
        PQLParser parser("print pr;\nSelect pr  such  that  Follows(pr,1)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(leftRef.getRep() == "pr");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "1");
    }

    SECTION("Valid Follows(s,_)") {
        PQLParser parser("if ifs;\nSelect ifs such that Follows(ifs,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::If);
        REQUIRE(leftRef.getRep() == "ifs");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Follows(integer,s)") {
        PQLParser parser("while w;\nSelect w such  that  Follows(1,w)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::While);
        REQUIRE(rightRef.getRep() == "w");
    }

    SECTION("Valid Follows(_,s)") {
        PQLParser parser("assign a;\nSelect a such that Follows(_,a)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(rightRef.getRep() == "a");
    }

    SECTION("Valid Follows(integer,integer)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Follows(2,3)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "2");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Follows(_,_)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Follows(_,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Follows);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Parent") {
    SECTION("Valid Parent(s1,s2)") {
        PQLParser parser("print s1, s2;\nSelect s1 such that Parent (s1,s2)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Parent(s,integer)") {
        PQLParser parser("print pr;\nSelect pr  such  that  Parent(pr,1)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(leftRef.getRep() == "pr");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "1");
    }

    SECTION("Valid Parent(s,_)") {
        PQLParser parser("if ifs;\nSelect ifs such that Parent(ifs,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::If);
        REQUIRE(leftRef.getRep() == "ifs");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Parent(integer,s)") {
        PQLParser parser("while w;\nSelect w such  that  Parent(1,w)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::While);
        REQUIRE(rightRef.getRep() == "w");
    }

    SECTION("Valid Parent(_,s)") {
        PQLParser parser("assign a;\nSelect a such that Parent(_,a)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(rightRef.getRep() == "a");
    }

    SECTION("Valid Parent(integer,integer)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Parent(2,3)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "2");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Parent(_,_)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Parent(_,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Parent);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Parent*") {
    SECTION("Valid Parent*(s1,s2)") {
        PQLParser parser("read s1, s2;\nSelect s1 such that Parent* (s1,s2)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Parent*(s,integer)") {
        PQLParser parser("assign assign;\nSelect assign such that  Parent*(assign,3)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "assign");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Parent*(s,_)") {
        PQLParser parser("read hello;\nSelect hello such that Parent*(hello,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(leftRef.getRep() == "hello");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Parent*(integer,s)") {
        PQLParser parser("stmt read;\nSelect read such  that  Parent*(1,read)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(rightRef.getRep() == "read");
    }

    SECTION("Valid Parent*(_,s)") {
        PQLParser parser("while while;\nSelect while such that Parent*(_,while)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::While);
        REQUIRE(rightRef.getRep() == "while");
    }

    SECTION("Valid Parent*(integer,integer)") {
        PQLParser parser("stmt s1; stmt s2;\nSelect s1  such  that  Parent*(2,3)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "2");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Parent*(_,_)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Parent*(_,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::ParentStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Next") {
    SECTION("Valid Next(s1,s2)") {
        PQLParser parser("print s1, s2;\nSelect s1 such that Next (s1,s2)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Next);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Next(s,integer)") {
        PQLParser parser("print pr;\nSelect pr  such  that  Next(pr,1)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Next);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(leftRef.getRep() == "pr");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "1");
    }

    SECTION("Valid Next(s,_)") {
        PQLParser parser("if ifs;\nSelect ifs such that Next(ifs,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Next);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::If);
        REQUIRE(leftRef.getRep() == "ifs");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Next(integer,s)") {
        PQLParser parser("while w;\nSelect w such  that  Next(1,w)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Next);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::While);
        REQUIRE(rightRef.getRep() == "w");
    }

    SECTION("Valid Next(_,s)") {
        PQLParser parser("assign a;\nSelect a such that Next(_,a)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Next);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(rightRef.getRep() == "a");
    }

    SECTION("Valid Next(integer,integer)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Next(2,3)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Next);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "2");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Next(_,_)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Next(_,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Next);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Next*") {
    SECTION("Valid Next*(s1,s2)") {
        PQLParser parser("read s1, s2;\nSelect s1 such that Next* (s1,s2)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::NextStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Next*(s,integer)") {
        PQLParser parser("assign assign;\nSelect assign such that  Next*(assign,3)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::NextStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "assign");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Next*(s,_)") {
        PQLParser parser("read hello;\nSelect hello such that Next*(hello,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::NextStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(leftRef.getRep() == "hello");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Next*(integer,s)") {
        PQLParser parser("stmt read;\nSelect read such  that  Next*(1,read)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::NextStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(rightRef.getRep() == "read");
    }

    SECTION("Valid Next*(_,s)") {
        PQLParser parser("while while;\nSelect while such that Next*(_,while)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::NextStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::While);
        REQUIRE(rightRef.getRep() == "while");
    }

    SECTION("Valid Next*(integer,integer)") {
        PQLParser parser("stmt s1; stmt s2;\nSelect s1  such  that  Next*(2,3)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::NextStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "2");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "3");
    }

    SECTION("Valid Next*(_,_)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Next*(_,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::NextStar);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Calls") {
    SECTION("Valid Calls(_, _)") {
        PQLParser parser("print s1; Select s1 such that Calls (_,_)");
        Query query = parser.parse();
        auto expectedClause = QPSTestUtil::createSuchThatClause(ClauseType::Calls, RefType::EntRef, RootType::Wildcard,
                                                                QueryEntityType::Invalid, "_", RefType::EntRef,
                                                                RootType::Wildcard, QueryEntityType::Invalid, "_");
        REQUIRE(*query.getSuchThat()[0] == *expectedClause);
    }

    SECTION("Valid Calls(p, procName)") {
        PQLParser parser("procedure procedure; Select procedure such that Calls (procedure, \"procName\")");
        Query query = parser.parse();
        auto expectedClause = QPSTestUtil::createSuchThatClause(
                ClauseType::Calls, RefType::EntRef, RootType::Synonym, QueryEntityType::Procedure, "procedure",
                RefType::EntRef, RootType::Ident, QueryEntityType::Invalid, "procName");
        REQUIRE(*query.getSuchThat()[0] == *expectedClause);
    }

    SECTION("Valid Calls(procName, _)") {
        PQLParser parser("procedure procedure; Select procedure such that Calls (\"procedure\", _)");
        Query query = parser.parse();
        auto expectedClause = QPSTestUtil::createSuchThatClause(ClauseType::Calls, RefType::EntRef, RootType::Ident,
                                                                QueryEntityType::Invalid, "procedure", RefType::EntRef,
                                                                RootType::Wildcard, QueryEntityType::Invalid, "_");
        REQUIRE(*query.getSuchThat()[0] == *expectedClause);
    }

    SECTION("Valid Calls(procName, p)") {
        PQLParser parser("procedure procedure, q; Select procedure such that Calls (\"procedure\", q)");
        Query query = parser.parse();
        auto expectedClause = QPSTestUtil::createSuchThatClause(ClauseType::Calls, RefType::EntRef, RootType::Ident,
                                                                QueryEntityType::Invalid, "procedure", RefType::EntRef,
                                                                RootType::Synonym, QueryEntityType::Procedure, "q");
        REQUIRE(*query.getSuchThat()[0] == *expectedClause);
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Calls*") {
    SECTION("Valid Calls*(_, p)") {
        PQLParser parser("print s1; procedure q; Select s1 such that Calls* (_,q)");
        Query query = parser.parse();
        auto expectedClause = QPSTestUtil::createSuchThatClause(
                ClauseType::CallsStar, RefType::EntRef, RootType::Wildcard, QueryEntityType::Invalid, "_",
                RefType::EntRef, RootType::Synonym, QueryEntityType::Procedure, "q");
        REQUIRE(*query.getSuchThat()[0] == *expectedClause);
    }

    SECTION("Valid Calls*(_, procName)") {
        PQLParser parser("procedure procedure; Select procedure such that Calls* (_, \"procName\")");
        Query query = parser.parse();
        auto expectedClause = QPSTestUtil::createSuchThatClause(
                ClauseType::CallsStar, RefType::EntRef, RootType::Wildcard, QueryEntityType::Invalid, "_",
                RefType::EntRef, RootType::Ident, QueryEntityType::Invalid, "procName");
        REQUIRE(*query.getSuchThat()[0] == *expectedClause);
    }

    SECTION("Valid Calls*(procName, procName)") {
        PQLParser parser(R"(procedure procedure; Select procedure such that Calls ("procedure", "procedure"))");
        Query query = parser.parse();
        auto expectedClause = QPSTestUtil::createSuchThatClause(ClauseType::Calls, RefType::EntRef, RootType::Ident,
                                                                QueryEntityType::Invalid, "procedure", RefType::EntRef,
                                                                RootType::Ident, QueryEntityType::Invalid, "procedure");
        REQUIRE(*query.getSuchThat()[0] == *expectedClause);
    }

    SECTION("Valid Calls*(p,_)") {
        PQLParser parser("procedure procedure, q; Select procedure such that Calls (q,_)");
        Query query = parser.parse();
        auto expectedClause = QPSTestUtil::createSuchThatClause(ClauseType::Calls, RefType::EntRef, RootType::Synonym,
                                                                QueryEntityType::Procedure, "q", RefType::EntRef,
                                                                RootType::Wildcard, QueryEntityType::Invalid, "_");
        REQUIRE(*query.getSuchThat()[0] == *expectedClause);
    }

    SECTION("Valid Calls*(p,q)") {
        PQLParser parser("procedure procedure, q; Select procedure such that Calls (procedure, q)");
        Query query = parser.parse();
        auto expectedClause = QPSTestUtil::createSuchThatClause(
                ClauseType::Calls, RefType::EntRef, RootType::Synonym, QueryEntityType::Procedure, "procedure",
                RefType::EntRef, RootType::Synonym, QueryEntityType::Procedure, "q");
        REQUIRE(*query.getSuchThat()[0] == *expectedClause);
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processSuchThatClause Affects") {
    SECTION("Valid Affects(s1,s2)") {
        PQLParser parser("stmt s1, s2;\nSelect s1 such that Affects (s1,s2)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(leftRef.getRep() == "s1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(rightRef.getRep() == "s2");
    }

    SECTION("Valid Affects(a,a)") {
        PQLParser parser("assign a1, a2;\nSelect a1 such that Affects (a1,a1)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "a1");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(rightRef.getRep() == "a1");
    }

    SECTION("Valid Affects(_,_)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Affects (_,_)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Affects(integer,integer)") {
        PQLParser parser("stmt s1, s2;\nSelect s1  such  that  Affects(4,5)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "4");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "5");
    }

    SECTION("Valid Affects(s, integer)") {
        PQLParser parser("stmt s;\nSelect s such that Affects (s, 100)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(leftRef.getRep() == "s");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "100");
    }

    SECTION("Valid Affects(integer, s)") {
        PQLParser parser("stmt s;\nSelect s such that Affects (99, s)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "99");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(rightRef.getRep() == "s");
    }

    SECTION("Valid Affects(_, integer)") {
        PQLParser parser("stmt s;\nSelect s such that Affects (_, 100)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "100");
    }

    SECTION("Valid Affects(integer, _)") {
        PQLParser parser("stmt s;\nSelect s such that Affects (99, _)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "99");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Affects(s, _)") {
        PQLParser parser("stmt s;\nSelect s such that Affects (s, _)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(leftRef.getRep() == "s");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Wildcard);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(rightRef.getRep() == "_");
    }

    SECTION("Valid Affects(_, s)") {
        PQLParser parser("stmt s;\nSelect s such that Affects (_, s)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Invalid);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Stmt);
        REQUIRE(rightRef.getRep() == "s");
    }

    SECTION("Valid Affects(read,print)") {
        PQLParser parser("read r; print p;\nSelect r such that Affects (r,p)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(leftRef.getRep() == "r");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(rightRef.getRep() == "p");
    }

    SECTION("Valid Affects(print,call)") {
        PQLParser parser("print p; call c;\nSelect p such that Affects (p, c)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Print);
        REQUIRE(leftRef.getRep() == "p");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Call);
        REQUIRE(rightRef.getRep() == "c");
    }

    SECTION("Valid Affects(call,while)") {
        PQLParser parser("call c; while w;\nSelect c such that Affects (c,w)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Call);
        REQUIRE(leftRef.getRep() == "c");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::While);
        REQUIRE(rightRef.getRep() == "w");
    }

    SECTION("Valid Affects(while, if)") {
        PQLParser parser("while w; if ifs;\nSelect w such that Affects (w, ifs)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::While);
        REQUIRE(leftRef.getRep() == "w");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::If);
        REQUIRE(rightRef.getRep() == "ifs");
    }

    SECTION("Valid Affects(if, assign)") {
        PQLParser parser("if ifs; assign a;\nSelect ifs such that Affects (ifs, a)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::If);
        REQUIRE(leftRef.getRep() == "ifs");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(rightRef.getRep() == "a");
    }

    SECTION("Valid Affects(assign, read)") {
        PQLParser parser("assign a; read r;\nSelect a such that Affects (a, r)");
        Query query = parser.parse();
        std::shared_ptr<SuchThatClause> clause = query.getSuchThat()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Affects);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "a");
        REQUIRE(rightRef.getType() == RefType::StmtRef);
        REQUIRE(rightRef.getRootType() == RootType::Synonym);
        REQUIRE(rightRef.getEntityType() == QueryEntityType::Read);
        REQUIRE(rightRef.getRep() == "r");
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Invalid processSuchThat cases") {
    SECTION("Invalid Syntax - general queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; print d;\nSelect a such", "Invalid query syntax");
        testcases.emplace_back("assign a; print d;\nSelect a such that random(a",
                               "Invalid token, abstraction expected");
        testcases.emplace_back("assign a; print d;\nSelect a such that Follows* ", "No left parenthesis");
        testcases.emplace_back("assign a; print d;\nSelect a such that Uses(a", "No comma");
        testcases.emplace_back("assign a; print d;\nSelect a such that Follows(a, d", "No right parenthesis");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }
    }

    SECTION("Invalid Uses queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("print a; print d;\nSelect a such that Uses(\"\", d)", "Identity invalid");
        testcases.emplace_back("assign a; print d;\nSelect a such that Uses(a, 2)", "Invalid RHS entRef");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }

        std::vector<std::pair<std::string, std::string>> testcases2;
        testcases2.emplace_back("assign a; variable v;\nSelect a such that Uses(_, v)", "Invalid LHS, wildcard found");
        testcases2.emplace_back("assign a; variable v;\nSelect a such that Uses(v, a)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("assign a; print d;\nSelect a such that Uses(b, d)",
                                "Invalid LHS, undeclared synonym found");

        for (const auto &testcase: testcases2) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SemanticException);
        }
    }

    SECTION("Invalid Modifies queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; constant d;\nSelect a such that Modifies(\"test, d)", "No right quote");
        testcases.emplace_back("print a; print d;\nSelect a such that Modifies(a, 3)", "Invalid RHS entRef");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }

        std::vector<std::pair<std::string, std::string>> testcases2;
        testcases2.emplace_back("assign a; variable v;\nSelect a such that Modifies(_, v)",
                                "Invalid LHS, wildcard found");
        testcases2.emplace_back("print a; constant v;\nSelect a such that Modifies(v, a)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("stmt a; variable d;\nSelect a such that Modifies(b, d)",
                                "Invalid LHS, undeclared synonym found");

        for (const auto &testcase: testcases2) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SemanticException);
        }
    }

    SECTION("Invalid Follow queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("procedure a; read v;\nSelect a such that Follows(\"hello\", v)",
                               "Invalid LHS, stmtRef expected");
        testcases.emplace_back("assign a; if v;\nSelect a such that Follows(a, \"world\")",
                               "Invalid RHS, stmtRef expected");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }

        std::vector<std::pair<std::string, std::string>> testcases2;
        testcases2.emplace_back("stmt a; variable v;\nSelect v such that Follows(v, a)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("procedure a; print v;\nSelect v such that Follows(v, a)",
                                "Invalid RHS synonym, non-statement found");
        testcases2.emplace_back("procedure a; assign v;\nSelect v such that Follows(hello, a)",
                                "Invalid LHS, undeclared synonym found");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }
    }

    SECTION("Invalid Parent queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("stmt a; print v;\nSelect a such that Parent(\"hello\", v)",
                               "Invalid LHS, stmtRef expected");
        testcases.emplace_back("print a; assign v;\nSelect a such that Parent(a, \"world\")",
                               "Invalid RHS, stmtRef expected");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }

        std::vector<std::pair<std::string, std::string>> testcases2;
        testcases2.emplace_back("stmt a; variable v;\nSelect v such that Parent(v, a)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("procedure a; stmt v;\nSelect v such that Parent(v, a)",
                                "Invalid RHS synonym, non-statement found");
        testcases2.emplace_back("constant a; stmt v;\nSelect v such that Parent(a, v)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("procedure a; stmt v;\nSelect v such that Parent(hello, a)",
                                "Invalid LHS, undeclared synonym found");
        for (const auto &testcase: testcases2) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SemanticException);
        }
    }

    SECTION("Invalid Parent* queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("stmt a; print v;\nSelect a such that Parent*(\"hello\", v)",
                               "Invalid LHS, stmtRef expected");
        testcases.emplace_back("print a; assign v;\nSelect a such that Parent*(a, \"world\")",
                               "Invalid RHS, stmtRef expected");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }

        std::vector<std::pair<std::string, std::string>> testcases2;
        testcases2.emplace_back("stmt a; variable v;\nSelect v such that Parent*(v, a)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("procedure a; stmt v;\nSelect v such that Parent*(v, a)",
                                "Invalid RHS synonym, non-statement found");
        testcases2.emplace_back("constant a; stmt v;\nSelect v such that Parent*(a, v)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("procedure a; stmt v;\nSelect v such that Parent*(hello, a)",
                                "Invalid LHS, undeclared synonym found");

        for (const auto &testcase: testcases2) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SemanticException);
        }
    }

    SECTION("Invalid Calls/Calls* queries") {
        PQLParser parser("assign a; variable v; Select a such that Calls(1,_)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v; procedure p;Select a such that Calls*(p, 1)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v; Select a such that Calls(v,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("assign a; variable v; procedure p;Select a such that Calls*(p, a)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);
    }

    SECTION("Invalid Affects queries") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("stmt s; print p;\nSelect a such that Affects(\"invalid\", p)",
                               "Invalid LHS, stmtRef expected");
        testcases.emplace_back("print p; assign a;\nSelect a such that Affects(p, \"invalid\")",
                               "Invalid RHS, stmtRef expected");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }

        std::vector<std::pair<std::string, std::string>> testcases2;
        testcases2.emplace_back("stmt a; variable v;\nSelect v such that Affects(v, a)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("stmt a; variable v;\nSelect v such that Affects(a, v)",
                                "Invalid RHS synonym, non-statement found");
        testcases2.emplace_back("procedure a; stmt v;\nSelect v such that Affects(a, v)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("procedure a; stmt v;\nSelect v such that Affects(v, a)",
                                "Invalid RHS synonym, non-statement found");
        testcases2.emplace_back("constant a; stmt v;\nSelect v such that Affects(a, v)",
                                "Invalid LHS synonym, non-statement found");
        testcases2.emplace_back("constant a; stmt v;\nSelect v such that Affects(v, a)",
                                "Invalid RHS synonym, non-statement found");
        testcases2.emplace_back("procedure a; stmt v;\nSelect v such that Affects(hello, a)",
                                "Invalid LHS, undeclared synonym found");
        for (const auto &testcase: testcases2) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SemanticException);
        }
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processPatternClause") {
    SECTION("Valid wildcard assign pattern") {
        PQLParser parser("assign a; variable v;\nSelect a pattern a(_,_)");
        Query query = parser.parse();

        std::shared_ptr<PatternClause> actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::Assign);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.first == ExpressionSpecType::Wildcard);
        REQUIRE(rightRef.second.empty());
    }

    SECTION("Valid assign pattern, Synonym entRef and exact match") {
        PQLParser parser("assign a; variable v;\nSelect a pattern a(v,\"x * (b * a + (n + (1%c))) \")");
        Query query = parser.parse();

        auto actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::Assign);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getRep() == "v");
        REQUIRE(rightRef.first == ExpressionSpecType::ExactMatch);
        REQUIRE(rightRef.second == "((x)*(((b)*(a))+((n)+((1)%(c)))))");
    }

    SECTION("Valid assign pattern, Synonym entRef and exact match") {
        PQLParser parser("assign a; variable v;\nSelect a pattern a(\"y\",_\"x\"_)");
        Query query = parser.parse();

        auto actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::Assign);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Ident);
        REQUIRE(leftRef.getRep() == "y");
        REQUIRE(rightRef.first == ExpressionSpecType::PartialMatch);
        REQUIRE(rightRef.second == "(x)");
    }

    SECTION("Valid assign pattern, Synonym entRef and exact match") {
        PQLParser parser("assign a; variable v;\nSelect a such that Uses(a, v) pattern a(\"y\",_\"x\"_)");
        Query query = parser.parse();

        auto actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::Assign);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Ident);
        REQUIRE(leftRef.getRep() == "y");
        REQUIRE(rightRef.first == ExpressionSpecType::PartialMatch);
        REQUIRE(rightRef.second == "(x)");

        auto clause = query.getSuchThat()[0];
        leftRef = clause->getFirstParam();
        Ref rightRef1 = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::Uses);
        REQUIRE(leftRef.getType() == RefType::StmtRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
        REQUIRE(leftRef.getRep() == "a");
        REQUIRE(rightRef1.getType() == RefType::EntRef);
        REQUIRE(rightRef1.getRootType() == RootType::Synonym);
        REQUIRE(rightRef1.getEntityType() == QueryEntityType::Variable);
        REQUIRE(rightRef1.getRep() == "v");
    }

    SECTION("Valid if pattern syntax firstparam:variable") {
        PQLParser parser("if ifs; variable v;\nSelect ifs pattern ifs(v,_,_)");
        Query query = parser.parse();

        std::shared_ptr<PatternClause> actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::If);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getRep() == "v");
        REQUIRE(rightRef.first == ExpressionSpecType::Wildcard);
        REQUIRE(rightRef.second.empty());
    }

    SECTION("Valid if pattern syntax firstparam:ident") {
        PQLParser parser("if ifs;\nSelect ifs pattern ifs(\"variable\",_,_)");
        Query query = parser.parse();

        std::shared_ptr<PatternClause> actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::If);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Ident);
        REQUIRE(leftRef.getRep() == "variable");
        REQUIRE(rightRef.first == ExpressionSpecType::Wildcard);
        REQUIRE(rightRef.second.empty());
    }

    SECTION("Valid if pattern syntax firstparam:wildcard") {
        PQLParser parser("if ifs;\nSelect ifs pattern ifs(_,_,_)");
        Query query = parser.parse();

        std::shared_ptr<PatternClause> actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::If);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.first == ExpressionSpecType::Wildcard);
        REQUIRE(rightRef.second.empty());
    }

    SECTION("Valid while pattern wildcard lhs") {
        PQLParser parser("while w; Select w pattern w(_,_)");
        Query query = parser.parse();

        std::shared_ptr<PatternClause> actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::While);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Wildcard);
        REQUIRE(leftRef.getRep() == "_");
        REQUIRE(rightRef.first == ExpressionSpecType::Wildcard);
        REQUIRE(rightRef.second.empty());
    }

    SECTION("Valid while pattern ident lhs") {
        PQLParser parser("while w; Select w pattern w(\"x\",_)");
        Query query = parser.parse();

        std::shared_ptr<PatternClause> actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::While);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Ident);
        REQUIRE(leftRef.getRep() == "x");
        REQUIRE(rightRef.first == ExpressionSpecType::Wildcard);
        REQUIRE(rightRef.second.empty());
    }

    SECTION("Valid while pattern var synonym lhs") {
        PQLParser parser("while w; variable v; Select w pattern w(v,_)");
        Query query = parser.parse();

        std::shared_ptr<PatternClause> actualClause = query.getPattern()[0];
        Ref leftRef = actualClause->getFirstParam();
        ExpressionSpec rightRef = actualClause->getSecondParam();
        REQUIRE(actualClause->getType() == ClauseType::While);
        REQUIRE(leftRef.getType() == RefType::EntRef);
        REQUIRE(leftRef.getRootType() == RootType::Synonym);
        REQUIRE(leftRef.getRep() == "v");
        REQUIRE(rightRef.first == ExpressionSpecType::Wildcard);
        REQUIRE(rightRef.second.empty());
    }


    SECTION("invalid pattern") {
        PQLParser parser("assign a; variable v;\nSelect a pattern a(\"y\",_ _)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern a(1,_)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern a(_, varName)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern v(\"y\",_);");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern v(\"y\",_");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern v(\"y\",_\"\"_");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern v(\"y\",\"\"");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern v(\"y\" _)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern a(\"y\",_,)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern a(\"y\",_,_");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("if i; variable v;\nSelect a pattern i(_,1,_)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("if i; variable v;\nSelect a pattern i(v,_,1)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("if i; variable v;\nSelect a pattern i(v,_,syn)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("if i; variable v;\nSelect a pattern i(v,_,\"hello\")");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("while w; variable v; Select w pattern w(_, v)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern v(_,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern a1(_,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("assign a; variable v;\nSelect a pattern a(v1,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("assign a;\nSelect a pattern i(_,_,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("assign i;\nSelect i pattern i(_,_,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("while w; variable v;\nSelect w pattern w(v, \"x\")");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("stmt s; variable v;\nSelect s pattern s(v,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("while w; constant v;\nSelect w pattern w(v,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("while w; Select a pattern while(_,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("while w; constant c; Select a pattern w(c,_)");
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);

        parser = PQLParser("while w; Select w pattern w(_, _, _)");// should be assumed as if pattern
        REQUIRE_THROWS_AS(parser.parse(), SemanticException);
    }
}

TEST_CASE_METHOD(UnitTestFixture, "processWithClause") {
    // Syntax Check
    SECTION("Valid Ident = Ident") {
        PQLParser parser("assign a; variable v;\nSelect a with \"hello\" = \"world\"");
        Query query = parser.parse();

        std::shared_ptr<WithClause> clause = query.getWith()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::With);
        REQUIRE(leftRef.getRootType() == RootType::Ident);
        REQUIRE(leftRef.getRep() == "hello");
        REQUIRE(rightRef.getRootType() == RootType::Ident);
        REQUIRE(rightRef.getRep() == "world");
    }

    SECTION("Valid Ident = attrRef") {
        PQLParser parser("assign a; procedure p;\nSelect a with \"hello\" = p.procName");
        Query query = parser.parse();

        std::shared_ptr<WithClause> clause = query.getWith()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::With);
        REQUIRE(leftRef.getRootType() == RootType::Ident);
        REQUIRE(leftRef.getRep() == "hello");
        REQUIRE(rightRef.getRootType() == RootType::AttrRef);
        REQUIRE(rightRef.getRep() == "p");
        REQUIRE(rightRef.getAttrName() == AttrName::ProcName);
    }

    SECTION("Valid Integer = Integer") {
        PQLParser parser("assign a; variable v;\nSelect a with 123 = 321");
        Query query = parser.parse();

        std::shared_ptr<WithClause> clause = query.getWith()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::With);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getRep() == "123");
        REQUIRE(rightRef.getRootType() == RootType::Integer);
        REQUIRE(rightRef.getRep() == "321");
    }

    SECTION("Valid Integer = attrRef") {
        PQLParser parser("assign a; constant c;\nSelect a with 3 = c.value");
        Query query = parser.parse();

        std::shared_ptr<WithClause> clause = query.getWith()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::With);
        REQUIRE(leftRef.getRootType() == RootType::Integer);
        REQUIRE(leftRef.getRep() == "3");
        REQUIRE(rightRef.getRootType() == RootType::AttrRef);
        REQUIRE(rightRef.getRep() == "c");
        REQUIRE(rightRef.getAttrName() == AttrName::Value);
    }

    SECTION("Valid attrRef = attrRef stmt#") {
        PQLParser parser("assign a; read r;\nSelect a with r.stmt# = a.stmt#");
        Query query = parser.parse();

        std::shared_ptr<WithClause> clause = query.getWith()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::With);
        REQUIRE(leftRef.getRootType() == RootType::AttrRef);
        REQUIRE(leftRef.getRep() == "r");
        REQUIRE(leftRef.getAttrName() == AttrName::StmtNo);
        REQUIRE(rightRef.getRootType() == RootType::AttrRef);
        REQUIRE(rightRef.getRep() == "a");
        REQUIRE(rightRef.getAttrName() == AttrName::StmtNo);
    }

    SECTION("Valid attrRef = attrRef value") {
        PQLParser parser("constant c1, c2;\nSelect c1 with c1.value = c2.value");
        Query query = parser.parse();

        std::shared_ptr<WithClause> clause = query.getWith()[0];
        Ref leftRef = clause->getFirstParam();
        Ref rightRef = clause->getSecondParam();
        REQUIRE(clause->getType() == ClauseType::With);
        REQUIRE(!clause->isNegation());
        REQUIRE(leftRef.getRootType() == RootType::AttrRef);
        REQUIRE(leftRef.getRep() == "c1");
        REQUIRE(leftRef.getAttrName() == AttrName::Value);
        REQUIRE(rightRef.getRootType() == RootType::AttrRef);
        REQUIRE(rightRef.getRep() == "c2");
        REQUIRE(rightRef.getAttrName() == AttrName::Value);
    }

    SECTION("Operator ==") {
        PQLParser parser("assign a; constant c; Select BOOLEAN with a.stmt# = c.value");
        Query query = parser.parse();
        std::shared_ptr<WithClause> clausePtr = query.getWith()[0];
        auto expectedClause = WithClause();

        RefType type = RefType::WithRef;
        RootType rootType = RootType::AttrRef;

        Ref leftRef = Ref();
        StringRep leftRep = "a";
        QueryEntityType leftEntityType = QueryEntityType::Assign;
        leftRef.setType(type);
        leftRef.setRep(leftRep);
        leftRef.setRootType(rootType);
        leftRef.setAttrName("stmt#");
        leftRef.setEntityType(leftEntityType);

        Ref rightRef = Ref();
        StringRep rightRep = "c";
        QueryEntityType rightEntityType = QueryEntityType::Constant;
        rightRef.setType(type);
        rightRef.setRep(rightRep);
        rightRef.setRootType(rootType);
        rightRef.setAttrName("value");
        rightRef.setEntityType(rightEntityType);


        expectedClause.setFirstParam(leftRef);
        expectedClause.setSecondParam(rightRef);
        REQUIRE(*clausePtr == expectedClause);
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Invalid processWithClause SyntaxError") {
    SECTION("Invalid general structure") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; print d;\nSelect a with ", "Invalid Ref");
        testcases.emplace_back("assign a; print d;\nSelect a with 1 2", "No equal sign");
        testcases.emplace_back("assign a; print d;\nSelect a with 1 =", "Invalid Ref");
        testcases.emplace_back("assign a; print d;\nSelect a with 1 = .", "Invalid Ref");
        testcases.emplace_back("assign a; print d;\nSelect a with = 1", "Invalid Ref");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }
    }

    SECTION("Invalid withRef type") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; print d;\nSelect a with c = 3", "Invalid LHS withRef");
        testcases.emplace_back("assign a; print d;\nSelect a with _ = \"ident\"", "Invalid LHS withRef");
        testcases.emplace_back("assign a; print d;\nSelect a with 1 = variable", "Invalid RHS withRef");
        testcases.emplace_back("assign a; print d;\nSelect a with \"ident\" = _", "Invalid RHS withRef");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }
    }

    SECTION("Invalid attrName") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; print d;\nSelect a with 1 = a.", "Invalid attrName");
        testcases.emplace_back("assign a; print d;\nSelect a with 1 = a.stmt", "Invalid attrName");
        testcases.emplace_back("assign a; print d;\nSelect a with d.varname = \"ident\"", "Invalid attrName");
        testcases.emplace_back("assign a; print d;\nSelect a with 1 = a.procname", "Invalid attrName");
        testcases.emplace_back("assign a; print d;\nSelect a with 1 = a.val", "Invalid attrName");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
        }
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Invalid processWithClause SemanticError") {
    SECTION("Different types in attrCompare") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; print d; procedure p; constant c;\nSelect a with p.procName = c.value",
                               "Different attribute value types");
        testcases.emplace_back(
                "assign a; if if; procedure p; constant c; variable v;\nSelect a with v.varName = if.stmt#",
                "Different attribute value types");
        testcases.emplace_back("assign a; call c;\nSelect a with a.stmt# = c.procName",
                               "Different attribute value types");
        testcases.emplace_back("assign a; print d; procedure p; constant c;\nSelect a with c.value = d.varName",
                               "Different attribute value types");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SemanticException);
        }
    }
    SECTION("Different types in attrCompare") {
        std::vector<std::pair<std::string, std::string>> testcases;
        testcases.emplace_back("assign a; print d; procedure p; constant c;\nSelect a with p.varName = \"test\"",
                               "Invalid attribute of the synonym");
        testcases.emplace_back("assign a; if if; procedure p; constant c; variable v;\nSelect a with 1 = v.stmt#",
                               "Invalid attribute of the synonym");
        testcases.emplace_back("assign a; call c;\nSelect a with \"procName\" = a.procName",
                               "Invalid attribute of the synonym");
        testcases.emplace_back("assign a; print d; procedure p; constant c;\nSelect a with d.value = 3",
                               "Invalid attribute of the synonym");

        for (const auto &testcase: testcases) {
            PQLParser parser(testcase.first);
            REQUIRE_THROWS_AS(parser.parse(), SemanticException);
        }
    }
}

TEST_CASE_METHOD(UnitTestFixture, "both clause present") {
    PQLParser parser("assign a; variable v;\nSelect a such that Uses(a, v) pattern a(\"y\",_\"x\"_)");
    Query query = parser.parse();

    auto actualClause = query.getPattern()[0];
    Ref leftRef = actualClause->getFirstParam();
    ExpressionSpec rightRef = actualClause->getSecondParam();
    REQUIRE(actualClause->getType() == ClauseType::Assign);
    REQUIRE(leftRef.getType() == RefType::EntRef);
    REQUIRE(leftRef.getRootType() == RootType::Ident);
    REQUIRE(leftRef.getRep() == "y");
    REQUIRE(rightRef.first == ExpressionSpecType::PartialMatch);
    REQUIRE(rightRef.second == "(x)");

    auto clause = query.getSuchThat()[0];
    leftRef = clause->getFirstParam();
    Ref rightRef1 = clause->getSecondParam();
    REQUIRE(clause->getType() == ClauseType::Uses);
    REQUIRE(leftRef.getType() == RefType::StmtRef);
    REQUIRE(leftRef.getRootType() == RootType::Synonym);
    REQUIRE(leftRef.getEntityType() == QueryEntityType::Assign);
    REQUIRE(leftRef.getRep() == "a");
    REQUIRE(rightRef1.getType() == RefType::EntRef);
    REQUIRE(rightRef1.getRootType() == RootType::Synonym);
    REQUIRE(rightRef1.getEntityType() == QueryEntityType::Variable);
    REQUIRE(rightRef1.getRep() == "v");
}

TEST_CASE_METHOD(UnitTestFixture, "invalid multi-clause queries") {
    SECTION("Syntax Errors") {
        // Use and between different clause types
        PQLParser parser("assign a; variable v; Select v such that Modifies(a,v) and pattern a(_,_) ");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        // Use both `and` & clause keyword (such that)
        parser = PQLParser("assign a; variable v; Select v such that Modifies(a,v) and such that Follows(1, 2)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        // Use both `and` & clause keyword (pattern)
        parser = PQLParser("assign a; variable v; Select a pattern a(_,_) and pattern a(v,_)");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

        // Trailing `and`
        parser = PQLParser("assign a; variable v; Select a pattern v(\"y\",_) and ");
        REQUIRE_THROWS_AS(parser.parse(), SyntaxException);
    }
}

TEST_CASE_METHOD(UnitTestFixture, "valid multi-clause queries") {

    SECTION("use AND in such that") {
        PQLParser parser("assign a; variable v; Select v such that Modifies(a,v) and Follows*(1,2) and Uses(a,v)");
        Query query = parser.parse();

        auto stClauses = query.getSuchThat();
        REQUIRE(stClauses.size() == 3);

        auto pClauses = query.getPattern();
        REQUIRE(pClauses.empty());

        auto c1 = QPSTestUtil::createSuchThatClause(ClauseType::Modifies, RefType::StmtRef, RootType::Synonym,
                                                    QueryEntityType::Assign, "a", RefType::EntRef, RootType::Synonym,
                                                    QueryEntityType::Variable, "v");
        auto c2 = QPSTestUtil::createSuchThatClause(ClauseType::FollowsStar, RefType::StmtRef, RootType::Integer,
                                                    QueryEntityType::Invalid, "1", RefType::StmtRef, RootType::Integer,
                                                    QueryEntityType::Invalid, "2");
        auto c3 = QPSTestUtil::createSuchThatClause(ClauseType::Uses, RefType::StmtRef, RootType::Synonym,
                                                    QueryEntityType::Assign, "a", RefType::EntRef, RootType::Synonym,
                                                    QueryEntityType::Variable, "v");
        REQUIRE(*stClauses[0] == *c1);
        REQUIRE(*stClauses[1] == *c2);
        REQUIRE(*stClauses[2] == *c3);
    }

    SECTION("use AND in pattern") {
        PQLParser parser(
                R"(assign a,pattern; variable v; assign a1; Select a pattern a(_,_) and pattern (v,_) and a1("y","1"))");
        Query query = parser.parse();

        auto stClauses = query.getSuchThat();
        REQUIRE(stClauses.empty());

        auto pClauses = query.getPattern();
        REQUIRE(pClauses.size() == 3);

        auto c1 = QPSTestUtil::createPatternClause(ClauseType::Assign, "a", RootType::Wildcard, "_",
                                                   ExpressionSpecType::Wildcard, "");
        auto c2 = QPSTestUtil::createPatternClause(ClauseType::Assign, "pattern", RootType::Synonym, "v",
                                                   ExpressionSpecType::Wildcard, "");
        auto c3 = QPSTestUtil::createPatternClause(ClauseType::Assign, "a1", RootType::Ident, "y",
                                                   ExpressionSpecType::ExactMatch, "(1)");
        REQUIRE(*pClauses[0] == *c1);
        REQUIRE(*pClauses[1] == *c2);
        REQUIRE(*pClauses[2] == *c3);
    }

    SECTION("use AND with all clause types") {
        PQLParser parser(
                R"(assign a; assign and, such; variable v; Select and pattern a(_,_) and and (v,_"1+x"_) such that  Follows(1,2) pattern such(v,_) such that Parent*(1,10))");
        Query query = parser.parse();

        auto stClauses = query.getSuchThat();
        REQUIRE(stClauses.size() == 2);

        auto pClauses = query.getPattern();
        REQUIRE(pClauses.size() == 3);

        auto pc1 = QPSTestUtil::createPatternClause(ClauseType::Assign, "a", RootType::Wildcard, "_",
                                                    ExpressionSpecType::Wildcard, "");
        auto pc2 = QPSTestUtil::createPatternClause(ClauseType::Assign, "and", RootType::Synonym, "v",
                                                    ExpressionSpecType::PartialMatch, "((1)+(x))");
        auto pc3 = QPSTestUtil::createPatternClause(ClauseType::Assign, "such", RootType::Synonym, "v",
                                                    ExpressionSpecType::Wildcard, "");
        auto sc1 = QPSTestUtil::createSuchThatClause(ClauseType::Follows, RefType::StmtRef, RootType::Integer,
                                                     QueryEntityType::Invalid, "1", RefType::StmtRef, RootType::Integer,
                                                     QueryEntityType::Invalid, "2");
        auto sc2 = QPSTestUtil::createSuchThatClause(ClauseType::ParentStar, RefType::StmtRef, RootType::Integer,
                                                     QueryEntityType::Invalid, "1", RefType::StmtRef, RootType::Integer,
                                                     QueryEntityType::Invalid, "10");

        REQUIRE(*pClauses[0] == *pc1);
        REQUIRE(*pClauses[1] == *pc2);
        REQUIRE(*pClauses[2] == *pc3);
        REQUIRE(!pClauses[0]->isNegation());
        REQUIRE(!pClauses[1]->isNegation());
        REQUIRE(!pClauses[2]->isNegation());

        REQUIRE(*stClauses[0] == *sc1);
        REQUIRE(*stClauses[1] == *sc2);
        REQUIRE(!stClauses[0]->isNegation());
        REQUIRE(!stClauses[1]->isNegation());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "tuple and boolean result clause") {

    PQLParser parser("assign a, b, c, d; Select<a  , b  , c> ");
    Query query = parser.parse();

    REQUIRE(query.getSelect().size() == 3);

    parser = PQLParser("assign a, b, c, d; Select<a.stmt#  , b> ");
    auto query2 = parser.parse();

    REQUIRE(query2.getSelect().size() == 2);
    REQUIRE(query2.getSelect()[0] == "a.stmt#");

    parser = PQLParser("procedure a, b, c, d; Select a.procName ");
    auto query3 = parser.parse();
    REQUIRE(query3.getSelect().size() == 1);
    REQUIRE(query3.getSelect()[0] == "a.procName");

    parser = PQLParser("variable v; constant k; procedure p; read r; print pr; call c; Select <p.procName, c.procName, "
                       "v.varName, r.varName, pr.varName, k.value> ");
    auto query4 = parser.parse();
    REQUIRE(query4.getSelect().size() == 6);

    parser = PQLParser("stmt stmt; read read; print print; call call; while while; if if; assign assign; Select "
                       "<stmt.stmt#, read.stmt#, print.stmt#, call.stmt#, while.stmt#, if.stmt#, assign.stmt#>");
    auto query5 = parser.parse();
    REQUIRE(query5.getSelect().size() == 7);

    parser = PQLParser("Select BOOLEAN");
    auto query6 = parser.parse();
    REQUIRE(query6.getSelect().size() == 0);

    parser = PQLParser("assign BOOLEAN; Select BOOLEAN");
    auto query7 = parser.parse();
    REQUIRE(query7.getSelect().size() == 1);

    parser = PQLParser("assign BOOLEAN; Select <BOOLEAN>");
    auto query8 = parser.parse();
    REQUIRE(query8.getSelect().size() == 1);

    parser = PQLParser("assign BOOLEAN; call c;Select <BOOLEAN, c>");
    auto query9 = parser.parse();
    REQUIRE(query9.getSelect().size() == 2);
}

TEST_CASE_METHOD(UnitTestFixture, "invalid result clause") {
    PQLParser parser("Select <>");
    REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

    parser = PQLParser("assign a; variable v; Select a,v ");
    REQUIRE_THROWS_AS(parser.parse(), SyntaxException);

    parser = PQLParser("Select <BOOLEAN>");
    REQUIRE_THROWS_AS(parser.parse(), SemanticException);
}

TEST_CASE_METHOD(UnitTestFixture, "not clauses") {
    PQLParser parser("constant k; read re; Select BOOLEAN with not 1 = 5 with not re.stmt# = k.value and not \"var\"= "
                     "re.varName");
    auto query1 = parser.parse();
    auto clauses = query1.getWith();
    REQUIRE(clauses[0]->isNegation());
    REQUIRE(clauses[1]->isNegation());
    REQUIRE(clauses[2]->isNegation());

    parser = PQLParser("assign a, a1; variable v; Select a such that not Uses(a, v) and not Uses(a1, v)");
    auto query2 = parser.parse();
    auto clauses2 = query2.getSuchThat();
    auto expectedStClause = QPSTestUtil::createSuchThatClause(ClauseType::Uses, RefType::StmtRef, RootType::Synonym,
                                                              QueryEntityType::Assign, "a", RefType::EntRef,
                                                              RootType::Synonym, QueryEntityType::Variable, "v");
    expectedStClause->setNegation(true);
    REQUIRE(clauses2[0]->isNegation());
    REQUIRE(*clauses2[0] == *expectedStClause);
    REQUIRE(clauses2[1]->isNegation());

    parser = PQLParser("assign a; variable v; if ifs; Select a pattern not ifs(v, _, _) and not a(v, _)");
    auto query3 = parser.parse();
    auto clauses3 = query3.getPattern();
    auto expectedPatternClause = QPSTestUtil::createPatternClause(ClauseType::Assign, "a", RootType::Synonym, "v",
                                                                  ExpressionSpecType::Wildcard, "");
    expectedPatternClause->setNegation(true);
    REQUIRE(clauses3[0]->isNegation());
    REQUIRE(clauses3[1]->isNegation());
    REQUIRE(*clauses3[1] == *expectedPatternClause);
}
