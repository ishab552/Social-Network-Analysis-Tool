# Social-Network-Analysis-Tool
 Graph-based Social Network Analysis Tool - This project involves building and analyzing a simple social network graph, where users can be represented as nodes and friendships as edges. 
 
 Project: Social Network Analysis Tool  
 
 Features to Implement: 
 1. *Add a User*: Add a new user to the network.
 2. *Add a Friendship*: Create a friendship (edge) between two users (nodes).
 3. *Remove a User*: Remove a user and all associated friendships.
 4. *Remove a Friendship*: Remove a specific friendship between two users.
 5. *Display Network*: Print the current state of the network.
 6. *Find Shortest Path*: Find the shortest path between two users using BFS.
 7. *Connected Components*: Find all connected components in the network using DFS.
 8. *Friend Recommendations*: Recommend friends based on mutual connections. 
 
 Steps to Implement:  
 1. *Define the Graph Class*:
    - Attributes: An adjacency list to store the graph (e.g., std::unordered_map<int, std::vector<int>>).
    - Methods:
      - addUser()
      - addFriendship()
      - removeUser()
      - removeFriendship()
      - displayNetwork()
      - findShortestPath()
      - connectedComponents()
      - recommendFriends()
 3. *Implement BFS for Shortest Path*:
    - Use a queue to explore nodes level by level.
    - Track visited nodes and their distances from the start node.
 5. *Implement DFS for Connected Components*:
    - Use a stack or recursion to explore all nodes in a component.
    - Track visited nodes to avoid reprocessing.
 7. *Main Function*:
    - Provide a menu to the user to select various options.
    - Call the corresponding methods from the Graph class based on user input.
