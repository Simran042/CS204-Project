#include<bits\stdc++.h>
using namespace std;
long long int PC ,MAR, RY , PC ,MDR ,RZ,RM, MuxMA_select, Mem_Read, numBytes;
map<int, vector<int>> dataMemory;
map<int, vector<int>> instructionMemory;
map<int,vector<int>> :: iterator it;

for(auto it : dataMemory) {
    it->second = {0, 0, 0, 0};
}

for(auto it : instructionMemory) {
    it->second = {0, 0, 0, 0};
}
string ProcessorMemoryInterface(){
        string ans;
        if(MuxMA_select == 0){
            if(Mem_Read == 1){
                vector<int> temp;
                for(int i = 0; i < numBytes; i++){
                    temp.push_back(dataMemory[MAR][i]);
                }
                reverse(temp.begin(), temp.end());
                ans = "0x";
                for(int i = 0; i < temp.size(); i++){
                    string curr = hex(temp[i])[2:];
                    ans += string(2-curr.length(), '0') + curr;
                }
                return ans;
            }
            else if(Mem_Write == 1){
                for(int i = 0; i < numBytes; i++){
                    dataMemory[MAR][i] = (MDR & int(string("0xFF") + string(2*i, '0'), 16)) >> (8*i);
                }
                return "0x1";
            }
        }
        else{
            string ans = instructionMemory[MAR];
            string newans = "";
            int x = ans.length();
            for(int i = 0; i < ans.length(); i++){
                newans += ans[x-1-i];
            }
            newans = "0x" + newans;
            return newans;
        }
    }
void IAG(){
    if(MuxPC_select == 0){
        PC = RA;
    }
    else{
        if(MuxINC_select == 0){
            PC = PC + 4;
        }
        else{
            PC = PC + immed;
        }
    }
}

void MemoryAccess(){
    // =========== CHECK =============
    // PC update (IAG module)
    IAG();

    if(MuxY_select == 0){
        RY = RZ;
    }
    else if(MuxY_select == 1){
        MAR = std::to_string(RZ).lower();
        MDR = RM;
        RY = std::stoi(ProcessorMemoryInterface(),nullptr,16);
        if(RY > pow(2,31) - 1){
             RY = -(pow(2,32) - RY);
        }
    }
    else if(MuxY_select == 2){
        RY = PC_Temp;
    }
}

void RegisterUpdate(){
    if(RF_Write == 1 && RD != 0){
        reg[RD] = RY;
    }
}

bool validateDataSegment(std::vector<std::string> y){
    if(y.size() != 2){
        return false;
    }
    std::string addr = y[0];
    std::string data = y[1];
    if(addr.substr(0,2) != "0x" || data.substr(0,2) != "0x"){
        return false;
    }
    try{
        if(std::stoi(addr,nullptr,16) < std::stoi("0x10000000",nullptr,16)){
            return false;
        }
        stoi(data,nullptr,16);
         }
    catch(...){
        return false;
    }
    return true;
}

bool validateInstruction(std::vector<std::string> y){
    if(y.size() != 2){
        return false
    }
}

void main(){
        // Read the .mc file as input
        std::ifstream mcFile("input.mc");
        // load the data segment
        int flag = 0;
        std::string x;
        while(getline(mcFile, x)){
            //creating a hashmap, data segment stored
            std::vector<std::string> y = split(x, '\n')[0].split();
            std::transform(y[1].begin(), y[1].end(), y[1].begin(), ::tolower);
            if(flag == 1){
                if(validateDataSegment(y) == false){
                    std::cout << "ERROR : INVALID DATA SEGMENT" << std::endl;
                    ui.errorUpdate("ERROR : INVALID DATA SEGMENT");
                    exit(1);
                }
                dataMemory[y[0]][0] = (std::stoi(y[1], nullptr, 16) & std::stoi("0xFF", nullptr, 16));
                dataMemory[y[0]][1] = (std::stoi(y[1], nullptr, 16) & std::stoi("0xFF00", nullptr, 16)) >> 8;
                dataMemory[y[0]][2] = (std::stoi(y[1], nullptr, 16) & std::stoi("0xFF0000", nullptr, 16)) >> 16;
                dataMemory[y[0]][3] = (std::stoi(y[1], nullptr, 16) & std::stoi("0xFF000000", nullptr, 16)) >> 24;
            }
            if(y.find('$') != std::string::npos){
                flag = 1;
            }
            if(flag == 0){
                //TODO : Add Validation______
                vector<string> y = split(x, '\n')[0].split();
                if(validateInstruction(y) == false){
                    cout << "ERROR : INVALID INSTRUCTION" <<endl;
                    exit();
                }
                dataMemory[y[0]][0] = (static_cast<int>(std::stoul(y[1], nullptr, 16)) & 0xFF);
            dataMemory[y[0]][1] = (static_cast<int>(std::stoul(y[1], nullptr, 16)) & 0xFF00) >> 8;
            dataMemory[y[0]][2] = (static_cast<int>(std::stoul(y[1], nullptr, 16)) & 0xFF0000) >> 16;
            dataMemory[y[0]][3] = (static_cast<int>(std::stoul(y[1], nullptr, 16)) & 0xFF000000) >> 24;
            }
            if (y.find('$') != std::string::npos) {
    flag = 1;
}
if (flag == 0) {
    //TODO : Add Validation______
    vector<string> y = split(x, '\n')[0].split();
    if (validateInstruction(y) == false) {
        cout << "ERROR : INVALID INSTRUCTION" << std::endl;
    }
}

transform(y[1].begin(), y[1].end(), y[1].begin(), ::tolower);
    for(int i = 0; i < 4; i++) {
        instructionMemory[y[0]][i] = std::to_string(static_cast<int>(std::stoul(y[1], nullptr, 16) & std::stoul("0xFF" + std::string(2 * i, '0'), nullptr)) >> (8 * i));
        instructionMemory[y[0]][i] = std::string(2 - instructionMemory[y[0]][i].length(), '0') + instructionMemory[y[0]][i];
        transform(instructionMemory[y[0]][i].begin(), instructionMemory[y[0]][i].end(), instructionMemory[y[0]][i].begin(), ::tolower);
    }
void UpdateFile(string filename){
        ofstream mcFile;
        mcFile.open(filename, ios::out);
        string i = "0x0";
        for(auto i : instructionMemory){
            string curr = "0x";
            for(auto j : instructionMemory[i][::-1]){
                curr += j;
            }
            mcFile << i << " " << curr << endl;
        }
        i = hex(int(i,16) + 4);
        mcFile << i << " $\n";
        for(auto i : dataMemory){
            if(i == "0x7fffffec"){
                break;
            }
            string curr = "0x";
            for(auto j : dataMemory[i][::-1]){
                curr += "0"*(2-len(hex(j)[2:])) + hex(j)[2:];
            }
            mcFile << i << " " << curr << endl;
        }
    }