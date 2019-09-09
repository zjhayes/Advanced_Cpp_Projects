// Fish Wars Game - This is not your childhood 'Go Fish', this is 'FISH WARS'!

// Zachary Hayes - zjhayes@dmacc.edu - September 5th, 2019

#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

enum Card {null, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, SHARK, PEACE};

class IPlayer
{
protected:
    
    string name = "Player";
    int score = 0;
    int battlePoints = 0;
    vector<Card> hand;
    Card lastCardPlayed = null;
    
private:
    
    virtual int getTurn() = 0;
    virtual void resetPlayer() = 0;
    
    // Reset hand.
    void newHand()
    {
        hand = {ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, SHARK, PEACE, PEACE};
    }
    
    // Removes card from hand by index.
    void removeCardFromHand(int cardIndex)
    {
        hand.erase(hand.begin() + cardIndex);
    }
    
public:
    
    virtual void rememberOpponentTurn(Card _opponentCard) = 0;
    
    // Ready player for new game.
    void newGame()
    {
        lastCardPlayed = null;
        score = 0;
        battlePoints = 0;
        newHand();
        resetPlayer();
    }
    
    // Runs getTurn() and sets lastCardPlayed accordingly.
    void takeTurn()
    {
        cout << endl << "--" << name << "'s turn--" << endl;
        cout << "-- score: " << score << "  battle points: " << battlePoints << " --" << endl;
        int cardIndex = getTurn();
        Card cardPlayed = hand[cardIndex];
        removeCardFromHand(cardIndex);
        lastCardPlayed = cardPlayed;
        cout << name << " has placed their card." << endl;
    }
    
    // Player loses all battle points.
    void loseBattlePoints()
    {
        battlePoints = 0;
    }
    
    // Player is rewarded for winning a round.
    void winRound()
    {
        battlePoints++;
        score++;
    }
    
    // Prints last placed card to the console.
    void flipCard(Card _card)
    {
        int cardValue = _card;
        if(cardValue == 12)
        {
            cout << "[P]";
        }
        else if(cardValue == 11)
        {
            cout << "[S]";
        }
        else
        {
            cout << "[" << cardValue << "]";
        }
    }
    
    // So flip card flips lastCardPlayed by default.
    void flipCard()
    {
        flipCard(lastCardPlayed);
    }
    
    Card getLastCardPlayed()
    {
        return lastCardPlayed;
    }
    
    int getBattlePoints()
    {
        return battlePoints;
    }
    
    int getScore()
    {
        return score;
    }
    
    string getName()
    {
        return name;
    }
    
    void setName(string _name)
    {
        name = _name;
    }
    
};

class Player : public IPlayer
{
private:
    
    int getTurn()
    {
        printHand();
        int cardIndex;
        cardIndex = getUserInput();
        
        return cardIndex;
    }
    
    void printHand()
    {
        // Number cards, formatted over the cards.
        for(int i = 0; i < hand.size();)
        {
            if(hand[i] >= 10){cout << " ";}
            cout << setw(3) << ++i;
            if(hand[i] <= 10){cout << " ";}
        }
        
        cout << endl;
        
        // Print cards.
        for(auto &card : hand)
        {
            cout << " "; // Spacer.
            flipCard(card);
        }
        
        cout << endl;
    }
    
    int getUserInput()
    {
        int cardChoice;
        cout << name << ", choose a card to play: ";
        cin >> cardChoice;
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush buffer.
        
        if(cardChoice > 0 && cardChoice <= hand.size())
        {
            return (cardChoice - 1); // Returns card index.
        }
        else
        {
            cout << "Invalid entry. Try again." << endl;
            return getUserInput();
        }
    }
    
    void resetPlayer() {} // Nothing needs done here.
    
public:
    
    Player(string _name)
    {
        name = _name;
    }
    
    void rememberOpponentTurn(Card _opponentCard) {} // Do nothing, this method is for AI players.
};

class AI : public IPlayer
{
private:
    
    vector<Card> memory;
    
    int getTurn()
    {
        int cardIndex = artificialIntelligenceEngine();
        return cardIndex;
    }
    
    // Clear memory of opponent's moves.
    void resetPlayer()
    {
        memory.clear();
    }
    
    // Nobody truly understands how this program's mind works.
    int artificialIntelligenceEngine()
    {
        int decisionIndex = (rand() % hand.size());
        return decisionIndex;
    }
    
public:
    
    // Construct AI with custom name.
    AI(string _name = "AI")
    {
        name = _name;
        srand((int)time(NULL));
    }
    
    // This allows the AI to make context based decisions.
    void rememberOpponentTurn(Card _opponentCard)
    {
        memory.push_back(_opponentCard);
        sort(memory.begin(), memory.end());
    }
};

class Game
{
private:
    
    IPlayer* player1;
    IPlayer* player2;
    
    const int NUM_OF_ROUNDS = 13;
    
    void newGame()
    {
        player1->newGame();
        player2->newGame();
        
        int roundsRemaining = NUM_OF_ROUNDS;
        
        while(roundsRemaining)
        {
            roundsRemaining--;
            cout << endl << "ROUND " << (NUM_OF_ROUNDS - roundsRemaining) << endl;
            
            runGameRound();
        }
        
        determineGameWinner();
    }
    
    void runGameRound()
    {
        player1->takeTurn();
        player2->takeTurn();
        
        flipCards();
        
        player1->rememberOpponentTurn(player2->getLastCardPlayed());
        player2->rememberOpponentTurn(player1->getLastCardPlayed());
        
        if(player1->getLastCardPlayed() > player2->getLastCardPlayed() )
        {
            calculateRoundWinner(player1, player2); // Player 1 had highest card value.
        }
        else if(player1->getLastCardPlayed() <= player2->getLastCardPlayed())
        {
            calculateRoundWinner(player2, player1); // Player 2 had highest card value.
        }
    }
    
    // Show cards on table face-up.
    void flipCards()
    {
        cout << endl << " "; // Spacer.
        player1->flipCard();
        player2->flipCard();
        cout << endl;
    }

    
    // Determine winner of this round.
    void calculateRoundWinner(IPlayer* highPlayer, IPlayer* lowPlayer)
    {
        if(highPlayer->getLastCardPlayed() == PEACE && lowPlayer->getLastCardPlayed() != PEACE)
        {
            // Tie, player with lowest card value loses battle points.
            lowPlayer->loseBattlePoints();
            cout << "Round is a tie. However, " << lowPlayer->getName() << " loses their battle points." << endl;
        }
        else if(highPlayer->getLastCardPlayed() == SHARK && lowPlayer->getLastCardPlayed() != SHARK)
        {
            // Player with highest card value wins.
            highPlayer->winRound();
            cout << highPlayer->getName() << " wins this round." << endl;
            
        }
        else if((highPlayer->getLastCardPlayed() + highPlayer->getBattlePoints()) >
                (lowPlayer->getLastCardPlayed() + lowPlayer->getBattlePoints()))
        {
            // Player with highest card value wins.
            highPlayer->winRound();
            cout << highPlayer->getName() << " wins this round." << endl;
        }
        else if((highPlayer->getLastCardPlayed() + highPlayer->getBattlePoints()) <
                (lowPlayer->getLastCardPlayed() + lowPlayer->getBattlePoints()))
        {
            // Player with lowest card value wins.
            lowPlayer->winRound();
            cout << lowPlayer->getName() << " wins this round." << endl;
        }
        else
        {
            // Tie game.
            cout << "Round is a tie." << endl;
        }
    }
    
    // Outputs final score, congratulates winner.
    void determineGameWinner()
    {
        int p1Score = 5;//player1->getScore();
        int p2Score = 5;//player2->getScore();
        cout << endl << "--FINAL SCORE--" << endl;
        cout << player1->getName() << ": " << p1Score << endl;
        cout << player2->getName() << ": " << p2Score << endl;
        
        if(p1Score > p2Score)
        {
            cout << endl << player1->getName() << " is the winner!" << endl;
        }
        else if(p1Score < p2Score)
        {
            cout << endl << player2->getName() << " is the winner!" << endl;
        }
        else
        {
            cout << endl << "Game is a tie." << endl;
        }
        
    }
    
    // Ask player if they'd like to exit or start new game.
    // Returns true to exit game.
    bool askToExit()
    {
        return true;
    }
    
public:
    
    Game(IPlayer* _player1, IPlayer* _player2)
    {
        player1 = _player1;
        player2 = _player2;
    }
    
    void runGame()
    {
        bool exit = false;
        while(!exit)
        {
            newGame();
            exit = askToExit();
        }
    }
};

int main()
{
    cout << "FISH WAR" << endl;
    IPlayer* player1 = new Player("Player1");
    IPlayer* player2 = new AI();
    
    Game game = Game(player1, player2);
    game.runGame();
    
    return 0;
}
