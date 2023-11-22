#include<iostream>
#include<vector>
#include<fstream>
using namespace  std;

class Instruction{
    public:
    int lc;
    string opcodeIC,op1IC,op2IC;
    Instruction(){
        lc=0;
        opcodeIC="";
        op1IC="";
        op2IC="";
    }
};

class MCGenerator{
    public:
    vector<string>machineCode;
    vector<string> readFile(string fname){
        fstream f;
        f.open(fname);
        vector<string>lines;
        string line;
        while (!f.eof())
        {
            getline(f,line);
            lines.push_back(line);
        }
        f.close();
        return lines;
    }

    vector<string>getWords(string line){
        vector<string>words;
        string word="";
        for(int i =0;i<line.size();i++){
            if(line[i]!=' '){
                word+=line[i];
            }
            else{
                words.push_back(word);
                word="";
            }
        }
        words.push_back(word);
        return words;
    }

    vector<vector<string>> getSplittedWords(vector<string>lines){
        vector<vector<string>> splittedWOrds;
        for(int i = 0;i<lines.size();i++){
            vector<string>v = getWords(lines[i]);
            splittedWOrds.push_back(v);
        }
        return splittedWOrds;
    }
    Instruction getInstruction(vector<string>line){
        int len = line.size();
        int i = 0;
        Instruction instr;
        instr.lc=stoi(line[i]);
        i++;
        instr.opcodeIC=line[i];
        i++;
        if(i<len){
            instr.op1IC=line[i];
            i++;
        }
        if(i<len){
            instr.op2IC=line[i];
            i++;
        }
        return instr;
    }

    vector<Instruction> getAllInstructions(vector<vector<string>>lines){
        vector<Instruction> allInstruction;
        for(int i = 0;i<lines.size();i++){
            Instruction instr = getInstruction(lines[i]);
            allInstruction.push_back(instr);
        }
        return allInstruction;
    }

    void performPass2(vector<Instruction>instr,vector<vector<string>>litTab,vector<vector<string>>symTab){

        for(int itr = 0;itr<instr.size();itr++){
            string mc="";
            // cout<<instr[itr].lc<<" "<<instr[itr].opcodeIC<<" "<<instr[itr].op1IC<<" "<<instr[itr].op2IC<<endl;
            if(instr[itr].lc!=-1){
                mc+=to_string(instr[itr].lc);
                mc+=" ";
                string category = instr[itr].opcodeIC.substr(1,2);
                // cout<<category<<endl;
                if(category=="DL"){
                    string code = instr[itr].opcodeIC.substr(4,2);
                    // cout<<code<<endl;
                    if(code=="01"){
                        mc+="00  ";
                        mc+="0 ";
                        string cnst = instr[itr].op1IC.substr(3,2);
                        mc+=cnst;
                        mc+=" ";
                    }
                    else{
                        mc="DL,02 : No Machine Code ";
                        // cout<<"DL,02 : No Machine Code "<<endl;
                    }
                    
                }
                else{
                    string code = instr[itr].opcodeIC.substr(4,2);
                    mc+=code;
                    mc+=" ";
                    if(instr[itr].op1IC!=""){
                        string regNum = instr[itr].op1IC.substr(1,1);
                        mc+=regNum;
                        mc+=" ";
                    }
                    if(instr[itr].op2IC!=""){
                        string cat = instr[itr].op2IC.substr(1,1);
                        if(cat=="S"){
                            int index = stoi(instr[itr].op2IC.substr(4,1));
                            // cout<<"index1 : "<<index<<endl;
                            string address = symTab[index-1][1];
                            mc+=address;    
                            mc+=" ";
                        }
                        else{
                            int index = stoi(instr[itr].op2IC.substr(4,1));
                            // cout<<"index2 : "<<index<<endl;
                            string address = litTab[index-1][1];
                            mc+=address;
                            mc+" ";
                        }
                    }
                }
            }
            else{
                mc="No Machine Code ";
                // cout<<"No Machine Code "<<endl;
            }
            if(mc!=""){
                machineCode.push_back(mc);
            }
            // cout<<mc<<endl;
        }
        for(auto i:machineCode){
            cout<<i<<endl;
        }
        
    }
    
};
int main(){
    MCGenerator obj;
    vector<string>readFile = obj.readFile("pass2test1.txt");
    vector<vector<string>>tokens = obj.getSplittedWords(readFile);
    vector<Instruction> allInstr = obj.getAllInstructions(tokens);

    vector<string>readSymFile = obj.readFile("symTab.txt");
    vector<string>readLitFile = obj.readFile("litTab.txt");
    vector<vector<string>>symTab = obj.getSplittedWords(readSymFile);
    vector<vector<string>>litTab = obj.getSplittedWords(readLitFile);
    
    
    // for(auto i:allInstr){
    //     cout<<i.lc<<" "<<i.opcodeIC<<" "<<i.op1IC<<" "<<i.op2IC<<endl;  
    // }
    obj.performPass2(allInstr,litTab,symTab);
}