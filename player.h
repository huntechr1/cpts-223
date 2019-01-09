//
// Created by Christian Hunter on 10/9/18.
//

#ifndef PA4_PLAYER_H
#define PA4_PLAYER_H

#include <iostream>

using std::ostream;
using std::cout;
using std::endl;

class Player
{
public:
    Player();
    Player(int newID, int newX, int newY);

    int getID() const;

    int getX() const;

    int getY() const;

    void setID(int ID);

    void setX(int x);

    void setY(int y);

    ~Player();
private:
    int ID;
    int x;
    int y;
};

ostream &operator << (ostream &lhs, Player &rhs);

#endif //PA4_PLAYER_H
