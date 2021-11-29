#ifndef __HPP_BSHIP__
#define __HPP_BSHIP__

#include <string> 

class Board{
    public: 
    //constructor
        Board();
    //getters
        std::string getBoardWidth();
        std::string getBoardHeight();
    //setters
        void setBoardWidth(int width);
        void setBoardHeight(int height);

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