#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono> // for sleep
#include <thread> // for sleep

using namespace std;

class Players {
    public:
        Players(int RerollAmount, int Score, int LocalScore) {
            amt_to_reroll = RerollAmount;
            score = Score;
            localscore = LocalScore;
        }
        void reset(int RerollAmount, int LocalScore) {
            amt_to_reroll = RerollAmount;
            localscore = LocalScore;
        }
        string playerType;
        vector<int> score_and_amt_to_keep;
        vector<int> rolls;
        char res;
        int score;
        int localscore;
        int amt_to_reroll;
};

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
vector<int> CalculateScore(vector<int> rolls, int dice_amount) {
    int score = 0;
    int straight16 = 0;
    int three_pairs = 0;
    int triplets = 0;
    int dice_amt_to_keep = 0;
    bool four_pairs = false;
    vector<int> number_frequency(6); // frequency table should always have 6 slots
    vector<int> score_and_amt_to_keep = {score, 6};

    //build frequency vector
    for(int i = 0; i < dice_amount; i++) {
        number_frequency[rolls[i] - 1]++; // -1 as vectors are 0 indexed (0-5) but our dice rolls are 1-6
    }

    //print frequency vector for debugging
    // for(int i = 0; i < 6; i++) {
    //     cout << number_frequency[i];
    // }
    // cout << endl;

    // These are ran outside main score loop as they only need to be checked once
    if(number_frequency[0] == 2) {
        score += 200;
        dice_amt_to_keep += 2;
    }
    if(number_frequency[4] == 2) {
        score += 100;
        dice_amt_to_keep += 2;
    }

    for(int i = 0; i < 6; i++) {
        //Six of a kind check, four pairs check, Three Pairs monitor, 2x Triplets monitor
        if(dice_amount == 6) {
            if(number_frequency[i] == 6) {
                score += 3000;
                score_and_amt_to_keep = {score, 6};
                return score_and_amt_to_keep;
            }
            if(number_frequency[i] == 2) {
                three_pairs++;
            }
            if(number_frequency[i] == 4) {
                four_pairs = true;
                score += 1000;
                dice_amt_to_keep += 4;
            }
            if(number_frequency[i] == 3) {
                triplets += 1;
            }
        }

        //3+, 4+, 5+ dice checks
        if(dice_amount >= 3) {
            // 3 of a kind check
            if(number_frequency[i] == 3) {
                dice_amt_to_keep += 3;
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
                        score_and_amt_to_keep = {-1, -1};
                        return score_and_amt_to_keep;
                }
            }

            if(number_frequency[i] == 4) {
                score += 1000;
                dice_amt_to_keep += 4;
            }

            if(number_frequency[i] == 5) {
                score += 2000;
                dice_amt_to_keep += 5;
            }
        }

        //Straight 1-6 monitor and single 1 or 5 check
        if(number_frequency[i] == 1) {
            straight16++;
            if(i == 0) {
                score += 100;
                dice_amt_to_keep += 1;
            }
            else if(i == 4) {
                score += 50;
                dice_amt_to_keep += 1;
            }
        }
    }

    if(triplets == 2) {
        score = 2500;
        score_and_amt_to_keep = {score, 6};
        return score_and_amt_to_keep;
    }

    if(four_pairs == true && three_pairs == 1) {
        score = 1500;
        score_and_amt_to_keep = {score, 6};
        return score_and_amt_to_keep;
    }

    if(straight16 == 6 || three_pairs == 3) {
        score = 1500;
        score_and_amt_to_keep = {score, 6};
        return score_and_amt_to_keep;
    }

    score_and_amt_to_keep = {score, dice_amt_to_keep};
    return score_and_amt_to_keep;
}

void PrintRolls(vector<int> rolls, int dice_amount) {
    cout << "Your roll is: [";
    for(int i = 0; i < dice_amount; i++) {
            cout << rolls[i];
            if(i < dice_amount - 1) {
                cout << " ";
            }
    }
    cout << "]";
    cout << endl;
}

char aiDecision(int amt_to_reroll, int score, int localscore) {
    if(score == 0 and localscore < 500) {
        return 'r';
    }
    return 'r';
}

int main () {

    Players human1(6, 0, 0);
    Players AI(6, 0, 0);
    char turn = 'h';

    cout << "Welcome to Farkle!" << endl;

    while(human1.score < 10000 || AI.score < 10000) {
        
        srand(time(NULL)); // random seed

        while(turn == 'h') {

            if(human1.score == 0) {
                cout << "Type 'r' to roll dice." << endl;
            }
            else {
                cout << "Type 'r' to roll dice, or 's' to save your score and start a new roll." << endl;
            }
            cin >> human1.res;
        
        
            if(human1.res == 'r') {
                cout << "Rolling dice!" << endl;

                human1.rolls = Roll(human1.amt_to_reroll);
                PrintRolls(human1.rolls, human1.amt_to_reroll);
                human1.score_and_amt_to_keep = CalculateScore(human1.rolls, human1.amt_to_reroll);

                if(human1.score_and_amt_to_keep[0] == 0) {
                    cout << "Farkle. All points on this roll run lost." << endl;
                    human1.reset(6, 0);
                    turn = 'a';
                }
                else {
                    cout << "Your roll scored: " << human1.score_and_amt_to_keep[0] << endl;
                    cout << "Your current amount of roll points on this turn is: " << human1.localscore << " + " << human1.score_and_amt_to_keep[0] << " = " << human1.localscore + human1.score_and_amt_to_keep[0] << endl;

                    human1.amt_to_reroll -= human1.score_and_amt_to_keep[1];
                    human1.localscore += human1.score_and_amt_to_keep[0];

                    if(human1.amt_to_reroll > 0) { //if we have at least one dice to roll, tell user
                        cout << "You need to re-roll " << human1.amt_to_reroll  << " dice." << endl;
                    }
                    else if(human1.amt_to_reroll == 0) {
                        cout << "You have no additional dice to roll. Points have been auto saved." << endl;
                        human1.score += human1.localscore;
                        human1.reset(6,0);
                        turn = 'a';
                    }
                }
            }

            else if(human1.res == 's') {
                if(human1.score == 0 && human1.localscore < 500) {
                    cout << "You must score at least 500 points to begin the game and start saving points." << endl;
                }
                else {
                    human1.score += human1.localscore;
                    human1.reset(6, 0);
                    turn = 'a';
                }
            }

            else if(human1.res == 'q') {
                exit(0);
            }

            else {
                cout << "invalid char" << endl;
            }

            cout << "Total score is: " << human1.score << endl;
        }

        if(turn == 'a') {
            cout << "It is turn of AI!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            char action = aiDecision(AI.amt_to_reroll, AI.score, AI.localscore);
            cout << "AI chose to: " << action << endl;
            turn = 'h';
        }
    }   

    cout << "Final Score: " << human1.score << endl;
   
    return 0;
}