# System Testing for SPA by Team 14

## Folder Structure
The system test files are stored in subdirectories according to milestones (i.e. milestone1, milestone2 and milestone3)

## milestone1 test cases
The following are the subdirectories for `/milestone1`.
- QPS_multi_clause
  - Tests the combination of one such-that clause with one pattern clause.
- QPS_single_clause
  - Tests each such that clause individually.
  - Tests each pattern clause individually (assign pattern).
- SIMPLE_bad_syntax
  - Tests SIMPLE program with Syntax Error.
  - Note: The `_queries.txt` files in this subdirectory is empty as program would have terminated due to Syntax Error while parsing SIMPLE program.
- SIMPLE_minimal
  - Tests each statement type individually.
- SIMPLE_typical
  - Tests common and edge SIMPLE program to ensure that our program can handle the cases.