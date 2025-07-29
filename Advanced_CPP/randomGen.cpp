#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void randomNumberGuessGame() {
    srand(time(0));
    int randomNum = rand() % 10 + 1;
    int chances = 0;
    while(chances < 5) {
        int userInput;
        cin>>userInput;
        if(userInput < 1 || userInput > 10) {
            cout<<"Please enter within the range\n";
        }
        else {
            if(userInput == randomNum) {
                cout<<"You won!. The number was: "<<randomNum;;
                break;
            }
            else {
                if(chances < 4)
                    cout<<"Try again! ";
            }
        }
        chances++;
    }
    if(chances == 5) {
        cout<<"You have used all your chances. The number was: "<<randomNum;
    }
}

int main() {
    cout<<"Hi, welcome to the number guesing game!\n";
    cout<<"Enter a number between 1-10 (You have 5 chances): ";

    randomNumberGuessGame();

    return 0;
}