#include"Header.h"
using namespace std;

class User
{
    string username;
    string password;
    vector<Driver> drivers;
    vector<Admin> admins;
    Controller c1;

public:
    User()
    {
        // getUserdata();
    }

    void getUserdata()
    {
        cout << "Enter username: " << endl;
        cin >> username;
        cout << "Enter password: " << endl;
        cin >> password;
        // checkUser();
    }

    void readDriverFile()
    {
        ifstream file("driver.txt");

        if (!file.is_open())
        {
            cerr << "Error opening driver file: driver.txt" << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            size_t commaPos = line.find(',');
            size_t semicolonPos = line.find(';');

            if (commaPos != string::npos && semicolonPos != string::npos)
            {
                string uname = line.substr(0, commaPos);
                string pwd = line.substr(commaPos + 1, semicolonPos - commaPos - 1);

                drivers.emplace_back(uname, pwd);
            }
            else
            {
                // cerr << "Invalid format in the driver file." << endl;
            }
        }

        file.close();
    }

    void readAdminFile()
    {
        ifstream file("admin.txt");

        if (!file.is_open())
        {
            cerr << "Error opening file: admin.txt" << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            size_t commaPos = line.find(',');

            if (commaPos != string::npos)
            {
                Admin admin(line.substr(0, commaPos), line.substr(commaPos + 1));
                admins.push_back(admin);
            }
            else
            {
                // cerr << "Invalid format in the admin file." << endl;
            }
        }

        file.close();
    }

    void RegisterUser()
    {
        int Choice = 0;
        cout << "1.Admin " << endl;
        cout << "2.Driver " << endl;
        cin >> Choice;

        switch (Choice)
        {
        case 1:
        {
            Admin* newAdmin = new Admin();
            newAdmin->SetAdmin();
            readAdminFile();

            int loginchoice = -1;

            cout << "you want to login again ? (yes =1 / no = 0)" << endl;
            cin >> loginchoice;
            if (loginchoice == 1)
                checkUser();

            break;
        }
        case 2:
        {
            Driver* newDriver = new Driver();
            newDriver->SetDriver();
            readDriverFile();
            int loginchoice = -1;

            cout << "you want to login again ? (yes =1 / no = 0)" << endl;
            cin >> loginchoice;
            if (loginchoice == 1)
                checkUser();

            break;
        }
        default:
        {
            cout << "Invalid Choice" << endl;
            break;
        }
        }
    }
    void checkUser()
    {
        readAdminFile();
        readDriverFile();
        // Search in Admins
        int choiceeeee = 0;
        do
        {
            cout << "1-Admin\n";
            cout << "2-Driver\n";
            cout << "3-Register\n";
            cout << "0-Exit\n";
            cin >> choiceeeee;
            if (choiceeeee == 1)
            {
                getUserdata();
                auto adminIt = find_if(admins.begin(), admins.end(), [this](const Admin& admin)
                    { return username == admin.username && password == admin.password; });
                if (adminIt != admins.end())
                {
                    cout << "User is Admin" << endl;
                    int returnedChoice = -1;
                    c1.WorkFlow();
                    do
                    {
                        returnedChoice = adminIt->AdminMenu();
                        if (returnedChoice == 1)
                        {
                            c1.findShortestRoute();
                        }
                        if (returnedChoice == 2)
                        {

                            c1.DisplayBinsDataForHour();
                        }
                        if (returnedChoice == 3)
                        {

                            c1.DisplayBins_Data();
                        }
                        if (returnedChoice == 4)
                        {

                            c1.gFilled->showGraphStructure();
                        }
                        if (returnedChoice == 5)
                        {
                            c1.creatgFilled();

                        }
                    } while (returnedChoice != 0);
                }
            }

            // drivers
            else if (choiceeeee == 2)
            {
                getUserdata();
                // Inside checkUser method
                auto driverIt = find_if(drivers.begin(), drivers.end(), [this](const Driver& driver)
                    { return username == driver.username && password == driver.password; });
                int id = 0;
                if (driverIt != drivers.end())
                {
                    if (username == "driver1")
                    {
                        id = 0;
                    }
                    else if (username == "driver2")
                    {
                        id = 1;
                    }
                    else if (username == "driver3")
                    {
                        id = 2;
                    }
                    else if (username == "driver4")
                    {
                        id = 3;
                    }
                    else if (username == "driver5")
                    {
                        id = 4;
                    }
                    else;
                    cout << "User is a valid driver." << endl;
                    int returnedChoice = -1;
                    Driver currentDriver = *driverIt; // Store the current Driver instance
                    cout << "==================" << endl;
                    do
                    {
                        returnedChoice = currentDriver.DriverMenu(); // Call the updated DriverMenu
                        if (returnedChoice == 1)
                        {
                            c1.drivers[id].MyTruck->Read_jobs_from_file();
                            c1.drivers[id].MyTruck->Jobs_from_file->Display();
                        }
                        else if (returnedChoice == 2)
                        {
                            // currentDriver.viewRemainingBins(c1.temp_bin_size, c1.bins);
                            c1.drivers[id].MyTruck->Jobs_from_file->Display();
                        }
                        else if (returnedChoice == 3)
                        {
                            currentDriver.ViewNotification();
                        }
                        else if (returnedChoice == 4)
                        {
                            c1.simulateTruckCollection();
                            c1.drivers[id].MyTruck->Jobs_from_file->empty();
                            c1.stop();

                        }
                        if (returnedChoice == 0)
                        {
                            Controller c;
                            c.stop();
                        }

                    } while (returnedChoice != 0);

                    // return;
                }
            }

            // exit
            else if (choiceeeee == 3)
            {
                cout << "==================" << endl;
                {
                    cout << "Invalid username or password." << endl;
                    int registerchoice = -1;
                    cout << "Do you want to register? (yes = 1/ no = 0)" << endl;
                    cin >> registerchoice;
                    if (registerchoice == 1)
                    {

                        RegisterUser();
                    }
                    else if (registerchoice == 0)
                    {
                        cout << "Exiting..." << endl;
                        exit(0);
                    }
                    else
                    {
                    }
                }
                cout << "==================" << endl;
            }
        } while (choiceeeee != 0);
    }
};

void Starter()
{
    User u1;
    u1.checkUser();
}

int main()

{
    cout << "\033[1;32m";                           // Set text color to green (32) and bold (1)
    cout << setfill('=') << setw(60) << "" << endl; // Border line
    cout << "Waste Collection Routing Optimization for Smart Cities" << endl;
    cout << setfill('=') << setw(60) << "" << endl; // Border line
    cout << "\033[0m";                              // Reset text color and formatting
    Starter();
    return 0;
}