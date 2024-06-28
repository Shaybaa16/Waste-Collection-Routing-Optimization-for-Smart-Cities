#pragma once
#include"Header.h"

using namespace std;

class Driver
{
public:
    string username;
    string password;
    Truck* MyTruck;

    Driver(const string& uname, const string& pwd) : username(uname), password(pwd) {}
    Driver()
    {
        username = "";
        password = "";

        MyTruck = new Truck("1", username);
    }

    int DriverMenu()
    {

        cout << "==================" << endl;
        cout << "1. View Jobs" << endl;
        cout << "2. View Remaining Bins" << endl; // Add this option
        cout << "3. View Notification\n";
        cout << "4. Show Truck Simulation\n";
        cout << "0. Exit" << endl;

        int choice;
        cin >> choice;
        if (choice >= 0 && choice <= 4)
            return choice; // Return the current instance of the Driver class
        else
        {
            cout << "Invalid choice" << endl;
            cout << "Exiting.." << endl;
            // exit(0);
        }
    }

    void ViewNotification()
    {
        cout << "==================" << endl;
        string notificationString;
        MyTruck->ReadNotification(notificationString);

        cout << "Notification" << endl;
        cout << notificationString << endl;
        cout << "==================" << endl;
    }
    void WriteDriverInFile()
    {
        ofstream outFile("driver.txt", ios::app); // Open the file in append mode

        if (outFile.is_open())
        {
            // Write the driver information to the file
            outFile << username << "," << password << ";" << endl;

            cout << "Driver information written to 'driver.txt' successfully." << endl;

            outFile.close(); // Close the file
        }
        else
        {
            cerr << "Error opening 'driver.txt' for writing." << endl;
        }
    }
    void SetDriver()
    {
        cout << "Enter Driver's username: " << endl;
        cin >> username;
        cout << "Enter Password: " << endl;
        cin >> password;
        WriteDriverInFile();
    }
    void viewRemainingBins(int temp_bin_size, Bin* bins)
    {
        cout << "Remaining Bins:" << endl;
        for (int i = 0; i < temp_bin_size - 2; ++i)
        {
            if (!bins[i].isCollected() && bins[i].filledPercent > 75)
            {
                bins[i].DisplayBin();
            }
        }
    }
};