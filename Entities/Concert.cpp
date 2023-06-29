#include <iostream>

using namespace std;

class Concert
{
private:
    int id;
    string title;
    int rating;

public:
    Concert(string title, int rating)
    {
        this->title = title;
        this->rating = rating;
    }
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
        return "Concert: " + title + "\nRating: " + to_string(rating) + "\n";
    }
};
