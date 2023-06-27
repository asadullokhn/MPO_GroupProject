#include <iostream>
#include <conio.h>
#include "./Entities/Session.cpp"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

using namespace std;

class ConsoleGUI
{
private:
    enum ConsoleColoursEnum : int
    {
        red = 31,
        green = 32,
        yellow = 33,
        magenta = 35,
        cyan = 36
    };

    Concert concerts[5] = {
        Concert("John Doe Concert 1", 5),
        Concert("John Doe Concert 2", 7),
        Concert("John Doe Concert 3", 6),
        Concert("John Doe Concert 4", 9),
        Concert("John Doe Concert 5", 10)};

    Hall halls[5] = {
        Hall(1, 6, 10), Hall(2, 7, 11), Hall(3, 5, 4), Hall(4, 4, 5), Hall(5, 8, 8)};

    Session sessions[3] = {
        Session(concerts[0], halls[1], "10AM"),
        Session(concerts[1], halls[3], "10AM"),
        Session(concerts[2], halls[4], "10AM")};

    void printTextWithColour(string text, ConsoleColoursEnum colourEnum)
    {
        cout << "\033[1;" + to_string(colourEnum) + "m" << text << "\033[0m";
    }

    void printAvailableTicketsForSession(Session *session, int row = 0, int column = 0)
    {
        Hall hall = session->getHall();
        Ticket **tickets = session->getTickets();

        cout << "Available seats for " << session->toString() << ":" << endl;

        for (int i = 0; i < hall.getNumberOfRows(); i++)
        {
            for (int j = 0; j < hall.getNumberOfSeatsPerRow(); j++)
            {
                Ticket &ticket = tickets[i][j];
                if (i == row && j == column)
                    printTextWithColour("[", cyan);

                printTextWithColour(ticket.getSeatNumberAsString(), ticket.getIsOccupied() ? red : yellow);

                if (i == row && j == column)
                    printTextWithColour("]", cyan);

                cout << " ";
            }

            cout << endl;
        }
    }

public:
    void mainMenu()
    {
        system("cls");
        int a;

        cout << "1. Concerts\n2. Sessions\n3. Halls\n4. Exit\n\nChoose what you want [a]: ";
        cin >> a;

        switch (a)
        {
        case 1:
            showConcerts();
            break;
        case 2:
            showSessions();
            break;
        case 3:
            showHalls();
            break;

        default:
            break;
        }
    }

    void showConcerts()
    {
        for (Concert concert : concerts)
        {
            cout << concert.toString() << endl;
        }
    }

    void showSessions()
    {
        system("cls");

        int sessionCount = 1;
        for (Session session : sessions)
        {
            cout << sessionCount << ". " << session.toString() << endl;
            sessionCount++;
        }

        int a;
        cout << "\n\nChoose session [a]: ";
        cin >> a;

        if (a > sessionCount || a < 1)
        {
            cout << "Please choose correct session. Press any key to continue\n";
            _getch();

            return showSessions();
        }

        showSessionTickets(&sessions[a - 1]);
    }

    void showSessionTickets(Session *session)
    {
        Session choosen_session = *session;

        int row = 0, column = 0;

        while (1)
        {
            system("cls");
            printAvailableTicketsForSession(&choosen_session, row, column);
            cout << "\n\nUse arrows to choose seat or press ESC to exit\n";

            switch (getch())
            {
            case KEY_UP:
                if (row == 0)
                    row = choosen_session.getHall().getNumberOfRows();

                row--;
                break;

            case KEY_DOWN:
                if (row >= choosen_session.getHall().getNumberOfRows() - 1)
                    row = -1;

                row++;
                break;

            case KEY_LEFT:
                if (column == 0)
                    column = choosen_session.getHall().getNumberOfSeatsPerRow();

                column--;
                break;

            case KEY_RIGHT:
                if (column >= choosen_session.getHall().getNumberOfSeatsPerRow() - 1)
                    column = -1;

                column++;
                break;

            case KEY_ENTER:
                if (choosen_session.isTicketAvailable(row, column))
                {

                    printTextWithColour("Seat is Avialable, would you like to purchase? [y / n]: ", green);

                    char yn[2];
                    cin.getline(yn, 2);

                    if (yn[0] == 'y')
                    {
                        if (choosen_session.buyTicket(row, column))
                            printTextWithColour("Successful!", green);
                        else
                            printTextWithColour("Unknown error occured", red);

                        _getch();
                    }
                }
                else
                {
                    printTextWithColour("This Seat is NOT Available", red);
                    _getch();
                }
                break;
            case KEY_ESC:
                return mainMenu();
            }
        }
    }

    void showHalls()
    {
        for (Hall hall : halls)
        {
            cout << hall.toString() << endl;
        }
    }
};