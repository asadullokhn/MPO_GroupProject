#include <iostream>

using namespace std;

class Concert {
    string title;
    int rating;

public:
    Concert(string title, int rating) {
        this->title = title;
        this->rating = rating;
    }

    string getTitle() {
        return title;
    }

    int getRating() {
        return rating;
    }

    string toString() {
        return "Concert: " + title + "\nRating: " + to_string(rating) + "\n";
    }
};
