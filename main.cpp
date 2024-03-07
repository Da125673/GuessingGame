#include <iostream>
#include <cstdlib> // For rand() and srand() functions
#include <ctime>   // For time() function
#include <vector>  // For storing leaderboard

using namespace std;

// Achievement structure
struct Achievement {
    string name;
    string description;
    int condition; // Condition to unlock achievement
    int reward;    // Reward for unlocking achievement
    bool unlocked; // Whether the achievement has been unlocked
};

// Function to check and unlock achievements
void checkAchievements(int attempts, int score, vector<Achievement>& achievements) {
    for (auto& achievement : achievements) {
        if (!achievement.unlocked && attempts <= achievement.condition) {
            cout << "Achievement Unlocked: " << achievement.name << " - " << achievement.description << endl;
            cout << "Reward: " << achievement.reward << " bonus points!" << endl;
            score += achievement.reward;
            achievement.unlocked = true;
        }
    }
}

void printWelcomeMessage() {
    cout << "===================================" << endl;
    cout << "       Welcome to the Guessing Game!" << endl;
    cout << "===================================" << endl;
    cout << "I have selected a number." << endl;
    cout << "Let's begin!" << endl;
}

void printGameOverMessage() {
    cout << "===================================" << endl;
    cout << "            Game Over!" << endl;
    cout << "===================================" << endl;
}

void printTryAgainMessage() {
    cout << "Do you want to play again? (y/n): ";
}

void printTooLowMessage() {
    cout << "Your guess is too low. Try a higher number." << endl;
}

void printTooHighMessage() {
    cout << "Your guess is too high. Try a lower number." << endl;
}

void printCongratsMessage(int secretNumber, int attempts) {
    cout << "Congratulations! You guessed the correct number (" << secretNumber << ") in " << attempts + 1 << " attempts!" << endl;
}

void printHint(int secretNumber) {
    cout << "Hint: The number is ";
    if (secretNumber % 2 == 0) {
        cout << "even. ";
    } else {
        cout << "odd. ";
    }

    if (secretNumber % 10 == 0) {
        cout << "It's divisible by 10.";
    } else if (secretNumber % 5 == 0) {
        cout << "It's divisible by 5.";
    } else if (secretNumber % 3 == 0) {
        cout << "It's divisible by 3.";
    }
    cout << endl;
}

void printLeaderboard(const vector<pair<string, int>>& leaderboard) {
    cout << "Leaderboard:" << endl;
    for (const auto& entry : leaderboard) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

int main() {
    // Seed the random number generator
    srand(time(0));
    
    bool playAgain = true;
    vector<pair<string, int>> leaderboard; // Vector to store player names and their scores

    // Define achievements
    vector<Achievement> achievements = {
        {"Novice Guesser", "Guess the number in 10 attempts or fewer", 10, 5, false},
        {"Expert Guesser", "Guess the number in 5 attempts or fewer", 5, 10, false},
        {"High Scorer", "Achieve a score of 10 or more", 0, 20, false}
    };

    while (playAgain) {
        int minRange, maxRange, maxAttempts;

        // Difficulty levels
        cout << "Choose difficulty level:" << endl;
        cout << "1. Easy (1-50, 10 attempts)" << endl;
        cout << "2. Medium (1-100, 7 attempts)" << endl;
        cout << "3. Hard (1-200, 5 attempts)" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                minRange = 1;
                maxRange = 50;
                maxAttempts = 10;
                break;
            case 2:
                minRange = 1;
                maxRange = 100;
                maxAttempts = 7;
                break;
            case 3:
                minRange = 1;
                maxRange = 200;
                maxAttempts = 5;
                break;
            default:
                cout << "Invalid choice. Defaulting to medium difficulty." << endl;
                minRange = 1;
                maxRange = 100;
                maxAttempts = 7;
        }

        // Generate a random number within the chosen range
        int secretNumber = rand() % (maxRange - minRange + 1) + minRange;
        int guess;
        int attempts = 0;
        int score = 0;

        printWelcomeMessage();

        // Loop until the player guesses the correct number or runs out of attempts
        while (attempts < maxAttempts) {
            cout << "Attempt " << attempts + 1 << "/" << maxAttempts << ": Enter your guess: ";
            cin >> guess;

            // Check if the guess is correct
            if (guess == secretNumber) {
                printCongratsMessage(secretNumber, attempts);
                score = maxAttempts - attempts;

                // Check and unlock achievements
                checkAchievements(attempts, score, achievements);

                break;
            } else if (guess < secretNumber) {
                printTooLowMessage();
            } else {
                printTooHighMessage();
            }

            attempts++;

            // Offer hint after 2 attempts
            if (attempts == 2) {
                printHint(secretNumber);
            }
        }

        // If the player runs out of attempts
        if (attempts == maxAttempts) {
            cout << "Sorry, you've run out of attempts. The correct number was " << secretNumber << "." << endl;
        }

        // Ask for player's name and update leaderboard
        string playerName;
        cout << "Enter your name for the leaderboard: ";
        cin >> playerName;
        leaderboard.push_back(make_pair(playerName, score));

        // Update and display leaderboard
        sort(leaderboard.begin(), leaderboard.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });
        printLeaderboard(leaderboard);

        // Display unlocked achievements
        for (const auto& achievement : achievements) {
            if (achievement.unlocked) {
                cout << "Achievement Unlocked: " << achievement.name << " - " << achievement.description << endl;
            }
        }

        // Ask the player if they want to play again
        printGameOverMessage();
        printTryAgainMessage();

        char playAgainChoice;
        cin >> playAgainChoice;

        if (playAgainChoice != 'y' && playAgainChoice != 'Y') {
            playAgain = false;
        }
    }

    cout << "Thanks for playing! Goodbye." << endl;

    return 0;
}
