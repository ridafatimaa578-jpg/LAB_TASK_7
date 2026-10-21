# Table No. 2: Code Review Report

| Line | Defect Type | Why it is a problem | Proposed solution | Severity |
|------|-------------|---------------------|-------------------|----------|
| 27 | Initialization | The pointer array holds garbage values until filled | `Monster* monsters[MAX_MONSTERS] = {};` | Low |
| 41 | Buffer overflow | No check that `monsterCount < MAX_MONSTERS`; writing past the array corrupts memory | Check the count first; return `false` if full | High |
| 47 | Control flow (`=` vs `==`) | Assigns instead of comparing; always true, so the first monster is returned and its id is overwritten | `if (monsters[i]->id == id)` | High |
| 54, 58 | Null pointer dereference | `findMonster` may return `nullptr`, and `m->health` then crashes | `if (!m) return -1;` | High |
| 55-56 | Arithmetic (signed/unsigned) | `dmg` is unsigned, so `health - dmg < 0` is never true | Use `int`: `if (m->health - damage < 0)` | Medium |
| 64 | Loop off-by-one | `i == monsterCount` reads an unused slot (undefined behavior) | `i < monsterCount` | High |
| 70-73 | Dangling reference | Returning a reference to local `label` is undefined behavior | Return `std::string` by value | High |
| 71-72 | Null pointer dereference | `m` is used without a null check | Add a `nullptr` check | High |
| 77 | Uninitialized variable | `sum` has an indeterminate value, so the result is garbage | `double sum = 0;` | High |
| 80 | Division by zero / narrowing | Divides by zero when there are no monsters; `double` result truncated to `int` | Guard `monsterCount == 0`; return `double` | Medium |
| 84 | Null pointer dereference | `m` is used in `delete` and `m->name` without a check | Check `m` first | Medium |
| 85 | Dangling pointer / double free | The array still holds the freed pointer; the destructor deletes it again | Remove it from the array and decrement `monsterCount` | High |
| 86 | Use after free | `m->name` is read after `delete m` | Print first, then delete | High |
| 91 | Arithmetic (integer division) | `attack * armorPercent / 100` loses the fraction and may overflow | `attack * (armorPercent / 100.0)` | Medium |
| 94-99 | Control flow (missing return) | No return when `score <= 100`; undefined behavior | Add `return 3;` at the end | High |
| 102, 105 | Buffer overflow | `cin >> name` overflows the 10-char buffer on long input | Use `std::string name;` | High |
| 103, 107 | Initialization / input | `health` stays uninitialized if the read fails | `int health = 0;` and check `if (!(std::cin >> health))` | Medium |
| 109 | Wrong deallocation | Memory from `new[]` must be freed with `delete[]` | Use `std::string` instead of a raw array | Medium |
| 119 | Buffer overflow (caller) | The 6th `spawnMonster` exceeds `MAX_MONSTERS = 5` | Remove it, or raise the limit and keep the bounds check | High |
| 121 | Memory leak | `bonus` is never deleted | `delete bonus;` or do not allocate it | Medium |
| 123 | Function call / null pointer | ID 99 does not exist, so `findMonster` returns `nullptr` and the call crashes | Handle the not-found case | High |
| 133 | Class (shallow copy) | The default copy shares pointers, so both destructors delete the same objects | Delete the copy operations or implement a deep copy | High |
| 12-15, 17-22 | Class design | Public data members and no initializer list | Use an initializer list; make members private | Low |
