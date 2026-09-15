#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <utility>
#include <algorithm>

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
    Board(int size = 3) : size(size), grid(size, vector<char>(size, ' ')) {
    }

    void display() const {
        cout << "\n  ";
        for (int i = 0; i < size; i++) {
            cout << " " << i + 1 << "  ";
        }
        cout << "\n";

        for (int i = 0; i < size; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < size; j++) {
                cout << " " << grid[i][j] << " ";
                if (j < size - 1) cout << "|";
            }
            cout << "\n";

            if (i < size - 1) {
                cout << "  ";
                for (int j = 0; j < size - 1; j++) {
                    cout << "---+";
                }
                cout << "---\n";
            }
        }
        cout << "\n";
    }

    bool makeMove(int row, int col, char symbol) {
        if (symbol == ' ') {
            if (row >= 0 && row < size && col >= 0 && col < size) {
                grid[row][col] = ' ';
                return true;
            }
            return false;
        }
        if (isValidMove(row, col)) {
            grid[row][col] = symbol;
            return true;
        }
        return false;
    }

    bool isValidMove(int row, int col) const {
		if (row < 0 || col < 0 || row >= size || col >= size) return false;
		if (grid[row][col] != ' ') return false;
		return true;
    }

    bool checkWin(char symbol) const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j] != symbol) break;
                if (j+1 == size) return true;
            }

            for (int j = 0; j < size; j++) {
                if (grid[j][i] != symbol) break;
                if (j+1 == size) return true;
            }
        }

        for (int j = 0; j < size; j++) {
            if (grid[j][size - j - 1] != symbol) break;
            if (j+1 == size) return true;
        }

        for (int j = 0; j < size; j++) {
            if (grid[j][j] != symbol) break;
            if (j+1 == size) return true;
        }

        return false;
    }

    bool isFull() const {
        for (const vector<char>& row: grid) {
            for (char symbol: row) {
                if (symbol == ' ') return false;
            }
        }

        return true;
    }

    char getCell(int row, int col) const {
        if (row >= 0 && row < size && col >= 0 && col < size) {
            return grid[row][col];
        }
        return ' ';
    }

    void reset() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                grid[i][j] = ' ';
            }
        }
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
        while (true) {
            cout << name << " (" << symbol << "), enter your move (row and column 1-3): ";
            if (cin >> row >> col) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            } else {
                cout << "Invalid input. Please enter numbers only!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
};

class AIPlayer : public Player {
private:
    Difficulty difficulty;

    int minimax(Board& board, int depth, bool isMaximizing) const {
        int score = evaluateBoard(board);

        if (score == 10) return score - depth;
        if (score == -10) return score + depth;
        if (board.isFull()) return 0;

        char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
        int size = board.getSize();

        if (isMaximizing) {
            int best = -1000;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board.isValidMove(i, j)) {
                        board.makeMove(i, j, symbol);
                        best = max(best, minimax(board, depth + 1, false));
                        board.makeMove(i, j, ' ');
                    }
                }
            }
            return best;
        } else {
            int best = 1000;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board.isValidMove(i, j)) {
                        board.makeMove(i, j, opponentSymbol);
                        best = min(best, minimax(board, depth + 1, true));
                        board.makeMove(i, j, ' ');
                    }
                }
            }
            return best;
        }
    }

public:
    AIPlayer(const string& name, char symbol, Difficulty difficulty)
        : Player(name, symbol), difficulty(difficulty) {
    }

    void getMove(int& row, int& col) override {
    }

    void getMove(Board& board, int& row, int& col) {
        if (difficulty == EASY) {
            getRandomMove(board, row, col);
        } else {
            getBestMove(board, row, col);
        }
    }

    void setDifficulty(Difficulty newDifficulty) {
        difficulty = newDifficulty;
    }

    void getRandomMove(const Board& board, int& row, int& col) const {
        vector<pair<int, int>> validMoves;
        int size = board.getSize();

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board.isValidMove(i, j)) {
                    validMoves.push_back({i, j});
                }
            }
        }

        if (!validMoves.empty()) {
            int index = rand() % validMoves.size();
            row = validMoves[index].first;
            col = validMoves[index].second;
        }
    }

    void getBestMove(Board& board, int& row, int& col) const {
        int bestVal = -1000;
        row = -1;
        col = -1;
        int size = board.getSize();

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board.isValidMove(i, j)) {
                    board.makeMove(i, j, symbol);
                    int moveVal = minimax(board, 0, false);
                    board.makeMove(i, j, ' ');

                    if (moveVal > bestVal) {
                        row = i;
                        col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
    }

    int evaluateBoard(const Board& board) const {
        char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
        if (board.checkWin(symbol)) {
            return 10;
        }
        if (board.checkWin(opponentSymbol)) {
            return -10;
        }
        return 0;
    }
};

class Game {
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    bool playing;

public:
    Game() : player1(nullptr), player2(nullptr), currentPlayer(nullptr), playing(false) {
    }

    ~Game() {
        delete player1;
        delete player2;
    }

    void start() {
        playing = true;
        while (playing) {
            showMenu();
            if (player1 == nullptr) {
                break;
            }

            while (true) {
                board.display();
                if (AIPlayer* aiPlayer = dynamic_cast<AIPlayer*>(currentPlayer)) {
                    handleAIMove(aiPlayer);
                }
                else {
                    handleHumanMove(currentPlayer);
                }

                if (checkGameEnd()) {
                    board.display();
                    displayResult();
                    break;
                }
                switchPlayer();
            }

            cout << "\nPlay again? (y/n): ";
            char again = 'n';
            cin >> again;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (again == 'y' || again == 'Y') {
                reset();
            } else {
                playing = false;
            }
        }
    }

    void showMenu() {
        cout << "TIC-TAC-TOE GAME\n";
        cout << "================\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer (Easy)\n";
        cout << "3. Player vs Computer (Hard)\n";
        cout << "4. Exit\n\n";
        cout << "Select game mode: ";

        int choice = 0;
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Invalid choice, please enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                setupPvP();
                break;
            case 2:
                setupPvC(Difficulty::EASY);
                break;
            case 3:
                setupPvC(Difficulty::HARD);
                break;
            case 4:
                delete player1;
                delete player2;
                player1 = nullptr;
                player2 = nullptr;
                cout << "Goodbye!\n";
                break;
        }
    }

    void setupPvP() {
        delete player1;
        delete player2;

        string name1, name2;

        cout << "\nPlayer 1 name: ";
        getline(cin, name1);
        player1 = new HumanPlayer(name1, 'X');

        cout << "Player 2 name: ";
        getline(cin, name2);
        player2 = new HumanPlayer(name2, 'O');

        currentPlayer = player1;

        cout << "\n" << player1->getName() << " (X) vs " << player2->getName() << " (O)\n";
    }

    void setupPvC(Difficulty difficulty) {
        delete player1;
        delete player2;

        string name;
        cout << "\nYour name: ";
        getline(cin, name);

        player1 = new HumanPlayer(name, 'X');
        player2 = new AIPlayer("Computer", 'O', difficulty);

        currentPlayer = player1;

        string diffLabel = (difficulty == Difficulty::EASY) ? "Easy" : "Hard";
        cout << "\n" << player1->getName() << " (X) vs Computer (O) [" << diffLabel << "]\n";
    }

    void switchPlayer() {
        if (currentPlayer == player1)
            currentPlayer = player2;
        else
            currentPlayer = player1;
    }

    void handleHumanMove(Player* player) {
        int row, col;
        while (true) {
            player->getMove(row, col);
            row--;
            col--;
            if (board.makeMove(row, col, player->getSymbol())) {
                break;
            }
            cout << "Invalid move. Cell occupied or out of bounds. Try again." << endl;
        }
    }

    void handleAIMove(AIPlayer* aiPlayer) {
        int row, col;
        aiPlayer->getMove(board, row, col);
        board.makeMove(row, col, aiPlayer->getSymbol());
    }

    bool checkGameEnd() {
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
