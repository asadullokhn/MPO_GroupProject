#include <iostream>

using namespace std;

class Hall
{
    int id;
    int numberOfRows;
    int numberOfSeatsPerRow;

public:
    Hall(int id, int numberOfRows, int numberOfSeatsPerRow)
    {
        this->id = id;
        this->numberOfRows = numberOfRows;
        this->numberOfSeatsPerRow = numberOfSeatsPerRow;
    }

    int getID() { return id; }

    int getNumberOfSeatsPerRow() { return numberOfSeatsPerRow; }

    int getNumberOfRows() { return numberOfRows; }

    int getNumberOfTickets() { return numberOfRows * numberOfSeatsPerRow; }

    string toString()
    {
        string hallStr = "Hall ID: " + to_string(id) + "\n";
        hallStr += "Number of Rows: " + to_string(numberOfRows) + "\n";
        hallStr += "Number of Seats per Row: " + to_string(numberOfSeatsPerRow) + "\n";
        return hallStr;
    }
};
