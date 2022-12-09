#include <iostream>
#include <vector>
#include <string>

#include "dice_roll.hpp"

using namespace std;

DiceRoll::DiceRoll(int results[6], int n_dice, int n_sides) {
    this->n_dice = n_dice;
    this->n_sides = n_sides;
    
    for (int i=1; i<n_sides+1; i++) {
        resultCounter[i] = 0;
    }

    for (int i=0; i<n_dice; i++) {
        int roll_i = results[i];
        this->results[i] = roll_i;
        resultCounter[roll_i]++;
    }
}

void DiceRoll::printCounter() {
    for (int i=1; i<n_sides+1; i++) {
        cout << i << ": " << resultCounter[i] << endl;
    }
}

int DiceRoll::sumAtN(int n) {
    return resultCounter[n] * n;
}

int DiceRoll::fullHouseSum() {
    vector<int> at_least_2;
    vector<int> at_least_3;

    // assumes only one full house in a round is possible
    for (int i=1; i<n_sides+1; i++) {
        if (resultCounter[i] >= 2) {
            at_least_2.push_back(i);
        }
        if (resultCounter[i] >= 3) {
            at_least_3.push_back(i);
        }
    }

    if (at_least_2.size() > 0 && at_least_3.size() > 0) {
        int best_3 = at_least_3.back();
        for (int i=at_least_2.size()-1; i>-1; i--) {
            int best_2 = at_least_2[i];
            if (best_2 != best_3) {
                return best_3 * 3 + best_2 * 2;
            }
        }
    }

    return 0;
}

int DiceRoll::fiveOfAKindSum() {
    // Assumes only one 'five of a kind' per round
    for (int i=1; i<n_sides+1; i++) {
        if (resultCounter[i] >= 5) {
            return resultCounter[i] * i;
        }
    }

    return 0;
}

int DiceRoll::smallStraight() {
    int n_ascending = 0;
    for (int i=1; i<n_dice; i++) {
        if (results[i-1] + 1 == results[i]) {
            n_ascending++;
        } else {
            n_ascending = 0;
        }

        if (n_ascending == 4) {
            return 30;
        }
    }

    return 0;
}

int DiceRoll::straight() {
    int n_ascending = 0;
    for (int i=1; i<n_dice; i++) {
        if (results[i-1] + 1 == results[i]) {
            n_ascending++;
        } else {
            n_ascending = 0;
        }

        if (n_ascending >= 5) {
            return 40;
        }
    }
    return 0;
}

int DiceRoll::timbre() {
    for (int i=1; i<n_sides+1; i++) {
        if (resultCounter[i] == n_dice) {
            return 50;
        }
    }
    return 0;
}

vector<RollResult> DiceRoll::getResults() {
    // sums at N
    vector<RollResult> results;
    results.push_back({"Ones", sumAtN(1)});
    results.push_back({"Twos", sumAtN(2)});
    results.push_back({"Threes", sumAtN(3)});
    results.push_back({"Fours", sumAtN(4)});
    results.push_back({"Fives", sumAtN(5)});
    results.push_back({"Sixes", sumAtN(6)});
    results.push_back({"Sevens", sumAtN(7)});
    results.push_back({"Eights", sumAtN(8)});

    // special rules
    results.push_back({"Full House", fullHouseSum()});
    results.push_back({"Five-of-a-kind", fiveOfAKindSum()});
    results.push_back({"Small Straight", smallStraight()});
    results.push_back({"Straight", straight()});
    results.push_back({"Timbre!", timbre()});

    return results;
}

void DiceRoll::getBestCategories() {
    vector<RollResult> results = getResults();
    int max_score = 0;

    for (RollResult r : results) {
        max_score = max(max_score, r.score);
    }

    vector<string> bestCategories;
    for (RollResult r : results) {
        if (r.score == max_score) {
            bestCategories.push_back(r.rule);
        }
    }

    if (bestCategories.size() == 1) {
        printf("Your best category was: %s. You scored %d points!\n", bestCategories[0].c_str(), max_score);
    } else {
        string joined;
        for (int i=0; i<bestCategories.size()-1; i++) {
            joined = joined + bestCategories[i] + " and ";
        }
        joined = joined + bestCategories.back();
        printf("Your best categories were: %s. You scored %d points!\n", joined.c_str(), max_score);
    }
}
