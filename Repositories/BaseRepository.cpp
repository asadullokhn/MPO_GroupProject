#include <iostream>
#include <optional>
#include <fstream>
#include <list>

using namespace std;

template <typename T>
class BaseRepository
{
protected:
    string filePath;
    string props[5];

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

    void _writeToFile(string toWrite, ios::openmode mode)
    {
        ofstream of;
        of.open(filePath, mode);
        of << toWrite;
        of.close();
    }

public:
    // returns new created item's id
    virtual int create(T obj) = 0;

    // returns all items from database
    virtual list<T> getAll() = 0;

    // returns nullopt if item not found
    virtual optional<T> get(int id) = 0;

    // returns true if item has been deleted
    virtual bool removeById(int id) = 0;
};
