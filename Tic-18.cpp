// TIC-18: Implement Game::showMenu()
// Input: none | Output: none
// Function: Displays mode selection menu and handles user choice
// ==========================================================================
void Game::showMenu() {
    std::cout << "TIC-TAC-TOE GAME\n";
    std::cout << "================\n";
    std::cout << "1. Player vs Player\n";
    std::cout << "2. Player vs Computer (Easy)\n";
    std::cout << "3. Player vs Computer (Hard)\n";
    std::cout << "4. Exit\n\n";
    std::cout << "Select game mode: ";
 
    int choice = 0;
    while (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cout << "Invalid choice, please enter a number between 1 and 4: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
 
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
            std::cout << "Goodbye!\n";
            break;
    }
}