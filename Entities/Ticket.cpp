#include <iostream>
#include <string>

using namespace std;

class Ticket
{
protected:
    int id;
    int row;
    int seat;
    int sessionId;
    bool isOccupied = false;

public:
    Ticket() {}

    Ticket(int ticketRow, int ticketSeat)
        : row(ticketRow), seat(ticketSeat) {}

    Ticket(int ticketSessionId, int ticketRow, int ticketSeat)
        : sessionId(ticketSessionId), row(ticketRow), seat(ticketSeat) {}

    Ticket(int ticketId, int ticketSessionId, int ticketRow, int ticketSeat, bool isTicketOccupied)
        : id(ticketId), sessionId(ticketSessionId), row(ticketRow), seat(ticketSeat), isOccupied(isTicketOccupied) {}

    int getId() { return id; }
    int getRow() { return row; }
    int getSeat() { return seat; }
    int getSessionId() { return sessionId; }

    string getSeatNumberAsString()
    {
        return static_cast<char>(row + 65) + to_string(seat);
    }

    bool getIsOccupied()
    {
        return isOccupied;
    }

    void setIsOccupied(bool isOccupied)
    {
        this->isOccupied = isOccupied;
    }

    string toString()
    {
        string ticketStr = "Ticket Information:\n";
        ticketStr += "Seat Number: " + getSeatNumberAsString() + "\n";
        ticketStr += "Is Occupied: " + string(isOccupied ? "Yes" : "No") + "\n";
        return ticketStr;
    }
};
