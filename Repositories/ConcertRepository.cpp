#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <list>
#include "..\Entities\Concert.cpp"

using namespace std;

class ConcertRepository
{
protected:
    string filePath = "./Data/concerts.txt";
    string props[3];

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
    void create(Concert concert)
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

    list<Concert> getAll()
    {
        string str;
        list<Concert> returnConcerts{};

        ifstream file(filePath);
        if (!file)
        {
            file.close();

            ofstream f(filePath);
            f << "";
            f.close();
        }

        while (getline(file, str))
        {
            split(str, '~');

            Concert tempConcert(stoi(props[0]), props[1], stoi(props[2]));

            returnConcerts.push_back(tempConcert);
        }

        file.close();
        return returnConcerts;
    }

    optional<Concert> get(int id)
    {
        for (Concert c : getAll())
            if (c.getId() == id)
                return c;

        return nullopt;
    }

    bool remove(int id)
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

        ofstream of(filePath);
        for (Concert c : items)
            of << to_string(c.getId()) + "~" + c.getTitle() + "~" + to_string(c.getRating()) + "\n";

        of.close();

        return true;
    }
};