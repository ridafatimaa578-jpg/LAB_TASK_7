# SVV Lab: Static Verification of C++ Code

## 1. Objective
Perform static verification of `game.cpp`: find defects without running the program, record them in a review checklist and a code review report, and fix them.

## 2. Tools Used
- Manual code review (checklist based)
- cppcheck
- clang-tidy
- g++ with `-Wall -Wextra` and AddressSanitizer

## 3. Deliverables
- [Table No. 1: Review Checklist](reports/table1_review_checklist.md)
- [Table No. 2: Code Review Report](reports/table2_code_review_report.md)
- [Original code: src/game.cpp](src/game.cpp)
- [Fixed code: src/game_fixed.cpp](src/game_fixed.cpp)

## 4. How to Run Static Analysis

```bash
cppcheck --enable=all --inconclusive --std=c++17 src/game.cpp
clang-tidy src/game.cpp -- -std=c++17
g++ -Wall -Wextra -fsanitize=address,undefined -g src/game.cpp -o game
```

## 5. Conclusion
The original `game.cpp` had defects in all 8 checklist categories. The most severe were null pointer dereferences, buffer overflows, use after free, and uninitialized variables. The fixed version (`src/game_fixed.cpp`) addresses all of them.
