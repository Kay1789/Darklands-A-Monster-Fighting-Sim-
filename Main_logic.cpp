/*
 * Darklands RPG Game
 *
 * A text-based role-playing game where players choose a character class,
 * battle randomly encountered monsters, and manage health and attacks.
 */

#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time() to seed random numbers
#include <iostream>  // For input/output operations
#include <string>    // For string handling

// Enumeration for character types
enum CharType {
    Warrior = 1,  // Melee fighter class
    Mage,         // Magic user class
    Assassin,     // Stealth-based class
};

// Enumeration for weapon types
enum WeaponType {
    Sword = 1,    // Warrior's weapon
    Daggers,      // Assassin's weapon
    Staff,        // Mage's weapon
};

// Returns description of weapons based on WeaponType
auto getYaWeaponInfo(WeaponType wp) {
    switch (wp) {
        case Sword: return "Sword of Light";
        case Daggers: return "Daggers of Abyss";
        case Staff: return "Staff of Elements";
        default: return " That's weird i've never seen such weapon before";
    }
}

// Returns character class name based on CharType
auto getCharInfo(CharType ct) {
    switch(ct) {
        case Warrior: return "Warrior";
        case Mage: return "Mage";
        case Assassin: return "Assassin";
        default: return "That's a class I've never heard of";
    }
};

// Enumeration for monster types
enum MonsterType {
    Slime = 1,           // Basic monster
    Undead,              // Intermediate monster
    Skeleton_Soldier,    // Advanced monster
};

// Returns monster name based on MonsterType
auto getMonsterInfo(MonsterType mt) {
    switch (mt) {
        case Slime: return "Slime";
        case Undead: return "Undead";
        case Skeleton_Soldier: return "Skeleton Soldier";
        default: return "Oh No king of Monsters Appeared 😬😬";
    }
}

// Enumeration for health status levels
enum HealthInfo {
    Full_Health = 100,          // 100% health
    Slightly_Injured = 70,      // 70% health
    Injured = 50,               // 50% health
    InCriticalCondition = 20,   // 20% health
    KO = 0,                     // 0% health (dead)
};

// Returns player health status description
auto getYaHealthInfo(HealthInfo yh) {
    switch (yh) {
        case Full_Health: return "Full Health";
        case Slightly_Injured: return "Slightly Injured";
        case Injured: return "Injured";
        case InCriticalCondition: return "In Critical Condition";
        case KO: return "Dead";
        default: return "Weird Nothing Happend 🙀🙀 ";
    }
}

// Returns monster health status with numerical values
auto getMonsterHealthInfo(HealthInfo mh) {
    switch (mh) {
        case Full_Health: return "Full Health[100/71]";
        case Slightly_Injured: return "Slightly Injured[70/51]";
        case Injured: return "Injured[50]";
        case InCriticalCondition: return "In Critical Condition[20/21]";
        case KO: return "Dead[0]";
        default: return "Weird Nothing Happend 🙀🙀 ";
    }
}

// Enumeration for attack strength types
enum AttackType {
    FullStrenghtAttack = 1,   // Strongest attack
    MidStrenghtAttack = 2,    // Medium attack
    WeakStrenghtAttack = 3,   // Weakest attack
};

// Returns player attack move names
auto getYaAttackInfo(AttackType yat) {
    switch (yat) {
        case FullStrenghtAttack: return "Abyss Howl";
        case MidStrenghtAttack: return "Dark Pulse";
        case WeakStrenghtAttack: return "Void Tap";
        default: return "Uh Idk about this attack move";
    }
}

// Returns monster attack move names
auto getMonsterAttackInfo(AttackType mat) {
    switch (mat) {
        case FullStrenghtAttack: return "Strike";
        case MidStrenghtAttack: return "Bash";
        case WeakStrenghtAttack: return "Jab";
        default: return "Monster's Thoughts (dammn Idk if i can do this)";
    }
}

// Global variables for health and damage
int healthC = 100;  // Player health (intentionally high for testing)
int healthM = 100;   // Monster health
int dmgC;            // Player damage dealt
int dmgM;            // Monster damage dealt

/*
 * Creation_M class - Base class for all monsters
 * Handles monster attributes and behaviors
 */
class Creation_M {
protected:
    MonsterType mType;    // Type of monster
    HealthInfo mHealth;   // Health status
    AttackType mAttack;   // Current attack type

public:
    // Constructor
    Creation_M(MonsterType typeM, HealthInfo typeH, AttackType typeA)
        : mType(typeM), mHealth(typeH), mAttack(typeA) {}

    virtual ~Creation_M() = default;  // Virtual destructor for polymorphism

    // Getters
    auto getM_Health() const { return mHealth; }
    auto getM_Aatack() const { return mAttack; }

    // Calculates damage based on attack type
    auto get_MAttacked(AttackType mAtk) {
        mAttack = mAtk;
        switch (mAtk) {
            case FullStrenghtAttack: return 60;
            case MidStrenghtAttack: return 30;
            case WeakStrenghtAttack: return 10;
            default: std::cout << " Nothing happend Maybe the attack failed "; return 0;
        }
    }

    // Displays monster's current health status
    auto M_HealthOutput() {
        std::cout << getMonsterHealthInfo(mHealth) << "\n";
    }

    // Shows monster type
    auto showMonstertype() {
        std::cout << getMonsterInfo(mType);
    }

    // Updates monster's health level based on current HP
    void MonsterHealtLvlInfo() {
        mHealth = static_cast<HealthInfo>(healthM);
        if(healthM == 0) {
            mHealth = KO;
        } else if (healthM <= 20) {
            mHealth = InCriticalCondition;
        } else if (healthM <= 50) {
            mHealth = Injured;
        } else if (healthM <= 70) {
            mHealth = Slightly_Injured;
        } else if (healthM <= 100) {
            mHealth = Full_Health;
        }
    }

    // Applies damage to monster and updates health status
    auto Mdmgtaken(int damageM) {
        healthM -= damageM;
        if(healthM < 0) {
            healthM = 0;
        } else if(healthM > 100) {
            healthM = 100;
        }
        MonsterHealtLvlInfo();
    }

    // Pure virtual functions for monster attacks (to be implemented by derived classes)
    virtual void monster_epic_attack() = 0;    // Strongest attack
    virtual void monster_mid_attack() = 0;     // Medium attack
    virtual void monster_normie_attack() = 0;  // Basic attack
};

/*
 * Creation_C class - Base class for all player characters
 * Handles player attributes and behaviors
 */
class Creation_C {
protected:
    CharType cType;         // Character class
    HealthInfo cHealth;     // Health status
    AttackType cAttack;     // Current attack type
    WeaponType cWeapon;     // Equipped weapon
    std::string cName;      // Character name

public:
    // Constructor
    Creation_C(CharType typeC, HealthInfo typeH, WeaponType typeW, std::string typeN)
        : cType(typeC), cHealth(typeH), cWeapon(typeW), cName(typeN) {}

    virtual ~Creation_C() = default;  // Virtual destructor for polymorphism

    // Getters
    auto getC_Health() const { return cHealth; }
    auto getC_Attack() const { return cAttack; }

    // Calculates damage based on attack type
    auto getC_Attacked(AttackType cAtk) {
        cAttack = cAtk;
        switch (cAtk) {
            case FullStrenghtAttack: return 60;
            case MidStrenghtAttack: return 30;
            case WeakStrenghtAttack: return 10;
            default: std::cout << " Nothing happend Maybe the attack failed "; return 0;
        }
    }

    // Updates and displays player health level
    auto YaHealthLvlInfo() {
        cHealth = static_cast<HealthInfo>(healthC);
        std::cout << "After healing: HP = " << healthC << "\n";
        if(healthC == 0) {
            cHealth = KO;
        } else if(healthC <= 20) {
            cHealth = InCriticalCondition;
        } else if(healthC <= 50) {
            cHealth = Injured;
        } else if(healthC <= 70) {
            cHealth = Slightly_Injured;
        } else if (healthC <= 100) {
            cHealth = Full_Health;
        }
    }

    // Applies damage to player and updates health status
    auto CDmgTaken(int damageC) {
        healthC -= damageC;
        if(healthC < 0) {
            healthC = 0;
        } else if (healthC > 100) {
            healthC = 100;
        }
        YaHealthLvlInfo();
    }

    // Heals the player based on current health status
    void healingYaSelf() {
        switch (cHealth) {
            case KO: std::cout << " Already Dead 💀💀"; break;
            case InCriticalCondition: cHealth = Injured; healthC += 30; break;
            case Injured: cHealth = Slightly_Injured; healthC += 20; break;
            case Slightly_Injured: cHealth = Full_Health; healthC += 30; break;
            case Full_Health: std::cout << " Lol bro what're you thinking ya HP is already maxed out"; break;
            default: std::cout << " Idk what's happening anymore "; break;
        }
        if(healthC > 100) { healthC = 100; }
    }

    // Displays all player stats
    void displayYaStats() {
        std::cout << "================================\n";
        std::cout << "Name: " << cName << "\n";
        std::cout << "Class: " << getCharInfo(cType) << "\n";
        std::cout << "HP: " << getYaHealthInfo(cHealth) << "\n";
        std::cout << "Weapon: " << getYaWeaponInfo(cWeapon) << "\n";
        std::cout << "================================\n";
    }

    // Displays player's current health status
    void C_HealthOutput() {
        std::cout << "[" << getYaHealthInfo(cHealth) << "]\n";
    }

    // Shows character class
    void show_character_type() {
        std::cout << getCharInfo(cType);
    }

    // Pure virtual function for player attack (to be implemented by derived classes)
    virtual void yaAttack() = 0;
};

/*
 * Melee class - Warrior character class
 * Derived from Creation_C
 */
class Melee: public Creation_C {
public:
    // Constructor - sets defaults for Warrior
    Melee(std::string warrName)
        : Creation_C(Warrior, Full_Health, Sword, warrName) {}

    // Implements attack mechanism for Warrior
    void yaAttack() override {
        int x;
        std::cout << "\n===== ATTACK MENU =====\n";
        std::cout << "Choose ya Attack power:\n";
        std::cout << "1. High\n";
        std::cout << "2. Mid\n";
        std::cout << "3. Low\n";
        std::cout << "=======================\n";
        std::cout << "Your choice: ";
        std::cin >> x;
        std::cout << "\n=== WARRIOR ATTACK ===\n";
        std::cout << "Melee Attack: ";
        dmgC = getC_Attacked(static_cast<AttackType>(x));
        std::cout << getYaAttackInfo(getC_Attack()) << "\n";
        std::cout << "=====================\n";
    }
};

/*
 * Wizard class - Mage character class
 * Derived from Creation_C
 */
class Wizard: public Creation_C {
public:
    // Constructor - sets defaults for Mage
    Wizard(std::string wizName)
        : Creation_C(Mage, Full_Health, Staff, wizName) {}

    // Implements attack mechanism for Mage
    void yaAttack() override {
        int x;
        std::cout << "\n===== ATTACK MENU =====\n";
        std::cout << "Choose ya Attack power:\n";
        std::cout << "1. High\n";
        std::cout << "2. Mid\n";
        std::cout << "3. Low\n";
        std::cout << "=======================\n";
        std::cout << "Your choice: ";
        std::cin >> x;
        std::cout << "\n=== MAGE ATTACK ===\n";
        std::cout << "Magic Attack: ";
        dmgC = getC_Attacked(static_cast<AttackType>(x));
        std::cout << getYaAttackInfo(getC_Attack()) << "\n";
        std::cout << "===================\n";
    }
};

/*
 * StealthKiller class - Assassin character class
 * Derived from Creation_C
 */
class StealthKiller: public Creation_C {
public:
    // Constructor - sets defaults for Assassin
    StealthKiller(std::string stealthName)
        : Creation_C(Assassin, Full_Health, Daggers, stealthName) {}

    // Implements attack mechanism for Assassin
    void yaAttack() override {
        int x;
        std::cout << "\n===== ATTACK MENU =====\n";
        std::cout << "Choose ya Attack power:\n";
        std::cout << "1. High\n";
        std::cout << "2. Mid\n";
        std::cout << "3. Low\n";
        std::cout << "=======================\n";
        std::cout << "Your choice: ";
        std::cin >> x;
        std::cout << "\n=== ASSASSIN ATTACK ===\n";
        std::cout << "Stealth Attack: ";
        dmgC = getC_Attacked(static_cast<AttackType>(x));
        std::cout << getYaAttackInfo(getC_Attack()) << "\n";
        std::cout << "=======================\n";
    }
};

/*
 * Slime1 class - Slime monster
 * Derived from Creation_M
 */
class Slime1: public Creation_M {
public:
    // Constructor - sets defaults for Slime
    Slime1(AttackType sAttack)
        : Creation_M(Slime, Full_Health, sAttack) {}

    int mid;
    int epic;

    // Implements strongest attack for Slime
    void monster_epic_attack () override {
        std::cout << "\n=== SLIME SPECIAL ===\n";
        std::cout << "Super Slime jump!\n";
        std::cout << getMonsterAttackInfo(getM_Aatack()) << "\n";
        std::cout << "=====================\n";
    }

    // Implements medium attack for Slime
    void monster_mid_attack() override {
        std::cout << "\n=== SLIME ANGRY ===\n";
        std::cout << "Angery Slime attack pew pew!\n";
        std::cout << getMonsterAttackInfo(getM_Aatack()) << "\n";
        std::cout << "===================\n";
    }

    // Implements basic attack for Slime (random strength)
    void monster_normie_attack() override {
        std::cout << "\n=== SLIME ATTACK ===\n";
        std::cout << "Slime is Attacking: ";
        dmgM = get_MAttacked(static_cast<AttackType>(rand() % 3 + 1));
        std::cout << getMonsterAttackInfo(getM_Aatack()) << "\n";
        std::cout << "====================\n";
    }
};

/*
 * Undead1 class - Undead monster
 * Derived from Creation_M
 */
class Undead1: public Creation_M {
public:
    // Constructor - sets defaults for Undead
    Undead1(AttackType uAttack)
        : Creation_M(Undead, Full_Health, uAttack) {}

    // Implements strongest attack for Undead
    void monster_epic_attack() override {
        std::cout << "\n=== UNDEAD SPECIAL ===\n";
        std::cout << "Undead Super Slap!\n";
        std::cout << getMonsterAttackInfo(getM_Aatack()) << "\n";
        std::cout << "======================\n";
    }

    // Implements medium attack for Undead
    void monster_mid_attack() override {
        std::cout << "\n=== UNDEAD ANGRY ===\n";
        std::cout << "Undead Lame Punch!\n";
        std::cout << getMonsterAttackInfo(getM_Aatack()) << "\n";
        std::cout << "====================\n";
    }

    // Implements basic attack for Undead (random strength)
    void monster_normie_attack() override {
        std::cout << "\n=== UNDEAD ATTACK ===\n";
        std::cout << "Undead is attacking: ";
        dmgM = get_MAttacked(static_cast<AttackType>(rand() % 3 + 1));
        std::cout << getMonsterAttackInfo(getM_Aatack()) << "\n";
        std::cout << "=====================\n";
    }
};

/*
 * SkeletonSoldier1 class - Skeleton Soldier monster
 * Derived from Creation_M
 */
class SkeletonSoldier1: public Creation_M {
public:
    // Constructor - sets defaults for Skeleton Soldier
    SkeletonSoldier1(AttackType sAttack)
        : Creation_M(Skeleton_Soldier, Full_Health, sAttack) {}

    // Implements strongest attack for Skeleton Soldier
    void monster_epic_attack() override {
        std::cout << "\n=== SKELETON SPECIAL ===\n";
        std::cout << "Skeleton Super Spits!\n";
        std::cout << getMonsterAttackInfo(getM_Aatack()) << "\n";
        std::cout << "========================\n";
    }

    // Implements medium attack for Skeleton Soldier
    void monster_mid_attack() override {
        std::cout << "\n=== SKELETON ANGRY ===\n";
        std::cout << "Skeleton kick!\n";
        std::cout << getMonsterAttackInfo(getM_Aatack()) << "\n";
        std::cout << "======================\n";
    }

    // Implements basic attack for Skeleton Soldier (random strength)
    void monster_normie_attack() override {
        std::cout << "\n=== SKELETON ATTACK ===\n";
        std::cout << "Skeleton Soldier is attacking: ";
        dmgM = get_MAttacked(static_cast<AttackType>(rand() % 3 + 1));
        std::cout << getMonsterAttackInfo(getM_Aatack());
        std::cout << "\n=======================\n";
    }
};

// Global pointers for player and monster objects
Creation_C* Char = nullptr;
Creation_M* Mons = nullptr;

/*
 * Main function - Game entry point
 * Handles game flow and user interactions
 */
int main() {
    // Initialize random number generator
    std::srand(std::time(0));
    int Default = 1;

    // Display game title
    std::cout << "========================================\n";
    std::cout << "           D A R K L A N D S            \n";
    std::cout << "      The Forbidden Forest Adventure    \n";
    std::cout << "========================================\n\n";

    // ======================
    // CHARACTER CREATION
    // ======================
    std::cout << "=== CHARACTER CREATION ===\n";
    std::cout << "What's ya character's name? ";
    std::string name;
    std::getline(std::cin >> std::ws, name);  // Read name with spaces

    // Character class selection
    int choice;
    std::cout << "\n=== CHOOSE YOUR CLASS ===\n";
    std::cout << "1. Warrior\n";
    std::cout << "2. Mage\n";
    std::cout << "3. Assassin\n";
    std::cout << "=========================\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    // Create player character based on selection
    switch (choice) {
        case 1:
            Char = new Melee(name);
            std::cout << "\n=== WARRIOR CREATED ===\n";
            std::cout << "  (•_•)\n";
            std::cout << "  [⚔️]>\n";
            std::cout << "  /|\\ \n";
            std::cout << "  / \\\n";
            std::cout << "======================\n";
            break;
        case 2:
            Char = new Wizard(name);
            std::cout << "\n=== MAGE CREATED ===\n";
            std::cout << "  (o_o)\n";
            std::cout << "  <)🪄)╯\n";
            std::cout << "  /|\\ \n";
            std::cout << "  / \\\n";
            std::cout << "====================\n";
            break;
        case 3:
            Char = new StealthKiller(name);
            std::cout << "\n=== ASSASSIN CREATED ===\n";
            std::cout << "  (^_^)>\n";
            std::cout << "  <|🔪\\>\n";
            std::cout << "  / \\\n";
            std::cout << "=======================\n";
            break;
        default:
            std::cout << "\nThat's a new class lol\n";
    }

    // Display character stats
    std::cout << "\n=== YOUR CHARACTER ===\n";
    Char->displayYaStats();

    // ======================
    // GAME START
    // ======================
    std::cout << "\n=== THE ADVENTURE BEGINS ===\n";
    char ope;
    std::cout << "Wanna enter the forbidden forest?\n";
    std::cout << "[Y] Yes, I'm ready!\n";
    std::cout << "[N] No, I'm scared!\n";
    std::cout << "Your choice: ";
    std::cin >> ope;

    if(ope == 'N') {
        std::cout << "\n================================\n";
        std::cout << "You chickened out and went home!\n";
        std::cout << "Maybe next time, brave adventurer!\n";
        std::cout << "==================================\n";
        return 1;
    } else if (ope == 'Y') {
        std::cout << "\n========================================\n";
        std::cout << "You bravely step into the dark forest...\n";
        std::cout << "The trees whisper secrets as you walk...\n";
        std::cout << "Suddenly, a monster appears!\n";
        std::cout << "========================================\n";

        // Randomly select a monster type
        int MonsType = rand() % 3 + 1;

        // Create monster based on random selection
        if(MonsType == 1) {
            Mons = new Slime1(static_cast<AttackType>(Default));
            std::cout << "\n=== MONSTER ENCOUNTER ===\n";
            std::cout << "Oh no! It's a ";
            Mons->showMonstertype();
            std::cout << "!\n";
            std::cout << "  ( oo )\n";
            std::cout << " /||\\\n";
            std::cout << "   vv vv\n";
            std::cout << "=======================\n";
        } else if(MonsType == 2) {
            Mons = new Undead1(static_cast<AttackType>(Default));
            std::cout << "\n=== MONSTER ENCOUNTER ===\n";
            std::cout << "Oh no! It's an ";
            Mons->showMonstertype();
            std::cout << "!\n";
            std::cout << "  (x_x)\n";
            std::cout << " /|||\\\n";
            std::cout << "  /   \\\n";
            std::cout << "=======================\n";
        } else if(MonsType == 3) {
            Mons = new SkeletonSoldier1(static_cast<AttackType>(Default));
            std::cout << "\n=== MONSTER ENCOUNTER ===\n";
            std::cout << "Oh no! It's a ";
            Mons->showMonstertype();
            std::cout << "!\n";
            std::cout << "  [o_o]\n";
            std::cout << "  /] [\\\n";
            std::cout << "  / | \\\n";
            std::cout << "=======================\n";
        }

        char op;
        int tryo = 2;  // Number of healing potions

        // ======================
        // BATTLE LOOP
        // ======================
        while(true) {
            std::cout << "\n=== BATTLE PHASE ===\n";

            // Player's turn to attack
            Char->yaAttack();

            // Apply damage to monster and show health status
            std::cout << "\n=== MONSTER STATUS ===\n";
            Mons->Mdmgtaken(dmgC);
            std::cout << "Health: ";
            Mons->M_HealthOutput();
            std::cout << "======================\n";

            // Check if monster is defeated
            if(Mons->getM_Health() == KO) {
                break;
            }

            // Monster's turn to attack - chooses attack based on health
            std::cout << "\n=== MONSTER'S TURN ===\n";
            if(Mons->getM_Health() == Full_Health) {
                // Basic attack when at full health
                Mons->monster_normie_attack();
            } else if (Mons->getM_Health() == Injured) {
                // Medium attack when injured
                Mons->monster_mid_attack();
            } else if (Mons->getM_Health() == InCriticalCondition) {
                // Strongest attack when in critical condition
                Mons->monster_epic_attack();
            }

            // Apply damage to player and show health status
            std::cout << "\n=== YOUR STATUS ===\n";
            std::cout << "Ya ";
            Char->show_character_type();
            std::cout << "'s Health: ";
            Char->CDmgTaken(dmgM);
            Char->C_HealthOutput();
            std::cout << "===================\n";

            // Check if player is defeated
            if(Char->getC_Health() == KO) {
                break;
            }

            // Offer healing when health is low
            if(Char->getC_Health() <= Slightly_Injured) {
                std::cout << "\n=== HEALING OPTION ===\n";
                std::cout << "Warning! Your health is low!\n";
                std::cout << "Potions remaining: " << tryo << "\n";
                std::cout << "Use a healing potion?\n";
                std::cout << "[Y] Yes\n";
                std::cout << "[N] No\n";
                std::cout << "======================\n";
                std::cout << "Your choice: ";
                std::cin >> op;

                if(op == 'Y' || op == 'y') {
                    if(tryo == 0) {
                        std::cout << "\n=== NO POTIONS LEFT ===\n";
                        std::cout << "You're out of healing potions!\n";
                        std::cout << "==============================\n";
                        continue;
                    }
                    std::cout << "\n=== HEALING ===\n";
                    Char->healingYaSelf();
                    tryo--;
                    std::cout << "Potions left: " << tryo << "\n";
                    std::cout << "Current HP: ";
                    Char->C_HealthOutput();
                    std::cout << "===============\n";
                }
            }
        }

        // ======================
        // BATTLE CONCLUSION
        // ======================
        std::cout << "\n=== BATTLE END ===\n";
        if(Mons->getM_Health() == KO) {
            std::cout << "VICTORY! The ";
            Mons->showMonstertype();
            std::cout << " has been defeated!\n";
            std::cout << "You emerge victorious from the battle!\n";
        } else if (Char->getC_Health() == KO) {
            std::cout << "DEFEAT! Ya ";
            Char->show_character_type();
            std::cout << " has fallen in battle...\n";
            std::cout << "The dark forest claims another victim...\n";
        }
        std::cout << "==================\n";
    }

    // Clean up memory
    delete Mons;
    delete Char;

    std::cout << "\n================================\n";
    std::cout << "   T H A N K   Y O U   F O R   \n";
    std::cout << "      P L A Y I N G            \n";
    std::cout << "        D A R K L A N D S      \n";
    std::cout << "================================\n";

    return 0;
}
