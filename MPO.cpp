#include <iostream>
#include "ConsoleGUI.cpp"

int main()
{
    system("cls");

    cout << "The Malaysian Philharmonic Orchestra (MPO)\n\n";
    cout << "[\033[1;31m1\033[0m] \033[1;32mUser\033[0m\n";
    cout << "[\033[1;31m2\033[0m] \033[1;32mAdmin\033[0m\n\n";
    cout << "[\033[1;31m0\033[0m] \033[1;32mExit\033[0m";

    cout << "\n\nChoose option [\033[1;31ma\033[0m] >> ";
    int a;
    cout << "\033[1;31m";
    cin >> a;
    cout << "\033[0m";

    if (a == 1)
    {
        UserConsoleGUI userApp;
        userApp.mainMenu();
    }
    else if (a == 2)
    {
        AdminConsoleGUI adminApp;
        adminApp.mainMenu();
    }
    else
    {
        return 0;
    }
    return 0;
}
