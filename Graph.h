#pragma once
#include"Header.h"

using namespace std;

class AdjList
{
public:
    Bin* head;
    Bin* tail;

    AdjList()
    {
        head = NULL;
        tail = NULL;
    }

    void insert(string s)
    {
        Bin* newBin = new Bin();
        newBin->SetBinLocation(s);

        if (head == NULL)
        {
            head = newBin;
            tail = newBin;
        }

        else
        {
            tail->next = newBin;
            tail = newBin;
        }
    }

    void display2()
    {
        Bin* temp = head;

        while (temp != NULL)
        {
            temp->DisplayBin();             
            cout << "\033[1;34m   \033[0m";
            temp = temp->next;
        }
        cout << endl;
    }

    void display()
    {
        Bin* temp = head;

        while (temp != NULL)
        {
            temp->DisplayBin();             
            cout << "\033[1;34m   \033[0m"; 
            temp = temp->next;
        }
        cout << endl;
    }
};
class Graph
{

public:
    AdjList* arr;
    int vertices;
    int currindex;
    int List_MaxCapacity;

    Graph(int a = 0)
    {
        arr = new AdjList[a + 1];
        vertices = a;

        currindex = 0;
    }

    // 3

    void showGraphStructure()
    {
        cout << "==================" << endl;
        for (int i = 0; i < vertices; i++)
        {
            if (i == 10)
            {
                // cout << "Truck Centre: " << endl;
            }
            if (i == 11)
            {
                // cout << "Dump Location: " << endl;
            }
            arr[i].display2();
            cout << endl;
        }
        cout << "==================" << endl;
    }

    void insertvertex(Bin* temp)
    {
        if (currindex < vertices)
        {
            arr[currindex].insert(temp->BinLocation);
            currindex++;
        }
        else
        {
            cout << "Adjlist reached to its Max capacity" << endl;
        }
    }

    void insertedge(int src, int dest, int weight)
    {
        // Check if src and dest are within the valid range
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices && src != dest)
        {
            // Check if the edge already exists
            Bin* current = arr[src].head;
            while (current != NULL)
            {
                string currentEdge = to_string(dest) + "(" + to_string(weight) + ")";
                if (current->BinLocation == currentEdge)
                {
                    // Edge already exists, no need to insert again
                    return;
                }
                current = current->next;
            }

            // Insert edge in the adjacency list of src
            arr[src].insert(to_string(dest) + "(" + to_string(weight) + ")");
        }
        else
        {
            // cerr << "Error: Invalid edge or self-loop." << endl;
        }
    }

    void getDistance(int src, int dest)
    {
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices)
        {
            Bin* current = arr[src].head;

            string edgeToFind = to_string(dest) + "(";
            bool edgeFound = false;
            string weightStr = "";

            while (current != nullptr)
            {
                string nodeValue = current->BinLocation;

                bool foundEdge = true;
                for (size_t i = 0; i < edgeToFind.length(); ++i)
                {
                    if (nodeValue[i] != edgeToFind[i])
                    {
                        foundEdge = false;
                        break;
                    }
                }

                if (foundEdge)
                {

                    size_t startPos = edgeToFind.length();
                    size_t endPos = startPos;

                    // Find the end position of the weight string
                    while (nodeValue[endPos] != ')')
                    {
                        ++endPos;
                    }

                    // Extract the weight
                    weightStr = nodeValue.substr(startPos, endPos - startPos);
                    edgeFound = true;
                    break;
                }
                current = current->next;
            }

            // Display the weight or indicate if the edge does not exist
            if (edgeFound)
            {
                cout << "Weight from Bin " << src << " to Bin " << dest << ": " << weightStr << endl;
            }
            else
            {
                cout << "Edge from Bin " << src << " to Bin " << dest << " does not exist." << endl;
            }
        }
        else
        {
            cerr << "Error: Invalid bins provided." << endl;
        }
    }
    void resetGraph()
    {
        currindex = 0;

        for (int i = 0; i < vertices; ++i)
        {
            Bin* current = arr[i].head;
            while (current != nullptr)
            {
                current->BinLocation = "";
                current->BinID = 0;
                current->filledPercent = 0;
                current->next = NULL;
                current = current->next;
            }
        }
    }
};