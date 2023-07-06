#include <iostream>

using namespace std;

class Concert
{
private:
    int id;
    string title;
    int rating;

public:
    // Constructor for creating a new object
    Concert(string title, int rating)
    {
        this->title = title;
        this->rating = rating;
    }

    // Constructor for loading an object from database
    Concert(int id, string title, int rating)
    {
        this->id = id;
        this->title = title;
        this->rating = rating;
    }

    string getTitle()
    {
        return title;
    }

    int getRating()
    {
        return rating;
    }

    int getId()
    {
        return id;
    }

    string toString()
    {
        string re = "\033[1;32m" + title;

        for (int i = 0; i < 25 - title.length(); i++)
            re += " ";

        re += "\033[0m | Concert Id: \033[1;32m" + to_string(id) +
              "\033[0m | Rating: \033[1;32m" + to_string(rating) +
              "\033[0m";

        return re;
    }
};
