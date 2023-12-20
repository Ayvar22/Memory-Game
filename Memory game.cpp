#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

const string RED = "\033[1;31m";
const string YELLOW = "\033[1;33m";
const string BLUE = "\033[1;34m";  
const string MAGENTA = "\033[1;35m";
const string RESET_COLOR = "\033[0m";

const int MXSIZE = 20;
const int MNSIZE = 6;

void clearConsole() {
    cout << "\033[2J\033[1;1H";
}

void displayArray(int arr[], int size, bool opened[]) {
    for (int i = 0; i < size; i++) {
        if (opened[i]) {
            cout << RED << arr[i] << " " << RESET_COLOR;
        } else {
            cout << "? ";
        }
    }
    cout << endl;
}


void startArray(int arr[], int size) {
    
    mt19937 rng(time(nullptr));
    uniform_int_distribution<int> dist(0, size - 1);

    for (int i = 0; i < size / 2; i++) { 
        arr[i * 2] = i + 1;
        arr[i * 2 + 1] = i + 1;
    }

    for (int i = 0; i < size; i++) {
        int randomIndex = dist(rng); 
        int initialElementIndex = arr[i];
        arr[i] = arr[randomIndex];
        arr[randomIndex] = initialElementIndex;
    }
}

int main() {
    int size;
    int moves = 0;

    cout << "Welcome " << BLUE << "to" << RESET_COLOR << " the Memory Game!" << endl;
    do {
        cout << "Enter the size" << BLUE << " of " << RESET_COLOR << "an array (" << RED << MNSIZE << RESET_COLOR << "-" << RED << MXSIZE << RESET_COLOR << "): ";
        cin >> size;
        
        if (size < MNSIZE || size > MXSIZE || size % 2 != 0) {
            cout << "Error. Enter an even number between " << MNSIZE << " and " << MXSIZE << "." << endl;
        }
    } while (size < MNSIZE || size > MXSIZE || size % 2 != 0);

    int array[MXSIZE];
    bool opened[MXSIZE] = { false };
    startArray(array, size);

    cout << "Here " << YELLOW << "is" << RESET_COLOR << " the array: ";
    displayArray(array, size, opened);

    int firstIndex, secondIndex;
    bool ifAllOpened = false;

    while (!ifAllOpened) {
        cout << "Enter the index " << BLUE << "to" << RESET_COLOR << " show: ";
        cin >> firstIndex;

        while (firstIndex < 0 || firstIndex >= size || opened[firstIndex]) {
            cout << "Index is wrong or the card was already opened. Enter a valid index: ";
            cin >> firstIndex;
        }

        opened[firstIndex] = true;
        cout << "The card at index " << RED << firstIndex << RESET_COLOR << YELLOW << " is: " << RESET_COLOR << RED << array[firstIndex] << RESET_COLOR << endl << endl;

        cout << "Enter the second index" << BLUE << " to " << RESET_COLOR << "show: ";
        cin >> secondIndex;

        while (secondIndex < 0 || secondIndex >= size || opened[secondIndex]) {
            cout << "Index is wrong or the card was already opened. Enter a valid index: ";
            cin >> secondIndex;
        }

        opened[secondIndex] = true;
        cout << "The card at index " << RED << secondIndex << RESET_COLOR << YELLOW << " is: " << RESET_COLOR << RED << array[secondIndex] << RESET_COLOR << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (array[firstIndex] == array[secondIndex]) {
            cout << "Great! The cards are matched. " << BLUE << "Continue..." << RESET_COLOR << endl << endl;
        } else {
            cout << "The cards " << BLUE << "do " << RESET_COLOR << "not" << YELLOW << " match." << BLUE << " Try " << RESET_COLOR << "again!" << endl;
            opened[firstIndex] = opened[secondIndex] = false;
        }

        displayArray(array, size, opened);
        moves++;

        ifAllOpened = true;
        for (int i = 0; i < size; ++i) {
            if (!opened[i]) {
                ifAllOpened = false;
                break;
            }
        }
        cout << "Press Enter " << BLUE << "to continue" << RESET_COLOR << "...";
        string input;
        while (getline(cin, input)) {
            if (input.empty()) {
                clearConsole();
                break;
            }
        }
        displayArray(array, size, opened);
    }

    cout << MAGENTA << "Congratulations! You beat the game!" << RESET_COLOR << endl;
    cout << "Total moves: " << moves << endl;

    return 0;
}