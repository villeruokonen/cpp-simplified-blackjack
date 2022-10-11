#include <iostream>
#include <cstdio>
#include <string>
#include <random>
using namespace std;

class Card // card class which holds its value (likely unnecessary...)
{
    private:
        int Value = 0;
    public:
        int GetValue()
        {
            return Value;
        }
        Card CreateNewCard(int value) // card generation method
        {
            Value = value;
            return *this; //return pointer to this new card
        }
};

// variables
Card cards[13]; //13 unique cards in a deck (52 cards / 4 houses = 13)
int curCardsSum = 1;
int dealerSum;
int random;
int cardValue;
bool playerBlackJack;
bool dealerBlackJack;
// function declarations
void CheckDealerHand();
void Play();
void AskToPlayAgain();
char TestFirstCharInInput();
void AddCardToHand();
void AddCardToDealerHand();
// random engine
std::random_device rd; // obtain "random engine / random device" from hardware
std::mt19937 eng(rd()); // seed rnd
std::uniform_int_distribution <> distr(0, 12); // set distribution to cards[] indices

int main()
{
    for (int c = 0; c < 13; c++)  // create cards used in play
    {
        cards[c] = cards[c].CreateNewCard(c + 1);
    }
    

    if (curCardsSum < 21)   // if it's feasible to continue playing...
    {
        Play();             //...play...
    }

    else                    //..and if not...
    {
        main();             //...try again...
        return 0;
    }
}

void Play() 
{
    std::cout << "Dealer must draw to 17." << endl;
    random = 0;             
    dealerSum = 0;          // initialize all integer variables to zero
    cardValue = 0;          
    curCardsSum = 0;        

    for (int i = 0; i <= 1; i++)    // generate player hand
    {
        AddCardToHand();
    }

    if (curCardsSum > 20)          // once again, check if we can actually play
    {
        
        Play();
        return;
    }
    AddCardToDealerHand();
// goto label...
play:           

    

    std::cout << "Dealer hand: " << dealerSum << " + ?" << endl;


    std::cout << "Current hand: " << curCardsSum << endl;
    std::cout << "(H)it or (S)tand? \n";
    string input;
    bool stand = false;
    random = 0;         
    cardValue = 0;

    switch (TestFirstCharInInput()) // check input character (hit or stand)
    {

        case 'S':
        case 's':
            CheckDealerHand();  // player decided to stand - check if they won or lost
            return;

        case 'H':
        case 'h':
            AddCardToHand();
            break;

        default:
            std::cout << "What?" << endl;   // bad input...
            goto play;
            return;
    }
    
    // check the sum of the cards' values in our hand
    if (curCardsSum <= 20)
    {
        goto play;      // jump to label "play" to keep playing
    }
    else if (curCardsSum == 21)
    {
        std::cout << "21. You win." << endl << endl;
        AskToPlayAgain();
        return;
    }
    else if (curCardsSum > 21)
    {
        std::cout << "Current hand: " << curCardsSum << endl;
        std::cout << "Bust. You lose." << endl << endl;
        AskToPlayAgain();
        return;
    }
}

// handle Y/N input
void AskToPlayAgain() 
{
    std::cout << "Play again? Y/N" << endl;
    switch (TestFirstCharInInput()) // check input character (hit or stand)
    {
        case 'Y':
        case 'y':
            Play();
            return;
        case 'N':
        case 'n':
            return;
        default:
            return;
    }
}

// checks the dealer's hand (dealerSum integer variable)
void CheckDealerHand() 
{
    while (dealerSum <= 17)  // since dealer must draw to 17, keep drawing cards until we've hit 17
    {
        AddCardToDealerHand();
    }

    std::cout << "Dealer hand: " << dealerSum << ". ";
    std::cout << "Your hand: " << curCardsSum << "." << endl;

    if (dealerSum > curCardsSum && dealerSum <= 21) // dealer win conditions
    {
        std::cout << "Dealer wins." << endl;
    }
    else if (dealerSum == curCardsSum)              // push or tie condition
    {
        std::cout << "Push. " << endl;
    }
    else                                            // if all else fails, the player wins...
    {
        std::cout << "You win." << endl;
    }

    AskToPlayAgain();
}

void AddCardToHand()
{
    random = distr(eng);                    // generate random number
    cardValue = cards[random].GetValue();   // get random card in "deck" with random number as index
    curCardsSum += cardValue;               // add random card's value to the current sum of the hand
}

void AddCardToDealerHand() 
{
    random = distr(eng);                    // generate random number
    cardValue = cards[random].GetValue();   // get random card in "deck" with random number as index
    dealerSum += cardValue;               // add random card's value to the current sum of the hand
}

char TestFirstCharInInput() 
{
    string input = "";                  // declare and initialize input string
    std::getline(std::cin, input);      // get console input line and assign it to the input string
    std::cout << endl;                  // add empty line for looks
    return input[0];                    // return the first character in the string input (ergo saying yo-yo would mean "yes")
}
