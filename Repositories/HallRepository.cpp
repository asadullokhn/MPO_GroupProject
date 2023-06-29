#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <list>
#include "..\Entities\Hall.cpp"

using namespace std;

class HallRepository
{
protected:
    string filePath = "./Data/halls.txt";
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
    void create(Hall hall)
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

    list<Hall> getAll()
    {
        string str;
        list<Hall> returnHalls{};

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

            Hall tempHall(stoi(props[0]), stoi(props[1]), stoi(props[2]));

            returnHalls.push_back(tempHall);
        }

        file.close();
        return returnHalls;
    }

    optional<Hall> get(int id)
    {
        for (Hall h : getAll())
            if (h.getId() == id)
                return h;

        return nullopt;
    }

    bool remove(int id)
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

        ofstream of(filePath);
        for (Hall h : items)
            of << to_string(h.getId()) + "~" + to_string(h.getNumberOfRows()) + "~" + to_string(h.getNumberOfSeatsPerRow()) + "\n";

        of.close();

        return true;
    }
};