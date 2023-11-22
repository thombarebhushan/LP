#include <bits/stdc++.h>
using namespace std;
// O(n)
// O(n) + O(fsize)
void callfifo(vector <int>& pages , int fsize){
    vector <int>frames(fsize , -1);//space O(fsize)
    unordered_map<int , int>mapp;//space O(n)
    int hit , miss , index;
    hit = miss = index = 0;
    for (int i = 0 ; i < pages.size(); i++){ // O(n)
        if(mapp[pages[i]] != 0){
            cout << "Hit , Present : " << pages[i] << "--> ";
            hit++;
            for (auto j : frames) cout << j << " ";
            cout << endl;
        }
        else{
            index %= fsize;
            miss++;
            cout << "Miss , Absent : " << pages[i] << "--> ";
            mapp[frames[index]] = 0;
            mapp[pages[i]] = 1;
            frames[index] = pages[i];
            for(auto j : frames) cout << j << " ";
            cout << endl;
            index++;
        }
    }
    cout << "Miss --> " << miss << endl;
    cout << "Hit --> " << hit << endl;
    return ;
}
void calloptimal(vector <int>pages , int fsize){
    vector <int> frames(fsize);
    unordered_map<int , int>mapp;
    int hit , miss , index ;
    hit = miss = index = 0;
    for (int i = 0; i < pages.size() ; i++){
        if(mapp[pages[i]] != 0){
            cout << "Hit , Present " << pages[i] << "--> ";
            hit++;
            for (auto j : frames) cout << j << " ";
            cout << endl;
        }
        else{
            if(index < fsize){
                frames[index] = pages[i];
                mapp[pages[i]] = 1;
                miss++;
                cout << "Miss , Absent (Put) " << pages[i] << "--> ";
                for (auto j : frames) cout << j << " ";
                cout << endl;
                index++;
            }
            else{
                int idx = -1;
                int val = -1;
                for (auto j : frames){
                    int present = 0;
                    for (int check = i+1 ; check < pages.size() ; check++){
                        if(pages[check] == j){
                            present = 1;
                            if(idx < check){
                                idx = check;
                                val = pages[idx];
                            }
                            break;
                        }
                    }
                    if(!present){
                        val = j;
                        break;
                    }
                }
                for (int j = 0 ; j < fsize ; j++){
                    if(frames[j] == val){
                        mapp[val] = 0;
                        mapp[pages[i]] = 1;
                        frames[j] = pages[i];
                        break;
                    }
                }
                miss++;
                cout << "Miss , Absent (Replace) " << pages[i] << "--> ";
                for (auto j : frames) cout << j << " ";
                cout << endl;
            }
        }
    }
    cout << "Miss --> " << miss << endl;
    cout << "Hit --> " << hit << endl;
    return ;
}
void calllru(vector <int>pages , int fsize){
    vector <int> frames(fsize);
    unordered_map<int , int>mapp;
    int hit , miss , index ;
    hit = miss = index = 0;
    for (int i = 0; i < pages.size() ; i++){
        if(mapp[pages[i]] != 0){
            cout << "Hit , Present " << pages[i] << "--> ";
            hit++;
            for (auto j : frames) cout << j << " ";
            cout << endl;
        }
        else{
            if(index < fsize){
                frames[index] = pages[i];
                mapp[pages[i]] = 1;
                miss++;
                cout << "Miss , Absent (Put) " << pages[i] << "--> ";
                for (auto j : frames) cout << j << " ";
                cout << endl;
                index++;
            }
            else{
                int idx = INT_MAX;
                int val = -1;
                for (auto j : frames){
                    int present = 0;
                    for (int check = i-1 ; check >= 0 ; check--){
                        if(pages[check] == j){
                            present = 1;
                            if(idx > check){
                                idx = check;
                                val = pages[idx];
                            }
                            break;
                        }
                    }
                }
                for (int j = 0 ; j < fsize ; j++){
                    if(frames[j] == val){
                        mapp[val] = 0;
                        mapp[pages[i]] = 1;
                        frames[j] = pages[i];
                        break;
                    }
                }
                miss++;
                cout << "Miss , Absent (Replace) " << pages[i] << "--> ";
                for (auto j : frames) cout << j << " ";
                cout << endl;
            }
        }
    }
    cout << "Miss --> " << miss << endl;
    cout << "Hit --> " << hit << endl;
    return ;
}
int main(){
    int n ; cout << "Enter Total Pages : "; cin >> n;
    int fsize; cout << "Enter Frame Size : ";cin >> fsize;
    cout << "Enter Pages : ";
    vector <int> pages(n);
    for (auto &i: pages) cin >> i;
    callfifo(pages , fsize);
    cout << endl << endl;
    calloptimal(pages , fsize);
    cout << endl << endl;
    calllru(pages , fsize);
    return 0;
}
// 16 5 0 3 4 2 3 1 0 7 5 3 6 0 1 3 4 0