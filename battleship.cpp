#include "bship.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>

const int BOARD_WIDTH = 9;
const int BOARD_HEIGHT = 9;
const int player = 1; 
const int computer = 2;
const char water = '-';

int playerScore = 0; 
int compScore = 0;
bool running = true;

char playerBoard[BOARD_WIDTH][BOARD_HEIGHT]; 
char compBoard[BOARD_WIDTH][BOARD_HEIGHT];
char hitBoard[BOARD_WIDTH][BOARD_HEIGHT];

enum DIRECTION {HORIZONTAL, VERTICAL};

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
                    notoccupied = true;
                }
                else notoccupied = false;
            }
            if(notoccupied == false){
                shipPlacement(tmp, computer);
            }
            else{
                for(int j = 0; j < tmp.getShipSize(); j++){
                    compBoard[y-1][x+j-1] = tmp.getShipTag();
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
                if(compBoard [y+i-1][x-1] == water){
                    notoccupied = true;
                }
                else notoccupied = false;
            }
            if(notoccupied == false){
                shipPlacement(tmp, computer);
            }
            else{
                for(int j = 0; j < tmp.getShipSize(); j++){
                    compBoard[y+j-1][x-1] = tmp.getShipTag();
                }
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
    //if(p == computer){
     //   PrintBoard(compBoard, computer);
    //}
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
    shipPlacement(battleShipC, computer);
    std::cout << "test";
    shipPlacement(cruiserC, computer);
    shipPlacement(submarineC, computer);
    shipPlacement(destroyerC, computer);
}

void takeTurn(int p){
    PrintBoard(playerBoard, player);
    PrintBoard(hitBoard, 3);
    int x, y;
    std::cout << "Enter coordinates to attack" << std::endl;
    std::cin >> x >> y;
    std::cout << std::endl;
    x -= 1; 
    y -= 1;
    if(compBoard[x][y] == water){
        std::cout << "MISS" << std::endl;
        hitBoard[x][y] = 'm'; 
    }
    if(compBoard[x][y] != water){
        std::cout << "HIT" << std::endl; 
        hitBoard[x][y] = '*';
        playerScore += 1;
    }
}

void computerTurn(){
    int x, y;
    x = (rand() % BOARD_WIDTH) - 1;
    y = (rand() % BOARD_HEIGHT) - 1;
    std::cout << "x : " << x << " y : " << y << std::endl;
    if(playerBoard[x][y] == water){
        std::cout << "Computer MISS" << std::endl;
        playerBoard[x][y] = 'm'; 
    }
    if(playerBoard[x][y] != water){
        std::cout << "Computer HIT" << std::endl; 
        playerBoard[x][y] = '*';
        compScore += 1;
    }

}

void playGame(){ 
    while(running){
        takeTurn(player);
        computerTurn();
        checkWinner();
    }
}

void checkWinner(){
    if(playerScore == 17){
        std::cout << "Player wins!!" << std::endl;
        running = false;
    }
    if(compScore == 17){
        std::cout << "Computer wins." << std::endl;
        running = false;
    }
}

int main(){
    srand(time(0));
    ResetBoard(playerBoard);
    ResetBoard(compBoard);
    PrintBoard(playerBoard, player);
    setUpGame();
    computerBoard();
    ResetBoard(hitBoard);
    PrintBoard(compBoard, computer);
    playGame();

    return 0;
}