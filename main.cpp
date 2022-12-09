#include <iostream>
#include <string>

#include "dice_roll.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    int n_dice = 6;
    int n_sides = 8;

    if (argc != n_dice+1) {
        printf("Not a valid round: please roll %dd%d.\n", n_dice, n_sides);
        return 1;
    }

    int results[n_dice];
    for (int i=0; i<n_dice; i++) {
        string arg_curr = argv[i+1];
        if (arg_curr.length() > 1) {
            cout << "Found an invalid die roll: " << arg_curr << endl;
            return 1;
        }

        int result = stoi(arg_curr);
        if (result > n_sides) {
            cout << "Found an invalid die roll: " << result << endl;
            return 1;
        }
        results[i] = result;
    }

    DiceRoll roll = DiceRoll(results, n_dice, n_sides);
    roll.getBestCategories();

    return 0;
}
