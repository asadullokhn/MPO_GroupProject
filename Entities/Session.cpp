#include <iostream>
#include "Hall.cpp"
#include "Concert.cpp"
#include "Ticket.cpp"

using namespace std;

class Session
{
    int id;
    Hall hall;
    Concert concert;
    string startTime;

    Ticket **tickets;

public:
    Session(Concert sessionConcert, Hall sessionHall, string sessionStartTime)
        : concert(sessionConcert), hall(sessionHall), startTime(sessionStartTime)
    {
        int numberOfRows = sessionHall.getNumberOfRows();
        int numberOfSeats = sessionHall.getNumberOfSeatsPerRow();

        tickets = new Ticket *[numberOfRows];
        for (int i = 0; i < numberOfRows; i++)
        {
            tickets[i] = new Ticket[numberOfSeats];

            for (int j = 0; j < numberOfSeats; j++)
                tickets[i][j] = Ticket(i, j + 1);
        }
    }

    Hall getHall() { return hall; }

    Concert getConcert() { return concert; }

    Ticket **getTickets() { return tickets; }

    string getStartTime() { return startTime; }

    bool buyTicket(int row, int seatNumber)
    {
        if (!isTicketAvailable(row, seatNumber))
            return false;

        tickets[row][seatNumber].setIsOccupied(true);
        return true;
    }

    bool isTicketAvailable(int row, int seatNumber)
    {
        if (row > hall.getNumberOfRows() || seatNumber > hall.getNumberOfSeatsPerRow() || row < 0 || seatNumber < 0)
            return false;

        return !tickets[row][seatNumber].getIsOccupied();
    }

    string toString()
    {
        return "\033[1;32m" + concert.getTitle() \
            + "\033[0m | \033[1;32m" + startTime \
            + "\033[0m | \033[1;32mHall-" \
            + to_string(hall.getID()) + "\033[0m";
    }
};
