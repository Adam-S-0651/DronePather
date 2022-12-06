# DronePather
This is team members Adam Smith and Nicholas Sardinia's final project for DSA comparing Dijkstra's and A* pathfinding in 3D space.

The goal of the project is to simulate an obstacle course for a drone meant to fly around in 3D space. The program is able to randomly generate this obstacle course after getting some user parameters in the form of a directed 3D graph. The user can then select start and end points for the drone to "fly" to followed by choosing the pathfinding algorithm for the drone to use. The output is the shortest path length, the path taken to get there, and the number of edges traversed to reach that result. That last metric is how we are comparing the algorithms, as the one that iterates through more edges will take more resources and is more likely to be slower (given similar code structure).

The project is able to run 100000 nodes for both algorithms, however due to the randomly generated nature of graph generation, it is best to only have one edge connecting the nodes for the code to run in a reasonable time frame. It will generate with more edges, but how long it takes increases exponentially.

This project was written and tested in Visual Studio Code, so in the scenario that you are unable to compile it, we have included an executable. 
