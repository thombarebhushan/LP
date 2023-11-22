#include <bits/stdc++.h>
using namespace std;

class Entry
{
public:
    string symbol;
    int address, index;
    Entry()
    {
        symbol = " ";

        address = index = 0;
    }
    Entry(string s, int add, int idx = 0)
    {
        symbol = s;
        address = add;
        index = idx;
    }

    void setSymbol(string sym)
    {
        symbol = sym;
    }
    void setAddress(int add)
    {
        address = add;
    }
    void setIndex(int idx)
    {
        index = idx;
    }

    string getSymbol()
    {
        return symbol;
    }
    int getAddress()
    {
        return address;
    }
    int getIndex()
    {
        return index;
    }
};

void tokenize(string s, vector<string> &res, string del = "\t")

{
    int start = 0;
    int end = s.find(del);
    if (end == 0)
        res.push_back("EMPTY");
    while (end != -1)
    {
        if (end - start > 0)
            res.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    if (s.substr(start, end - start) != "")
        res.push_back(s.substr(start, end - start));
}

class Pass2
{
private:
    vector<Entry> SYMTAB, LITTAB;

public:
    void readTables();
    void generateCode(string filename);
};

void Pass2::readTables()
{
    string line;
    ifstream fin1("SYMTAB.txt");
    while (getline(fin1, line))
    {
        vector<string> parts;
        tokenize(line, parts);
        Entry e(parts[1], stoi(parts[2]), stoi(parts[0]));
        SYMTAB.push_back(e);
    }
    ifstream fin2("LITTAB.txt");
    while (getline(fin2, line))
    {
        vector<string> parts;
        tokenize(line, parts);
        string temp = "";

        for (unsigned int i = 0; i < parts[1].size(); i++)
        {
            if (parts[1][i] != '\'' && parts[1][i] != '=')
            {
                temp += parts[1][i];
            }
        }
        parts[1] = temp;
        Entry e(parts[1], stoi(parts[2]), stoi(parts[0]));
        LITTAB.push_back(e);
    }
}

void Pass2::generateCode(string filename)

{
    readTables();
    ifstream fin(filename);
    ofstream fout("MachineCode.txt");
    string line, code;

    while (getline(fin, line))
    {
        vector<string> parts;
        tokenize(line, parts);

        if ((parts[0].find("AD") != string::npos) || (parts[0].find("DL,02") != string ::npos))
        {
            fout << "\n";
        }
        else if (parts.size() == 2)
        {
            if (parts[0].find("DL") != string::npos)
            {
                string temp = "";

                for (unsigned int i = 0; i < parts[0].length(); i++)
                {
                    if (isdigit(parts[0][i]))
                    {
                        temp += parts[0][i];
                    }
                }
                parts[0] = temp;

                if (stoi(parts[0]) == 1)
                {
                    temp = "";

                    for (unsigned int i = 0; i < parts[1].length(); i++)
                    {
                        if (isdigit(parts[1][i]))
                        {
                            temp += parts[1][i];
                        }
                    }
                    parts[1] = temp;

                    int cons = stoi(parts[1]);
                    fout.fill('0');
                    fout << "00\t0\t" << setw(3) << cons << "\n";
                }
            }

            else if (parts[0].find("IS") != string::npos)
            {
                string temp = "";

                for (unsigned int i = 0; i < parts[0].length(); i++)
                {
                    if (isdigit(parts[0][i]))
                    {
                        temp += parts[0][i];
                    }
                }

                    parts[0] = temp;
                int opcode = stoi(parts[0]);

                if (opcode == 10)
                {
                    if (parts[1].find("S") != string::npos)
                    {
                        temp =
                            "";

                        for (unsigned int i = 0; i < parts[1].length(); i++)
                        {
                            if (isdigit(parts[1][i]))
                            {
                                temp += parts[1][i];
                            }
                        }
                        parts[1] = temp;

                        int symIndex = stoi(parts[1]);
                        fout.fill('0');

                        fout << setw(2) << opcode << "\t0\t" << setw(3) << SYMTAB[symIndex - 1].getAddress() << "\n";
                    }
                    else if (parts[1].find("L") != string::npos)
                    {
                        temp =
                            "";

                        for (unsigned int i = 0; i < parts[1].length(); i++)
                        {
                            if (isdigit(parts[1][i]))
                            {
                                temp += parts[1][i];
                            }
                        }
                        parts[1] = temp;

                        int litIndex = stoi(parts[1]);
                        fout.fill('0');

                        fout << setw(2) << opcode << "\t0\t" << setw(3) << LITTAB[litIndex - 1].getAddress() << "\n";
                    }
                }
            }
        }

        else if (parts.size() == 1 && parts[0].find("IS") != string::npos)
        {
            string temp =
                "";

            for (unsigned int i = 0; i < parts[0].length(); i++)
            {
                if (isdigit(parts[0][i]))
                {
                    temp += parts[0][i];
                }
            }
            parts[0] = temp;

            int opcode = stoi(parts[0]);
            fout.fill('0');
            fout << setw(2) << opcode << "\t0\t000\n";
        }

        else if (parts[0].find("IS") != string::npos && parts.size() == 3)
        {
            string temp =
                "";

            for (unsigned int i = 0; i < parts[0].length(); i++)
            {
                if (isdigit(parts[0][i]))
                {
                    temp += parts[0][i];
                }
            }
            parts[0] = temp;
            temp =
                "";

            for (unsigned int i = 0; i < parts[1].size(); i++)
            {
                if (parts[1][i] != '(' && parts[1][i] != ')')
                {
                    temp += parts[1][i];
                }
            }
            parts[1] = temp;
            int opcode = stoi(parts[0]);
            int regcode = stoi(parts[1]);

            if (parts[2].find("S") != string::npos)
            {
                temp =
                    "";

                for (unsigned int i = 0; i < parts[2].length(); i++)
                {
                    if (isdigit(parts[2][i]))
                    {
                        temp += parts[2][i];
                    }
                }
                parts[2] = temp;

                int symIndex = stoi(parts[2]);
                fout.fill('0');

                fout << setw(2) << opcode << "\t" << regcode << "\t" << setw(3) << SYMTAB[symIndex - 1].getAddress() << "\n";
            }
            else if (parts[2].find("L") != string::npos)
            {
                temp =
                    "";

                for (unsigned int i = 0; i < parts[2].length(); i++)
                {
                    if (isdigit(parts[2][i]))
                    {
                        temp += parts[2][i];
                    }
                }
                parts[2] = temp;

                int litIndex = stoi(parts[2]);
                fout.fill('0');

                fout << setw(2) << opcode << "\t" << regcode << "\t" << setw(3) << LITTAB[litIndex - 1].getAddress() << "\n";
            }
        }
    }
}

int main()
{
    Pass2 p1;
    p1.generateCode("Intermediate_Code.txt");
}