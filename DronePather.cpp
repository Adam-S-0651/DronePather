
#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include "Graph.h"

using namespace std;

int main()
{
    unsigned int numNodes = 0, maxEdges = 0, maxXYZ = 0, selection = 2;
    char algorithm;
    Graph myGraph(numNodes, maxEdges, maxXYZ);

    // Get the user input to send to the Graph object
    cout << "\nWelcome to DronePather! Please enter the following information below:" << endl;
    cout << "*--------------------------------------------------------------------*" << '\n' << endl;
    
    while (selection != 0) {
        if (selection == 2) {
            // Get max bounds of axis
            cout << "Enter bounds of axis as a number (cube edge length between 1 and 1000): ";
            cin >> maxXYZ;
            while (maxXYZ > 1000 || maxXYZ < 1) {
                cout << "Error: Invalid coordinate bounds" << endl;
                cout << "Enter bounds of axis as a number (cube edge length between 1 and 1000): ";
                cin >> numNodes;
            }

            // Get number of vertices
            cout << "\nEnter number of vertices (must be at least 2 and fit in grid): ";
            cin >> numNodes;
            // This ensures that there is a number of vertices that will actually fit in the coordinate range
            while (numNodes > pow(maxXYZ + 1, 3) || numNodes < 2) {
                cout << "Error: Impossible number of vertices for graph" << endl;
                cout << "Enter number of vertices: ";
                cin >> numNodes;
            }

            // Get maximum edges allowed
            cout << "\nEnter maximum number of edges per vertex (must be at least one and possible for number of vertices): ";
            cin >> maxEdges;
            while (maxEdges > numNodes - 1 || maxEdges == 0) {
                cout << "Error: Max edges not possible with current number of vertices" << endl;
                cout << "Enter maximum number of edges per vertex: ";
                cin >> maxEdges;
            }

            //Make Graph object
            cout << "\nConstructing Potential Drone Paths..." << endl;
            myGraph = Graph(numNodes, maxEdges, maxXYZ);
            myGraph.printGraph();
        }
        
        // User-selected from and to nodes
        int from, to;
        cout << "\nEnter the numbers for the nodes:\nFrom: ";
        cin >> from;
        while (from >= numNodes || from < 0) {
            cout << "Error: Invalid Node" << endl;
            cout << "From: ";
            cin >> from;
        }
        cout << "To: ";
        cin >> to;
        while (from >= numNodes || to < 0 || from == to) {
            cout << "Error: Invalid Node" << endl;
            cout << "To: ";
            cin >> to;
        }


        // This will go to the Pathfinder to decide how to find a path from point A to B, BOTH will run in final version
        cout << "\nEnter algorithm to use; 'd' for Dijkstra and 'a' for A*: ";
        cin >> algorithm;
        while (algorithm != 'a' && algorithm != 'd') {
            cout << "Error: Invalid character entered" << endl;
            cout << "Enter algorithm to use; 'd' for Dijkstra and 'a' for A*: ";
            cin >> algorithm;
        }

        // Using this for now until we implement a way to select points
        cout << '\n' << "Finding shortest path for the Drone..." << endl;

        myGraph.runPathfinder(algorithm, from, to);

        cout << "\nEnter an option: \n0: Exit\n1: Select new nodes with same graph\n2: Generate a new graph\nYour selection: ";
        cin >> selection;
        while (selection != 0 && selection != 1 && selection != 2) {
            cout << "\nError: not a valid choice" << endl;
            cout << "Your selection: ";
            cin >> selection;
        }
    }
    cout << "\nThank you for using Drone Pather! Goodbye." << endl;
    return 0;
}