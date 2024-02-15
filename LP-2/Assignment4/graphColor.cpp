/*Implement a solution for a Constraint Satisfaction Problem using 
Branch and Bound and Backtracking for n-queens problem 
or a graph coloring problem*/
#include <bits/stdc++.h>
using namespace std;
void inputForList(vector <int> adjacencyList[] , int edges){
    for (int i = 0 ; i < edges ; i++){
        int u , v;
        cout << "Enter Node which have Edge Between : ";cin >> u >> v;
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }
    return ;
}
void printGraphList(vector<int> adjacencyList[] , int nodes){
    for (int i = 0 ; i < nodes ; i++){
        cout << "{" << i << "} : " ;
        for (auto j : adjacencyList[i]){
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
    return ;
}
bool isSafe(int startNode , vector <int>& color , vector <int>adjacencyList[] , int nodes , int toColor){
    for (auto i : adjacencyList[startNode]){
        if(color[i] == toColor) return false;
    }
    return true;
}
void recursion(int startNode , vector <int>& color , vector <int>adjacencyList[] ,int nodes, vector<vector <int>>& answer , int colorToPaint){
    if(startNode == nodes){
        answer.push_back(color);
        return ;
    }
    for (int i = 1 ; i <= colorToPaint ; i++){
        if(isSafe(startNode , color , adjacencyList , nodes , i)){
            color[startNode] = i;
            recursion(startNode + 1 , color , adjacencyList , nodes ,answer, colorToPaint);
            color[startNode] = 0;
        }
    }
}
vector <vector <int>> graphColoring(int nodes , vector <int> adjacencyList[] , int colorToPaint){
    vector <vector <int>> answer;
    vector <int> color(nodes , 0);
    int startNode = 0;
    recursion(startNode , color , adjacencyList , nodes , answer,colorToPaint);
    return answer;
}
int main(){
    int nodes , edges ;
    cout << "Enter Numbers of Nodes : "; cin >> nodes;
    cout << "Enter Numbers of Edges : "; cin >> edges;
    vector <int> adjacencyList[nodes];
    inputForList(adjacencyList , edges);
    int colorToPaint = 0;
    cout << "Enter Colors : "; cin >> colorToPaint;
    vector <vector <int>> answer = graphColoring(nodes , adjacencyList , colorToPaint);
    if(answer.size() == 0) answer.push_back({-1});
    for (auto i: answer){
        for(auto j : i){
            cout << j << " ";
        }
        cout << endl;
    } 
    // printGraphList(adjacencyList , nodes);
    return 0;
}