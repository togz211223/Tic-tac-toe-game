#include <iostream>
#include <vector>
#include <string>
#include <limits> // Needed for numeric_limits to clear cin

using namespace std;

enum Difficulty {
    EASY,
    HARD
};

class Board {
private:
    vector<vector<char>> grid;
    const int size;

public:
    Board(int size = 3) : size(size) {
    }

    void display() const {
    }

    bool makeMove(int row, int col, char symbol) {
        return false;
    }

    bool isValidMove(int row, int col) const {
        return false;
    }

    bool checkWin(char symbol) const {
        return false;
    }

    bool isFull() const {
        return false;
    }

    char getCell(int row, int col) const {
        return ' ';
    }

    void reset() {
    }

    int getSize() const {
        return size;
    }
};

class Player {
protected:
    string name;
    char symbol;

public:
    Player(const string& name, char symbol) : name(name), symbol(symbol) {
    }

    virtual ~Player() {
    }

    virtual void getMove(int& row, int& col) = 0;

    string getName() const {
        return name;
    }

    char getSymbol() const {
        return symbol;
    }

    void setName(const string& newName) {
        name = newName;
    }
};

// [TIC-10] FIXED: Concrete HumanPlayer with Robust Input Validation
class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol) : Player(name, symbol) {
    }

    void getMove(int& row, int& col) override {
        while (true) {
            cout << name << " (" << symbol << "), enter your move (row and column 1-3): ";
            if (cin >> row >> col) {
                break; // Valid integers entered
            } else {
                // Clear the error state and ignore bad string inputs to prevent crashes
                cout << "Invalid input. Please enter numbers only!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
};

class AIPlayer : public Player {
private:
    Difficulty difficulty;

public:
    AIPlayer(const string& name, char symbol, Difficulty difficulty)
        : Player(name, symbol), difficulty(difficulty) {
    }

    void getMove(int& row, int& col) override {
    }

    void setDifficulty(Difficulty newDifficulty) {
        difficulty = newDifficulty;
    }

    void getRandomMove(const Board& board, int& row, int& col) const {
    }

    void getBestMove(Board& board, int& row, int& col) const {
    }

    int evaluateBoard(const Board& board) const {
        return 0;
    }
};

class Game {
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;

public:
    Game() : player1(nullptr), player2(nullptr), currentPlayer(nullptr) {
    }

    ~Game() {
        // Remember to eventually delete player1 and player2 here!
    }

    void start() {
        char replay;
        
        showMenu(); // Moved OUTSIDE the loop to prevent memory leaks

        do {
            board.display();
            
            while (true) {
                if (AIPlayer* aiPlayer = dynamic_cast<AIPlayer*>(currentPlayer)) {
                    handleAIMove(aiPlayer);
                }
                else {
                    handleHumanMove(currentPlayer);
                }
                
                board.display();
                
                if (checkGameEnd()) {
                    break;
                }
                
                switchPlayer();
            }
            
            displayResult();
            
            cout << "Replay confirmation (y/n): ";
            cin >> replay;
            
            if (replay == 'y' || replay == 'Y') {
                reset();
            }
            
        } while (replay == 'y' || replay == 'Y');
    }

    void showMenu() {
    }

    void setupPvP() {
    }

    void setupPvC(Difficulty difficulty) {
    }

    void switchPlayer() {
        // FIXED: currentplayer typo changed to currentPlayer
        if (currentPlayer == player1)
            currentPlayer = player2;
        else
            currentPlayer = player1;
    }

    void handleHumanMove(Player* player) {
        int row, col;
        player->getMove(row, col);
        row--;
        col--;
        
        while (!board.makeMove(row, col, player->getSymbol())) {
            cout << "Invalid move. Cell occupied or out of bounds. Try again." << endl;
            player->getMove(row, col);
            row--;
            col--;
        }
    }

    void handleAIMove(AIPlayer* aiPlayer) {
        int row, col;
        aiPlayer->getMove(row, col);
        board.makeMove(row, col, aiPlayer->getSymbol());
    }

    bool checkGameEnd() {
        // FIXED: Player1/Player2 typos corrected to player1/player2. 
        // FIXED: Print statements removed to prevent double-printing.
        if (board.checkWin(player1->getSymbol())) {
            return true;
        }
        if (board.checkWin(player2->getSymbol())) {
            return true;
        }
        if (board.isFull()) {
            return true;
        }
        return false;
    }

    void displayResult() const {
        if (board.checkWin(player1->getSymbol())) {
            cout << player1->getName() << " wins!" << endl;
        }
        else if (board.checkWin(player2->getSymbol())) {
            cout << player2->getName() << " wins!" << endl;
        }
        else if (board.isFull()) {
            cout << "It's a draw!" << endl;
        }
    }

    void reset() {
        board.reset();
        currentPlayer = player1;
    }
};

int main() {
    Game game;
    game.start();

    return 0;
}
