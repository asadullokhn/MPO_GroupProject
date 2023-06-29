#include <iostream>
#include "../Repositories/HallRepository.cpp"
#include "../Repositories/TicketRepository.cpp"
#include "../Repositories/ConcertRepository.cpp"

using namespace std;

class Session
{
    int id;
    Hall hall;
    Concert concert;
    string startTime;

    Ticket **tickets;

public:
    Session(int id, Concert sessionConcert, Hall sessionHall, string sessionStartTime, Ticket **sessionTickets)
        : concert(sessionConcert), hall(sessionHall), startTime(sessionStartTime), tickets(sessionTickets)
    {
        this->id = id;

        int numberOfRows = sessionHall.getNumberOfRows();
        int numberOfSeats = sessionHall.getNumberOfSeatsPerRow();
    }

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
            {
                tickets[i][j] = Ticket(i, j + 1);
            }
        }
    }

    int getId() { return id; }

    Hall getHall() { return hall; }

    Concert getConcert() { return concert; }

    Ticket **getTickets() { return tickets; }

    string getStartTime() { return startTime; }

    int getAvailableTicketsCount()
    {
        int numberOfRows = hall.getNumberOfRows();
        int numberOfSeats = hall.getNumberOfSeatsPerRow();

        int count = 0;
        for (int i = 0; i < numberOfRows; i++)
            for (int j = 0; j < numberOfSeats; j++)
                if (!tickets[i][j].getIsOccupied())
                    count++;

        return count;
    }

    bool buyTicket(int row, int seatNumber)
    {
        if (!isTicketAvailable(row, seatNumber))
            return false;

        tickets[row][seatNumber].setIsOccupied(true);

        TicketRepository repo;
        repo.update(tickets[row][seatNumber].getId(), true);

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
        string re = "\033[1;32m" + concert.getTitle();

        for (int i = 0; i < 25 - concert.getTitle().length(); i++)
            re += " ";
            
        re +=
            "\033[0m | \033[1;32m" + startTime +
            "\033[0m | \033[1;32mHall-" + to_string(hall.getId()) +
            "\033[0m | \033[1;32mTickets Left-" + to_string(getAvailableTicketsCount()) +
            "\033[0m";

        return re;
    }
};
