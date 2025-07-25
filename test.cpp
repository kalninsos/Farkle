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

int CalculateScore(vector<int> rolls) {
    int score = 0;
    int straight16 = 0;
    vector<int> number_frequency(6); // should always be 6 dice

    //build frequency vector
    for(int i = 0; i < 6; i++) {
        number_frequency[rolls[i] - 1]++; // -1 as vectors are 0 indexed (0-5) but our dice rolls are 1-6
    }

    //print frequency vector for debugging
    for(int i = 0; i < 6; i++) {
        cout << number_frequency[i];
    }
    cout << endl;

    for(int i = 0; i < 6; i++) {
        if(number_frequency[i] == 1) {
            straight16++; //1-6 straight check
            if(i == 1) {
                score += 100;
            }
            else if(i == 5) {
                score += 50;
            }
        }
    }

    if(straight16 == 6) {
        score = 1500;
    }

    return score;
}

void PrintRolls(vector<int> rolls) {
    for(int i = 0; i < 6; i++) {
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

        vector<int> rolls = Roll(6);
        PrintRolls(rolls);
        int score = CalculateScore(rolls);
    }
    else {
        cout << "invalid char" << endl;
    }
    return 0;
}