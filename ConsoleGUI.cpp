#include <iostream>
#include <conio.h>
#include "./Repositories/SessionRepository.cpp"

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
    list<Concert> concerts;
    list<Hall> halls;
    list<Session> sessions;

    ConcertRepository concertRepository;
    HallRepository hallRepository;
    SessionRepository sessionRepository;

    enum ConsoleColoursEnum : int
    {
        red = 31,
        green = 32,
        yellow = 33,
        magenta = 35,
        cyan = 36
    };

    void printTextWithColour(string text, ConsoleColoursEnum colourEnum)
    {
        cout << "\033[1;" + to_string(colourEnum) + "m" << text << "\033[0m";
    }

    void printAvailableTicketsForSession(Session session, int row = 0, int column = 0)
    {
        Hall hall = session.getHall();
        Ticket **tickets = session.getTickets();

        cout << "Available seats for:\n"
             << session.toString() << ":" << endl
             << endl
             << endl;

        for (int i = 0; i < hall.getNumberOfRows(); i++)
        {
            for (int j = 0; j < hall.getNumberOfSeatsPerRow(); j++)
            {
                Ticket &ticket = tickets[i][j];
                if (i == row && j == column)
                    printTextWithColour("[", cyan);

                printTextWithColour(ticket.getIsOccupied() ? "XX" : ticket.getSeatNumberAsString(), ticket.getIsOccupied() ? red : yellow);

                if (i == row && j == column)
                    printTextWithColour("]", cyan);

                cout << " ";
            }

            cout << endl;
        }
    }

    int getIntFromUserWithColor(ConsoleColoursEnum colourEnum = red)
    {
        int a;

        cout << "\033[1;" + to_string(colourEnum) + "m";
        cin >> a;
        cout << "\033[0m";

        return a;
    }

public:
    ConsoleGUI()
    {
        concerts = concertRepository.getAll();
        halls = hallRepository.getAll();
        sessions = sessionRepository.getAll();
    }

    void mainMenu()
    {
        system("cls");

        cout << "1. Concerts\n2. Sessions\n3. Halls\n4. Exit\n\nChoose what you want [a]: ";

        int a = getIntFromUserWithColor();
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
        system("cls");

        int concertCount = 1;
        for (Concert concert : concerts)
        {
            cout << concert.toString() << endl;
        }

        cout << "\n\nChoose concert [a]: ";
        int a = getIntFromUserWithColor();

        if (a > concertCount || a < 1)
        {
            cout << "Please choose correct concert. Press any key to continue\n";
            _getch();

            return showConcerts();
        }
    }

    void showSessions(int hallId = -1, bool clearConsole = true)
    {
        if (clearConsole)
            system("cls");

        int sessionCount = 1;
        list<Session> choosableS;

        for (Session session : sessions)
        {
            if (hallId == -1)
            {
                cout << "[" << sessionCount << "]: " << session.toString() << endl;
                sessionCount++;
                choosableS.push_back(session);
            }
            else
            {
                if (session.getHall().getId() == hallId)
                {
                    cout << "[" << sessionCount << "]: " << session.toString() << endl;
                    sessionCount++;
                    choosableS.push_back(session);
                }
            }
        }

        cout << "\n\nChoose session [a] >> ";
        int a = getIntFromUserWithColor();

        if (a >= sessionCount || a < 1)
        {
            cout << "Please choose correct session. Press any key to continue\n";
            _getch();

            return showSessions(hallId);
        }

        list<Session>::iterator it = choosableS.begin();
        for (int i = 0; i < a-1; i++)
            ++it;

        showSessionTickets(*it);
    }

    void showSessionTickets(Session choosenSession)
    {
        int row = 0, column = 0;

        while (1)
        {
            system("cls");
            printAvailableTicketsForSession(choosenSession, row, column);

            if (!choosenSession.isTicketAvailable(row, column))
                printTextWithColour("\nUnavailable seat", red);
            else
                printTextWithColour("\nAvailable seat", green);

            cout << "\n\nUse ";
            printTextWithColour("arrows", magenta);
            cout << " to choose seat or press ";
            printTextWithColour("ESC", magenta);
            cout << " to exit\nTo buy a ticket double click ";
            printTextWithColour("ENTER\n", magenta);

            switch (getch())
            {
            case KEY_UP:
                if (row == 0)
                    row = choosenSession.getHall().getNumberOfRows();

                row--;
                break;

            case KEY_DOWN:
                if (row >= choosenSession.getHall().getNumberOfRows() - 1)
                    row = -1;

                row++;
                break;

            case KEY_LEFT:
                if (column == 0)
                    column = choosenSession.getHall().getNumberOfSeatsPerRow();

                column--;
                break;

            case KEY_RIGHT:
                if (column >= choosenSession.getHall().getNumberOfSeatsPerRow() - 1)
                    column = -1;

                column++;
                break;

            case KEY_ENTER:
                if (choosenSession.isTicketAvailable(row, column))
                {
                    printTextWithColour("\n\nSeat is Avialable, would you like to purchase? [y / n]: ", green);

                    char yn[2];
                    cin.getline(yn, 2);

                    if (yn[0] == 'y')
                    {
                        if (choosenSession.buyTicket(row, column))
                            printTextWithColour("Successful!", green);
                        else
                            printTextWithColour("Unknown error occured", red);

                        _getch();
                    }
                }
                else
                {
                    printTextWithColour("Unavailable seat", red);
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
        system("cls");

        int hallCount = 1;
        for (Hall hall : halls)
        {
            cout << "[" << hallCount << "]: " << hall.toString() << endl;
            hallCount++;
        }

        cout << "\n\nChoose hall [a] >> ";
        int a = getIntFromUserWithColor();

        if (a > hallCount || a < 1)
        {
            cout << "Please choose correct hall. Press any key to continue\n";
            _getch();

            return showHalls();
        }

        list<Hall>::iterator it = halls.begin();
        for (int i = 0; i < a - 1; i++)
            ++it;

        cout << "\n\nYou have choose: " << it->toString() << "\nSessions available in this hall:\n\n";

        showSessions(it->getId(), false);
    }
};