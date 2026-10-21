// game_fixed.cpp - corrected version after static review
#include <iostream>
#include <string>
#include <utility>

const int MAX_MONSTERS = 5;

struct Monster {
    int id;
    std::string name;
    int health;
    int attack;

    Monster(int i, std::string n, int h, int a)
        : id(i), name(std::move(n)), health(h), attack(a) {}
};

class Game {
private:
    Monster* monsters[MAX_MONSTERS] = {};
    int monsterCount = 0;

public:
    Game() = default;
    Game(const Game&) = delete;             // prevent shallow copy
    Game& operator=(const Game&) = delete;

    ~Game() {
        for (int i = 0; i < monsterCount; i++)
            delete monsters[i];
    }

    bool spawnMonster(int id, std::string name, int health, int attack) {
        if (monsterCount >= MAX_MONSTERS) return false;   // bounds check
        monsters[monsterCount++] = new Monster(id, std::move(name), health, attack);
        return true;
    }

    Monster* findMonster(int id) {
        for (int i = 0; i < monsterCount; i++)
            if (monsters[i]->id == id)                    // == not =
                return monsters[i];
        return nullptr;
    }

    int attackMonster(int id, int damage) {
        Monster* m = findMonster(id);
        if (!m) return -1;                                // null check
        if (m->health - damage < 0) { m->health = 0; return 0; }
        m->health -= damage;
        return m->health;
    }

    int totalMonsterHealth() const {
        int total = 0;
        for (int i = 0; i < monsterCount; i++)            // < not <=
            total += monsters[i]->health;
        return total;
    }

    std::string getMonsterLabel(int id) {                 // by value
        Monster* m = findMonster(id);
        if (!m) return "Unknown";
        return "Monster-" + std::to_string(m->id) + ":" + m->name;
    }

    double averageAttack() const {
        if (monsterCount == 0) return 0.0;
        double sum = 0.0;                                 // initialized
        for (int i = 0; i < monsterCount; i++)
            sum += monsters[i]->attack;
        return sum / monsterCount;
    }

    void defeatMonster(int id) {
        for (int i = 0; i < monsterCount; i++) {
            if (monsters[i]->id == id) {
                std::cout << "Defeated " << monsters[i]->name << "\n"; // print before delete
                delete monsters[i];
                monsters[i] = monsters[monsterCount - 1];  // remove from array
                monsters[monsterCount - 1] = nullptr;
                monsterCount--;
                return;
            }
        }
        std::cout << "Monster not found\n";
    }
};

double calculateDamage(int attack, int armorPercent) {
    return attack * (armorPercent / 100.0);
}

int playerRank(int score) {
    if (score > 1000) return 1;
    else if (score > 100) return 2;
    return 3;                                             // all paths return
}

void readBoss(Game& game) {
    std::string name;                                     // no raw buffer
    int health = 0;
    std::cout << "Enter boss name: ";
    std::cin >> name;
    std::cout << "Enter boss health: ";
    if (!(std::cin >> health)) { std::cout << "Invalid health\n"; return; }
    if (!game.spawnMonster(100, name, health, 50))
        std::cout << "Monster list full\n";
}

int main() {
    Game game;
    game.spawnMonster(1, "Goblin", 30, 5);
    game.spawnMonster(2, "Orc", 60, 12);
    game.spawnMonster(3, "Skeleton", 40, 8);
    game.spawnMonster(4, "Troll", 90, 20);
    game.spawnMonster(5, "Dragon", 200, 45);
    if (!game.spawnMonster(6, "Bat", 10, 3))
        std::cout << "Cannot spawn Bat: list full\n";

    std::cout << "Attack: " << game.attackMonster(99, 20) << "\n";
    std::cout << "Label: " << game.getMonsterLabel(2) << "\n";
    std::cout << "Total health: " << game.totalMonsterHealth() << "\n";
    std::cout << "Average attack: " << game.averageAttack() << "\n";
    std::cout << "Damage: " << calculateDamage(80, 25) << "\n";
    std::cout << "Rank: " << playerRank(50) << "\n";

    game.defeatMonster(3);
    readBoss(game);
    return 0;      // Game copy = game; removed (copy is now deleted)
}
