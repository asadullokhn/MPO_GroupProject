#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <list>
#include "..\Entities\Ticket.cpp"

using namespace std;

class TicketRepository : public BaseRepository<Ticket>
{
public:
    TicketRepository()
    {
        filePath = "./Data/tickets.txt";
    }

    int create(Ticket ticket) override
    {
        list<Ticket> tickets = getAll();

        int lastId = 0;
        if (tickets.size() > 0)
        {
            Ticket h = tickets.back();
            lastId = h.getId() + 1;
        }

        // id~sessionId~row~seat~isOccupied
        string toWrite = to_string(lastId) + "~" +
                         to_string(ticket.getSessionId()) + "~" +
                         to_string(ticket.getRow()) + "~" +
                         to_string(ticket.getSeat()) + "~" +
                         to_string(ticket.getIsOccupied()) + "\n";

        _writeToFile(toWrite, ios::app);

        return lastId;
    }

    void createAll(Ticket **ticketArray, int sessionId, int numberOfRows, int numberOfSeats)
    {
        list<Ticket> tickets = getAll();
        int lastId = 0;

        if (tickets.size() > 0)
        {
            Ticket h = tickets.back();
            lastId = h.getId() + 1;
        }

        string toWrite = "";
        for (int i = 0; i < numberOfRows; i++)
            for (int j = 0; j < numberOfSeats; j++)
                // id~sessionId~row~seat~isOccupied
                toWrite += to_string(lastId++) + "~" +
                           to_string(sessionId) + "~" +
                           to_string(ticketArray[i][j].getRow()) + "~" +
                           to_string(ticketArray[i][j].getSeat()) + "~" +
                           to_string(ticketArray[i][j].getIsOccupied()) + "\n";

        ofstream of;
        of.open(filePath, ios::app);

        if (!of)
        {
            of.close();

            ofstream file(filePath);
            file << toWrite;
            file.close();
        }
        else
        {
            of << toWrite;
            of.close();
        }
    }

    list<Ticket> getAll() override
    {
        list<Ticket> returnTickets{};
        ifstream file(filePath);
        string str;

        while (getline(file, str))
        {
            // id~sessionId~row~seat~isOccupied
            split(str, '~');
            Ticket tempTicket(stoi(props[0]), stoi(props[1]), stoi(props[2]), stoi(props[3]), bool(stoi(props[4])));

            returnTickets.push_back(tempTicket);
        }

        file.close();
        return returnTickets;
    }

    Ticket **getAll(int sessionId, int rowSize, int seatPerRow)
    {
        list<Ticket> items = getAll();
        list<Ticket>::iterator it = items.begin();

        while (it != items.end())
        {
            if (it->getSessionId() != sessionId)
            {
                it = items.erase(it);
                continue;
            }
            it++;
        }

        Ticket **arr = new Ticket *[rowSize];
        for (int i = 0; i < rowSize; i++)
            arr[i] = new Ticket[seatPerRow];

        int i = 0, j = 0;
        for (Ticket t : items)
        {
            arr[i][j++] = t;

            if (j == seatPerRow)
            {
                j = 0;
                i++;
            }
        }

        return arr;
    }

    optional<Ticket> get(int id) override
    {
        for (Ticket h : getAll())
            if (h.getId() == id)
                return h;

        return nullopt;
    }

    bool removeById(int id) override
    {
        list<Ticket> items = getAll();
        list<Ticket>::iterator it = items.begin();

        // Deleting element from list while iterating
        while (it != items.end())
        {
            if (it->getId() == id)
            {
                it = items.erase(it);
                continue;
            }
            it++;
        }

        ofstream file(filePath);
        for (Ticket ticket : items)
            // id~sessionId~row~seat~isOccupied
            file << to_string(ticket.getId()) + "~" +
                        to_string(ticket.getSessionId()) + "~" +
                        to_string(ticket.getRow()) + "~" +
                        to_string(ticket.getSeat()) + "~" +
                        to_string(ticket.getIsOccupied()) + "\n";

        file.close();

        return true;
    }

    bool removeAllBySession(int sessionId)
    {
        list<Ticket> items = getAll();
        list<Ticket>::iterator it = items.begin();

        // Deleting element from list while iterating
        while (it != items.end())
        {
            if (it->getSessionId() == sessionId)
            {
                it = items.erase(it);
                continue;
            }
            it++;
        }

        ofstream file(filePath);
        for (Ticket ticket : items)
            // id~sessionId~row~seat~isOccupied
            file << to_string(ticket.getId()) + "~" +
                        to_string(ticket.getSessionId()) + "~" +
                        to_string(ticket.getRow()) + "~" +
                        to_string(ticket.getSeat()) + "~" +
                        to_string(ticket.getIsOccupied()) + "\n";

        file.close();

        return true;
    }

    void update(int id, bool isOccupied)
    {
        list<Ticket> tickets = getAll();

        ofstream file(filePath);
        for (Ticket t : tickets)
        {
            if (t.getId() == id)
                t.setIsOccupied(isOccupied);

            file << to_string(t.getId()) + "~" +
                        to_string(t.getSessionId()) + "~" +
                        to_string(t.getRow()) + "~" +
                        to_string(t.getSeat()) + "~" +
                        to_string(t.getIsOccupied()) + "\n";
        }

        file.close();
    }
};