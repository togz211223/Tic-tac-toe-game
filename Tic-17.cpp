// TIC-17: Implement Game Constructor & Core Setup
// Input: none | Output: constructs a Game object
// Function: Initializes game with empty board and null players
// ==========================================================================
Game::Game()
    : player1(nullptr), player2(nullptr), currentPlayer(nullptr),
      vsComputer(false), playing(false) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col] = ' ';
        }
    }
}
 
Game::~Game() {
    delete player1;
    delete player2;
}
 
// Main entry point — ties the pieces together. Not one of the three
// assigned tickets, but included as a thin driver so the class can be
// exercised end-to-end once teammates' methods land.
void Game::start() {
    playing = true;
    while (playing) {
        showMenu();
        if (player1 == nullptr) {
            // showMenu() chose "Exit"
            break;
        }
 
        do {
            displayBoard();
            if (!vsComputer || currentPlayer == player1) {
                handleHumanMove(currentPlayer);
            } else {
                handleAIMove(static_cast<AIPlayer*>(currentPlayer));
            }
            switchPlayer();
        } while (!checkGameEnd());
 
        displayBoard();
        displayResult();
 
        std::cout << "\nPlay again? (y/n): ";
        char again = 'n';
        std::cin >> again;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
 
        if (again == 'y' || again == 'Y') {
            reset();
        } else {
            playing = false;
        }
    }
}