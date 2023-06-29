#include <iostream>

using namespace std;

class Hall
{
    int id;
    int numberOfRows;
    int numberOfSeatsPerRow;

public:
    Hall(int numberOfRows, int numberOfSeatsPerRow)
    {
        this->numberOfRows = numberOfRows;
        this->numberOfSeatsPerRow = numberOfSeatsPerRow;
    }
    
    Hall(int id, int numberOfRows, int numberOfSeatsPerRow)
    {
        this->id = id;
        this->numberOfRows = numberOfRows;
        this->numberOfSeatsPerRow = numberOfSeatsPerRow;
    }

    int getId() { return id; }

    int getNumberOfSeatsPerRow() { return numberOfSeatsPerRow; }

    int getNumberOfRows() { return numberOfRows; }

    int getNumberOfTickets() { return numberOfRows * numberOfSeatsPerRow; }

    string toString()
    {
        return "\033[1;32mHall-" + to_string(id) +
               "\033[0m | Rows: \033[1;32m" + to_string(numberOfRows) +
               "\033[0m | Seat:\033[1;32m" + to_string(numberOfSeatsPerRow) +
               "\033[0m | Tickets: \033[1;32m" + to_string(getNumberOfTickets()) + "\033[0m";
    }
};
