#include<iostream>
#include<map>
#include<vector>
#include<fstream>
using namespace std;


class MacroProcesser{
    public:
    fstream file,kpdtab,mdt,mnt;
    vector<string>mainFile;
    vector<string>output;
    map<string,vector<int>>MNT;
    map<int,vector<string>>MDT;
    map<int,map<string,string>>KPDTAB;
    map<string,map<int,string>>ALLAPTABS;
    MacroProcesser(){
        cout<<"LEt me open the files"<<endl;
        file.open("macroInput.txt");
        if(!file.is_open()){
            cout<<"Error in opening the file "<<endl;
        }
        else{
            //read mainFile
            string line;
            while (!file.eof())
            {
                getline(file,line);
                mainFile.push_back(line);
            }
        }

        kpdtab.open("kpdtab.txt");
        if(!kpdtab.is_open()){
            cout<<"Error in opening the kpdtab file "<<endl;
        }
        else{
            //read mainFile
            string line;
            while (!kpdtab.eof())
            {
                getline(kpdtab,line);
                vector<string>words;
                string w="";
                for(int i = 0;i<line.length();i++){
                    if(line[i]!=' '){
                        w+=line[i];
                    }
                    else{
                        words.push_back(w);
                        w="";
                    }
                }
                words.push_back(w);
                map<string,string>mp;
                mp[words[1]]=words[2];
                KPDTAB[stoi(words[0])] = mp;
            }
        }
        
        mdt.open("mdt.txt");
        if(!mdt.is_open()){
            cout<<"Error in opening the mdt file "<<endl;
        }
        else{
            string line;
            int ind = 1;
            while (!mdt.eof())
            {
                getline(mdt,line);
                vector<string>words;
                string w="";
                for(int i = 0;i<line.length();i++){
                    if(line[i]!=' '){
                        w+=line[i];
                    }
                    else{
                        words.push_back(w);
                        w="";
                    }
                }
                words.push_back(w);
                MDT[ind]=words;
                ind++;
            }
        }

        mnt.open("mnt.txt");
        if(!mnt.is_open()){
            cout<<"Error in opening the mnt file "<<endl;
        }
        else{
            string line;
            
            while (!mnt.eof())
            {
                getline(mnt,line);
                vector<string>words;
                string w="";
                for(int i = 0;i<line.length();i++){
                    if(line[i]!=' '){
                        w+=line[i];
                    }
                    else{
                        words.push_back(w);
                        w="";
                    }
                }
                words.push_back(w);
                vector<int>temp;
                for(int k =1;k<words.size();k++){
                    temp.push_back(stoi(words[k]));
                }
                MNT[words[0]] = temp;
            }
        }
        cout<<"all filrs are opened"<<endl;
    }

    void PerformPass2(){
        int macrosEncountered = 0;
        for(int i = 0;i<mainFile.size();i++){
            vector<string>splittedlines;
            string w="";
            string currLine = mainFile[i];
            for(int j = 0;j<mainFile[i].length();j++){
                if(currLine[j]!=' '){
                    w+=currLine[j];
                }
                else{
                    splittedlines.push_back(w);
                    w="";
                }
            }
            splittedlines.push_back(w);

            if(splittedlines[0]=="MEND"){
                macrosEncountered++;
            }
            
            string firstWord = splittedlines[0];
            if(MNT.find(firstWord)!=MNT.end() && macrosEncountered==MNT.size()){
                string macroName = firstWord;
                int noOfPP = MNT[macroName][0];
                int noOfKP = MNT[macroName][1];

                map<int,string>currAPTAB;
                //add all positional parameters
                for(int num = 1;num<=noOfPP;num++){
                    cout<<"Adding "<<splittedlines[num]<<endl;
                    currAPTAB[num] = splittedlines[num];
                }
                //add all kps as it is
                int kpdtptr = MNT[macroName][3];
                int cntKP = 0;
                for(auto itr:KPDTAB){
                    if(cntKP < noOfKP){
                        if(itr.first >= kpdtptr){
                            for(auto itr2:itr.second){
                                currAPTAB[noOfPP+1+cntKP] = itr2.second;
                                cntKP++;
                            }
                        }
                    }
                    else{
                        break;
                    }
                }

                for(int num = noOfPP+1;num<splittedlines.size();num++){
                    string completeWord = splittedlines[num];
                    int indOfEqu = 0;
                    for(int l = 0;l<completeWord.length();l++){
                        if(completeWord[l]=='='){
                            indOfEqu = l;
                            break;
                        }
                    }

                    string paraName = completeWord.substr(0,indOfEqu);
                    string value = completeWord.substr(indOfEqu+1,completeWord.length()-(indOfEqu+1));
                    int indOfAPTAB;
                    for(auto itr:KPDTAB){
                        for(auto itr2:itr.second){
                            if(itr2.first==paraName){
                                indOfAPTAB = itr.first;
                                break;
                            }
                        }
                    }
                    currAPTAB[indOfAPTAB+noOfPP] = value;
                }
                ALLAPTABS[macroName] = currAPTAB;

                //expand macro
                int mdtptr = MNT[macroName][2];
                for(auto itr:MDT){
                    if(itr.first >= mdtptr){
                        vector<string>temp = itr.second;
                        if(temp[0]=="MEND"){
                            break;
                        }
                        else{
                            string currAns = "";
                            currAns+="+";
                            currAns+=" ";
                            currAns+=temp[0];
                            currAns+=" ";
                            if(temp[1][0]=='('){
                                int ind = temp[1][3]-'0';
                                string val = ALLAPTABS[macroName][ind];
                                currAns+=val;
                                currAns+=" ";
                            }
                            else{
                                currAns+=temp[1];
                                currAns+=" ";
                            }

                            if(temp[2][0]=='('){
                                int ind = temp[2][3]-'0';
                                string val = ALLAPTABS[macroName][ind];
                                currAns+=val;
                                currAns+=" ";
                            }
                            else{
                                currAns+=temp[2];
                                currAns+=" ";
                            }
                            output.push_back(currAns);
                        }
                    }
                    
                }   

            }
            else{
                output.push_back(currLine);
            }

        }
    }

    void display(){
        cout<<"Display MDT"<<endl;
        for(auto itr:MDT){
            cout<<itr.first<<" ";
            for(auto itr2:itr.second){
                cout<<itr2<<" ";
            }
            cout<<endl;
        }        
        cout<<endl;
        cout<<"Display MNT"<<endl;
        for(auto itr:MNT){
            cout<<itr.first<<" ";
            for(auto itr2:itr.second){
                cout<<itr2<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<"Display KPDTAB"<<endl;
        for(auto itr:KPDTAB){
            cout<<itr.first<<" ";
            for(auto itr2:itr.second){
                cout<<itr2.first<<" "<<itr2.second<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        
        cout<<"Display ALLAPTABS"<<endl;
        for(auto itr:ALLAPTABS){
            cout<<"Macro Name : "<<itr.first<<" "<<endl;
            for(auto itr2:itr.second){
                cout<<itr2.first<<" "<<itr2.second<<endl;
            }
            cout<<endl;
        }

        cout<<endl;
        cout<<"Display output File"<<endl;
        for(auto itr:output){
            cout<<itr<<" "<<endl;
        }
    }
    
};
int main(){
    MacroProcesser obj;
    obj.PerformPass2();
    obj.display();
}