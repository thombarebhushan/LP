#include <bits/stdc++.h>
using namespace std;
struct Process{
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int priority;
    int id;
};
void display(vector <Process> &p){
    cout << "ProcessID\tArrivalTime\tBurstTime\tCompletionTime\tTAT\t\tWT\n";
    for(Process &proc : p){
        cout << proc.id << "\t\t" << proc.at << "\t\t" << proc.bt << "\t\t" << proc.ct << "\t\t" << proc.tat << "\t\t" << proc.wt << endl;
    }
    return;
} 
void FCFS(vector <Process>& p1){
    int currentTime = 0;
    for (Process& proc : p1){
        currentTime = max(currentTime , proc.at);
        currentTime += proc.bt;
        proc.ct = currentTime;
        proc.tat = proc.ct - proc.at;
        proc.wt = proc.tat - proc.bt;
    }
    display(p1);
    return ;
}
//Non-Preemptive
void SJF(vector <Process> &p2){
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
            currentTime++;
        }
        else{
            currentTime += p2[index].bt;
            p2[index].ct = currentTime;
            p2[index].tat = p2[index].ct - p2[index].at;
            p2[index].wt = p2[index].tat - p2[index].bt;
            answer.push_back(p2[index]);
            p2.erase(p2.begin() + index);
        }
    }
    display(answer);
    return ;
}
//Preemptive
void SJF2(vector <Process> &p3){
    int currentTime = 0;
    int n = p3.size();
    vector <int> storeBurstTime(n);
    for (int i = 0 ; i < n ; i++){
        storeBurstTime[i] = p3[i].bt;
    }
    vector<Process> answer;
    while(!p3.empty()){
        int index = -1;
        int minBurstTime = 1e9;
        for (int i = 0 ; i < p3.size() ; i++){
            if(p3[i].at <= currentTime and p3[i].bt < minBurstTime and p3[i].bt > 0){
                minBurstTime = p3[i].bt;
                index = i;
            }
        }
        if(index == -1){
            currentTime++;
        }
        else{
            currentTime++;
            p3[index].bt -= 1;
            minBurstTime =  p3[index].bt;
            if( p3[index].bt == 0){
                p3[index].bt = storeBurstTime[p3[index].id-1];
                minBurstTime = 1e9;
                p3[index].ct = currentTime;
                p3[index].tat = p3[index].ct - p3[index].at;
                p3[index].wt = p3[index].tat - p3[index].bt;
                answer.push_back(p3[index]);
                p3.erase(p3.begin() + index);
            }
        }
    }
    display(answer);
    return ;
}
void PRI(vector <Process> &p4){
    int currentTime = 0;
    vector <Process> answer;
    while(!p4.empty()){
        int index = -1;
        int minPriority = 1e9;
        for (int i = 0 ; i < p4.size() ; i++){
            if(p4[i].at <= currentTime and p4[i].priority < minPriority){
                minPriority = p4[i].priority;
                index = i;
            }
        }
        if(index == -1){
            currentTime++;
        }
        else{
            currentTime += p4[index].bt;
            p4[index].ct = currentTime;
            p4[index].tat = p4[index].ct - p4[index].at;
            p4[index].wt = p4[index].tat - p4[index].bt;
            answer.push_back(p4[index]);
            p4.erase(p4.begin() + index);
        }
    }
    display(answer);
    return ;
}
void RR(vector <Process>& p5 , int quantum){
    queue<int>readyQ;
    int currentTime = 0;
    int n = p5.size();
    vector<int>storeBurstTime(n);
    for (int i =0 ; i < p5.size() ; i++){
        storeBurstTime[i] = p5[i].bt;
        if(p5[i].at <= currentTime){
            readyQ.push(i);
        }
    }
    int countP = 0;
    while(countP != n){
        int index = readyQ.front();
        readyQ.pop();
        int counter = 0;
        while(counter != quantum and storeBurstTime[index] != counter){
            counter++;
            currentTime++;
            for (int i =0 ; i < n ; i++){
                if(p5[i].at == currentTime) readyQ.push(i);
            }
        }
        storeBurstTime[index] -= counter;
        if(storeBurstTime[index] == 0){
            countP++;
            p5[index].ct = currentTime;
            p5[index].tat = p5[index].ct - p5[index].at;
            p5[index].wt = p5[index].tat - p5[index].bt;
        }
        else{
            readyQ.push(index);
        }
    }
    display(p5);
    return ;
}
int main(){
    int n ;
    cout << "Enter Number of the Process : "; cin >> n;
    vector <Process> p(n);
    for (int i = 0 ; i < n ; i++){
        cout << "Enter Arriving Time for the Process : " << i+1 << " : " ; cin >> p[i].at;
        p[i].id = i+1;
    }
    for (int i = 0 ; i < n ; i++){
        cout << "Enter Burst Time for the Process : " << i+1 << " : " ; cin >> p[i].bt;
    }
    for (int i = 0; i < n ; i++){
        cout << "Enter Priority for the Process : " << i+1 << " : " ; cin >> p[i].priority;
    }
    vector<Process>p1 = p;
    FCFS(p1);
    vector <Process>p2 = p;
    SJF(p2);
    vector <Process>p3 = p;
    SJF2(p3);
    vector <Process>p4 = p;
    PRI(p4);
    int quantum;
    cout << "Enter Time Quantum : "; cin >> quantum;
    vector <Process>p5 = p;
    RR(p5 , quantum);
    return 0;
}