#include <iostream>
#include <vector>
#include <string>

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

class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol) : Player(name, symbol) {
    }

    void getMove(int& row, int& col) override {
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
    }

    void start() {
        char replay;
        do {
            showMenu();
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
            cout<<"Replay confirmation (y/n): ";
            cin >> replay;
            if (replay == 'y' || replay == 'Y') {
                reset();
            }
        }
		while (replay == 'y' || replay == 'Y');
    }

    void showMenu() {
    }

    void setupPvP() {
    }

    void setupPvC(Difficulty difficulty) {
    }

    void switchPlayer() {
        if(currentplayer==player1)
            currentPlayer=player2;
        else
            currentPlayer=player1;
    }

    void handleHumanMove(Player* player) {
        int row, col;
        player->getMove(row, col);
        row--;
        col--;
        while (!board.makeMove(row, col, player->getSymbol())) {
            cout << "Invalid move. Try again." << endl;
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
		if (board.checkWin(Player1->getSymbol())) {
			cout << currentPlayer->getName() << " wins!" << endl;
			return true;
		}
        if(board.checkWin(Player2->getSymbol()))
            {
                cout << currentPlayer->getName() << " wins!" << endl;
                return true;
                }
		else if (board.isFull()) {
			cout << "It's a draw!" << endl;
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
