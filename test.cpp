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

int main () {

    char res;
    cout << "Type 'r' to roll dice." << endl;
    cin >> res;
    if(res == 'r') {
        cout << "rolling dice!" << endl;

        vector<int> rolls = Roll(6);

        for(int i = 0; i < 6; i++) {
            cout << rolls[i];
        }
        
    }
    else {
        cout << "invalid char" << endl;
    }
    return 0;
}