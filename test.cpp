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
    int score;
    vector<int> number_frequency(6); // should always be 6 dice

    for(int i = 0; i < 6; i++) {
        number_frequency[rolls[i] - 1]++; // -1 as vectors are 0 indexed (0-5) but our dice rolls are 1-6
    }

    for(int i = 0; i < 6; i++) {
        cout << number_frequency[i];
    }

    return score;
}

void PrintScore(vector<int> rolls) {
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
        PrintScore(rolls);
        int score = CalculateScore(rolls);

    }
    else {
        cout << "invalid char" << endl;
    }
    return 0;
}