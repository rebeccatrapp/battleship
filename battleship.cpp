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

/**
 * @brief Construct a new Ship:: Ship object
 * 
 * @param name 
 * @param size 
 * @param tag 
 */
Ship::Ship(std::string name, int size, char tag){
    this->name = name;
    this->size = size;
    this->tag = tag;
}

/**
 * @brief returns the Ships name 
 * 
 * @return std::string 
 */
std::string Ship::getShipName(){
    return name;
}

/**
 * @brief returns the Ship's size 
 * 
 * @return int 
 */
int Ship::getShipSize(){
    return size;
}

/**
 * @brief returns the Ship's tag. A unique identifier for each ship. 
 * 
 * @return char 
 */
char Ship::getShipTag(){
    return tag;
}

/**
 * @brief set's the ship's name
 * 
 */
void Ship::setShipName(){
    this->name = name;
}

/**
 * @brief set's the ship's size. 
 * 
 */
void Ship::setShipSize(){
    this->size = size;
}

/**
 * @brief set's the ship's tag. 
 * 
 */
void Ship::setShipTag(){
    this->tag = tag;
}

/**
 * @brief Prints out the board, a multidimensional array. 
 * 
 * @param b - the board which is being printed
 * @param p - player number
 */
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

/**
 * @brief initializes and resets the board to be blank
 * 
 * @param b 
 */
void ResetBoard(char b[BOARD_WIDTH][BOARD_HEIGHT]){
    for(int h = 0; h<BOARD_HEIGHT; h++){
        for(int w = 0; w<BOARD_WIDTH; w++){
            b[h][w] = water;
        }
    }
}

/**
 * @brief Places a ship tmp. The board it's placed on is dependant on which player (p) is going. 
 * I struggled to get the computerPlayer to behave, this is probably because of the rands.
 * The player part is working great though. 
 * 
 * @param tmp 
 * @param p 
 */
void shipPlacement(Ship tmp, int p){
    int d;
    int x, y; 
    bool notoccupied = false;
    //if the player is human, ask them for their input. d is direction, x is for xcoords, y is for ycoords
    if(p == player){
        std::cin >> d >> x >> y;
    }
    //if the player is the computer, randomly generates a direction (0 or 1) and then randomly generates an x and y based on the board width and board height
    if(p == computer){
        d = rand() % 2;
        x = rand() % BOARD_WIDTH;
        y = rand() % BOARD_HEIGHT; 
    }
    //if they want it to be horizontal 
    if(d == 0){
        if(p == player){
            for(int i = 0; i < tmp.getShipSize(); i++){
                //check to make sure that the entire ships length is 'water' and therefore available, so no overlapping. 
                if(playerBoard[y-1][x+i-1] == water){
                    for(int j = 0; j < tmp.getShipSize(); j++){
                        playerBoard[y-1][x+j-1] = tmp.getShipTag();
                    }
                    notoccupied = true;
                }
            }
        }
        //for some reason, this isn't doing so well. I tried to make it so that the computer couldn't stack ships over each other, but it is still doing that.
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
    //if the direction is vertical 
    if(d == 1){
        if(p == player){
            for(int i = 0; i < tmp.getShipSize(); i++){
                //checks to ensure that the whole ship's length is in water. Ensures that the ships can't overlap 
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
    //if the place they attempted to place the ship was invalid, recursively calls the function to have them try again 
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

/**
 * @brief Takes a Ship and gives the player a set of instructions. This is more so I didn't have to type a ton
 * 
 * @param a 
 */
void instructions(Ship a){
    std::string instructions = "To place ships enter 3 numbers followed by a space: The first number is for facing (0 is horizontal and 1 is vertical), the second number is x coords, and the third number is y coords";
    std::cout << instructions << std::endl;
    std::cout << "Ship to place: " << a.getShipName() << " which has a length of " << a.getShipSize() << std::endl;
    std::cout << "Where do you want to place it?" << std::endl; 
    shipPlacement(a, player);
}

/**
 * @brief sets up the game by adding ships and then calling on the instructions which then call on the shipPlacement 
 * 
 */
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

/**
 * @brief sets up the computer board
 * 
 */
void computerBoard(){
    Ship aircraftCarrierC("Aircraft Carrier", 5, 'A');
    Ship battleShipC("Battleship", 4, 'B');
    Ship cruiserC("Cruiser", 3, 'C');
    Ship submarineC("Submarine", 3, 'S');
    Ship destroyerC("Destroyer", 2 ,'D');
    shipPlacement(aircraftCarrierC, computer);
    shipPlacement(battleShipC, computer);
    shipPlacement(cruiserC, computer);
    shipPlacement(submarineC, computer);
    shipPlacement(destroyerC, computer);
}

/**
 * @brief When the human player takes a turn. It'll ask the player for a set of coordinates and then let them know if it's a hit or miss and display as such. 
 * 
 * @param p 
 */
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

/**
 * @brief This is the computer's turn. 
 * I know you said to not use rand, but for now, that's what I have 
 * This is also not working correctly and I'm not 100% sure why. 
 * 
 */
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

/**
 * @brief checks to see if there is a winner or not based on the number of points. 
 * 17 points is the total number of pips on the ships. 
 * 
 */
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

/**
 * @brief A function I made that could have maybe been in the main function, but basically, the player takes their turn, then the computer, then checks to ensure there is no winner.
 * 
 */
void playGame(){ 
    while(running){
        takeTurn(player);
        computerTurn();
        checkWinner();
    }
}

/**
 * @brief Main function.
 * 
 * @return int 
 */

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