#include <bits/stdc++.h>
using namespace std;
struct Process{
    int id;
    int at ;
    int bt ;
    int ct ;
    int priority;
    int tat;
    int wt;
};
void display(vector <Process>&p){
    cout << "ProcessId\tArrivalTime\tBurstTime\tCompletionTime\tTAT\tWT\n";
    for (Process&proc : p){
        cout << proc.id << "\t\t" << proc.at << "\t\t" << proc.bt << "\t\t" << proc.ct << "\t\t" << proc.tat << "\t\t" << proc.wt << endl;
    }
    return ;
}
void FCFS(vector <Process>&p1){
    sort(p1.begin() , p1.end() , [](const Process&a , const Process&b){
        return a.at < b.at;
    });
    int currentTime = 0;
    for (Process&p : p1){
        currentTime = max(currentTime , p.at);
        currentTime += p.bt;
        p.ct = currentTime;
        p.tat= p.ct - p.at;
        p.wt = p.tat - p.bt;
    }
    display(p1);
    return ;
}
void SJF(vector <Process>&p2){
    int currentTime = 0;
    vector <Process> answer;
    while(!p2.empty()){
        int index = -1;
        int minBurstTime = 1e9;
        for (int i = 0 ; i < p2.size() ; i++){
            if(p2[i].at <= currentTime and p2[i].bt < minBurstTime){
                minBurstTime = p2[i].bt;
                index = i;
            }
        }
        if(index == -1){
            currentTime++;//cpu ideal Condition
        }
        else{
            Process&proc = p2[index];
            currentTime += p2[index].bt;
            proc.ct = currentTime;
            proc.at = p2[index].at;
            proc.bt = p2[index].bt;
            proc.tat = proc.ct - proc.at;
            proc.wt = proc.tat - proc.bt;
            answer.push_back(proc);
            p2.erase(p2.begin() + index);
        }
    }
    display(answer);
    return ;
}
void PRI(vector <Process>&p3){
    int currentTime = 0;
    vector <Process> answer;
    while(!p3.empty()){
        int index = -1;
        int minPriority = 1e9;
        for (int i = 0 ; i < p3.size() ; i++){
            if(p3[i].at <= currentTime and p3[i].priority < minPriority){
                minPriority = p3[i].priority;
                index = i;
            }
        }
        if(index == -1){
            currentTime++;//cpu ideal Condition
        }
        else{
            Process&proc = p3[index];
            currentTime += p3[index].bt;
            proc.ct = currentTime;
            proc.at = p3[index].at;
            proc.bt = p3[index].bt;
            proc.tat = proc.ct - proc.at;
            proc.wt = proc.tat - proc.bt;
            answer.push_back(proc);
            p3.erase(p3.begin() + index);
        }
    }
    display(answer);
    return ;
}
int main(){
    int n;
    cout << "Enter Number of Processes : "; cin >> n;
    vector<Process> p(n);
    for (int i = 0 ; i < n ; i++){
        p[i].id = i+1;
        cout << "Entet Arriving Time for the Process " << i+1 << " : "; cin >> p[i].at;
    }
    for (int i = 0 ; i < n ; i++){
        p[i].id = i+1;
        cout << "Entet Burst Time for the Process " << i+1 << " : "; cin >> p[i].bt;
    }
    vector <Process>p1 = p;
    FCFS(p1);
    vector <Process>p2 = p;
    SJF(p2);
    for (int i = 0 ;i < n ;i++){
        cout << "Enter Prioroty for the Process : " << i+1 << " : ";cin >> p[i].priority;
    }
    vector <Process>p3 = p;
    PRI(p3);
    return 0;
}