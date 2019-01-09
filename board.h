//
// Created by Christian Hunter on 10/9/18.
//

#ifndef PA4_BOARD_H
#define PA4_BOARD_H

#include "player.h"
#include <map>


class Board
{
public:
    Board();
    Board(int size);

    bool Insert(Player newPlayer);
    bool Insert(int newID, int newX, int newY);
    bool find(int ID);
    void PrintByID();
    void printLocations();
    bool checkXY(int x, int y);
    bool remove(int ID);
    bool remove(int x, int y);
    bool removeLocation(int x, int y);
    bool MoveTo(int ID, int x, int y);
    bool checkDiagonals(Player player, int newX, int newY);


    void setM(int m);
    void setN(int n);

    int getM() const;
    int getN() const;

    ~Board();

private:

    int m;
    int n;
    std::map<int, Player> players;
    std::multimap<int, Player> locations;

};

#endif //PA4_BOARD_H
