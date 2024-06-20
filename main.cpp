#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjList;

public:
    void addUser(int user) {
        if (adjList.find(user) == adjList.end()) {
            adjList[user] = std::vector<int>();
            std::cout << "User " << user << " added successfully!" << std::endl;
        } else {
            std::cout << "User already exists!" << std::endl;
        }
    }

    void addFriendship(int user1, int user2) {
        if (adjList.find(user1) != adjList.end() && adjList.find(user2) != adjList.end()) {
            adjList[user1].push_back(user2);
            adjList[user2].push_back(user1);
            std::cout << "Friendship added between " << user1 << " and " << user2 << std::endl;
        } else {
            std::cout << "One or both users do not exist!" << std::endl;
        }
    }

    void removeUser(int user) {
        if (adjList.find(user) != adjList.end()) {
            for (auto& friendID : adjList[user]) {
                adjList[friendID].erase(std::remove(adjList[friendID].begin(), adjList[friendID].end(), user), adjList[friendID].end());
            }
            adjList.erase(user);
            std::cout << "User " << user << " removed successfully!" << std::endl;
        } else {
            std::cout << "User does not exist!" << std::endl;
        }
    }

    void removeFriendship(int user1, int user2) {
        if (adjList.find(user1) != adjList.end() && adjList.find(user2) != adjList.end()) {
            adjList[user1].erase(std::remove(adjList[user1].begin(), adjList[user1].end(), user2), adjList[user1].end());
            adjList[user2].erase(std::remove(adjList[user2].begin(), adjList[user2].end(), user1), adjList[user2].end());
            std::cout << "Friendship removed between " << user1 << " and " << user2 << std::endl;
        } else {
            std::cout << "One or both users do not exist!" << std::endl;
        }
    }

    void displayNetwork() {
        for (const auto& pair : adjList) {
            std::cout << "User " << pair.first << ": ";
            for (const auto& friendID : pair.second) {
                std::cout << friendID << " ";
            }
            std::cout << std::endl;
        }
    }

    void findShortestPath(int startUser, int endUser) {
        std::queue<int> q;
        std::unordered_map<int, int> distances;
        std::unordered_map<int, int> predecessors;

        for (const auto& pair : adjList) {
            distances[pair.first] = -1;
        }

        q.push(startUser);
        distances[startUser] = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (const auto& neighbor : adjList[current]) {
                if (distances[neighbor] == -1) {
                    q.push(neighbor);
                    distances[neighbor] = distances[current] + 1;
                    predecessors[neighbor] = current;
                }
            }
        }

        if (distances[endUser] == -1) {
            std::cout << "No path found between " << startUser << " and " << endUser << std::endl;
            return;
        }

        std::vector<int> path;
        for (int at = endUser; at != startUser; at = predecessors[at]) {
            path.push_back(at);
        }
        path.push_back(startUser);

        std::reverse(path.begin(), path.end());
        std::cout << "Shortest path between " << startUser << " and " << endUser << ": ";
        for (const auto& user : path) {
            std::cout << user << " ";
        }
        std::cout << std::endl;
    }

    void connectedComponents() {
        std::unordered_map<int, bool> visited;

        for (const auto& pair : adjList) {
            visited[pair.first] = false;
        }

        for (const auto& pair : adjList) {
            if (!visited[pair.first]) {
                std::cout << "Component: ";
                DFS(pair.first, visited);
                std::cout << std::endl;
            }
        }
    }

    void recommendFriends(int user) {
        if (adjList.find(user) == adjList.end()) {
            std::cout << "User does not exist!" << std::endl;
            return;
        }

        std::unordered_map<int, int> mutualFriends;

        for (const auto& friendID : adjList[user]) {
            for (const auto& friendOfFriend : adjList[friendID]) {
                if (friendOfFriend != user && std::find(adjList[user].begin(), adjList[user].end(), friendOfFriend) == adjList[user].end()) {
                    mutualFriends[friendOfFriend]++;
                }
            }
        }

        std::vector<std::pair<int, int>> sortedMutualFriends(mutualFriends.begin(), mutualFriends.end());
        std::sort(sortedMutualFriends.begin(), sortedMutualFriends.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second;
        });

        std::cout << "Friend recommendations for " << user << ": ";
        for (const auto& pair : sortedMutualFriends) {
            std::cout << pair.first << " (" << pair.second << " mutual friends) ";
        }
        std::cout << std::endl;
    }

private:
    void DFS(int user, std::unordered_map<int, bool>& visited) {
        visited[user] = true;
        std::cout << user << " ";

        for (const auto& neighbor : adjList[user]) {
            if (!visited[neighbor]) {
                DFS(neighbor, visited);
            }
        }
    }
};

int main() {
    Graph g;
    int choice;
    do {
        std::cout << "\nSocial Network Analysis Tool\n";
        std::cout << "1. Add User\n2. Add Friendship\n3. Remove User\n4. Remove Friendship\n";
        std::cout << "5. Display Network\n6. Find Shortest Path\n7. Connected Components\n8. Recommend Friends\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        int user1, user2;
        switch (choice) {
            case 1:
                std::cout << "Enter user ID: ";
                std::cin >> user1;
                g.addUser(user1);
                break;

            case 2:
                std::cout << "Enter user IDs for friendship: ";
                std::cin >> user1 >> user2;
                g.addFriendship(user1, user2);
                break;

            case 3:
                std::cout << "Enter user ID to remove: ";
                std::cin >> user1;
                g.removeUser(user1);
                break;

            case 4:
                std::cout << "Enter user IDs to remove friendship: ";
                std::cin >> user1 >> user2;
                g.removeFriendship(user1, user2);
                break;

            case 5:
                g.displayNetwork();
                break;

            case 6:
                std::cout << "Enter user IDs to find shortest path: ";
                std::cin >> user1 >> user2;
                g.findShortestPath(user1, user2);
                break;

            case 7:
                g.connectedComponents();
                break;

            case 8:
                std::cout << "Enter user ID for friend recommendations: ";
                std::cin >> user1;
                g.recommendFriends(user1);
                break;

            case 0:
                std::cout << "Exiting..." << std::endl;
                break;

            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}