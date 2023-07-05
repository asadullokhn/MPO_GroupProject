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
public:
    virtual void mainMenu() = 0;

protected:
    list<Concert> concerts;
    list<Hall> halls;
    list<Session> sessions;

    ConcertRepository concertRepository;
    HallRepository hallRepository;
    SessionRepository sessionRepository;
    TicketRepository ticketsRepository;

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
};

class UserConsoleGUI : public ConsoleGUI
{
public:
    UserConsoleGUI()
    {
        concerts = concertRepository.getAll();
        halls = hallRepository.getAll();
        sessions = sessionRepository.getAll();
    }

    void mainMenu()
    {
        system("cls");

        cout << "[";
        printTextWithColour("1", red);
        cout << "] ";
        printTextWithColour("Concerts\n", green);
        cout << "[";
        printTextWithColour("2", red);
        cout << "] ";
        printTextWithColour("Sessions\n", green);
        cout << "[";
        printTextWithColour("3", red);
        cout << "] ";
        printTextWithColour("Halls\n", green);
        cout << "[";
        printTextWithColour("4", red);
        cout << "] ";
        printTextWithColour("Report\n\n", green);
        cout << "[";
        printTextWithColour("0", red);
        cout << "] ";
        printTextWithColour("Exit\n\n", green);
        cout << "Choose what you want [a] >> ";

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
        case 4:
            showReport();
            break;

        default:
            break;
        }
    }

private:
    void showReport()
    {
        system("cls");

        printTextWithColour("Ticket Sales Summary Report\n\n", magenta);
        for (Session s : sessions)
        {
            cout << "\nConcert ";
            printTextWithColour("hall-" + to_string(s.getHall().getId()), green);
            cout << ": ";

            printTextWithColour(s.getConcert().getTitle(), green);
            cout << " (";
            printTextWithColour(to_string(s.getHall().getNumberOfTickets()) + " seats", green);
            cout << ")\nUnsold: ";
            printTextWithColour(to_string(s.getAvailableTicketsCount()) + "\t", green);
            cout << "Sold: ";
            printTextWithColour(to_string(s.getHall().getNumberOfTickets() - s.getAvailableTicketsCount()) + "\n", green);
        }

        cout << "\n\nPress any key to return\n";
        _getch();

        return mainMenu();
    }

    void showConcerts()
    {
        system("cls");

        int concertCount = 1;
        for (Concert concert : concerts)
        {
            cout << "[";
            printTextWithColour(to_string(concertCount), red);
            cout << "]: " << concert.toString() << endl;
            concertCount++;
        }

        cout << "\n\nChoose concert [a] >> ";
        int a = getIntFromUserWithColor();

        if (a > concertCount || a < 1)
        {
            cout << "Please choose correct concert. Press any key to continue\n";
            _getch();

            return showConcerts();
        }

        list<Concert>::iterator it = concerts.begin();
        for (int i = 0; i < a - 1; i++)
            ++it;

        cout << "\n\nYou have choose: " << it->toString() << "\nSessions available for this concert:\n\n";

        showSessions(-1, it->getId(), false);
    }

    void showSessions(int hallId = -1, int concertId = -1, bool clearConsole = true)
    {
        if (clearConsole)
            system("cls");

        int sessionCount = 1;
        list<Session> choosableSessions;
        if (concertId == -1)
        {
            for (Session session : sessions)
            {
                if (hallId == -1)
                {
                    cout << "[";
                    printTextWithColour(to_string(sessionCount), red);
                    cout << "]: " << session.toString() << endl;

                    sessionCount++;
                    choosableSessions.push_back(session);
                }
                else
                {
                    if (session.getHall().getId() == hallId)
                    {
                        cout << "[";
                        printTextWithColour(to_string(sessionCount), red);
                        cout << "]: " << session.toString() << endl;
                        sessionCount++;
                        choosableSessions.push_back(session);
                    }
                }
            }
        }
        else
        {
            for (Session session : sessions)
            {
                if (concertId == -1)
                {
                    cout << "[";
                    printTextWithColour(to_string(sessionCount), red);
                    cout << "]: " << session.toString() << endl;
                    sessionCount++;
                    choosableSessions.push_back(session);
                }
                else
                {
                    if (session.getConcert().getId() == concertId)
                    {
                        cout << "[";
                        printTextWithColour(to_string(sessionCount), red);
                        cout << "]: " << session.toString() << endl;
                        sessionCount++;
                        choosableSessions.push_back(session);
                    }
                }
            }
        }

        if (choosableSessions.size() == 0)
        {
            printTextWithColour("Unfortunately there is no session. Press any key to continue\n", red);
            _getch();

            return mainMenu();
        }

        cout << "\n\nChoose session [a] >> ";
        int a = getIntFromUserWithColor();

        if (a >= sessionCount || a < 1)
        {
            cout << "Please choose correct session. Press any key to continue\n";
            _getch();

            return showSessions(hallId, concertId);
        }

        list<Session>::iterator it = choosableSessions.begin();
        for (int i = 0; i < a - 1; i++)
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
            cout << "[";
            printTextWithColour(to_string(hallCount), red);
            cout << "]: " << hall.toString() << endl;
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

        showSessions(it->getId(), -1, false);
    }
};

class AdminConsoleGUI : public ConsoleGUI
{
public:
    AdminConsoleGUI()
    {
        concerts = concertRepository.getAll();
        halls = hallRepository.getAll();
        sessions = sessionRepository.getAll();
    }

    void mainMenu()
    {
        system("cls");

        cout << "[";
        printTextWithColour("1", red);
        cout << "] ";
        printTextWithColour("Concerts\n", green);
        cout << "[";
        printTextWithColour("2", red);
        cout << "] ";
        printTextWithColour("Sessions\n", green);
        cout << "[";
        printTextWithColour("3", red);
        cout << "] ";
        printTextWithColour("Halls\n", green);
        cout << "[";
        printTextWithColour("4", red);
        cout << "] ";
        printTextWithColour("Report\n\n", green);
        cout << "[";
        printTextWithColour("0", red);
        cout << "] ";
        printTextWithColour("Exit\n\n", green);
        cout << "Choose what you want [a] >> ";

        int a = getIntFromUserWithColor();
        switch (a)
        {
        case 1:
            chooseAction("Concerts", 1);
            break;
        case 2:
            chooseAction("Sessions", 2);
            break;
        case 3:
            chooseAction("Halls", 3);
            break;
        case 4:
            showReport();
            break;
        case 0:
            return;
        default:
            return mainMenu();
        }
    }

private:
    void chooseAction(string action, int iaction)
    {
        system("cls");

        if (iaction == 1)
            for (Concert c : concerts)
                cout << c.toString() << endl;
        else if (iaction == 2)
            for (Session s : sessions)
                cout << s.toString() << endl;
        else
            for (Hall h : halls)
                cout << h.toString() << endl;

        printTextWithColour("\n\n" + action + "\n", green);
        cout << "[";
        printTextWithColour("1", red);
        cout << "] ";
        printTextWithColour("Add\n", green);
        cout << "[";
        printTextWithColour("2", red);
        cout << "] ";
        printTextWithColour("Delete\n\n", green);
        cout << "[";
        printTextWithColour("0", red);
        cout << "] ";
        printTextWithColour("Return\n\n", green);
        cout << "Choose what you want [a] >> ";

        int addDelete = getIntFromUserWithColor();
        switch (addDelete)
        {
        case 1:
            if (iaction == 1)
                addDeleteConcert(true);
            else if (iaction == 2)
                addDeleteSession(true);
            else
                addDeleteHall(true);

            break;
        case 2:
            if (iaction == 1)
                addDeleteConcert(false);
            else if (iaction == 2)
                addDeleteSession(false);
            else
                addDeleteHall(false);

            break;
        case 0:
            return mainMenu();
        default:
            return chooseAction(action, iaction);
        }
    }

    void addDeleteConcert(bool add)
    {
        system("cls");

        if (add)
        {
            string title = " ";
            int rating;

            cout << "Enter concert title: \033[1;31m";
            getline(cin, title);
            getline(cin, title);
            cout << "\033[0mEnter concert rating [a]: \033[1;31m";
            cin >> rating;
            cout << "\033[0m";

            concertRepository.create(Concert(title, rating));
            concerts = concertRepository.getAll();

            printTextWithColour("Successfully added new concert!", green);
            cout << "\n\nPress any key to return\n";
            _getch();

            return mainMenu();
        }
        else
        {
            int concertCount = 1;
            for (Concert concert : concerts)
            {
                cout << "[";
                printTextWithColour(to_string(concertCount), red);
                cout << "]: " << concert.toString() << endl;
                concertCount++;
            }

            cout << "\n[";
            printTextWithColour(to_string(0), red);
            cout << "]: ";
            printTextWithColour("Return", green);
            cout << "\n\n\nChoose concert [\033[1;31ma\033[0m] >> ";

            int a = getIntFromUserWithColor();

            if (a == 0)
                return mainMenu();

            else if (a >= concertCount || a < 1)
            {
                cout << "Please choose correct concert. Press any key to continue\n";
                _getch();

                return addDeleteConcert(add);
            }

            printTextWithColour("\n\nWould you like to delete? [y / n]: ", green);

            char yn;
            cin >> yn;

            if (yn == 'y')
            {
                list<Concert>::iterator it = concerts.begin();
                for (int i = 0; i < a - 1; i++)
                    ++it;

                int choosenConcertId = it->getId();
                if (sessionRepository.removeByConcert(choosenConcertId) && concertRepository.remove(choosenConcertId))
                {   
                    printTextWithColour("Successful!", green);

                    concerts = concertRepository.getAll();
                    sessions = sessionRepository.getAll();
                }
                else
                    printTextWithColour("Unknown error occured", red);

                _getch();
            }

            return addDeleteConcert(add);
        }
    }

    void addDeleteSession(bool add)
    {
        system("cls");

        if (add)
        {
            string startTime;

            cout << "Enter session starting time: \033[1;31m";
            getline(cin, startTime);
            getline(cin, startTime);
            cout << "\033[0m";

            system("cls");
            cout << "Choose concert for new session\n\n";

            int concertCount = 1;
            for (Concert concert : concerts)
            {
                cout << "[";
                printTextWithColour(to_string(concertCount), red);
                cout << "]: " << concert.toString() << endl;
                concertCount++;
            }

            cout << "\n[";
            printTextWithColour(to_string(0), red);
            cout << "]: ";
            printTextWithColour("Return", green);
            cout << "\n\n\nChoose concert [\033[1;31ma\033[0m] >> ";

            int choosenConcert = getIntFromUserWithColor();

            if (choosenConcert == 0)
                return mainMenu();

            else if (choosenConcert >= concertCount || choosenConcert < 1)
            {
                cout << "Please choose correct concert. Press any key to continue\n";
                _getch();

                return addDeleteSession(add);
            }

            list<Concert>::iterator concert = concerts.begin();
            for (int i = 0; i < choosenConcert - 1; i++)
                ++concert;

            system("cls");
            cout << "Choose hall for new session\n\n";

            int hallCount = 1;
            for (Hall hall : halls)
            {
                cout << "[";
                printTextWithColour(to_string(hallCount), red);
                cout << "]: " << hall.toString() << endl;
                hallCount++;
            }

            cout << "\n[";
            printTextWithColour(to_string(0), red);
            cout << "]: ";
            printTextWithColour("Return", green);
            cout << "\n\n\nChoose hall [\033[1;31ma\033[0m] >> ";

            int choosenHall = getIntFromUserWithColor();
            if (choosenHall == 0)
                return mainMenu();

            else if (choosenHall >= hallCount || choosenHall < 1)
            {
                cout << "Please choose correct hall. Press any key to continue\n";
                _getch();

                return addDeleteHall(add);
            }

            list<Hall>::iterator hall = halls.begin();
            for (int i = 0; i < choosenHall - 1; i++)
                ++hall;

            Session s(*concert, *hall, startTime);
            int sessionId = sessionRepository.create(s);
            ticketsRepository.createAll(s.getTickets(), sessionId, hall->getNumberOfRows(), hall->getNumberOfSeatsPerRow());

            printTextWithColour("Successfully added new session!", green);
            cout << "\n\nPress any key to return\n";
            _getch();
            sessions = sessionRepository.getAll();

            return mainMenu();
        }
        else
        {
            int sessionCount = 1;
            for (Session session : sessions)
            {
                cout << "[";
                printTextWithColour(to_string(sessionCount), red);
                cout << "]: " << session.toString() << endl;
                sessionCount++;
            }

            cout << "\n[";
            printTextWithColour(to_string(0), red);
            cout << "]: ";
            printTextWithColour("Return", green);
            cout << "\n\n\nChoose session [\033[1;31ma\033[0m] >> ";

            int a = getIntFromUserWithColor();

            if (a == 0)
                return mainMenu();

            else if (a >= sessionCount || a < 1)
            {
                cout << "Please choose correct session. Press any key to continue\n";
                _getch();

                return addDeleteSession(add);
            }

            printTextWithColour("\n\nWould you like to delete? [y / n]: ", green);

            char yn;
            cin >> yn;

            if (yn == 'y')
            {
                list<Session>::iterator it = sessions.begin();
                for (int i = 0; i < a - 1; i++)
                    ++it;

                int choosenSessionId = it->getId();
                if (sessionRepository.remove(choosenSessionId))
                {
                    printTextWithColour("Successful!", green);
                    sessions = sessionRepository.getAll();
                }
                else
                    printTextWithColour("Unknown error occured", red);

                _getch();
            }

            return addDeleteSession(add);
        }
    }

    void addDeleteHall(bool add)
    {
        system("cls");

        if (add)
        {
            int numberOfRows, numberOfSeatsPerRow;

            cout << "Enter number of rows at new hall [a]: \033[1;31m";
            cin >> numberOfRows;

            cout << "\033[0mEnter number of seats per row [a]: \033[1;31m";
            cin >> numberOfSeatsPerRow;
            cout << "\033[0m";

            hallRepository.create(Hall(numberOfRows, numberOfSeatsPerRow));
            halls = hallRepository.getAll();

            printTextWithColour("Successfully added new hall!", green);
            cout << "\n\nPress any key to return\n";
            _getch();

            return mainMenu();
        }
        else
        {
            int hallCount = 1;
            for (Hall hall : halls)
            {
                cout << "[";
                printTextWithColour(to_string(hallCount), red);
                cout << "]: " << hall.toString() << endl;
                hallCount++;
            }

            cout << "\n[";
            printTextWithColour(to_string(0), red);
            cout << "]: ";
            printTextWithColour("Return", green);
            cout << "\n\n\nChoose hall [\033[1;31ma\033[0m] >> ";

            int a = getIntFromUserWithColor();

            if (a == 0)
                return mainMenu();

            else if (a >= hallCount || a < 1)
            {
                cout << "Please choose correct hall. Press any key to continue\n";
                _getch();

                return addDeleteHall(add);
            }

            printTextWithColour("\n\nWould you like to delete? [y / n]: ", green);

            char yn;
            cin >> yn;

            if (yn == 'y')
            {
                list<Hall>::iterator it = halls.begin();
                for (int i = 0; i < a - 1; i++)
                    ++it;

                int choosenHallId = it->getId();
                if (sessionRepository.removeByHall(choosenHallId) && hallRepository.remove(choosenHallId))
                {
                    printTextWithColour("Successful!", green);

                    halls = hallRepository.getAll();
                    sessions = sessionRepository.getAll();
                }
                else
                    printTextWithColour("Unknown error occured", red);

                _getch();
            }

            return addDeleteHall(add);
        }
    }

    void showReport()
    {
        system("cls");

        printTextWithColour("Ticket Sales Summary Report\n\n", magenta);
        for (Session s : sessions)
        {
            cout << "\nConcert ";
            printTextWithColour("hall-" + to_string(s.getHall().getId()), green);
            cout << ": ";

            printTextWithColour(s.getConcert().getTitle(), green);
            cout << " (";
            printTextWithColour(to_string(s.getHall().getNumberOfTickets()) + " seats", green);
            cout << ")\nUnsold: ";
            printTextWithColour(to_string(s.getAvailableTicketsCount()) + "\t", green);
            cout << "Sold: ";
            printTextWithColour(to_string(s.getHall().getNumberOfTickets() - s.getAvailableTicketsCount()) + "\n", green);
        }

        cout << "\n\nPress any key to return\n";
        _getch();

        return mainMenu();
    }
};
