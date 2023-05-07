#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <String>
#include <fstream>
using namespace std;
int insNum = 0;

int UnsignedBinaryToDecimal(string s){
    int n=0;
    for(int i=0; i<s.length(); i++){
        if(s[i]=='0'){
            n=n*2;
        }
        else if(s[i]=1){
            n= n*2 + 1;
        }
    }
    return n;
}
 

int binaryToDecimal(string s)
    {
        string binString = s;
        int signedInt = 0;
        int base = 1;
        // cout<<
        int len = binString.length();
        // cout << binString[0] << " lllll " << endl;
        if (binString[0] == '0')
        {
            signedInt = UnsignedBinaryToDecimal(s);
        }

        else
        {
            // cout << "IMM CH" << endl;
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
            signedInt = UnsignedBinaryToDecimal(binString);
            signedInt = 0 - signedInt;
        }
        // cout << signedInt << endl;
        return signedInt;
    }

    string HexToBin(string s)
    {
        // cout<<s<<endl;
        string bin = "";
        for (char c : s)

        {
            // cout<<c<<endl;
            // TODO handle default / error
            switch (toupper(c))
            {
            case '0':
                bin += "0000";break;
            case '1':
                bin += "0001";break;
            case '2':
                bin += "0010";break;
            case '3':
                bin += "0011";break;
            case '4':
                bin += "0100";break;
            case '5':
                bin += "0101";break;
            case '6':
                bin += "0110";break;
            case '7':
                bin += "0111";break;
            case '8':
                bin += "1000";break;
            case '9':
                bin += "1001";break;
            case 'A':
                bin += "1010";break;
            case 'B':
                bin += "1011";break;
            case 'C':
                bin += "1100";break;
            case 'D':
                bin += "1101";break;
            case 'E':
                bin += "1110";break;
            case 'F':
                bin += "1111";break;
            }            
        }
        return bin;
    }
class Registers
{
public:
    int R[32]{0};

    void WriteToRegister(int num, int data)
    {
        R[num] = data;
    }
    int ReadFromRegister(int num)
    {
        return R[num];
    }
    void PrintAllRegisters()
    {
        for (int i = 0; i < 31; i++)
        {
            cout << "x" << i << " = " << ReadFromRegister(i) << " ; ";
        }
        cout << endl;
    }
};

class Instructions
{
public:
    map<int, string> g;
    vector<string> d;
    map<int, int> dataMem;
    int numIns = 0;
    int numData = 0;

    void TakeDataToMap()
    {
        fstream fileIns;
        fileIns.open("sample.txt", ios::in);
        if (fileIns.is_open())
        { // checking whether the file is open
            string line;
            while (getline(fileIns, line))
            { // read data from file object and put it into string.
                // cout << line << "\n"; // print the data of the string

                if (line == "end")
                {
                    while (getline(fileIns, line))
                    {
                        // cout << line << endl;
                        d.push_back(line);
                    }
                }
            }
        }

        // cout<<d.size()<<endl;
        d.pop_back();
        for (string line : d)
        {
            // cout<<line<<endl;
            numData += 1;
            string temp = "";
            string pc = "pc";
            string ins = "in";
            int count = 0;
            int i = 0;
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
            string s1= HexToBin(pc);
            int intpc= binaryToDecimal(s1);
            string s2= HexToBin(ins);
            int intdata= binaryToDecimal(s2);
            // cout<<intpc<<"c"<<endl;
            // cout<<ins<<"d"<<endl;
            dataMem.insert({intpc, intdata});
        }
    }

    void TakeInstructionsToMap()
    {
        fstream fileIns;
        fileIns.open("sample.txt", ios::in);
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
                    // cout<<"Program Terminated";
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
                string s1= HexToBin(pc);
                int intpc= binaryToDecimal(s1);
                // cout<<intpc<<"c"<<endl;
                // cout<<ins<<"d"<<endl;
                g.insert({intpc, ins});
            }
            fileIns.close();
        }
    }
    void PrintMap()
    {
        cout << "INSTRUCTIONS HERE" << endl;
        for (auto itr = g.begin(); itr != g.end(); ++itr)
        {
            cout << itr->first << '\t' << itr->second << '\n';
        }
        cout << "DATA HERE" << endl;
        for (auto itr = dataMem.begin(); itr != dataMem.end(); ++itr)
        {
            cout << itr->first << '\t' << itr->second << '\n';
        }
    }
    void PrintData()
    {
        for (auto itr = dataMem.begin(); itr != dataMem.end(); ++itr)
        {
            cout << itr->first << '\t' << itr->second << '\n';
        }
    }
};

Instructions i1;
map<int, string> dataMemory;
class Memorys : Registers
{
public:
    int aout, rs1, rs2, rd, immediate, numBytes = 4, RA, PC, RB;
    bool RF_Write = false, MuxB_select = false, MuxY_select = false, MuxMA_select = false, MuxINC_select = false, MuxPC_select = false, Mem_Read = false, Mem_Write = false;

    void GetControls(vector<int> ControlSig)
    {
        Mem_Write = ControlSig.back();
        ControlSig.pop_back();
        numBytes = ControlSig.back();
        ControlSig.pop_back();
        MuxINC_select = ControlSig.back();
        ControlSig.pop_back();
        MuxPC_select = ControlSig.back();
        ControlSig.pop_back();
        MuxMA_select = ControlSig.back();
        ControlSig.pop_back();
        Mem_Read = ControlSig.back();
        ControlSig.pop_back();
        MuxY_select = ControlSig.back();
        ControlSig.pop_back();
        MuxB_select = ControlSig.back();
        ControlSig.pop_back();
        RF_Write = ControlSig.back();
        ControlSig.pop_back();
        // cout<<MuxB_select<<endl;
    }

    int AccessMemory(int address, int value = 0)
    {
        if (Mem_Read)
        {
            return ReadFromMemory(address);
        }
        else if (Mem_Read)
        {
            return WriteToMemory(address, value);
        }
    }
    int ReadFromMemory(int address)
    {
        return i1.dataMem[address];
    }

    int WriteToMemory(int address, int value)
    {
        i1.dataMem[address] = value;
    }

    int IAG(int numIns, int immediate)
    {
        // cout<<"INIT "<<numIns<<endl;
        // cout<<" MUXINC "<<MuxINC_select<<" MuxPC "<<MuxPC_select<<endl;
        if (MuxPC_select == 1)
        {
            numIns = (immediate);
            // cout<<"1 "<<endl;
        }
        else
        {
            if (MuxINC_select == 0)
            {
                numIns = numIns + 4;
                // cout << "2 " << endl;
            }
            else
            {
                numIns = numIns + (immediate);
                // cout << "immediate" << endl;
            }
        }
        // cout<<"Final "<<numIns<<endl;
        return numIns;
    }
};

Memorys m;
class Decoder
{
public:
    

    vector<int> getParametersForInstructions(string s)
    {
        vector<int> Parameters;
        // stringstream ss;
        // ss << hex << s;
        // int n;
        // ss >> n;
        // bitset<32> b(n);
        // cout<<s<<"gg"<<endl;
        string hexs=s;
        string full = HexToBin(hexs);
        // cout << full << endl;
        string opcodeString = full.substr(25, 7);
        int opcode = binaryToDecimal(opcodeString);
        // cout << opcodeString << " " << opcode << endl;

        if (opcode == 51)
        {
            string rdString = full.substr(20, 5);
            int rd = binaryToDecimal(rdString);
            string func3String = full.substr(17, 3);
            int func3 = UnsignedBinaryToDecimal(func3String);
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
            int func3 = UnsignedBinaryToDecimal(func3String);
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
            string rdString = full.substr(20, 5);
            int rd = binaryToDecimal(rdString);
            string func3String = full.substr(17, 3);
            int func3 = UnsignedBinaryToDecimal(func3String);
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

        if (opcode == 35)
        {
            string imm1String = full.substr(20, 5);
            // unsigned int imm1 = std::stoul(imm1String, nullptr, 2);
            string func3String = full.substr(17, 3);
            int func3 = UnsignedBinaryToDecimal(func3String);
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
            int func3 = UnsignedBinaryToDecimal(func3String);
            string rs1String = full.substr(12, 5);
            int rs1 = binaryToDecimal(rs1String);
            string rs2String = full.substr(7, 5);
            int rs2 = binaryToDecimal(rs2String);
            string imm2String = full.substr(1, 6);
            // cout<<imm2String<<" "<<imm1String<<endl;
            string immString = full[0] + imm2String + imm1String+"0";
            int imm = binaryToDecimal(immString);
            // cout << immString << " ff f " << imm << endl;
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
Registers r;
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

        if (Parameters.front() == 35)
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
            // cout << Parameters[0] << endl;
            // cout << Parameters[1] << endl;
            // cout << Parameters[2] << endl;
            // cout << Parameters[3] << endl;
            // cout << Parameters[4] << endl;
            rs2 = Parameters.back();
            Parameters.pop_back();
            rs1 = Parameters.back();
            Parameters.pop_back();
            func3 = Parameters.back();
            Parameters.pop_back();
            immediate = Parameters.back();
            // cout << immediate << "   lkjj" << endl;
            Parameters.pop_back();
            opcode = Parameters.back();
            Parameters.pop_back();
            // cout << opcode << endl;
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

    vector<int> ControlSig;

    void Control_Signals(bool write_in_reg, bool MuxB, bool MuxY, bool Memory_Read, bool MuxMA, bool MuxPC, bool Mux_INC, int NUM_B, bool Memory_Write)
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

    vector<int> ALU_COntrol_Generator()
    {

        // cout << opcode << " " << func3 << endl;
        ControlSig = {1, 0, 0, 0, 0, 0, 0, 0, 0};
        Control_Signals(1, 0, 0, 0, 0, 0, 0, 0, 0);
        // cout<<opcode<<endl;
        if (opcode == 51)
        {
            RA = r.ReadFromRegister(rs1);
            RB = r.ReadFromRegister(rs2);
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
                RA = r.ReadFromRegister(rs1);
                RB = immediate;
                ALU_Operation = 10;
                if (func3 == 0)
                {
                    printf("This is LB instruction.\n");
                    ControlSig = {1, 1, 0, 1, 0, 0, 0, 1, 0};
                    Control_Signals(1, 1, 0, 1, 0, 0, 0, 1, 0);
                }
                else if (func3 == 1)
                {
                    printf("This is LH instruction.");
                    ControlSig = {1, 1, 0, 1, 0, 0, 0, 2, 0};
                    Control_Signals(1, 1, 0, 1, 0, 0, 0, 2, 0);
                }
                else if (func3 == 2)
                {
                    printf("This is LW instruction.\n");
                    ControlSig = {1, 1, 0, 1, 0, 0, 0, 4, 0};
                    Control_Signals(1, 1, 0, 1, 0, 0, 0, 4, 0);
                }
                else
                {
                    printf("Wrong func3) for lb/lh/lw\n");
                    exit(1);
                }
            }

            else if (opcode == 19)
            {
                RA = r.ReadFromRegister(rs1);
                RB = immediate;
                ControlSig = {1, 1, 0, 0, 0, 0, 0, 4, 0};
                Control_Signals(1, 1, 0, 0, 0, 0, 0, 4, 0);
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
                ControlSig = {1, 0, 2, 0, 0, 0, 0, 1, 4};
                Control_Signals(1, 0, 2, 0, 0, 0, 0, 1, 4);
                if (func3 == 0)
                {
                    ALU_Operation = 130;
                }
                else
                {
                    printf("Error wrong func3) for jalr\n");
                    exit(1);
                }
            }
        }

        else if (opcode == 35)
        {
            ALU_Operation = 10;
            RA = r.ReadFromRegister(rs1);
            RB = immediate;

            if (func3 == 0)
            {
                printf("This is SB instruction.\n");
                ControlSig = {1, 1, 0, 0, 0, 0, 0, 1, 1};
                Control_Signals(1, 1, 0, 0, 0, 0, 0, 1, 1);
            }
            else if (func3 == 1)
            {
                printf("This is SH instruction.\n");
                ControlSig = {1, 1, 0, 0, 0, 0, 0, 2, 1};
                Control_Signals(1, 1, 0, 0, 0, 0, 0, 2, 1);
            }
            else if (func3 == 2)
            {
                printf("This is SW instruction.\n");
                ControlSig = {1, 1, 0, 0, 0, 0, 0, 4, 1};
                Control_Signals(1, 1, 0, 0, 0, 0, 0, 4, 1);
            }
            else
            {
                printf("invalid func3) => S format\n");
                exit(1);
            }
        }
        else if (opcode == -29)
        {
            RA = r.ReadFromRegister(rs1);
            RB = r.ReadFromRegister(rs2);
            // cout<<immediate<<"fff"<<endl;
            ControlSig = {0, 0, 0, 0, 0, 0, 0, 4, 0};
            Control_Signals(0, 0, 0, 0, 0, 0, 0, 4, 0);
            if (func3 == 0)
            {
                printf("This is BEQ instruction.\n");
                ALU_Operation = 140;
            }
            else if (func3 == 1)
            {
                printf("This is BNE instruction.\n");
                ALU_Operation = 150;
            }
            else if (func3 == 4)
            {
                printf("This is BLT instruction.\n");
                ALU_Operation = 120;
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
                ControlSig = {0, 0, 0, 0, 0, 0, 1, 1, 0};
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
            ControlSig = {1, 1, 0, 0, 0, 0, 1, 0, 0};
            Control_Signals(1, 1, 0, 0, 0, 0, 1, 0, 0);
        }
        else if (opcode == -17)
        {
            printf("This is JAL instruction.\n");
            ALU_Operation = 10;
            RA = insNum;
            RB = 4;
            ControlSig = {1, 0, 0, 0, 0, 0, 1, 4, 0};
            Control_Signals(1, 0, 0, 0, 0, 0, 1, 4, 0);
        }
        else
        {
            printf("invalid opcode\n");
        }
        // cout << ALU_Operation << " " << RB << endl;
        ControlSig = Execute_instructions(ControlSig, ALU_Operation, RA, RB);
        // cout << ControlSig[6] << endl;
        return ControlSig;
    }

    vector<int> GetRSPC()
    {
        vector<int> reqs;
        reqs.push_back(RA);
        reqs.push_back(RB);
        reqs.push_back(PC);
        reqs.push_back(immediate);
        return reqs;
    }

    vector<int> Execute_instructions(vector<int> ControlSig, int Operation, int a1, int a2)
    {
        // cout<<a1<<" "<<a2<<endl;

        if (Operation == 10)
        {
            // cout<<"Adding"<<endl;
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
            if (aout != 0)
            {
                ControlSig = {0, 0, 0, 0, 0, 0, 1, 4, 0};
                // cout<<immediate<<endl;
            }
        }
        else if (Operation == 130)
        {
            aout = int(a1 >= a2);
            if (aout != 0)
            {
                ControlSig = {0, 0, 0, 0, 0, 0, 1, 4, 0};
                // cout<<immediate<<endl;
            }
        }
        else if (Operation == 140)
        {
            aout = int(a1 == a2);
            // cout<<"dd"<<aout<<endl;
            if (aout != 0)
            {
                ControlSig = {0, 0, 0, 0, 0, 0, 1, 4, 0};
                // cout<<immediate<<endl;
            }
        }
        else if (Operation == 150)
        {
            // cout<<a1<<" "<<a2<<endl;
            aout = int(a1 != a2);
            // cout<<aout<<endl;
            if (aout != 0)
            {
                ControlSig = {0, 0, 0, 0, 0, 0, 1, 4, 0};
                // cout<<immediate<<endl;
            }
        }

        // cout<<RF_Write<<endl;

        if (RF_Write && !Mem_Read && !Mem_Write)
        {
            // cout<<"1"<<endl;
            r.WriteToRegister(rd, aout);
            // cout << r.ReadFromRegister(rd) << endl;
        }

        else if (RF_Write && !Mem_Read && Mem_Write)
        {
            // cout<<aout<<" gy "<<r.R[rs2]<<endl;
            // cout<<"2"<<endl;
            m.WriteToMemory(aout, r.R[rs2]);
            // cout << m.ReadFromMemory(aout) << endl;
            // i1.PrintMap();
        }

        else if (RF_Write && Mem_Read && !Mem_Write)
        {
            // cout<<aout<<endl;
            r.WriteToRegister(rd, m.ReadFromMemory(aout));
            // cout << r.ReadFromRegister(rd) << endl;
        }
        // else if (!RF_Write && !Mem_Read && !Mem_Write)
        // {
        //     // cout<<aout<<" gy "<<r.R[rs2]<<endl;
        //     // cout<<"2"<<endl;
        //     m.WriteToMemory(aout, r.R[rs2]);
        //     // cout << m.ReadFromMemory(aout) << endl;
        //     // i1.PrintMap();
        // }
        return ControlSig;
    }
};

int et = -1;

class Simulator
{
public:
    string currIns = "-1";
    vector<int> Parameters;

    void Fetch()
    {

        // cout<<" ggggg "<<insNum<<endl;
        // i1.PrintMap();
        currIns = i1.g[insNum];
        // cout << currIns << endl;

        // insNum += 4;
    }
    vector<int> ControlSig;
    vector<int> reqs;
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
    Executer e;
    void Execute()
    {

        if (Parameters.size() != 0)
        {
            e.identifyParameters(Parameters);
            ControlSig = e.ALU_COntrol_Generator();
            reqs = e.GetRSPC();
            // cout << e.aout << endl;
        }
    }
    void Memory()
    {
        // int aout, rs1, rs2, rd, immediate, numBytes, RA, PC, RB;
        // bool RF_Write = false, MuxB_select = false, MuxY_select = false, MuxMA_select = false, MuxINC_select = false, MuxPC_select = false, Mem_Read = false, Mem_Write = false;
        m.GetControls(ControlSig);
        // cout<<e.immediate<<"ff"<<endl;
        insNum = m.IAG(insNum, e.immediate);
        // cout<<"ff "<<insNum<<endl;
        // m.InitMemory(i1.dataMem);
        if (insNum == (i1.numIns) * 4)
        {
            et = 0;
        }
    }
};

int main()
{
    i1.TakeInstructionsToMap();
    i1.TakeDataToMap();
    i1.PrintMap();
    Simulator s;
    int i = 0;
    while (i < 160)
    {
        cout << endl;
        cout << "-----------------------------CLOCK " << i << "-------------------------------------" << endl;
        s.Fetch();
        s.Decode();
        s.Execute();
        s.Memory();
        cout << endl;
        cout << "REGISTER VALUES-----------" << endl;
        r.PrintAllRegisters();
        cout << endl;
        cout << "DATA VALUES------------" << endl;
        i1.PrintData();
        i++;
    }
}
