/*Implement a solution for a Constraint Satisfaction Problem using 
Branch and Bound and Backtracking for n-queens problem 
or a graph coloring problem*/
#include <bits/stdc++.h>
using namespace std;
void print(vector <vector <string>>& ans){
    for (auto i : ans){
        for(auto j : i){
            for (auto k : j){
                cout << k  << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return ;
}
bool isSafe(int row , int col , vector <string>& board , int n){
    int dummyRow = row , dummyCol = col;
    while(dummyRow >= 0 and dummyCol >= 0){
        if(board[dummyRow][dummyCol] == 'Q') return false;
        dummyCol--;
        dummyRow--;
    }
    dummyCol = col;
    while(dummyCol >= 0){
        if(board[row][dummyCol] == 'Q') return false;
        dummyCol--;
    }
    dummyRow = row , dummyCol = col;
    while(dummyRow < n and dummyCol >= 0){
        if(board[dummyRow][dummyCol] == 'Q') return false;
        dummyRow++;
        dummyCol--;
    }
    return true;
}
void recursion(int col , vector <vector <string>>& ans , vector <string>& board , int n){
    if(col == n){
        ans.push_back(board);
        return ;
    }
    for (int row = 0 ; row < n ; row++){
        if(isSafe(row , col , board , n)){
            board[row][col] = 'Q';
            recursion(col+1 , ans , board , n);
            board[row][col] = '.';
        }
    }
}
void recursion1(int col , vector <vector <string>>& ans , vector <string>& board , int n , vector <int>& left ,
    vector <int>& lowerDiagonal , vector<int>& upperDiagonal){
        if(col == n){
            ans.push_back(board);
            return ;
        }
        for (int row = 0 ; row < n ; row++){
            if(left[row] == 0 and lowerDiagonal[col+row] == 0 and upperDiagonal[n-1+col-row] == 0){
                board[row][col] = 'Q';
                left[row] = 1;
                lowerDiagonal[col+row] = 1;
                upperDiagonal[n-1+col-row] = 1;
                recursion1(col+1 , ans , board , n , left ,lowerDiagonal , upperDiagonal);
                board[row][col] = '.';
                left[row] = 0;
                lowerDiagonal[col+row] = 0;
                upperDiagonal[n-1+col-row] = 0;
            }
        }
    }
vector<vector<string>> solveNQueens(int n) {
    vector <vector<string>> ans;
    string s(n ,'.');
    vector <string> board(n , s);
    int coloumn = 0;
    // recursion(coloumn , ans , board , n);
    vector <int> left(n , 0) , lowerDiagonal(2*n-1,0) , upperDiagonal(2*n-1,0);
    recursion1(coloumn , ans , board , n , left , lowerDiagonal , upperDiagonal);
    return ans;
}
int main(){
    int N ;
    cout << "Enter Numbers of Queens : "; cin >> N;
    vector <vector <string>> ans = solveNQueens(N);
    print(ans);
    return 0;
}
