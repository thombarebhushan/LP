#include<iostream>
#include<map>
#include<fstream>
#include<vector>
using namespace std;

class Instruction{
    public:
    string label,op1,op2,opcode;
    
    Instruction(){
        this->label="";
        this->opcode="";
        this->op1="";
        this->op2="";
    }
    friend class ICGenerator;
};

class ICGenerator{
    map<string,string>IS;
    map<string,string>DL;
    map<string,string>REG;
    map<string,string>AD;
    map<string,string>CC;

    vector<pair<string,int>> symTab;
    vector<pair<string,int>>litTab;
    vector<int>poolTab;
    vector<string> intermediateCode;
    int lc;
    public:
    ICGenerator(){
        lc = 0;

        //adding first entry to the poolTabel
        poolTab.push_back(1);
        IS["STOP"]="00";
        IS["ADD"]="01";
        IS["SUB"]="02";
        IS["MULT"]="03";
        IS["MOVER"]="04";
        IS["MOVEM"]="05";
        IS["COMP"]="06";
        IS["BC"]="07";
        IS["DIV"]="08";
        IS["READ"]="09";
        IS["PRINT"]="10";


        AD["START"]="01";
        AD["END"]="02";
        AD["ORIGIN"]="03";
        AD["EQU"]="04";
        AD["LTORG"]="05";

        DL["DS"]="02";
        DL["DC"]="01";


        REG["AREG"]="01";
        REG["BREG"]="02";
        REG["CREG"]="03";
        REG["DREG"]="04";



        CC["LT"]="01";
        CC["LE"]="02";
        CC["EQ"]="03";
        CC["GT"]="04";
        CC["GE"]="05";
        CC["ANY"]="06";
    }

    //Read the file and insert all strings in a vector
    vector<string> readFile(string fname){
        ifstream f;
        vector<string> lines;
        f.open(fname);

        string line;
        while (!f.eof())
        {
            getline(f,line);
            lines.push_back(line);
        }
        f.close();
        return lines;
    }

    //Get/Split words from a string
    vector<string> getWords(string line){
        vector<string>words;
        string word = "";
        for(int i = 0;i<line.size();i++){
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

    //generate a vector of all splitted words
    vector<vector<string>> getAllWords(vector<string>lines){
        vector<vector<string>> allLines;
        for(auto i:lines){
            vector<string>words = getWords(i);
            allLines.push_back(words);
        }
        return allLines;
    }

    //Function to create an instruction from splitted words
    Instruction getInstruction(vector<string>words){
        int i = 0;
        Instruction instr;
        if(IS[words[i]]=="" && AD[words[i]]=="" && DL[words[i]]==""){
            instr.label=words[i];
            i++;
        }
        instr.opcode=words[i];
        i++;
        if(i<words.size()){
            instr.op1=words[i];
            i++;
        }
        if(i<words.size()){
            instr.op2=words[i];
            i++;
        }
        return instr;
    }

    //Generate vector of all instructions
    vector<Instruction>getInstructions(vector<vector<string>>allLines){
        vector<Instruction>allInstructions;
        for(auto i:allLines){
            Instruction instr = getInstruction(i);
            allInstructions.push_back(instr); 
        }
        return allInstructions;
    }

    //check if symbol is in symTab or not
    bool isInSymTab(string sym){
        for(auto i:symTab){
            if(i.first==sym) return true;
        }
        return false;
    }

    //Perform Pass1
    void performPass1(vector<Instruction>instr){

        for(auto i:instr){
            
            string ic = "";

            //If current instruction has a label
            if(i.label!=""){
                //if label is not present in symTab
                if(!isInSymTab(i.label)){
                    // cout<<"adding to symbol table 1"<<i.label<<"with lc"<<lc<<endl;
                    symTab.push_back({i.label,lc});
                }
                else{
                    for(int j = 0;j<symTab.size();j++){
                        if(symTab[j].first==i.label){
                            symTab[j].second=lc;
                            break;
                        }
                    }
                }
            }

            //If its an IS statement
            if(IS[i.opcode]!=""){
                
                //Add Intermediate code for Opcode
                ic+=to_string(lc)+" ";
                ic+="(IS,"+IS[i.opcode]+") ";

                //Add Intermediate code for Operand1
                if(i.op1!=""){
                    if(REG[i.op1]!=""){
                        ic+="("+REG[i.op1]+") ";
                    }
                    else if(CC[i.op1]!=""){
                        ic+="(CC,"+CC[i.op1]+") ";
                    }
                    else{                    
                        if(!isInSymTab(i.op1)){
                            symTab.push_back({i.op1,-1});
                            ic+="(S,"+to_string(symTab.size())+") ";
                        }
                        else{
                            for(int j = 0;j<symTab.size();j++){
                                if(symTab[j].first==i.op1){
                                    ic+="(S,"+to_string(j+1)+") ";
                                    break;
                                }
                            }
                        }
                    }
                }

                //Add intermediate code for Operand2
                if(i.op2!=""){
                    //  If its a Literal
                    if(i.op2[0]=='='){
                        litTab.push_back({i.op2,-1});
                        ic+="(L,"+to_string(litTab.size())+") ";
                    }
                    else{
                        if(!isInSymTab(i.op2)){
                            //  cout<<"adding to symbol table 3"<<i.op2<<endl;
                            symTab.push_back({i.op2,-1});
                            ic+="(S,"+to_string(symTab.size())+") ";
                        }
                        else{
                            for(int j = 0;j<symTab.size();j++){
                                if(symTab[j].first==i.op2){
                                    ic+="(S,"+to_string(j+1)+") ";
                                    break;
                                }
                            }
                        }
                    }
                }
                lc++;
            }
            //If opcode is an assembler directive
            else if(AD[i.opcode]!=""){
                if(i.opcode=="START"){
                    ic+="    ";
                    ic+="(AD,"+AD[i.opcode]+") ";
                    if(i.op1!=""){
                        lc=stoi(i.op1);
                        ic+="(C,"+i.op1+") ";
                    }
                    else{
                        lc=0;
                    }
                }
                else if(i.opcode=="ORIGIN"){
                    //Intermediate code for opcode
                    
                    ic+="    (AD,"+AD[i.opcode]+") ";

                    string oprnd1=i.op1;
                    vector<string>exp;
                    string wrd="";
                    string oprtr="";
                    for(auto i:oprnd1){
                        if(i!='+' && i!='-'){
                            wrd+=i;
                        }
                        else{
                            oprtr=i;
                            exp.push_back(wrd);
                            wrd="";
                        }
                    }
                    exp.push_back(wrd);
                    int newLC=0;
                    int index=-1;
                    for(int i = 0;i<symTab.size();i++){
                        if(symTab[i].first==exp[0]){
                            index=i+1;
                            newLC=symTab[i].second;
                            break;
                        }
                    }
                    //intermediate code for operand
                    ic+="(S,"+to_string(index)+")"+oprtr+exp[1];
                    if(oprtr=="+"){
                        // cout<<"added"<<stoi(exp[1])<<"to"<<newLC<<endl;
                        lc=newLC+stoi(exp[1]);
                    }
                    else{
                        lc=newLC-stoi(exp[1]);
                    }
                    
                }
                else if(i.opcode=="LTORG"){
                    ic="    (AD,05)";
                    intermediateCode.push_back(ic);
                    int getIndex = poolTab.back()-1;
                    string temp = "";
                    for(int ind = getIndex;ind<litTab.size();ind++){
                        if(litTab[ind].second==-1){
                            litTab[ind].second=lc;
                            lc++;
                            string literal = litTab[ind].first;
                            literal = literal.substr(2,literal.length()-3);
                            temp=to_string(lc)+" (DL,02) (C,"+literal+") ";
                            intermediateCode.push_back(temp);
                        }
                    }
                    poolTab.push_back(litTab.size()+1);
                }
                else if(i.opcode=="EQU"){
                    string lbl=i.label;
                    string oprnd1=i.op1;
                    
                    //intermediate code for opcode
                    ic+="    (AD,"+AD[i.opcode]+") ";
                    int addOfOp2 = -404;
                    int indexOfOp2 = -101;
                    for(int j = 0;j<symTab.size();j++){
                        if(symTab[j].first==oprnd1){
                            addOfOp2=symTab[j].second;
                            indexOfOp2=j+1;
                            break;
                        }
                    }
                    for(int j = 0;j<symTab.size();j++){
                        if(symTab[j].first==lbl){
                            symTab[j].second=addOfOp2;
                            break;
                        }
                    }
                    //intermediate code for right side operand
                    ic+="(S,"+to_string(indexOfOp2)+") ";
                }
                else{
                    ic="    (AD,02)";
                    intermediateCode.push_back(ic);
                    int getIndex = poolTab.back()-1;
                    string temp = "";
                    for(int ind = getIndex;ind<litTab.size();ind++){
                        if(litTab[ind].second==-1){
                            litTab[ind].second=lc;
                            lc++;
                            string literal = litTab[ind].first;
                            literal = literal.substr(2,literal.length()-3);
                            temp=to_string(lc)+" (DL,02) (C,"+literal+") ";
                            intermediateCode.push_back(temp);
                        }
                    }
                }
            }
            else if(DL[i.opcode]!=""){
                if(i.opcode=="DS"){
                    ic=to_string(lc)+" (DL,02) (C,"+i.op1+") ";
                    lc+=stoi(i.op1);
                }
                else if(i.opcode=="DC"){
                    string oprnd1 = i.op1.substr(1,i.op1.length()-2);
                    ic+=to_string(lc)+" (DL,01) (C,"+oprnd1+") ";
                    lc++;
                }
            }
            if(i.opcode!="LTORG" && i.opcode!="END") intermediateCode.push_back(ic);
        }


        for(auto p:intermediateCode){
            cout<<p<<endl;
        }
        cout<<endl;
        cout<<"Printing LitTab"<<endl;
        for(auto i:litTab){
            cout<<i.first<<" "<<i.second<<endl;
        }
        cout<<"Printing SymTab"<<endl;
        for(auto i:symTab){
            cout<<i.first<<" "<<i.second<<endl;
        }
        cout<<"Printing poolTable"<<endl;
        for(auto i:poolTab){
            cout<<i<<endl;
        }
    }
};


int main(){
    ICGenerator obj;

    vector<string>ln = obj.readFile("pass1test3.txt");

    vector<vector<string>>allWords = obj.getAllWords(ln);
    
    vector<Instruction>instr = obj.getInstructions(allWords);

    for(auto i:instr){
        cout<<i.label<<" "<<i.opcode<<" "<<i.op1<<" "<<i.op2<<endl;
    }
    cout<<"-------------------------------"<<endl;
    obj.performPass1(instr);
}