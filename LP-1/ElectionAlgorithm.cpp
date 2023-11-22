#include <bits/stdc++.h>
using namespace std;
int Process[100],n,Leader;
void displayStatus(){
    cout << "##############################################################" << endl;
    cout << "Leader is : " << Leader << endl;
    cout << "##############################################################" << endl;
    cout << "Processes : ";
    for (int i = 1 ; i <= n ; i++){
        cout << i << " ";
    }
    cout << endl;
    cout << "Status    : ";
    for (int i = 1 ; i <= n ; i++){
        cout << Process[i] << " ";
    }
    cout << endl;
    cout << "##############################################################" << endl;
    return ;
}
void bullyAlgo(){
    int temp = 1;
    while(temp == 1){
        cout << "##############################################################" << endl;
        cout << "Enter 1 to Crash Process : " << endl;
        cout << "Enter 2 to Activate Process : " << endl;
        cout << "Enter 3 to Display Status : " << endl;
        cout << "Enter 4 Exit Bully Algorithm: " << endl;
        cout << "##############################################################" << endl;
        int choice = 1;
        cout << "Enter Your Choice : "; cin >> choice;
        if(choice == 1){
            int counter = 0;
            for (int i = 1 ; i <= n ; i++){
                if(Process[i] == 0) counter++;
            }
            if(counter >= (n-1)){
                cout << "At Least One Leader is Needed !!!!" << endl;
                char ch;
                cout << "Do you want to Continue in {Bully} (y/n) : "; cin >> ch;
                if(ch == 'y' or ch == 'Y'){
                    temp = 1;
                }
                else{
                    temp = 0;
                    cout << "Bully Exited SuccessFully " << endl;
                    return ;
                }
            }
            int crash;
            cout << "Enter Process Number to Crash : "; cin >> crash;
            if(Process[crash]){
                Process[crash] = 0;
                cout << "Now Process " << crash << " is Crashed" << endl;
            }
            else{
                cout << "Process " << crash << " is allready Crashed" << endl;
            }
            
            if(crash == Leader){
                int nextLeader;
                cout << "Enter Process Number to start Election : "; cin >> nextLeader;
                while(nextLeader == Leader or Process[nextLeader] == 0){
                    cout << "Enter Process Number to start Election : "; cin >> nextLeader;
                }
                bool flag = false;
                int CoLeader ;
                for (int i = nextLeader+1 ; i <= n ; i++){
                    cout << "Sending Request From " << nextLeader << " to " << i << endl;
                    if(Process[i]){
                        cout << "Process " << i << " Replying OK to " << nextLeader << endl;
                        flag = true;
                        CoLeader = i;
                    }
                }
                cout << "New Leader is SET " ;
                if(flag){
                    Leader = CoLeader;
                }
                else{
                    Leader = nextLeader ;
                }
                cout << Leader << endl;
            }
            char ch;
            cout << "Do you want to Continue in {Bully} (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y'){
                temp = 1;
            }
            else{
                temp = 0;
                cout << "Bully Exited SuccessFully " << endl;
                return ;
            }
        }
        else if(choice == 2){
            int activate;
            cout << "Enter Process Number to Activate : "; cin >> activate;
            if(Process[activate] == 0){
                Process[activate] = 1;
                cout << "Now Process " << activate << " is Activate" << endl;
            }
            else{
                cout << "Process " << activate << " is allready Activate" << endl;
            }
            if(activate == n){
                Leader = n;
                cout << "New Leader is SET "  << Leader << endl; 
            }
            else{
                bool flag = false;
                int CoLeader ;
                for (int i = activate+1 ; i <= n ; i++){
                    cout << "Sending Request From " << activate << " to " << i << endl;
                    if(Process[i]){
                        cout << "Process " << i << " Replying OK to " << activate << endl;
                        flag = true;
                        CoLeader = i;
                    }
                }
                cout << "New Leader is SET " ;
                if(flag){
                    Leader = CoLeader;
                }
                else{
                    Leader = activate ;
                }
                cout << Leader << endl;
            }
            char ch;
            cout << "Do you want to Continue in {Bully} (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y'){
                temp = 1;
            }
            else{
                temp = 0;
                cout << "Bully Exited SuccessFully " << endl;
                return ;
            }
        }
        else if(choice == 3){
            displayStatus();
            char ch;
            cout << "Do you want to Continue in {Bully} (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y'){
                temp = 1;
            }
            else{
                temp = 0;
                cout << "Bully Exited SuccessFully " << endl;
                return ;
            }
        }
        else{
            cout << "Bully Exited SuccessFully " << endl;
            return ;
        }
    }
}
void ringAlgo(){
    int temp = 1;
    while(temp == 1){
        cout << "##############################################################" << endl;
        cout << "Enter 1 to Crash Process : " << endl;
        cout << "Enter 2 to Activate Process : " << endl;
        cout << "Enter 3 to Display Status : " << endl;
        cout << "Enter 4 Exit Ring Algorithm: " << endl;
        cout << "##############################################################" << endl;
        int choice = 1;
        cout << "Enter Your Choice : "; cin >> choice;
        if(choice == 1){
            int counter = 0;
            for (int i = 1 ; i <= n ; i++){
                if(Process[i] == 0) counter++;
            }
            if(counter >= (n-1)){
                cout << "At Least One Leader is Needed !!!!" << endl;
                char ch;
                cout << "Do you want to Continue in {Bully} (y/n) : "; cin >> ch;
                if(ch == 'y' or ch == 'Y'){
                    temp = 1;
                }
                else{
                    temp = 0;
                    cout << "Ring Exited SuccessFully " << endl;
                    return ;
                }
            }
            int crash;
            cout << "Enter Process Number to Crash : "; cin >> crash;
            if(Process[crash]){
                Process[crash] = 0;
                cout << "Now Process " << crash << " is Crashed" << endl;
            }
            else{
                cout << "Process " << crash << " is allready Crashed" << endl;
            }
            
            if(crash == Leader){
                int intiater;
                cout << "Enter Process Number to start Election : "; cin >> intiater;
                while(intiater == Leader ){
                    cout << "Enter Process Number to start Election : "; cin >> intiater;
                }
                vector <int> ring;
                int behind = intiater;
                for (int i = intiater ; i <= n ; i++){
                    if(Process[i]){
                        cout << "Sending Request from " << behind << " to " << i << endl;
                        behind = i;
                        ring.push_back(i); 
                        cout << "Ring contain { " ;
                        for (auto it : ring) cout << it << " ";
                        cout << "}" << endl;
                    }
                }
                for (int i = 1 ; i < intiater ; i++){
                    if(Process[i]){
                        cout << "Sending Request from " << behind << " to " << i << endl;
                        behind = i;
                        ring.push_back(i); 
                        cout << "Ring contain { " ;
                        for(auto it : ring) cout << it << " ";
                        cout << " }" << endl;
                    }
                }
                cout << "New Leader is SET " ;
                Leader = *max_element(ring.begin() , ring.end());
                cout << Leader << endl;
            }
            char ch;
            cout << "Do you want to Continue in {Ring} (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y'){
                temp = 1;
            }
            else{
                temp = 0;
                cout << "Ring Exited SuccessFully " << endl;
                return ;
            }
        }
        else if(choice == 2){
            int activate;
            cout << "Enter Process Number to Activate : "; cin >> activate;
            if(Process[activate] == 0){
                Process[activate] = 1;
                cout << "Now Process " << activate << " is Activate" << endl;
            }
            else{
                cout << "Process " << activate << " is allready Activate" << endl;
            }
            if(activate == n){
                Leader = n;
                cout << "New Leader is SET "  << Leader << endl; 
            }
            else if(activate > Leader){
                int intiater;
                cout << "Enter Process Number to start Election : "; cin >> intiater;
                while(intiater == Leader ){
                    cout << "Enter Process Number to start Election : "; cin >> intiater;
                }
                vector <int> ring;
                int behind = intiater;
                for (int i = intiater ; i <= n ; i++){
                    if(Process[i]){
                        cout << "Sending Request from " << behind << " to " << i << endl;
                        behind = i;
                        ring.push_back(i); 
                        cout << "Ring contain { " ;
                        for(auto it : ring) cout << it << " ";
                        cout << "}" << endl;
                    }
                }
                for (int i = 1 ; i < intiater ; i++){
                    if(Process[i]){
                        cout << "Sending Request from " << behind << " to " << i << endl;
                        behind = i;
                        ring.push_back(i); 
                        cout << "Ring contain { " ;
                        for(auto it : ring) cout << it << " ";
                        cout << " }" << endl;
                    }
                }
                cout << "New Leader is SET " ;
                Leader = *max_element(ring.begin() , ring.end());
                cout << Leader << endl;
            }
            char ch;
            cout << "Do you want to Continue in {Ring} (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y'){
                temp = 1;
            }
            else{
                temp = 0;
                cout << "Ring Exited SuccessFully " << endl;
                return ;
            }
        }
        else if(choice == 3){
            displayStatus();
            char ch;
            cout << "Do you want to Continue in {Ring} (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y'){
                temp = 1;
            }
            else{
                temp = 0;
                cout << "Ring Exited SuccessFully " << endl;
                return ;
            }
        }
        else{
            cout << "Ring Exited SuccessFully " << endl;
            return ;
        }
    }
}
int main(){
    cout << "Enter total Processes : ";cin >> n;
    int counter = 0;
    for (int i = 1 ; i <= n ; i++){
        cout << "Enter Status of the Process " << i << " (0/1) : " ; cin >> Process[i];
        if(Process[i]){
            Leader = i;
        }
        else{
            counter++;
        }
    }
    if(counter == n){
        cout << "At Least one Leader is Needed !!!!! " << endl ; 
        return 0;
    }
    int temp = 1;
    while(temp == 1){
        cout << "##############################################################" << endl;
        cout << "Enter 1 to Execute Bully Algorithm : " << endl;
        cout << "Enter 2 to Execute Ring Algorithm : " << endl;
        cout << "Enter 3 to Display Status : " << endl;
        cout << "Enter 4 Exit : " << endl;
        cout << "##############################################################" << endl;
        int choice = 1;
        cout << "Enter Your Choice : "; cin >> choice;
        if(choice == 1){
            bullyAlgo();
            char ch;
            cout << "Do you want to Continue in {Main} (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y'){
                temp = 1;
            }
            else{
                temp = 0;
                cout << "Program Exited SuccessFully " << endl;
                return 0;
            }
        }
        else if(choice == 2){
            ringAlgo();
            char ch;
            cout << "Do you want to Continue in {Main} (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y'){
                temp = 1;
            }
            else{
                temp = 0;
                cout << "Program Exited SuccessFully " << endl;
                return 0;
            }
        }
        else if(choice == 3){
            displayStatus();
            char ch;
            cout << "Do you want to Continue in {Main} (y/n) : "; cin >> ch;
            if(ch == 'y' or ch == 'Y'){
                temp = 1;
            }
            else{
                temp = 0;
                cout << "Program Exited SuccessFully " << endl;
                return 0;
            }
        }
        else{
            cout << "Program Exited SuccessFully " << endl;
            return 0;
        }
    }   
    return 0;
}