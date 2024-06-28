#pragma once
#include"Admin.h"


using namespace std;

class Admin
{
public:
    string username;
    string password;

    Admin(const string& uname, const string& pwd) : username(uname), password(pwd) {}
    Admin()
    {
        username = "";
        password = "";
    }

    int AdminMenu()
    {
        int choice;
        cout << "==================" << endl;
        cout << "\033[1;34m1. Distance Value \033[0m" << endl;                     // Set text color to blue (34) and bold (1), then reset
        cout << "\033[1;35m2. Display last 3 days Bins percentage\033[0m" << endl; // Set text color to magenta (35) and bold (1), then reset
        cout << "\033[1;36m3. Display Bins_Data\033[0m" << endl;                   // Set text color to cyan (36) and bold (1), then reset
        cout << "\033[1;33m4. Display Graph\033[0m" << endl;                       // Set text color to yellow (33) and bold (1), then reset
        cout << "\033[1;32m5. Display Dynamic\033[0m" << endl;                       // Set text color to yellow (33) and bold (1), then reset
        cout << "\033[1;31m0. Exit\033[0m" << endl;                                // Set text color to red (31) and bold (1), then reset

        cin >> choice;
        if (choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5)
            return choice;
        else
        {
            cout << "Invalid choice" << endl;
            cout << "Exiting.." << endl;
            exit(0);
        }
    }
    void SetAdmin()
    {
        cout << "Enter Admin's username: " << endl;
        cin >> username;
        cout << "Enter Password: " << endl;
        cin >> password;
        WriteAdminInFile();
    }

    void WriteAdminInFile()
    {
        ofstream outFile("admin.txt", ios::app); // Open the file in append mode

        if (outFile.is_open())
        {
            // Write the admin information to the file
            outFile << username << "," << password << endl;

            cout << "\033[1;32mAdmin information written to 'admin.txt' successfully.\033[0m" << endl;

            outFile.close(); // Close the file
        }
        else
        {
            cerr << "Error opening 'admin.txt' for writing." << endl;
        }
    }
};
