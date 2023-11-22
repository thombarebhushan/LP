#include <bits/stdc++.h>
using namespace std;

void processMacroPass1(const string &inputFile)
{
    ifstream infile(inputFile);
    if (!infile)
    {
        cerr << "Failed to open input file: " << inputFile << endl;
        return;
    }

    ofstream mnt("mnt.txt");
    ofstream mdt("mdt.txt");
    ofstream kpdt("kpdt.txt");
    ofstream pnt("pntab.txt");

    string line;
    bool isMacro = false, isBody = false;
    int mdtPtr = 1, kpdPtr = 101, itr = kpdPtr;
    vector<unordered_map<string, int>> pntab;
    vector<pair<string, string>> kpdtab;
    unordered_map<string, int> tempPntab;

    while (getline(infile, line))
    {
        istringstream iss(line);
        vector<string> allWords;


        // Loop through all words in the line
        string word;
        while (iss >> word)
        {
            // Output each word
            allWords.push_back(word);
        }

        if (allWords[0] == "MACRO" and isMacro == false)
        {
            isMacro = true;
            continue;
        }

        if (isMacro == true)
        {
            int tot_kp = 0;
            int tot_para = allWords.size() - 1;
            tempPntab.clear();
            for (int i = 1; i < allWords.size(); i++)
            {
                string param = allWords[i];
                string temp = "";
                for (int j = 1; j < param.length(); j++)
                {
                    if (param[j] == '=')
                    {
                        string value = "";
                        for (int k = j + 1; k < param.length(); k++)
                        {
                            value += param[k];
                        }
                        kpdtab.push_back({temp, value});
                        tot_kp++;
                        break;
                    }
                    temp += param[j];
                }
                if (temp[temp.size() - 1] == ',')
                    temp.pop_back();
                tempPntab[temp] = i;
            }

            int tot_pp = tot_para - tot_kp;
            mnt << allWords[0] << "\t" << tot_pp << "\t" << tot_kp << "\t" << mdtPtr << "\t" << kpdPtr << endl;
            kpdPtr += tot_kp;
            isMacro = false;
            isBody = true;
            pntab.push_back(tempPntab);
            continue;
        }

        if (isBody == true)
        {
            if (allWords[0] == "MEND")
            {
                mdt << mdtPtr << "\t" << allWords[0] << endl;
                mdtPtr++;
                isBody = false;
                continue;
            }
            mdt << mdtPtr << "\t" << allWords[0] << "\t";
            for (int i = 1; i < allWords.size(); i++)
            {
                string param = allWords[i];
                string temp = "";
                for (int j = 1; j < param.length(); j++)
                {
                    temp += param[j];
                }
                if (temp[temp.size() - 1] == ',')
                    temp.pop_back();
                mdt << "(P, " << tempPntab[temp] << ")\t";
            }
            mdt << endl;
            mdtPtr++;
        }
    }



    for (auto i : pntab)
    {
        for (auto j : i)
        {
            pnt << j.first << "\t" << j.second << endl;
        }
        cout << endl;
    }

    for (auto i : kpdtab)
    {
        kpdt << itr << "\t" << i.first << "\t" << i.second << endl;
        itr++;
    }
}

int main()
{
    processMacroPass1("macro_input.txt");
    return 0;
}



/*

MACRO
ONE &O, &N, &E=AREG
MOVER &E, &O
ADD &E, &N
MOVEM &E, &O
MEND
MACRO
TWO &T, &W, &O=DREG
MOVER &O, &T
ADD &O, &W
MOVEM &O, &T
MEND
START
READ O
READ T
ONE O, 9
TWO T, 7
STOP
O DS 1
T DS 1
END

*/