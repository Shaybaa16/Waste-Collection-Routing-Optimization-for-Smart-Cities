#pragma once
#include"Header.h"

using namespace std;

class BinStack
{


public:
    int size;
    Bin* Topjob;
    BinStack()
    {
        Topjob = NULL;
        size = 1;
    }

    void Push_job(Bin* job)
    {
        if (Topjob == NULL)
        {
            Topjob = new Bin(*job);
            size++;
        }
        else
        {
            Bin* temp = new Bin(*job);
            temp->next = Topjob;
            Topjob = temp;
            size++;
        }
    }

    void Display()
    {
        cout << "==================" << endl;
        if (Topjob == NULL)
        {
            cout << "\033[1;31mNo jobs available\033[0m" << endl;
        }
        else
        {
            cout << "\033[1;33mJobs Stack:\033[0m" << endl;
            Bin* temp = Topjob;
            while (temp)
            {
                // Set text color to cyan (36) and bold (1), then reset
                cout << "\033[1;36mJob: " << temp->BinLocation << " | Filled: " << temp->filledPercent << "\033[0m" << endl;
                temp = temp->next;
            }
        }
        cout << "==================" << endl;
    }

    void Pop_job()
    {
        if (size == 1)
        {
            cout << "\033[1;31mNo jobs available for driver\033[0m" << endl;
        }
        else
        {
            Bin* temp = Topjob;
            Topjob->filledPercent = 0;
            Topjob = Topjob->next;
            delete temp;
            size--;
        }
    }
    void empty()
    {
        while (Topjob != NULL)
        {
            Pop_job();
        }
    }

    Bin& PopBin()
    {
        return *Topjob;
    }
};
