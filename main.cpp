#include <iostream>
#include "owaregame.hpp"


void drawGame(OwareGame const & game)
{
    using namespace std;

    auto pits = game.getBoard();
    auto bottomScore = game.getBottomPlayerScore();
    auto topScore = game.getTopPlayerScore();

    cout << "\n";

    cout << topScore << "   ";
    for(int i = 11; i >= 6; --i)
    {
        cout << (int)pits[i] << " ";
    }
    cout << "\n" << "    ";
    for(int i = 0; i <= 5; ++i)
    {
        cout << (int)pits[i] << " ";
    }

    cout << "   " << bottomScore;
    cout << "\n";
}


int main(int argc, char** argv)
{

    std:: cout << "Welcome to Oware!";


    OwareGame game;
    game.move(0);
    game.setTopPlayerTurn();
    game.move(6);
    game.setBottomPlayerTurn();
    game.move(1);


    drawGame(game);

    return 0;
}
