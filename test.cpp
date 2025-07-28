#include <iostream>
#include <vector>

using namespace std;

vector<int> Roll(int dice_amount) {
    vector<int> rolls(dice_amount);
    for(int i = 0; i < dice_amount; i++) {
        rolls[i] = (rand() % 6) + 1;
    }
    return rolls;
}
/*
REMEMBER as vector's are 0 indexed, rolls are stored as follows:
Roll # | Position in Vector
    1  |   0
    2  |   1
    3  |   2
    4  |   3
    5  |   4
    6  |   5
*/
int CalculateScore(vector<int> rolls, int dice_amount) {
    int score = 0;
    int straight16 = 0;
    int three_pairs = 0;
    int triplets = 0;
    bool four_pairs = false;
    vector<int> number_frequency(6); // frequency table should always have 6 slots

    //build frequency vector
    for(int i = 0; i < dice_amount; i++) {
        number_frequency[rolls[i] - 1]++; // -1 as vectors are 0 indexed (0-5) but our dice rolls are 1-6
    }

    //print frequency vector for debugging
    for(int i = 0; i < 6; i++) {
        cout << number_frequency[i];
    }
    cout << endl;

    // These are ran outside main score loop as they only need to be checked once
    if(number_frequency[0] == 2) {
        score += 200;
    }
    if(number_frequency[4] == 2) {
        score += 100;
    }

    for(int i = 0; i < 6; i++) {
        //Six of a kind check, four pairs check, Three Pairs monitor, 2x Triplets monitor
        if(dice_amount == 6) {
            if(number_frequency[i] == 6) {
                score += 3000;
                return score;
            }
            if(number_frequency[i] == 2) {
                three_pairs++;
            }
            if(number_frequency[i] == 4) {
                four_pairs = true;
                score += 1000;
            }
            if(number_frequency[i] == 3) {
                triplets += 1;
            }
        }

        //3+, 4+, 5+ dice checks
        if(dice_amount >= 3) {
            // 3 of a kind check
            if(number_frequency[i] == 3) {
                switch(i) {
                    case 0:
                        score += 300;
                        break;
                    case 1:
                        score += 200;
                        break;
                    case 2:
                        score += 300;
                        break;
                    case 3:
                        score += 400;
                        break;
                    case 4:
                        score += 500;
                        break;
                    case 5:
                        score += 600;
                        break;
                    default:
                        cout << "Error, i exceeded 5 in CalculateScore";
                        return 7;
                }
            }

            if(number_frequency[i] == 4) {
                score += 1000;
            }

            if(number_frequency[i] == 5) {
                score += 2000;
            }
        }

        //Straight 1-6 monitor and single 1 or 5 check
        if(number_frequency[i] == 1) {
            straight16++;
            if(i == 0) {
                score += 100;
            }
            else if(i == 4) {
                score += 50;
            }
        }
    }

    if(triplets == 2) {
        score = 2500;
        return score;
    }

    if(four_pairs == true && three_pairs == 1) {
        score = 1500;
        return score;
    }

    if(straight16 == 6 || three_pairs == 3) {
        score = 1500;
        return score;
    }

    return score;
}

void PrintRolls(vector<int> rolls, int dice_amount) {
    for(int i = 0; i < dice_amount; i++) {
            cout << rolls[i];
    }
    cout << endl;
}

int main () {

    char res;
    cout << "Type 'r' to roll dice." << endl;
    cin >> res;
    if(res == 'r') {
        cout << "rolling dice!" << endl;

        // vector<int> rolls = Roll(6);
        // PrintRolls(rolls);
        // int score = CalculateScore(rolls, 6);

        //DEBUGGING
        vector<int> rolls = {1, 1, 4, 5, 5, 5};
        PrintRolls(rolls, 6);
        int score = CalculateScore(rolls, 6);
        cout << score;
    }
    else {
        cout << "invalid char" << endl;
    }
    return 0;
}