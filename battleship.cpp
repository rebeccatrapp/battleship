#include "bship.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>

const int BOARD_WIDTH = 9;
const int BOARD_HEIGHT = 9;
const int player = 1; 
const int computer = 2;
const char water = '-';
char playerBoard[BOARD_WIDTH][BOARD_HEIGHT]; 
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

void PrintBoard(char b[BOARD_WIDTH][BOARD_HEIGHT], int p){
    std::cout << "------BOARD " << p << "------  " << std::endl;
    std::cout << "   1 2 3 4 5 6 7 8 9 " << std::endl;
    for(int h=0; h<BOARD_HEIGHT; h++){
        for(int w=0; w<BOARD_WIDTH; w++){
            if (w==0) std::cout << h+1 << " ";
            if (w<10 && w==0) std::cout << " ";
            std::cout << b[h][w] << " ";
            if(w == BOARD_WIDTH-1) std::cout << "\n";
        }
    }
}

void ResetBoard(char b[BOARD_WIDTH][BOARD_HEIGHT]){
    for(int h = 0; h<BOARD_HEIGHT; h++){
        for(int w = 0; w<BOARD_WIDTH; w++){
            b[h][w] = water;
        }
    }
}

void shipPlacement(Ship tmp, int p){
    int d;
    int x, y; 
    bool notoccupied = false;

    if(p == player){
        std::cin >> d >> x >> y;
    }
    if(p == computer){
        srand(time(0));
        d = rand() % 2;
        x = rand() % 9;
        y = rand() % 9; 
    }
    if(d == 0){
        if(p == player){
            for(int i = 0; i < tmp.getShipSize(); i++){
                if(playerBoard[y-1][x+i-1] == water){
                    for(int j = 0; j < tmp.getShipSize(); j++){
                        playerBoard[y-1][x+j-1] = tmp.getShipTag();
                    }
                    notoccupied = true;
                }
            }
        }
        if(p == computer){
            for(int i = 0; i < tmp.getShipSize(); i++){
                if(compBoard[y-1][x+i-1] == water){
                    for(int j = 0; j < tmp.getShipSize(); j++){
                        compBoard[y-1][x+i-1] = tmp.getShipTag();
                    }
                    notoccupied = true;
                }
            }
        }
    }
    if(d == 1){
        if(p == player){
            for(int i = 0; i < tmp.getShipSize(); i++){
                if(playerBoard[y+i-1][x-1] == water){
                    for(int j = 0; j < tmp.getShipSize(); j++){
                        playerBoard[y+i-1][x-1] = tmp.getShipTag();
                    }
                    notoccupied = true;
                }
            }
        }
        if(p == computer){
            for(int i = 0; i < tmp.getShipSize(); i++){
                if(compBoard[y+i-1][x-1] == water){
                    for(int j = 0; j < tmp.getShipSize(); j++){
                        compBoard[y+i-1][x-1] = tmp.getShipTag();
                    }
                }
                notoccupied = true;
            }
        }
    }
    if(notoccupied == false){
        if(p==player){
            std::cout << "Invalid Placement. Try again" << std::endl;
            shipPlacement(tmp, player);
        }
        if(p==computer){
            shipPlacement(tmp, computer);
        }
    }
    if(p == player){
        PrintBoard(playerBoard, player);
    }
}

void instructions(Ship a){
    std::string instructions = "To place ships enter 3 numbers followed by a space: The first number is for facing (0 is horizontal and 1 is vertical), the second number is x coords, and the third number is y coords";
    std::cout << instructions << std::endl;
    std::cout << "Ship to place: " << a.getShipName() << " which has a length of " << a.getShipSize() << std::endl;
    std::cout << "Where do you want to place it?" << std::endl; 
    shipPlacement(a, player);
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
    shipPlacement(aircraftCarrierC, computer);
    srand(time(0));
    shipPlacement(battleShipC, computer);
    shipPlacement(cruiserC, computer);
    shipPlacement(submarineC, computer);
    shipPlacement(destroyerC, computer);
}

int main(){
    //ResetBoard(playerBoard);
    ResetBoard(compBoard);
    PrintBoard(compBoard, computer);
    //PrintBoard(playerBoard, player);
    //setUpGame();
    computerBoard();
    PrintBoard(compBoard, computer);


    return 0;
}