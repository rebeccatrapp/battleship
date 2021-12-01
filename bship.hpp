#ifndef __HPP_BSHIP__
#define __HPP_BSHIP__

#include <string> 

class GamePlay{
    void PrintBoard(int player);
    void ResetBoard();
    void shipPlacement();
    void instructions();
    void setupGame();
    void computerBoard();
    void checkWinner();
    void takeTurn();
    void computerTurn();
    void playGame();
};

class Board{
    public: 
    //constructor
        Board();
        Board(int width, int height);
    //getters
        std::string getBoardWidth();
        std::string getBoardHeight();
    //setters
        void setBoardWidth(int x);
        void setBoardHeight(int y);

        int width;
        int height;

};

class Ship{
    public: 
        Ship();
        Ship(std::string name, int size, char tag);

        std::string name;
        int size; 
        char tag;
    //getters 
        std::string getShipName();
        int getShipSize();
        char getShipTag();
    //setters 
        void setShipName();
        void setShipSize();
        void setShipTag();



};


#endif