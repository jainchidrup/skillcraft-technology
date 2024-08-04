#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 1 and 100
    int randomNumber = rand() % 100 + 1;
    int userGuess = 0;

    cout << "I have generated a random number between 1 and 100." << endl;
    cout << "Can you guess what it is?" << endl;

    // Loop until the user guesses the correct number
    while (true) {
        cout << "Enter your guess: ";
        cin >> userGuess;

        if (userGuess < randomNumber) {
            cout << "Too low. Try again!" << endl;
        } else if (userGuess > randomNumber) {
            cout << "Too high. Try again!" << endl;
        } else {
            cout << "Congratulations! You guessed the number!" << endl;
            break;
        }
    }

    return 0;
}

