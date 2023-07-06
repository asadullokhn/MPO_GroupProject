#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <list>
#include "./BaseRepository.cpp"
#include "..\Entities\Session.cpp"

using namespace std;

class SessionRepository : public BaseRepository<Session>
{
public:
    SessionRepository()
    {
        filePath = "./Data/sessions.txt";
    }

    int create(Session session) override
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

        _writeToFile(toWrite, ios::app);

        return lastId;
    }

    list<Session> getAll() override
    {
        list<Session> returnSessions{};
        ifstream file(filePath);
        string str;

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

    optional<Session> get(int id) override
    {
        for (Session h : getAll())
            if (h.getId() == id)
                return h;

        return nullopt;
    }

    bool removeById(int id) override
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

        return _remove(items, choosenSessionId);
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

        return _remove(items, choosenSessionId);
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

        return _remove(items, choosenSessionId);
    }

private:
    bool _remove(list<Session> sessions, int choosenSessionId)
    {
        ofstream of;
        of.open(filePath, ios::out);

        for (Session s : sessions)
            // id~hallId~concertId~startingTime
            of << to_string(s.getId()) + "~" +
                      to_string(s.getHall().getId()) + "~" +
                      to_string(s.getConcert().getId()) + "~" +
                      s.getStartTime() + "\n";

        of.close();

        TicketRepository tickRepo;
        tickRepo.removeAllBySession(choosenSessionId);

        return true;
    }
};