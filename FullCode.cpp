#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <String>
#include <fstream>
using namespace std;

class Instructions
{
public:
    map<int, string> g;
    int numIns = 0;
    void TakeInstructionsToMap()
    {
        fstream fileIns;
        fileIns.open("input.txt", ios::in);
        if (fileIns.is_open())
        { // checking whether the file is open
            string line;
            while (getline(fileIns, line))
            { // read data from file object and put it into string.
                // cout << line << "\n"; // print the data of the string
                numIns += 1;
                string temp = "";
                string pc = "pc";
                string ins = "in";
                int count = 0;
                int i = 0;
                if (line == "end")
                {
                    return;
                }
                else
                {
                    for (char c : line)
                    {
                        i++;
                        if (c == ' ')
                        {
                            if (count == 0)
                            {
                                pc = temp;
                                count++;
                                temp = "";
                            }
                            else
                            {
                                count++;
                            }
                        }
                        else if (c == '\n' || i == line.length())
                        {
                            temp = temp + c;
                            ins = temp;
                        }
                        else
                        {
                            temp = temp + c;
                        }
                    }
                }
                unsigned int intpc = std::stoul(pc, nullptr, 16);
                // cout<<intpc<<"c"<<endl;
                // cout<<ins<<"d"<<endl;
                g.insert({intpc, ins});
            }
            fileIns.close();
        }
    }
    void PrintMap()
    {
        for (auto itr = g.begin(); itr != g.end(); ++itr)
        {
            cout << itr->first << '\t' << itr->second << '\n';
        }
    }
};

class Decoder
{
public:
    int binaryToDecimal(string s)
    {
        string binString = s;
        int signedInt = 0;
        int base = 1;
        int len = binString.length();
        // cout << binString[0] << endl;
        if (binString[0] == '0')
        {
            signedInt = std::stoul(s, nullptr, 2);
        }

        else
        {
            int i = -1;
            for (i = len - 1; i >= 0; i--)
                if (binString[i] == '1')
                    break;
            if (i == -1)
                binString = '1' + binString;
            for (int j = i - 1; j >= 0; j--)
            {
                if (binString[j] == '1')
                    binString[j] = '0';
                else
                    binString[j] = '1';
            }
            signedInt = std::stoul(binString, nullptr, 2);
            signedInt = 0 - signedInt;
        }
        return signedInt;
    }

    vector<int> getParametersForInstructions(string s)
    {
        vector<int> Parameters;
        stringstream ss;
        ss << hex << s;
        int n;
        ss >> n;
        bitset<32> b(n);
        string full = b.to_string();
        // cout << full << endl;
        string opcodeString = full.substr(25, 7);
        int opcode = binaryToDecimal(opcodeString);
        // cout << opcodeString << " " << opcode << endl;

        if (opcode == 51)
        {
            string rdString = full.substr(20, 5);
            int rd = binaryToDecimal(rdString);
            string func3String = full.substr(17, 3);
            int func3 = binaryToDecimal(func3String);
            string rs1String = full.substr(12, 5);
            int rs1 = binaryToDecimal(rs1String);
            string rs2String = full.substr(7, 5);
            int rs2 = binaryToDecimal(rs2String);
            string func7String = full.substr(0, 7);
            int func7 = binaryToDecimal(func7String);
            Parameters.push_back(opcode);
            Parameters.push_back(rd);
            Parameters.push_back(func3);
            Parameters.push_back(rs1);
            Parameters.push_back(rs2);
            Parameters.push_back(func7);
        }

        if (opcode == 19)
        {
            string rdString = full.substr(20, 5);
            int rd = binaryToDecimal(rdString);
            string func3String = full.substr(17, 3);
            int func3 = binaryToDecimal(func3String);
            string rs1String = full.substr(12, 5);
            int rs1 = binaryToDecimal(rs1String);
            string immString = full.substr(0, 12);
            int imm = binaryToDecimal(immString);
            Parameters.push_back(opcode);
            Parameters.push_back(rd);
            Parameters.push_back(func3);
            Parameters.push_back(rs1);
            Parameters.push_back(imm);
        }

        if (opcode == 3)
        {
            string imm1String = full.substr(20, 5);
            // unsigned int imm1 = std::stoul(imm1String, nullptr, 2);
            string func3String = full.substr(17, 3);
            int func3 = binaryToDecimal(func3String);
            string rs1String = full.substr(12, 5);
            int rs1 = binaryToDecimal(rs1String);
            string rs2String = full.substr(7, 5);
            int rs2 = binaryToDecimal(rs2String);
            string imm2String = full.substr(0, 7);
            string immString = imm2String + imm1String;
            int imm = binaryToDecimal(immString);
            Parameters.push_back(opcode);
            Parameters.push_back(imm);
            Parameters.push_back(func3);
            Parameters.push_back(rs1);
            Parameters.push_back(rs2);
        }

        if (opcode == -29)
        {
            string imm1String = full.substr(20, 4);
            // unsigned int imm1 = std::stoul(imm1String, nullptr, 2);
            string func3String = full.substr(17, 3);
            int func3 = binaryToDecimal(func3String);
            string rs1String = full.substr(12, 5);
            int rs1 = binaryToDecimal(rs1String);
            string rs2String = full.substr(7, 5);
            int rs2 = binaryToDecimal(rs2String);
            string imm2String = full.substr(1, 7);
            string immString = full.substr(0, 1) + full[24] + imm2String + imm1String;
            int imm = binaryToDecimal(immString);
            Parameters.push_back(opcode);
            Parameters.push_back(imm);
            Parameters.push_back(func3);
            Parameters.push_back(rs1);
            Parameters.push_back(rs2);
        }

        if (opcode == 55)
        {
            string rdString = full.substr(20, 5);
            int rd = binaryToDecimal(rdString);
            string immString = full.substr(0, 20);
            int imm = binaryToDecimal(immString);
            Parameters.push_back(opcode);
            Parameters.push_back(rd);
            Parameters.push_back(imm);
        }

        if (opcode == -17)
        {
            string rdString = full.substr(20, 5);
            int rd = binaryToDecimal(rdString);
            string immString = full.substr(0, 1) + full.substr(12, 8) + full.substr(11, 1) + full.substr(1, 10);
            int imm = binaryToDecimal(immString);
            Parameters.push_back(opcode);
            Parameters.push_back(rd);
            Parameters.push_back(imm);
        }

        return Parameters;
    }
};

class Executer
{
public:
    int aout, rs1, rs2, rd, immediate, numBytes, RA, PC, RB;
    bool RF_Write = false, MuxB_select = false, MuxY_select = false, MuxMA_select = false, MuxINC_select = false, MuxPC_select = false, Mem_Read = false, Mem_Write = false;
    int func3, func7, opcode, ALU_Operation;

    void identifyParameters(vector<int> Parameters)
    {
        if (Parameters.front() == 51)
        {
            func7 = Parameters.back();
            Parameters.pop_back();
            rs2 = Parameters.back();
            Parameters.pop_back();
            rs1 = Parameters.back();
            Parameters.pop_back();
            func3 = Parameters.back();
            Parameters.pop_back();
            rd = Parameters.back();
            Parameters.pop_back();
            opcode = Parameters.back();
            Parameters.pop_back();
        }

        if (Parameters.front() == 19)
        {
            immediate = Parameters.back();
            Parameters.pop_back();
            rs1 = Parameters.back();
            Parameters.pop_back();
            func3 = Parameters.back();
            Parameters.pop_back();
            rd = Parameters.back();
            Parameters.pop_back();
            opcode = Parameters.back();
            Parameters.pop_back();
        }

        if (Parameters.front() == 3)
        {
            rs2 = Parameters.back();
            Parameters.pop_back();
            rs1 = Parameters.back();
            Parameters.pop_back();
            func3 = Parameters.back();
            Parameters.pop_back();
            immediate = Parameters.back();
            Parameters.pop_back();
            opcode = Parameters.back();
            Parameters.pop_back();
        }

        if (Parameters.front() == -29)
        {
            rs2 = Parameters.back();
            Parameters.pop_back();
            rs1 = Parameters.back();
            Parameters.pop_back();
            func3 = Parameters.back();
            Parameters.pop_back();
            immediate = Parameters.back();
            Parameters.pop_back();
            opcode = Parameters.back();
            Parameters.pop_back();
            // cout << func3 << endl;
        }

        if (Parameters.front() == 55)
        {
            immediate = Parameters.back();
            Parameters.pop_back();
            rd = Parameters.back();
            Parameters.pop_back();
            opcode = Parameters.back();
            Parameters.pop_back();
        }

        if (Parameters.front() == -17)
        {
            immediate = Parameters.back();
            Parameters.pop_back();
            rd = Parameters.back();
            Parameters.pop_back();
            opcode = Parameters.back();
            Parameters.pop_back();
        }
    }

    void Control_Signals(bool write_in_reg, bool MuxB, bool MuxY, bool Memory_Read, bool Memory_Write, bool MuxMA, bool MuxPC, bool Mux_INC, int NUM_B)
    {
        RF_Write = write_in_reg;
        MuxB_select = MuxB;
        MuxY_select = MuxY;
        Mem_Read = Memory_Read;
        MuxMA_select = MuxMA;
        MuxPC_select = MuxPC;
        MuxINC_select = Mux_INC;
        numBytes = NUM_B;
        Mem_Write = Memory_Write;
    };

    void ALU_COntrol_Generator()
    {
        // cout << opcode << " " << func3 << endl;
        if (opcode == 51)
        {
            if (func3 == 0)
            {
                if (func7 == 0)
                {
                    ALU_Operation = 10;
                    printf("This is ADD operation\n");
                }
                else if (func7 == 32)
                {
                    ALU_Operation = 20;
                    printf("This is SUB instruction.\n");
                }
                else if (func7 == 1)
                {
                    ALU_Operation = 30;
                    printf("This is MUL instruction.\n");
                }
                else
                {
                    printf("Invalid Func7 for Add/Sub\n");
                    exit(1);
                }
            }
            else if (func3 == 7)
            {
                printf("This is AND instruction.\n");
                if (func7 == 0)
                    ALU_Operation = 110;
                else
                {
                    printf("Invalid func7 for AND\n");
                    exit(1);
                }
            }
            else if (func3 == 6)
            {
                if (func7 == 0)
                {
                    printf("This is OR instruction\n");
                    ALU_Operation = 100;
                }
                else if (func7 == 1)
                {
                    ALU_Operation = 50;
                    printf("This is REMAINDER instruction.\n");
                }
                else
                {
                    printf("Invalid Func7 for OR/REM\n");

                    exit(1);
                }
            }
            else if (func3 == 1)
                if (func7 == 0)
                {
                    ALU_Operation = 70;
                    printf("This is SLL instruction.\n");
                }

                else
                {
                    printf("Invalid Func7 for SLL\n");

                    exit(1);
                }
            else if (func3 == 2)
            {
                printf("This is SLT instruction.\n");
                if (func7 == 0)
                    ALU_Operation = 120;
                else
                {
                    printf("Invalid Func7 for SLT");
                    exit(1);
                }
            }
            else if (func3 == 5)
            {
                if (func7 == 32)
                {
                    printf("This is SRA instruction.\n");
                    ALU_Operation = 90;
                }
                else if (func7 == 0)
                {
                    printf("This is SRL instruction.\n");
                    ALU_Operation = 80;
                }
                else
                {
                    printf("Invalid Func7 for SRA/SRL");

                    exit(1);
                }
            }
            else if (func3 == 4)
                if (func7 == 0)
                {
                    printf("This is XOR instruction.\n");
                    ALU_Operation = 60;
                }

                else if (func7 == 1)
                {
                    printf("This is DIV instruction.\n");
                    ALU_Operation = 40;
                }
                else
                {
                    printf("Invalid Func7 for XOR/div");
                    exit(1);
                }
            else
            {
                printf("(func3) not matching in R format");
                exit(1);
            }
        }

        else if (opcode == 3 || opcode == 19 || opcode == 103)
        {
            if (immediate > 2047)
            {
                immediate -= 4096;
            }

            if (opcode == 3)
            {
                ALU_Operation == 10;
                if (func3 == 0)
                {
                    printf("This is LB instruction.\n");
                    Control_Signals(1, 1, 1, 1, 0, 0, 1, 0, 1);
                }
                else if (func3 == 1)
                {
                    printf("This is LH instruction.");
                    Control_Signals(1, 1, 1, 1, 0, 0, 1, 0, 2);
                }
                else if (func3 == 2)
                {
                    printf("This is LW instruction.\n");
                    Control_Signals(1, 1, 1, 1, 0, 0, 1, 0, 4);
                }
                else
                {
                    printf("Wrong func3) for lb/lh/lw\n");
                    exit(1);
                }
            }
        }
        else if (opcode == 19)
        {
            Control_Signals(1, 1, 0, 0, 0, 0, 1, 0, 4);
            if (func3 == 0)
            {
                printf("This is ADDI instruction.\n");
                ALU_Operation = 10;
            }
            else if (func3 == 7)
            {
                printf("This is ANDI instruction.\n");
                ALU_Operation = 110;
            }
            else if (func3 == 6)
            {
                printf("This is ORI instruction.\n");
                ALU_Operation = 100;
            }
            else
            {
                printf("Error func3 not matching for addi/andi/ori\n");
                exit(1);
            }
        }
        else if (opcode == 103)
        {
            printf("This is JALR instruction.\n");
            Control_Signals(1, 0, 2, 0, 0, 0, 0, 1, 4);
            if (func3 == 0)
            {
                ALU_Operation == 10;
            }
            else
            {
                printf("Error wrong func3) for jalr\n");
                exit(1);
            }
        }

        else if (opcode == 35)
        {
            ALU_Operation = 10;

            if (func3 == 0)
            {
                printf("This is SB instruction.\n");
                Control_Signals(0, 1, 1, 0, 1, 0, 1, 0, 1);
            }
            else if (func3 == 1)
            {
                printf("This is SH instruction.\n");
                Control_Signals(0, 1, 1, 0, 1, 0, 1, 0, 2);
            }
            else if (func3 == 2)
            {
                printf("This is SW instruction.\n");
                Control_Signals(0, 1, 1, 0, 1, 0, 1, 0, 4);
            }
            else
            {
                printf("invalid func3) => S format\n");
                exit(1);
                return;
            }
        }
        else if (opcode == -29)
        {
            if (func3 == 0)
            {
                printf("This is BEQ instruction.\n");
                ALU_Operation = 140;
            }
            else if (func3 == 1)
            {
                printf("This is BNE instruction.\n");
                ALU_Operation == 150;
            }
            else if (func3 == 4)
            {
                printf("This is BLT instruction.\n");
                ALU_Operation == 120;
            }
            else if ((func3) == 5)
            {
                printf("This is BGE instruction.\n");
                ALU_Operation = 130;
            }
            else
            {
                printf("Invalid func3) for SB Format instruction. Terminating the program.\n");
                exit(1);
                Control_Signals(0, 0, 0, 0, 0, 0, 1, 1, 0);
            }
        }

        else if (opcode == 23 || opcode == 55)
        {
            if (opcode == 23)
            {
                printf("This is AUIPC instruction.\n");
                ALU_Operation = 10;
                RA = PC;
                (immediate) = (immediate) << 12;
            }
            else
            {
                printf("This is LUI instruction.\n");
                ALU_Operation = 70;
                RA = immediate;
                immediate = 12;
            }
            Control_Signals(1, 1, 0, 0, 0, 0, 1, 0, 0);
        }
        else if (opcode == -17)
        {
            printf("This is JALR instruction.\n");
            ALU_Operation = 130;
            RA = 0;
            RB = 0;

            Control_Signals(1, 0, 2, 0, 0, 0, 1, 1, 0);
        }
        else
        {
            printf("invalid opcode\n");
        }

        Execute_instructions(ALU_Operation, RA, RB);
    }

    void Execute_instructions(int Operation, int a1, int a2)
    {

        if (Operation == 10)
        {
            aout = a1 + a2;
        }

        else if (Operation == 20)
        {
            aout = a1 - a2;
        }

        else if (Operation == 30)
        {
            aout = a1 * a2;
        }

        else if (Operation == 40)
        {
            if (a2 != 0)
            {
                aout = a1 / a2;
            }
            else
            {
                printf("Error Division by 0");
                exit(1);
            }
        }

        else if (Operation == 50)
        {
            if (a2 != 0)
            {
                aout = a1 % a2;
            }
            else
            {
                printf("Error Division by 0");
                exit(1);
            }
        }

        else if (Operation == 60)
        {
            aout = a1 ^ a2;
        }
        else if (Operation == 70)
        {
            if (a2 < 0)
            {
                printf("Error can't shift negative times");
            }
            else
            {
                aout = a1 << a2;
            }
        }

        else if (Operation == 80)
        {
            if (a2 < 0)
            {
                printf("Error can't shift negative times");
            }
            else
                aout = a1 >> a2;
        }

        else if (Operation == 90)
        {
            printf("Skipping");
        }

        else if (Operation == 100)
        {
            aout = a1 | a2;
        }

        else if (Operation == 110)
        {
            aout = a1 & a2;
        }

        else if (Operation == 120)
        {
            aout = int(a1 < a2);
        }
        else if (Operation == 130)
        {
            aout = int(a1 >= a2);
        }
        else if (Operation == 140)
        {
            aout = int(a1 == a2);
        }
        else if (Operation == 150)
        {
            aout = int(a1 != a2);
        }
    }
};

Instructions i1;
class Simulator
{
public:
    int insNum = 0;
    string currIns = "-1";
    vector<int> Parameters;
    void Fetch()
    {
        // i1.PrintMap();
        currIns = i1.g[insNum];
        // cout << currIns << endl;
        insNum += 4;
    }
    void Decode()
    {
        Decoder d;
        if (currIns != "-1")
        {
            Parameters = d.getParametersForInstructions(currIns);
            for (auto elem : Parameters)
            {
                cout << elem << " ";
            }
            cout << endl;
        }
    }
    void Execute()
    {
        Executer e;
        if (Parameters.size() != 0)
        {
            e.identifyParameters(Parameters);
            e.ALU_COntrol_Generator();
            cout<<e.aout<<endl;
        }
    }
};

int main()
{
    i1.TakeInstructionsToMap();
    // i1.PrintMap();
    Simulator s;
    for (int i = 0; i < i1.numIns; i++)
    {
        s.Fetch();
        s.Decode();
        s.Execute();
    }
}