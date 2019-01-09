//
// Created by Christian Hunter on 10/9/18.
//
#include "board.h"

Board::Board()
{
    this->m = 0;
    this->n = 0;
}

Board::Board(int size)
{
    this->m = size;
    this->n = 0;
}

Board::~Board()
{

}

// Inserts a player into the players map and locations multimap
// Returns true if insertion is successful false if not

bool Board::Insert(Player newPlayer)
{
    bool found = true, inserted = false;

    // Check to make sure the ID isn't already in the players map
    this->n++;
    try {
        this->players.at(newPlayer.getID());
    }
    catch(const std::out_of_range& oor)
    {
        found = false;
    }

    // If the ID isn't already inserted then move on
    if(!found)
    {
        // Check if (X,Y) is already occupied, insert if not
        if(!(this->checkXY(newPlayer.getX(),newPlayer.getY()))) {
            this->players.emplace(newPlayer.getID(), newPlayer);
            this->locations.emplace(newPlayer.getX(), newPlayer);
            inserted = true;
        }

        else
        {
            cout << "Position (" << newPlayer.getX() << "," << newPlayer.getY() << ") already occupied, insertion failed" << endl;
            this->n--;
            inserted = false;
        }
    }

    else
    {
        cout << "ID: " << newPlayer.getID() << " already exists, insertion failed" << endl;
        this->n--;
        inserted = false;
    }
    return inserted;
}

// Creates a new player with an ID, X, and Y value and place it into the players map and locations multimap
// Returns true if insertion is successful false if not
bool Board::Insert(int newID, int newX, int newY)
{
    Player tempPlayer(newID, newX, newY);

    bool found = true, inserted = false;

    // Increase number of players
    this->n++;

    // Check if number of players is less than or equal to board size
    if(this->n <= this->m) {

        // Check If the ID is already inserted
        try {
            this->players.at(newID);
        }
        catch (const std::out_of_range &oor) {
            found = false;
        }

        // If ID isn't inserted than continue
        if (!found) {
            // If (X,Y) value isn't already being used continue
            if (!(this->checkXY(newX, newY))) {
                // Insert player into players map and locations multimap
                this->players.emplace(newID, tempPlayer);
                this->locations.emplace(tempPlayer.getX(), tempPlayer);
                inserted = true;
            } else {
                cout << "Position (" << newX << "," << newY << ") already occupied, insertion failed" << endl;
                // If player wasn't inserted decrease number of players
                this->n--;
                inserted = false;
            }
        } else {
            cout << "ID: " << newID << " already exists, insertion failed" << endl;
            // Decrease number of players
            this->n--;
            inserted = false;
        }
    }

    else
    {
        cout << "Too many players" << endl;
        // Decrease number of players
        this->n--;
        inserted = false;
    }
    return inserted;
}

void Board::setM(int m) {
    this->m = m;
}

void Board::setN(int n) {
    this->n = n;
}

int Board::getM() const {
    return this->m;
}

int Board::getN() const {
    return this->n;
}

// Checks if a given ID number is already inserted into the players map
// Returns true if found false if not
bool Board::find(int ID)
{
    bool found = true;
    try {
        this->players.at(ID);
    }
    catch(const std::out_of_range& oor)
    {
        found = false;
    }

    return found;
}

// Prints all players in order by ID number
void Board::PrintByID()
{
    std::map<int, Player>::iterator it;
    // Assign iterator to the beginning of the map
    it = players.begin();
    // Loop until at the end of the map
    while(it != players.end())
    {
        cout << it->second << endl;
        it++;
    }
}

// Determines if a given x,y value is already being used
// Returns true if already inserted false if not
bool Board::checkXY(int x, int y)
{
    bool found = false;
    std::pair<std::multimap<int, Player>::iterator, std::multimap<int,Player>::iterator> ret;
    // Assigns ret to the range of values that all have the same key
    ret = this->locations.equal_range(x);

    // Iterate through the range and check Y values for a correct match
    for(std::multimap<int,Player>::iterator it = ret.first; it != ret.second && !found; ++it)
    {
        if((it->second).getY() == y)
        {
            found = true;
        }
    }

    return found;
}

// Removes a player from the players map and locations multimap with an ID number
// Returns true if removal is successful and false if not
bool Board::remove(int ID)
{
    bool found = false, removed = false;
    std::pair<std::multimap<int, Player>::iterator, std::multimap<int,Player>::iterator> ret;
    std::map<int, Player>::iterator pIt;

    //find the player with matching ID and return an iterator to its object in players std::map
    pIt = this->players.find(ID);

    //Check and make sure the player was actually found
    if(pIt != this->players.end()) {
        //Get the beginning and end iterator to the range that matches the players x value
        ret = this->locations.equal_range((pIt->second).getX());

        // Check all y values in x range with the found players y value
        std::multimap<int, Player>::iterator lIt = ret.first;
        for (; lIt != ret.second && !found; ++lIt) {
            if ((lIt->second).getY() == (pIt->second).getY()) {
                found = true;
            }
        }

        // If the player is found then remove from locations and players
        if (found) {
            lIt--;
            cout << "Player: " << lIt->second << " was removed" << endl;
            this->locations.erase(lIt);
            this->players.erase(pIt);
            this->n--;
            removed = true;
        }
    }

    else
    {
        cout << "Error: Player not found for removal" << endl;
    }

    return removed;
}

// Removes a player from the players map and locations multimap based on an X,Y value
// Returns true if removed false if not
bool Board::remove(int x, int y)
{
    bool found = false, removed = false;
    std::pair<std::multimap<int, Player>::iterator, std::multimap<int, Player>::iterator> ret;

    ret = this->locations.equal_range(x);

    // Check all y values in x range with the found players y value
    std::multimap<int, Player>::iterator lIt = ret.first;
    for (; lIt != ret.second && !found; ++lIt) {
        if ((lIt->second).getY() == y) {
            found = true;
        }
    }

    // If player is found then remove from locations and players
    if(found)
    {
        std::map<int, Player>::iterator pIt;
        lIt--;

        cout << "Player: "<< lIt->second << " was removed" << endl;
        pIt = this->players.find((lIt->second).getID());
        this->locations.erase(lIt);
        this->players.erase(pIt);
        this->n--;
        removed = true;
    }
   /* else
    {
        cout << "Error: Player not found for removal" << endl;
    } */

    return removed;
}

// Removes a location from the locations multimap
// Returns true if removed and false if not
bool Board::removeLocation(int x, int y)
{
    bool found = false, removed = false;
    std::pair<std::multimap<int, Player>::iterator, std::multimap<int, Player>::iterator> ret;

    ret = this->locations.equal_range(x);

    // Check all y values in x range with the found players y value
    std::multimap<int, Player>::iterator lIt = ret.first;
    for (; lIt != ret.second && !found; ++lIt) {
        if ((lIt->second).getY() == y) {
            found = true;
        }
    }

    // If player found then remove from locations
    if(found)
    {
        lIt--;
        this->locations.erase(lIt);
        removed = true;
    }
    return removed;
}

// Prints all players locations on the board
void Board::printLocations()
{
    std::multimap<int, Player>::iterator it = this->locations.begin();

    cout << "Player locations:" << endl;
    // Iterate through the entire locations multimap printing locations of players
    while(it != this->locations.end())
    {
        cout << it->first << " ";
        cout << (it->second).getY() << endl;
        it++;
    }
}

// Moves a player to a new position, removes a player if they are in the position being moved to
// Returns true if move is successful, false if not
bool Board::MoveTo(int ID, int x, int y)
{
    bool success = false;
    // Check if new location is on the board
    if(x <= this->m && y <= this->m)
    {
        std::map<int, Player>::iterator it;
        it = this->players.find(ID);

        // Check if new position is either in the same column, row, or in a diagonal
            if ( x == it->second.getX() || y == it->second.getY() || this->checkDiagonals(it->second, x, y)) {

                this->removeLocation(it->second.getX(), it->second.getY());
                (it->second).setX(x);
                (it->second).setY(y);
                this->remove(x, y);
                this->locations.emplace(x, it->second);
                success = true;
            }

            else{
                cout << "Error: Move location invalid" << endl;
            }
    }

    else
    {
        cout << "Error: X or Y is out of bounds" << endl;
    }

    return success;
}

// Checks if new position is in a diagonal from players previous position
bool Board::checkDiagonals(Player player, int newX, int newY)
{
    bool found = false;

    // Check up right diagonal
    for(int tempX = player.getX(), tempY = player.getY(); tempX <= this->m && tempY <= this->m && !found; tempX++, tempY++)
    {
        if(tempX == newX && tempY == newY)
        {
            found = true;
        }
    }

    // Check up left diagonal
    if(!found)
    {
        for(int tempX = player.getX(), tempY = player.getY(); tempX >= 0 && tempY <= this->m && !found; tempX--, tempY++)
        {
            if(tempX == newX && tempY == newY)
            {
                found = true;
            }
        }
    }

    // Check right down diagonal
    if(!found)
    {
        for(int tempX = player.getX(), tempY = player.getY(); tempX <= this->m && tempY >= 0 && !found; tempX++, tempY--)
        {
            if(tempX == newX && tempY == newY)
            {
                found = true;
            }
        }
    }

    // Check down left diagonal
    if(!found)
    {
        for(int tempX = player.getX(), tempY = player.getY(); tempX >= 0 && tempY >= 0 && !found; tempX--, tempY--)
        {
            if(tempX == newX && tempY == newY)
            {
                found = true;
            }
        }
    }

    return found;
}