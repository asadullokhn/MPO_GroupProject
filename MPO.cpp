#include <iostream>
#include "ConsoleGUI.cpp"
// #include "./Repositories/SessionRepository.cpp"

int main()
{
    ConsoleGUI app;
    app.mainMenu();
    // HallRepository hallsrepo;
    // ConcertRepository consrepo;

    // SessionRepository sessionRepo;

    // Session s(consrepo.get(0).value(), hallsrepo.get(2).value(), "11:00pm");
    // int sessionId = sessionRepo.create(s);

    // TicketRepository ticketsRepo;
    // ticketsRepo.createAll(s.getTickets(), sessionId, s.getHall().getNumberOfRows(), s.getHall().getNumberOfSeatsPerRow());

    return 0;
}
