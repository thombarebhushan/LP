/*
Implement depth first search algorithm and Breadth First Search algorithm,
Use an undirected graph and develop a recursive algorithm for searching 
all the vertices of a graph or tree data structure.
*/
#include <bits/stdc++.h>
using namespace std;
void inputGraphList(vector <int> adjacencyList[], int edges){
    for (int i = 0 ; i < edges ; i++){
        int u , v;
        cout << "Enter Nodes have the edges in Between : "; cin >> u >> v;
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }
    return ;
}
void printGraphList(vector <int> adjacencyList[] , int nodes){
    for (int i = 1 ; i <= nodes ; i++){
        cout << "{" << i << "} : ";
        for (auto j : adjacencyList[i]){
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
    return ;
}
void BFS(vector <int> adjacencyList[] , int nodes){
    int source ;
    cout << "Enter Source Node to Start Traversal : "; cin >> source;
    vector <int> visited(nodes+1 , 0);
    visited[0] = 1;
    visited[source] = 1;
    queue <int> q;
    q.push(source);
    cout << "BFS Traversal : ";
    while(!q.empty()){
        int front = q.front();
        q.pop();
        cout << front << " ";
        for (auto i : adjacencyList[front]){
            if(!visited[i]){
                visited[i] = 1;
                q.push(i);
            }
        }
    }
    cout << endl;
    return ;
}
void dfsRecursion(int node , vector <int>& visited , vector <int> adjacencyList[]){
    visited[node] = 1;
    cout << node << " ";
    for (auto i : adjacencyList[node]){
        if(!visited[i]){
            dfsRecursion(i , visited , adjacencyList);
        }
    }
    return ;
}
void DFS(vector <int> adjacencyList[] , int nodes){
    int source ;
    cout << "Enter Source Node to Start Traversal : "; cin >> source;
    vector <int> visited(nodes+1 , 0);
    visited[0] = 1;
    cout << "DFS Traversal : ";
    dfsRecursion(source , visited , adjacencyList);
    return ;
} 
int main(){
    int nodes , edges;
    cout << "Enter Number of nodes : "; cin >> nodes;
    cout << "Enter Numbers of Edeges : "; cin >> edges;
    vector <int> adjacencyList[nodes+1];
    int temp = 1;
    while(temp){
        cout << "----------------------------------" << endl;
        cout << "Enter 1 To Create Graph " << endl;
        cout << "Enter 2 To Print Adjacency List " << endl;
        cout << "Enter 3 To Print BFS " << endl;
        cout << "Enter 4 To Print DFS " << endl;
        cout << "Enter 5 To Exit " << endl;
        cout << "----------------------------------" << endl;
        int choice = 1;
        cout << "Enter your from above choice : "; cin >> choice;
        if(choice == 1){
            inputGraphList(adjacencyList , edges);
            char ch ;
            cout << "Do you want to continue : (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y') temp = 1;
            else{
                temp = 0;
                cout << "Exited" << endl;
                return 0;
            }
        }
        else if(choice == 2){
            printGraphList(adjacencyList , nodes);
            char ch ;
            cout << "Do you want to continue : (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y') temp = 1;
            else{
                temp = 0;
                cout << "Exited" << endl;
                return 0;
            }
        }
        else if(choice == 3){
            BFS(adjacencyList , nodes);
            char ch ;
            cout << "Do you want to continue : (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y') temp = 1;
            else{
                temp = 0;
                cout << "Exited" << endl;
                return 0;
            }
        }
        else if(choice == 4){
            DFS(adjacencyList , nodes);
            cout << endl;
            char ch ;
            cout << "Do you want to continue : (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y') temp = 1;
            else{
                temp = 0;
                cout << "Exited" << endl;
                return 0;
            }
        }
        else{
            cout << "Exited" << endl; 
            return 0;
        }
    }
    return 0; 
}