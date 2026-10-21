# Table No. 1: Review Checklist

| # | Category | Result | Defect |
|---|----------|--------|--------|
| 1 | Initialization | **Issue** | `double sum` is uninitialized (L77); `monsters[]` is uninitialized (L27); `health` is read without checking input success (L103, L107) |
| 2 | Pointer (Null / defect) | **Issue** | `findMonster` may return `nullptr` and callers do not check it (L54, L71, L84); use after free (L85-86); dangling pointer left in array (L85); `bonus` is leaked (L121) |
| 3 | Arrays / buffers | **Issue** | No bounds check in `spawnMonster` (L41); a 6th monster is spawned (L119); `char name[10]` can be overflowed by `cin` (L102, L105) |
| 4 | Loops | **Issue** | Off-by-one error: `i <= monsterCount` (L64) |
| 5 | Arithmetic | **Issue** | Signed/unsigned mix makes the check always false (L55-56); integer division (L91); division by zero (L80); `double` truncated to `int` (L80) |
| 6 | Control flow | **Issue** | `=` used instead of `==` (L47); `playerRank` has a path with no return (L94-99) |
| 7 | Function call | **Issue** | Returns a reference to a local variable (L70-73); `delete` used instead of `delete[]` (L109); call with non-existent ID 99 (L123) |
| 8 | Classes | **Issue** | Rule of Three violated; `Game copy = game;` causes a double delete (L133); public data members (L12-15); no initializer list (L17-22) |
