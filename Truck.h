#pragma once
#include"Header.h"

using namespace std;



class Truck
{

    string TruckID;
    string DriverName;
    string line;
    BinStack* myJobs;

public:
    BinStack* Jobs_from_file;
    Truck(const string& truckID, const string& driverName)
    {
        TruckID = truckID;
        DriverName = driverName;
        myJobs = new BinStack();
        Jobs_from_file = new BinStack();
        Read_jobs_from_file();

        // menus
    }

    ~Truck()
    {
        delete myJobs;
    }

    void Menu()
    {
        cout << "\033[1;36m";

        cout << "1. View current Jobs" << endl;


        cout << "\033[0m";

        cout << "************" << endl;
    }

    void Write_job_in_file(Bin* currentJob)
    {
        // Open the file in append mode
        ofstream outFile("jobsfordriver.txt", ios::app);

        if (outFile.is_open())
        {
            // Write the job information to the file
            outFile << currentJob->BinLocation << ";" << currentJob->filledPercent << "%" << endl;

            // cout << "Job information written to 'jobs.txt' successfully." << endl;

            // Close the file
            outFile.close();
        }
        else
        {
            cerr << "Error opening 'jobs.txt' for writing." << endl;
        }
    }
    void getBins(Bin* arr, int size)
    {
        myJobs->empty();
        for (int i = 0; i < size; ++i)
        {
            Write_job_in_file(&arr[i]);
            CheckNotification(&arr[i]);
            myJobs->Push_job(&arr[i]);

        }
    }

    void AddnewJob(Bin job)
    {
        myJobs->Push_job(&job);
    }
    void Read_jobs_from_file()
    {
        std::ifstream inFile("jobsfordriver.txt");

        if (inFile.is_open())
        {
            std::string line;

            int i = 0;
            while (std::getline(inFile, line))
            {
                if (i == 0)
                {

                }
                else
                {
                    std::istringstream iss(line);
                    std::string location;
                    int filledPercent;

                    // Read location and filled percentage from the line
                    if (std::getline(iss, location, ';') && (iss >> filledPercent))
                    {

                        Bin* newJob = new Bin(location, filledPercent);

                        Jobs_from_file->Push_job(newJob);
                    }

                }
                i++;
            }

            // std::cout << "Jobs read from 'jobs.txt' successfully." << std::endl;

            inFile.close(); // Close the file
        }
        else
        {
            std::cerr << "Error opening 'jobs.txt' for reading." << std::endl;
        }
    }

    void ReadNotification(std::string& notificationString)
    {
        std::ifstream inFile("Notification.txt");

        if (inFile.is_open())
        {
            std::stringstream buffer;
            buffer << inFile.rdbuf(); // Read the entire content of the file into the stringstream
            notificationString = buffer.str();

            inFile.close(); // Close the file
        }
        else
        {
            std::cerr << "Error opening 'Notification.txt' for reading." << std::endl;
        }
    }
    void CheckNotification(Bin* currentJob)
    {
        ofstream outFile("Notification.txt", ios::app);

        if (outFile.is_open())
        {
            // Write the job information to the file
            outFile << currentJob->BinLocation << ";" << currentJob->filledPercent << "%";

            // cout << "Job information written to 'Notification.txt' successfully." << endl;

            // Close the file
            outFile.close();
        }
        else
        {
            cerr << "Error opening 'Notification.txt' for writing." << endl;
        }
    }
    void currentJobs()
    {
        cout << "\033[1;33m";

        cout << "Truck " << TruckID << " with driver " << DriverName << " is on the way with the following jobs" << endl;
        myJobs->Display();

        cout << "\033[0m";
    }
    void Send_Truck_to_Bins()
    {
        myJobs->Pop_job();

        myJobs->Display();
    }
};