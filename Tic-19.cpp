// TIC-19: Implement Game::setupPvP() and Game::setupPvC()
// ==========================================================================
 
// void setupPvP()
// Input: none | Output: none
// Function: Configures player vs player mode with user input
void Game::setupPvP() {
    delete player1;
    delete player2;
 
    std::string name1, name2;
 
    std::cout << "\nPlayer 1 name: ";
    std::getline(std::cin, name1);
    player1 = new Player(name1, 'X');
 
    std::cout << "Player 2 name: ";
    std::getline(std::cin, name2);
    player2 = new Player(name2, 'O');
 
    vsComputer = false;
    currentPlayer = player1;
 
    std::cout << "\n" << player1->name << " (X) vs " << player2->name << " (O)\n";
}
 
// void setupPvC(Difficulty difficulty)
// Input: AI difficulty level | Output: none
// Function: Configures player vs computer mode with user input
void Game::setupPvC(Difficulty difficulty) {
    delete player1;
    delete player2;
 
    std::string name;
    std::cout << "\nYour name: ";
    std::getline(std::cin, name);
 
    player1 = new Player(name, 'X');
    player2 = new AIPlayer("Computer", 'O', difficulty);
 
    vsComputer = true;
    currentPlayer = player1;
 
    std::string diffLabel = (difficulty == Difficulty::EASY) ? "Easy" : "Hard";
    std::cout << "\n" << player1->name << " (X) vs Computer (O) [" << diffLabel << "]\n";
}