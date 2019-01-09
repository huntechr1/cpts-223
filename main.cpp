/*
#include <iostream>
#include "board.h"

using namespace std;

int main() {

    int x = 10, y = 11, newX = 9, newY = 9, size = 100;
    bool found = false;

    for(int tempX = x, tempY = y; tempX >= 0 && tempY >= 0 && found == false; tempX--, tempY--)
    {
        if(tempX == newX && tempY == newY)
        {
            found = true;
        }
    }

    if(found == true)
    {
        cout << "Ok" << endl;
    }
    else
    {
        cout << "Not allowed" << endl;
    }

    Player p1(5,2,3);
    Player p2(7,3,4);
    Player p3(1,4,5);
    Player p4(9,4,5);
    Player p5(9,4,7);

    std::map<int, Player> temp;
    std::map<int, Player>::iterator it;
    std::map<int, Player>::iterator it2;

    temp.emplace(p1.getID(), p1);
    temp.emplace(p2.getID(), p2);
    temp.emplace(p3.getID(), p3);

    for(it2 = temp.begin(); it2 != temp.end(); it2++)
    {
        cout << it2->second << endl;
    }

    it = temp.find(p1.getID());
    (it->second).setX(50);
    (it->second).setY(100);

    for(it2 = temp.begin(); it2 != temp.end(); it2++)
    {
        cout << it2->second << endl;
    }



    Board board(50);

    board.Insert(1,2,5);
    board.Insert(2,9,5);
    board.Insert(4,2,7);
    board.Insert(3,3,5);


    board.PrintByID();
    board.printLocations();

    cout << "--------------" << endl;

    board.MoveTo(2, 30, 25);
    board.MoveTo(1, 55, 4);
    board.MoveTo(3, 23, 56);
    board.MoveTo(4, 3, 5);

    board.PrintByID();
    board.printLocations();

    return 0;
}
*/

