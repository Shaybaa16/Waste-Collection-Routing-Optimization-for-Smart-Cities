#pragma once
#include"Header.h"


using namespace std;

class Bin
{
public:
    int filledPercent;
    int BinID;
    string BinLocation;
    Bin* next;
    Bin(string Location = "", int filledPer = 0)
    {
        next = NULL;
        this->BinLocation = Location;
        this->filledPercent = filledPer;
    }

    Bin(Bin* bin)
    {
        this->BinLocation = bin->BinLocation;
        this->BinID = bin->BinID;
        this->filledPercent = bin->filledPercent;
        this->next = bin->next;
    }

    void SetBinLocation(string Location)
    {
        this->BinLocation = Location;
    }

    bool FilledNotification()
    {
        return true; // helps in controlled class to send notification to nearest truck
    }

    void checkFilled()
    {
        srand(time(NULL));

        int val = rand() % 100 + 1;

        filledPercent = val;

        if (filledPercent >= 75)
        {
            cout << "\033[1;31mFilled Percent : " << filledPercent << "\033[0m" << endl; // Set text color to red (31) and bold (1), then reset
            cout << "\033[1;31mCall FilledNotification function\033[0m" << endl;         // Set text color to red (31) and bold (1), then reset
            FilledNotification();
        }
        else
        {
            cout << "\033[1;32mFilled Percent : " << filledPercent << "\033[0m" << endl; // Set text color to green (32) and bold (1), then reset
        }
    }

    void DisplayBin()
    {
        cout << "\033[1;36m"; // Set text color to cyan (36) and bold (1)
        cout << "Bin Location: " << BinLocation << endl;
        cout << "\033[0m"; // Reset text color and formatting
    }

    void DisplayFilledPercent()
    {
        cout << "\033[1;33m"; // Set text color to yellow (33) and bold (1)
        cout << "Filled Percent: " << filledPercent << "%" << endl;
        cout << "\033[0m"; // Reset text color and formatting
    }

    void simulateCollection()
    {
        cout << "Collecting bin... Please wait." << endl;
        Sleep(2000);

        cout << "Bin collected." << endl;
    }

    void updateFillLevel(int newFillLevel)
    {
        filledPercent = newFillLevel;
    }

    bool isCollected()
    {
        return filledPercent == 0;
    }
};