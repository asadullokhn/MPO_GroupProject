#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <list>
#include "..\Entities\Concert.cpp"

using namespace std;

class ConcertRepository : public BaseRepository<Concert>
{
public:
    ConcertRepository()
    {
        filePath = "./Data/concerts.txt";
    }

    int create(Concert concert) override
    {
        list<Concert> cons = getAll();
        int lastId = 0;

        if (cons.size() > 0)
        {
            Concert c = cons.back();
            lastId = c.getId() + 1;
        }

        // 45~Salom Nomi~45
        string toWrite = to_string(lastId) + "~" + concert.getTitle() + "~" + to_string(concert.getRating()) + "\n";
        _writeToFile(toWrite, ios::app);

        return lastId;
    }

    list<Concert> getAll() override
    {
        list<Concert> returnConcerts{};
        ifstream file(filePath);
        string str;

        while (getline(file, str))
        {
            split(str, '~');

            Concert tempConcert(stoi(props[0]), props[1], stoi(props[2]));

            returnConcerts.push_back(tempConcert);
        }

        file.close();
        return returnConcerts;
    }

    optional<Concert> get(int id) override
    {
        for (Concert c : getAll())
            if (c.getId() == id)
                return c;

        return nullopt;
    }

    bool removeById(int id) override
    {
        list<Concert> items = getAll();
        list<Concert>::iterator it = items.begin();

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
        for (Concert c : items)
            file << to_string(c.getId()) + "~" + c.getTitle() + "~" + to_string(c.getRating()) + "\n";

        file.close();

        return true;
    }
};