#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <list>
#include "..\Entities\Hall.cpp"

using namespace std;

class HallRepository : public BaseRepository<Hall>
{
public:
    HallRepository()
    {
        filePath = "./Data/halls.txt";
    }

    int create(Hall hall) override
    {
        list<Hall> halls = getAll();

        int lastId = 0;
        if (halls.size() > 0)
        {
            Hall h = halls.back();
            lastId = h.getId() + 1;
        }

        string toWrite = to_string(lastId) + "~" +
                         to_string(hall.getNumberOfRows()) + "~" +
                         to_string(hall.getNumberOfSeatsPerRow()) + "\n";
        
        _writeToFile(toWrite, ios::app);

        return lastId;
    }

    list<Hall> getAll() override
    {
        list<Hall> returnHalls{};
        ifstream file(filePath);
        string str;

        while (getline(file, str))
        {
            split(str, '~');

            Hall tempHall(stoi(props[0]), stoi(props[1]), stoi(props[2]));

            returnHalls.push_back(tempHall);
        }

        file.close();
        return returnHalls;
    }

    optional<Hall> get(int id) override
    {
        for (Hall h : getAll())
            if (h.getId() == id)
                return h;

        return nullopt;
    }

    bool removeById(int id) override
    {
        list<Hall> items = getAll();
        list<Hall>::iterator it = items.begin();

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
        for (Hall h : items)
            file << to_string(h.getId()) + "~" + to_string(h.getNumberOfRows()) + "~" + to_string(h.getNumberOfSeatsPerRow()) + "\n";

        file.close();
        return true;
    }
};