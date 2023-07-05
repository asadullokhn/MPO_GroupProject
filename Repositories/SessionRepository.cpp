#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <list>
#include "..\Entities\Session.cpp"

using namespace std;

class SessionRepository
{
protected:
    string filePath = "./Data/sessions.txt";
    string props[4];

    int len(string str)
    {
        int length = 0;
        for (int i = 0; str[i] != '\0'; i++)
            length++;

        return length;
    }

    void split(string str, char seperator)
    {
        int currIndex = 0, i = 0;
        int startIndex = 0, endIndex = 0;
        while (i <= len(str))
        {
            if (str[i] == seperator || i == len(str))
            {
                endIndex = i;
                string subStr = "";
                subStr.append(str, startIndex, endIndex - startIndex);
                props[currIndex] = subStr;
                currIndex += 1;
                startIndex = endIndex + 1;
            }
            i++;
        }
    }

public:
    // returns new session id
    int create(Session session)
    {
        list<Session> sessions = getAll();
        int lastId = 0;

        if (sessions.size() > 0)
        {
            Session s = sessions.back();
            lastId = s.getId() + 1;
        }

        // id~hallId~concertId~startingTime
        string toWrite = to_string(lastId) + "~" +
                         to_string(session.getHall().getId()) + "~" +
                         to_string(session.getConcert().getId()) + "~" +
                         session.getStartTime() + "\n";

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

        return lastId;
    }

    list<Session> getAll()
    {
        string str;
        list<Session> returnSessions{};

        ifstream file(filePath);
        if (!file)
        {
            file.close();

            ofstream f(filePath);
            f << "";
            f.close();
        }

        ConcertRepository concertRepo;
        HallRepository hallRepo;
        TicketRepository ticketRepo;

        while (getline(file, str))
        {
            // id~hallId~concertId~startingTime
            split(str, '~');

            Hall h = hallRepo.get(stoi(props[1])).value();
            Concert c = concertRepo.get(stoi(props[2])).value();
            Ticket **ticks = ticketRepo.getAll(stoi(props[0]), h.getNumberOfRows(), h.getNumberOfSeatsPerRow());

            Session tempSession(stoi(props[0]), c, h, props[3], ticks);
            returnSessions.push_back(tempSession);
        }

        file.close();

        return returnSessions;
    }

    optional<Session> get(int id)
    {
        for (Session h : getAll())
            if (h.getId() == id)
                return h;

        return nullopt;
    }

    bool remove(int id)
    {
        list<Session> items = getAll();
        list<Session>::iterator it = items.begin();

        int choosenSessionId = id;
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

        string toWrite = "";
        for (Session s : items)
            // id~hallId~concertId~startingTime
            toWrite += to_string(s.getId()) + "~" +
                       to_string(s.getHall().getId()) + "~" +
                       to_string(s.getConcert().getId()) + "~" +
                       s.getStartTime() + "\n";

        ofstream of;
        of.open(filePath, ios::out);

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

        TicketRepository tickRepo;
        tickRepo.removeAllBySession(choosenSessionId);

        return true;
    }

    bool removeByConcert(int concertId)
    {
        list<Session> items = getAll();
        list<Session>::iterator it = items.begin();

        int choosenSessionId = -1;

        // Deleting element from list while iterating
        while (it != items.end())
        {
            if (it->getConcert().getId() == concertId)
            {
                choosenSessionId = it->getId();
                it = items.erase(it);
                continue;
            }
            it++;
        }

        string toWrite = "";
        for (Session s : items)
            // id~hallId~concertId~startingTime
            toWrite += to_string(s.getId()) + "~" +
                       to_string(s.getHall().getId()) + "~" +
                       to_string(s.getConcert().getId()) + "~" +
                       s.getStartTime() + "\n";

        ofstream of;
        of.open(filePath, ios::out);

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

        TicketRepository tickRepo;
        tickRepo.removeAllBySession(choosenSessionId);

        return true;
    }

    bool removeByHall(int hallId)
    {
        list<Session> items = getAll();
        list<Session>::iterator it = items.begin();

        int choosenSessionId = -1;
        // Deleting element from list while iterating
        while (it != items.end())
        {
            if (it->getHall().getId() == hallId)
            {
                choosenSessionId = it->getId();
                it = items.erase(it);
                continue;
            }
            it++;
        }

        string toWrite = "";
        for (Session s : items)
            // id~hallId~concertId~startingTime
            toWrite += to_string(s.getId()) + "~" +
                       to_string(s.getHall().getId()) + "~" +
                       to_string(s.getConcert().getId()) + "~" +
                       s.getStartTime() + "\n";

        ofstream of;
        of.open(filePath, ios::out);

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

        TicketRepository tickRepo;
        tickRepo.removeAllBySession(choosenSessionId);

        return true;
    }
};