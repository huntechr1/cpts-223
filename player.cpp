//
// Created by Christian Hunter on 10/9/18.
//

#include "player.h"

Player::Player()
{
    this->ID = -1;
    this->x = -1;
    this->y = -1;
}

Player::Player(int newID, int newX, int newY)
{
    this->ID = newID;
    this->x = newX;
    this->y = newY;
}


Player::~Player()
{

}

int Player::getID() const {
    return ID;
}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

void Player::setID(int ID) {
    this->ID = ID;
}

void Player::setX(int x) {
    this->x = x;
}

void Player::setY(int y) {
    this->y = y;
}

ostream &operator << (ostream &lhs, Player &rhs)
{

    lhs << "ID: " << rhs.getID() << " | ";
    lhs << "(X,Y): (" << rhs.getX() << ", ";
    lhs << rhs.getY() << ")";
    return lhs;
}

