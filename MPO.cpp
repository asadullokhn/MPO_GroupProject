#include <iostream>
#include "ConsoleGUI.cpp"

int main()
{
    system("cls");

    string image[] = {
        "       <<<    MMM     MMM       PPPPPPPPPPP        OOOOOOOOOO     >>>",
        "     <<<      M  M   M  M       PP        PP     OO          OO     >>>",
        "   <<<        M   M M   M       PP        PP    OO             OO      >>>",
        " <<<          M    M    M       PPPPPPPPPPP    OO               OO       >>>",
        "   <<<        M         M       PP              OO             OO      >>>",
        "     <<<      M         M       PP               OO           OO    >>>",
        "       <<<    M         M       PP                 OOOOOOOOOO     >>>"};

    cout << "\033[1;31m";
    for (int i = 0; i < 7; i++)
        cout << image[i] << endl;
    cout << "\033[0m\n";

    cout << "The Malaysian Philharmonic Orchestra\n\n";
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
    
    return 0;
}
