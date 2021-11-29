#include "bship.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>

const int BOARD_WIDTH = 9;
const int BOARD_HEIGHT = 9;
const char noship = '!';
char board[BOARD_WIDTH][BOARD_HEIGHT]; 
char compBoard[BOARD_WIDTH][BOARD_HEIGHT];

enum DIRECTION {HORIZONTAL, VERTICAL};

void PrintBoard(int player);
void ResetBoard();
void PlaceShips();
void Attack();
void GameOver();
void loadShips();
void shipPlacement();

Ship::Ship(std::string name, int size, char tag){
    this->name = name;
    this->size = size;
    this->tag = tag;
}

std::string Ship::getShipName(){
    return name;
}

int Ship::getShipSize(){
    return size;
}

char Ship::getShipTag(){
    return tag;
}

void Ship::setShipName(){
    this->name = name;
}

void Ship::setShipSize(){
    this->size = size;
}

void Ship::setShipTag(){
    this->tag = tag;
}

void PrintBoard(){
    std::cout << "   1 2 3 4 5 6 7 8 9 " << std::endl;
    for(int h=0; h<BOARD_HEIGHT; h++){
        for(int w=0; w<BOARD_WIDTH; w++){
            if (w==0) std::cout << h+1 << " ";
            if (w<10 && w==0) std::cout << " ";
            std::cout << board[h][w] << " ";
            if(w == BOARD_WIDTH-1) std::cout << "\n";
        }
    }
}

void ResetBoard(){
    for(int h = 0; h<BOARD_HEIGHT; h++){
        for(int w = 0; w<BOARD_WIDTH; w++){
            board[h][w] = ' ';
            //std::cout << board[h][w];
        }
    }
}

void shipPlacement(Ship tmp){
    int d;
    int x, y; 
    std::cin >> d >> x >> y;
    if(d = 0){
        for(int i = 0; i < tmp.getShipSize(); i++){
            board[y-1][x+i-1] = tmp.getShipTag();
        }
    }
    if (d = 1){
        for(int j = 0; j < tmp.getShipSize(); j++){
            board[y+j-1][x-1] = tmp.getShipTag();
        }
    }
    PrintBoard();

}

void computerShipPlacement(int d, int y, int x, Ship tmp){
    if(d = 0){
        for(int i = 0; i < tmp.getShipSize(); i++){
            compBoard[x+i-1][y-1] = tmp.getShipTag();
        }
    }
    else if(d = 1){
        std::cout << "blah1";
        for(int j = 0; j < tmp.getShipSize(); j++){
            compBoard[x-1][y+j-1] = tmp.getShipTag();
        }
    }
    else return;
}

void instructions(Ship a){
    std::string instructions = "To place ships enter 3 numbers followed by a space: The first number is for facing (0 is horizontal and 1 is vertical), the second number is x coords, and the third number is y coords";
    std::cout << instructions << std::endl;
    std::cout << "Ship to place: " << a.getShipName() << " which has a length of " << a.getShipSize() << std::endl;
    std::cout << "Where do you want to place it?" << std::endl; 
    shipPlacement(a);
    

}

void setUpGame(){
    Ship aircraftCarrier("Aircraft Carrier", 5, 'A');
    Ship battleShip("Battleship", 4, 'B');
    Ship cruiser("Cruiser", 3, 'C');
    Ship submarine("Submarine", 3, 'S');
    Ship destroyer("Destroyer", 2 ,'D');    
    instructions(aircraftCarrier);
    instructions(battleShip);
    instructions(cruiser);
    instructions(submarine);
    instructions(destroyer);    
}

void computerBoard(){
    Ship aircraftCarrierC("Aircraft Carrier", 5, 'A');
    Ship battleShipC("Battleship", 4, 'B');
    Ship cruiserC("Cruiser", 3, 'C');
    Ship submarineC("Submarine", 3, 'S');
    Ship destroyerC("Destroyer", 2 ,'D');

    for(int h = 0; h<BOARD_HEIGHT; h++){
        for(int w = 0; w<BOARD_WIDTH; w++){
            compBoard[h][w] = ' ';
            //std::cout << compBoard[h][w];
        }
    }

    computerShipPlacement(0, 1, 5, aircraftCarrierC);
    computerShipPlacement(0, 7, 9, battleShipC);
    computerShipPlacement(1, 2, 1, cruiserC);
    computerShipPlacement(1, 7, 4, submarineC);
    computerShipPlacement(1, 1, 7, destroyerC);
    
    std::cout << "   1 2 3 4 5 6 7 8 9 " << std::endl;
    for(int h=0; h<BOARD_HEIGHT; h++){
        for(int w=0; w<BOARD_WIDTH; w++){
            if (w==0) std::cout << h+1 << " ";
            if (w<10 && w==0) std::cout << " ";
            std::cout << compBoard[h][w] << " ";
            if(w == BOARD_WIDTH-1) std::cout << "\n";
        }
    }

    
}

int main(){
    ResetBoard();
    PrintBoard();
    setUpGame();
    //computerBoard();


    return 0;
}