#pragma once
#include"Header.h"
#include <chrono>

#include <ctime>
#include <windows.h>
using namespace std;

class Controller
{
public:
    int temp_bin_size = 12;
    Bin bins[12];
    int bin_Distance[12][12];
    Bin bins2[12];
    int bin_distance2[12][12];
    Bin bins3[12];
    Graph* g;
    Graph* gFilled;
    Driver drivers[5];
    const int NUM_HOURS = 72;
    const int NUM_BINS = 10;
    int temp;
    Controller()
    {
        g = new Graph(12);
        gFilled = new Graph(12);
    }

    void SendJobsToDriver(int i)
    {
        temp = i;
        drivers[i - 1].MyTruck->getBins(bins3, gFilled->currindex);
        drivers[i - 1].MyTruck->currentJobs();
    }
    void ShowDriversJob()
    {
        std::ifstream inputFile("jobsfordriver.txt");

        if (!inputFile.is_open())
        {
            std::cerr << "Error opening the file." << std::endl;
            return;
        }
        std::string line;
        while (std::getline(inputFile, line, '\n'))
        {

            std::cout << line << endl;
        }

        // Close the file
        inputFile.close();
    }
    void InsertVerticesInGraph()
    {
        for (int i = 0; i < temp_bin_size; i++)
        {
            g->insertvertex(&bins[i]);
        }
    }

    void FileReadingForBin_Data(string x)
    {

        string filename = x;

        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (int i = 0; i < 12; ++i)
        {
            string line;
            if (getline(inputFile, line))
            {
                istringstream iss(line);
                for (int j = 0; j < 12; ++j)
                {
                    string value;
                    getline(iss, value, ',');
                    bin_Distance[i][j] = stoi(value);
                }
            }
            else
            {
                cerr << "Error reading data from file." << endl;
                return;
            }
        }

        inputFile.close();
    }

    void ReadRandomDataAndInsertIntoBins()
    {

        srand(time(NULL));

        int hour = rand() % 72 + 1;

        if (hour < 1 || hour > 72)
        {
            cerr << "Invalid hour. Please enter an hour between 1 and 72." << endl;
            return;
        }

        ifstream inputFile("random_data.txt");

        if (!inputFile.is_open())
        {
            cerr << "Error opening file: random_data.txt" << endl;
            return;
        }

        // Move to the specified hour in the file
        for (int i = 1; i < hour; ++i)
        {
            string line;
            getline(inputFile, line);
            if (inputFile.eof())
            {
                cerr << "Error: Hour " << hour << " not found in the file." << endl;
                inputFile.close();
                return;
            }
        }

        // Read and assign values for the specified hour
        string line;
        getline(inputFile, line);
        istringstream iss(line);
        for (int j = 0; j < 10; ++j)
        {
            string value;
            getline(iss, value, ',');

            // Assuming bins is a 2D array of Bin objects in the Controller class
            // You may need to adjust this depending on your actual implementation
            bins[j].filledPercent = stoi(value); // Assuming FilledPercentage is a member variable of the Bin class
        }

        cout << "Values assigned to bins for hour " << hour << endl;

        inputFile.close();
    }

    void DisplayBinsDataForHour()
    {
        cout << "==================" << endl;
        for (int j = 0; j < 10; ++j)
        {
            cout << "Bin " << j + 1 << ": " << bins[j].filledPercent << "%" << endl;
        }
        cout << "==================" << endl;
    }

    void DisplayBins_Data()
    {
        cout << "==================" << endl;
        for (int i = 0; i < 12; ++i)
        {
            for (int j = 0; j < 12; ++j)
            {
                cout << bin_Distance[i][j] << " ";
            }
            cout << endl;
        }
        cout << "==================" << endl;
    }

    void InsertEdgesinGraph()
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                g->insertedge(i, j, bin_Distance[i][j]);
            }
        }
    }

    void GenerateRandomValues()
    {
        srand(static_cast<unsigned int>(time(nullptr)));

        ofstream outputFile("random_data.txt");

        if (!outputFile.is_open())
        {
            cerr << "Error opening the file." << endl;
            return;
        }

        for (int i = 0; i < NUM_HOURS; ++i)
        {
            for (int j = 0; j < NUM_BINS; ++j)
            {
                int random_value = rand() % 101;
                outputFile << random_value;

                if (j < NUM_BINS - 1)
                {
                    outputFile << ",";
                }
            }
            outputFile << endl;
        }

        outputFile.close();
        cout << "Random values written to 'random_data.txt' successfully." << endl;
    }

    void WorkFlow()
    {
        SectorChoice();
        cout << endl << endl;
    }
    void CreateGraphForFilledBins()
    {
        int filledCount = 0;
        int temp = 0;
        for (int i = 0; i < 12; i++)
        {
            if (bins[i].filledPercent > 75 || i == 10 || i == 11)
            {

                bins2[filledCount] = bins[i];

                temp = 0;
                for (int j = 0; j < 12; j++)
                {
                    if ((bins[j].filledPercent > 75) || (j == 11) || (j == 10))
                    {
                        if (i == 10 && j == 11)
                        {
                        }
                        else
                        {
                            bin_distance2[filledCount][temp] = bin_Distance[i][j];
                            temp++;
                        }
                    }
                }

                filledCount++;
            }
        }

        for (int i = 0; i < filledCount; i++)
        {
            gFilled->insertvertex(&bins2[i]);
        }
        for (int i = 0; i < filledCount; i++)
        {
            for (int j = 0; j < filledCount; j++)
            {
                gFilled->insertedge(i, j, bin_distance2[i][j]);
            }
        }
    }

    void stop()
    {
        std::ofstream driverJobsFile("jobsfordriver.txt", std::ios::out | std::ios::trunc);

        if (!driverJobsFile.is_open())
        {
            std::cerr << "Error opening driver jobs file: jobsfordriver.txt" << std::endl;
        }
        // Close the file
        driverJobsFile.close();
        std::ofstream Noti_JobsFile("Notification.txt", std::ios::out | std::ios::trunc);

        if (!Noti_JobsFile.is_open())
        {
            std::cerr << "Error opening driver jobs file: Notification.txt" << std::endl;
        }
        // Close the file
        Noti_JobsFile.close();
    }

    void SectorChoice()
    {
        int number;

        cout << "\033[1;33mEnter Sector:\033[0m" << endl; // Set text color to yellow (33) and bold (1), then reset
        cout << "==================" << endl;

        cout << "\033[1;34m1. G6\033[0m" << endl;  // Set text color to blue (34) and bold (1), then reset
        cout << "\033[1;34m2. G7\033[0m" << endl;  // Set text color to blue (34) and bold (1), then reset
        cout << "\033[1;34m3. G8\033[0m" << endl;  // Set text color to blue (34) and bold (1), then reset
        cout << "\033[1;34m4. G9\033[0m" << endl;  // Set text color to blue (34) and bold (1), then reset
        cout << "\033[1;34m5. G10\033[0m" << endl; // Set text color to blue (34) and bold (1), then reset
        cout << "\033[1;31m6. End\033[0m" << endl; // Set text color to red (31) and bold (1), then reset
        cout << "==================" << endl;

        cin >> number;
        switch (number)
        {
        case 1:

            FileReadingForBins("Bins_1.txt");
            FileReadingForBin_Data("Bins_Data_1.txt");
            InsertVerticesInGraph();
            InsertEdgesinGraph();
            GenerateRandomValues();
            ReadRandomDataAndInsertIntoBins();
            DisplayBinsDataForHour();
            CreateGraphForFilledBins();
            findShortestRoute();
            SendJobsToDriver(1);
            break;
        case 2:
            FileReadingForBins("Bins_2.txt");
            FileReadingForBin_Data("Bins_Data_2.txt");
            InsertVerticesInGraph();
            InsertEdgesinGraph();
            GenerateRandomValues();
            ReadRandomDataAndInsertIntoBins();
            DisplayBinsDataForHour();
            CreateGraphForFilledBins();
            findShortestRoute();
            SendJobsToDriver(2);
            break;
        case 3:
            FileReadingForBins("Bins_3.txt");
            FileReadingForBin_Data("Bins_Data_3.txt");
            InsertVerticesInGraph();
            InsertEdgesinGraph();
            GenerateRandomValues();
            ReadRandomDataAndInsertIntoBins();
            DisplayBinsDataForHour();
            CreateGraphForFilledBins();
            findShortestRoute();
            SendJobsToDriver(3);
            break;
        case 4:
            FileReadingForBins("Bins_4.txt");
            FileReadingForBin_Data("Bins_Data_4.txt");
            InsertVerticesInGraph();
            InsertEdgesinGraph();
            GenerateRandomValues();
            ReadRandomDataAndInsertIntoBins();
            DisplayBinsDataForHour();
            CreateGraphForFilledBins();
            findShortestRoute();
            SendJobsToDriver(4);
            break;
        case 5:
            FileReadingForBins("Bins_5.txt");
            FileReadingForBin_Data("Bins_Data_5.txt");
            InsertVerticesInGraph();
            InsertEdgesinGraph();
            GenerateRandomValues();
            ReadRandomDataAndInsertIntoBins();
            DisplayBinsDataForHour();
            CreateGraphForFilledBins();
            findShortestRoute();
            SendJobsToDriver(5);
            break;
        case 6:
            stop();
            exit(0);
            break;
        default:
            cout << "Wrong Choice" << endl;
            break;
        }
    }

    void FileReadingForBins(string x)
    {

        ifstream dataFile(x);

        if (!dataFile.is_open())
        {
            cout << "Could not open file" << endl;
            return;
        }

        for (int i = 0; i < 12; i++)
        {

            getline(dataFile, bins[i].BinLocation, ';');
        }

        dataFile.close();

        /*  for (int i = 0; i < 12; i++)
          {
              bins[i].DisplayBin();
          }*/
    }
    // 2

    void findShortestRoute()
    {
        vector<int> path;
        int totalDistance = 0;
        int shortestDistance = INT_MAX;
        vector<int> shortestPath;

        int startVertex = gFilled->currindex - 2; // Truck center
        int endVertex = gFilled->currindex - 1;   // Dump location

        vector<int> verticesToVisit;
        for (int i = 0; i < gFilled->currindex; ++i)
        {
            if (i != startVertex && i != endVertex)
            {
                verticesToVisit.push_back(i);
            }
        }

        do
        {
            int currentVertex = startVertex;
            totalDistance = 0;

            // Print the starting bin (Truck Center)
            // cout << "Visiting Truck Center - " << bins2[startVertex].BinLocation << endl;

            for (int i = 0; i < verticesToVisit.size(); ++i)
            {
                int nextVertex = verticesToVisit[i];
                totalDistance += bin_distance2[currentVertex][nextVertex];

                // Print the visited bin and its information
                //   cout << "Visiting Bin " << nextVertex << " - " << bins2[nextVertex].BinLocation << endl;

                currentVertex = nextVertex;
            }

            totalDistance += bin_distance2[currentVertex][endVertex];

            // Print the dump location
            // cout << "Visiting Dump Location - " << bins2[endVertex].BinLocation << endl;

            // Store the path for each permutation
            path = verticesToVisit;
            path.push_back(endVertex);

            // Update the shortest path if a shorter one is found
            if (totalDistance < shortestDistance)
            {
                shortestDistance = totalDistance;
                shortestPath = path;
            }
        } while (next_permutation(verticesToVisit.begin(), verticesToVisit.end()));

        cout << "==================" << endl;
        // Display the shortest path indices and total distance
        cout << "Shortest path indices: ";
        cout << startVertex << " "; // Truck center
        cout << bins2[startVertex].BinLocation << endl;
        int z = 0;
        bins3[z] = bins2[startVertex];
        z++;
        for (int i = 0; i < shortestPath.size(); ++i)
        {
            cout << shortestPath[i] << " ";
            cout << bins2[shortestPath[i]].BinLocation << endl;
            bins3[z] = bins2[shortestPath[i]];
            z++;
        }

        // cout << endVertex << " "; // Dump location
        cout << "\nTotal distance: " << shortestDistance << endl;
        cout << "==================" << endl;
    }

    void simulateTruckCollection()
    {
        cout << "==================" << endl;
        int x = 0;
        int time;
        auto start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        struct tm local_time;
        localtime_s(&local_time, &start_time);

        char time_buffer[80];
        strftime(time_buffer, 80, "%H:%M", &local_time);
        cout << "\033[1;35mTruck Collection Started at: " << time_buffer << "\033[0m" << endl;


        auto current_time = std::chrono::system_clock::now();

        for (int i = 0; i < gFilled->currindex; ++i)
        {
            if (i == 0)
            {
                cout << "\nStarting from: " << bins3[i].BinLocation << endl;
            }
            else {
                if (bins3[i].filledPercent > 0) 
                {
                    bins3[i].simulateCollection();
                    int temp = gettime(x, i);

                    bins3[i].updateFillLevel(0);

                    // Calculate time based on distance and speed
                    int speed = 8.33333; // speed in meters/second
                    int distance = temp; // distance in meters

                    int time = (distance) / (speed ); 

                    // Update current_time based on the calculated time
                    std::chrono::seconds timeToAdd(time); // Convert seconds to chrono duration
                    current_time += timeToAdd;

                    auto updated_time = std::chrono::system_clock::to_time_t(current_time);
                    struct tm updated_local_time;
                    localtime_s(&updated_local_time, &updated_time);
                    strftime(time_buffer, 80, "%H:%M", &updated_local_time);
                    cout << "\033[1;35mUpdated time: " << time_buffer << "\033[0m" << endl;

                    cout << "Bin " << bins3[i].BinLocation << " collected." << endl;
                }

                if (i == gFilled->currindex - 1) {
                    cout << "\nArriving at Dumping" << endl;
                    // Use Sleep for 2 seconds (2000 milliseconds)
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    cout << "Dumping Location: " << bins3[i].BinLocation << " Arrived." << endl;
                }
            }
        }
        cout << "\033[1;35mTruck Collection Completed.\033[0m" << endl;
        cout << "==================" << endl;
    }

    int gettime(int x, int y)
    {
        int temp = 0;
        for (int i = 0; i < 12; i++) {
            if (bins3[x].BinLocation == bins2[i].BinLocation) {
                for (int j = 0; j < 12; j++) {
                    if (bins3[y].BinLocation == bins2[j].BinLocation) {
                        temp = bin_distance2[i][j];
                        return temp; // Return the calculated distance in meters
                    }
                }
            }
        }
        return temp; // Return a default value if conditions are not met
    }

    void creatgFilled()
    {
        for (int i = 0; i < 12; i++)
        {
            bins2[i].BinID = 0;
            bins2[i].BinLocation = "";
            bins2[i].filledPercent = 0;
            bins3[i].BinID = 0;
            bins3[i].BinLocation = "";
            bins3[i].filledPercent = 0;
        }
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                bin_distance2[i][j] = 0;
            }
        }
        gFilled->resetGraph();

        DynamicAddBin();

        CreateGraphForFilledBins();

        findShortestRoute();

        stop();

        SendJobsToDriver(temp);
    }

    void DynamicAddBin()
    {
        bool foundBin = false;
        int index;

        while (!foundBin)
        {
            index = rand() % 10;
            if (bins[index].filledPercent < 75)
            {
                bins[index].filledPercent = 75 + index + 1;
                foundBin = true;
            }
        }

    }
};