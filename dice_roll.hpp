#ifndef _DICEROLL
#define _DICEROLL

#include <map>
#include <string>
#include <vector>

using namespace std;

struct RollResult {
    string rule;
    int score;
};

class DiceRoll {
    public:
        DiceRoll(int results[6], int n_die, int n_sides);
        void printCounter();
        int sumAtN(int n);
        int fullHouseSum();
        int fiveOfAKindSum();
        int smallStraight();
        int straight();
        int timbre();
        void getBestCategories();
    
    private:
        int n_dice;
        int n_sides;
        int results[6];
        map<int, int> resultCounter;
        vector<RollResult> getResults();
};

#endif