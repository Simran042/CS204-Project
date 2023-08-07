#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <String>
#include <fstream>
using namespace std;
int insNum = 0;
int numhitsins = 0;
int nummissins = 0;
int hitlatencyins = 0;
int misslatencyins = 0;
int dataNum = 0;
int numhitsdata = 0;
int nummissdata = 0;
int hitlatencydata = 0;
int misslatencydata = 0;
map<int, int> step;
int ending = 0;
int UnsignedBinaryToDecimal(string s)
{
    int n = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0')
        {
            n = n * 2;
        }
        else if (s[i] = 1)
        {
            n = n * 2 + 1;
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
            bin += "0000";
            break;
        case '1':
            bin += "0001";
            break;
        case '2':
            bin += "0010";
            break;
        case '3':
            bin += "0011";
            break;
        case '4':
            bin += "0100";
            break;
        case '5':
            bin += "0101";
            break;
        case '6':
            bin += "0110";
            break;
        case '7':
            bin += "0111";
            break;
        case '8':
            bin += "1000";
            break;
        case '9':
            bin += "1001";
            break;
        case 'A':
            bin += "1010";
            break;
        case 'B':
            bin += "1011";
            break;
        case 'C':
            bin += "1100";
            break;
        case 'D':
            bin += "1101";
            break;
        case 'E':
            bin += "1110";
            break;
        case 'F':
            bin += "1111";
            break;
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
        for (int i = 0; i < 32; i++)
        {
            cout << "x" << i << " = " << ReadFromRegister(i) << " ; ";
        }
        cout << endl;
    }
};

int inscachesize = 0;
int insblocksize = 0;
int instype = 0;
int insasso = 0;
int insrepl = 0;
int inssetsize = 0;
int coldins = 0;
int capacityins = 0;
int insset = 0;
class InstrxnCache
{
public:
    int numSets = 0;
    int arrsize = 0;
    map<int, vector<string>> CacheForIns;
    map<int, vector<int>> AlreadySetIns;
    map<int, vector<int>> TagForIns;
    map<int, vector<int>> lru;
    map<int, vector<int>> lfu;
    vector<int> alreadyins;
    void initCache()
    {
        cout << "Cache size for instructions? " << endl;
        cin >> inscachesize;
        cout << "Block size for instructions? " << endl;
        cin >> insblocksize;
        cout << "Type of mapping? 0 for DM, 1 for FA, 2 for SA? " << endl;
        cin >> instype;
        if (instype == 1)
        {
            cout << "What replacement policy for instructions? 0 for FIFO, 1 for RANDOM, 2 for LRU, 3 for LFU: ";
            cin >> insrepl;
        }
        if (instype == 2)
        {
            cout << "What way set associative for instructions? ";
            cin >> insasso;
            cout << "What replacement policy for instructions? 0 for FIFO, 1 for RANDOM, 2 for LRU, 3 for LFU: ";
            cin >> insrepl;
        }

        if (instype == 1)
        {
            insset = 1;
        }
        else if (instype == 0)
        {
            insset = inscachesize / insblocksize;
        }
        else if (instype == 2)
        {
            insset = inscachesize / (insblocksize * insasso);
        }
        else
        {
            cout << "Please enter valid mapping" << endl;
        }
        numSets = insset;
        arrsize = inscachesize / (insblocksize * insset);
        cout << numSets << endl;
        cout << arrsize << endl;
        // int cache[numSets][arrsize]{-1};
        // int tag[numSets][arrsize]{-1};
        // for (int i = 0; i < numSets; i++)
        // {
        //     vector<string> temp;
        //     for (int j = 0; j < arrsize; j++)
        //     {
        //         temp.push_back("-1");
        //     }
        //     for (int k = 0; k < temp.size(); k++)
        //     {
        //         cout << temp[k] << " ";
        //     }
        //     cout << endl;
        //     CacheForIns.insert({i, temp});
        // }
        // cout << "EE" << endl;

        // for(int i=0; i<numBlocks; i++){
        //     for(int j=0; j<arrsize; j++){
        // tag[i][j]=-1;
        // cache[i][j]=-1;
        // // cout<<cache[i][j];
        // CacheForIns.insert({-1,{-1,-1}});
        //     }
        //     cout<<endl;
        // }

        for (auto itr = CacheForIns.begin(); itr != CacheForIns.end(); ++itr)
        {
            cout << itr->first << ": ";
            for (auto itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
            {
                cout << *itr2 << " ";
            }
            cout << endl;
            // cout << itr->first << itr->second << '\n';
        }
    }

    int as = 0;
    void TakeInstrxnToCache(int addr, string val)
    {

        if (instype == 0)
        { // DM
            int check = 0;
            for (auto itr = TagForIns.begin(); itr != TagForIns.end(); ++itr)
            {
                int i = 0;
                // cout<<itr->first<<": ";
                for (auto itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
                {
                    // cout<<*itr2<<" ";
                    if (*itr2 == addr)
                    {
                        check = 1;
                        vector<string> temp = CacheForIns[itr->first];
                        temp[i] = val;
                        CacheForIns[itr->first] = temp;
                        vector<int> lfint = lfu[itr->first];
                        lfint[i] = lfint[i] + 1;
                    }
                    else
                    {
                        i++;
                    }
                }
                cout << endl;
                // cout << itr->first << itr->second << '\n';
            }
            if (check == 0)
            {
                alreadyins.push_back(addr);
                vector<int> tempal = AlreadySetIns[addr % numSets];
                tempal.push_back(addr);
                AlreadySetIns[addr % numSets] = tempal;
                if (TagForIns.size() < numSets)
                {
                    TagForIns.insert({TagForIns.size(), {addr}});
                    CacheForIns.insert({CacheForIns.size(), {val}});
                    lfu.insert({lfu.size(), {1}});
                }
                else
                {
                    ReplacePolicy(addr, val);
                }
            }
        }

        if (instype == 1)
        { // FA
            cout << "st1" << endl;
            for (int u = 0; u < lfu.size(); u++)
            {
                for (int v = 0; v < lfu[u].size(); v++)
                {
                    cout << lfu[u][v] << " ";
                }
                cout << endl;
            }
            int check = 0;
            vector<int> tagarr = TagForIns[0];
            int i = 0;
            // cout<<itr->first<<": ";
            for (auto itr2 = tagarr.begin(); itr2 != tagarr.end(); ++itr2)
            {
                // cout<<*itr2<<" ";
                if (*itr2 == addr)
                {
                    check = 1;
                    vector<string> temp = CacheForIns[0];
                    temp[i] = val;
                    CacheForIns[0] = temp;
                    vector<int> lfint = lfu[0];
                    // cout<<"---------------------"<<endl;
                    lfint[i] = lfint[i] + 1;
                }
                else
                {
                    i++;
                }
            }
            cout << endl;
            // cout << itr->first << itr->second << '\n';

            if (check == 0)
            {
                alreadyins.push_back(addr);
                // cout << "Hi" << endl;
                vector<int> tempal = AlreadySetIns[addr % numSets];
                tempal.push_back(addr);
                AlreadySetIns[addr % numSets] = tempal;
                if (CacheForIns[0].size() > 0)
                {
                    // cout << "j" << endl;
                    vector<int> addrs = TagForIns[0];
                    vector<int> lfii = lfu[0];
                    vector<string> temp = CacheForIns[0];
                    // cout<<addrs.size(<<endl;
                    // cout<<temp[0]<<endl;
                    if (temp.size() < arrsize && addrs.size() < arrsize)
                    {
                        // cout<<temp.size()<<endl;
                        // cout<<arrsize<<endl;
                        // temp[temp.size()] = val;
                        temp.push_back(val);
                        addrs.push_back(addr);
                        lfii.push_back(1);
                        CacheForIns[0] = temp;
                        TagForIns[0] = addrs;
                        lfu[0] = lfii;
                    }
                    else
                    {
                        // cout << "MM" << endl;
                        ReplacePolicy(addr, val);
                    }
                }
                else
                {
                    vector<string> temp;
                    vector<int> addrs;
                    vector<int> lfrii;
                    temp.push_back(val);
                    addrs.push_back(addr);
                    lfrii.push_back(1);
                    // cout<<arrsize<<" "<<lfrii.size();
                    // as++;
                    CacheForIns[0] = temp;
                    TagForIns[0] = addrs;
                    lfu[0] = lfrii;
                }
            }
        }
        if (instype == 2)
        { // FA
            int set = addr % numSets;
            // cout << "st1" << endl;
            int check = 0;
            vector<int> tagarr = TagForIns[set];
            int i = 0;
            // cout<<itr->first<<": ";
            // for (int u = 0; u < lfu.size(); u++)
            // {
            //     for (int v = 0; v < lfu[u].size(); v++)
            //     {
            //         cout << lfu[u][v] << " ";
            //     }
            //     cout << endl;
            // }
            for (auto itr2 = tagarr.begin(); itr2 != tagarr.end(); ++itr2)
            {
                // cout<<*itr2<<" ";
                if (*itr2 == addr)
                {
                    check = 1;
                    vector<string> temp = CacheForIns[set];
                    temp[i] = val;
                    CacheForIns[set] = temp;
                    vector<int> lfint = lfu[set];
                    // cout<<"---------------------"<<endl;
                    lfint[i] = lfint[i] + 1;
                }
                else
                {
                    i++;
                }
            }
            cout << endl;
            // cout << itr->first << itr->second << '\n';

            if (check == 0)
            {
                alreadyins.push_back(addr);
                // cout << "Hi" << endl;
                vector<int> tempal = AlreadySetIns[addr % numSets];
                tempal.push_back(addr);
                AlreadySetIns[addr % numSets] = tempal;
                if (CacheForIns[set].size() > 0)
                {
                    // cout << "j" << endl;
                    vector<int> addrs = TagForIns[set];
                    vector<string> temp = CacheForIns[set];
                    vector<int> lfii = lfu[set];
                    // cout<<addrs.size(<<endl;
                    // cout<<temp[0]<<endl;
                    if (temp.size() < arrsize && addrs.size() < arrsize)
                    {
                        // cout<<temp.size()<<endl;
                        // cout<<arrsize<<endl;
                        // temp[temp.size()] = val;
                        temp.push_back(val);
                        addrs.push_back(addr);
                        CacheForIns[set] = temp;
                        TagForIns[set] = addrs;
                        lfii.push_back(1);
                        lfu[set] = lfii;
                    }
                    else
                    {

                        ReplacePolicy(addr, val);
                    }
                }
                else
                {
                    vector<string> temp;
                    vector<int> addrs;
                    temp.push_back(val);
                    addrs.push_back(addr);
                    CacheForIns[set] = temp;
                    TagForIns[set] = addrs;
                    vector<int> lfrii;
                    lfrii.push_back(1);
                    lfu[set] = lfrii;
                }
            }
        }
        cout << "INSTRUCTION CACHE VALUES: " << endl;
        for (auto itr = CacheForIns.begin(); itr != CacheForIns.end(); ++itr)
        {
            cout << itr->first << ": ";
            for (auto itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
            {
                cout << *itr2 << " ";
            }
            cout << endl;
            // cout << itr->first << itr->second << '\n';
        }
        cout << "INSTRUCTION CACHE ADDRESSES: " << endl;
        for (auto itr = TagForIns.begin(); itr != TagForIns.end(); ++itr)
        {
            cout << itr->first << ": ";
            for (auto itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
            {
                cout << *itr2 << " ";
            }
            cout << endl;
            // cout << itr->first << itr->second << '\n';
        }
    }

    void ReplacePolicy(int addr, string val)
    {
        if (instype == 0)
        { // dm
            int set = addr % insset;
            // cout << insset << endl;
            vector<int> addresses = TagForIns[set];
            vector<string> values = CacheForIns[set];
            // cout << addresses.size() << " " << values.size() << endl;
            addresses[0] = addr;
            values[0] = val;
            TagForIns[set] = addresses;
            CacheForIns[set] = values;
        }
        if (insrepl == 0)
        { // FIFO
            if (instype == 1)
            { // fa
                vector<int> addresses = TagForIns[0];
                vector<string> values = CacheForIns[0];
                for (int i = 0; i < addresses.size() - 1; i++)
                {
                    addresses[i] = addresses[i + 1];
                }
                addresses[addresses.size() - 1] = addr;
                for (int i = 0; i < values.size() - 1; i++)
                {
                    values[i] = values[i + 1];
                }
                values[values.size() - 1] = val;
                TagForIns[0] = addresses;
                CacheForIns[0] = values;
            }
            if (instype == 2)
            { // fa
                int set = addr % numSets;
                vector<int> addresses = TagForIns[set];
                vector<string> values = CacheForIns[set];
                for (int i = 0; i < addresses.size() - 1; i++)
                {
                    addresses[i] = addresses[i + 1];
                }
                addresses[addresses.size() - 1] = addr;
                for (int i = 0; i < values.size() - 1; i++)
                {
                    values[i] = values[i + 1];
                }
                values[values.size() - 1] = val;
                TagForIns[set] = addresses;
                CacheForIns[set] = values;
            }
        }

        if (insrepl == 1)
        { // RANDOM uses fifo only
            if (instype == 1)
            { // fa
                vector<int> addresses = TagForIns[0];
                vector<string> values = CacheForIns[0];
                for (int i = 0; i < addresses.size() - 1; i++)
                {
                    addresses[i] = addresses[i + 1];
                }
                addresses[addresses.size() - 1] = addr;
                for (int i = 0; i < values.size() - 1; i++)
                {
                    values[i] = values[i + 1];
                }
                values[values.size() - 1] = val;
                TagForIns[0] = addresses;
                CacheForIns[0] = values;
            }
            if (instype == 2)
            { // fa
                int set = addr % numSets;
                vector<int> addresses = TagForIns[set];
                vector<string> values = CacheForIns[set];
                for (int i = 0; i < addresses.size() - 1; i++)
                {
                    addresses[i] = addresses[i + 1];
                }
                addresses[addresses.size() - 1] = addr;
                for (int i = 0; i < values.size() - 1; i++)
                {
                    values[i] = values[i + 1];
                }
                values[values.size() - 1] = val;
                TagForIns[set] = addresses;
                CacheForIns[set] = values;
            }
        }

        if (insrepl == 2)
        { // LRU
            if (instype == 1)
            {// fa
                vector<int> addresses = TagForIns[0];
                vector<string> values = CacheForIns[0];
                vector<int> rus = lfu[0];
                int min = *min_element(rus.begin(), rus.end());
                int max = *max_element(rus.begin(), rus.end());
                for (int h = 0; h < rus.size(); h++)
                {
                    if (rus[h] == min)
                    {
                        addresses[h] = addr;
                        values[h] = val;
                        rus[h] = max + 1;
                        break;
                    }
                }
                TagForIns[0] = addresses;
                CacheForIns[0] = values;
                lfu[0] = rus;
            }
            if (instype == 2)
            { // sa
                int set = addr % numSets;
                vector<int> addresses = TagForIns[set];
                vector<string> values = CacheForIns[set];
                vector<int> rus = lfu[set];
                int min = *min_element(rus.begin(), rus.end());
                int max = *max_element(rus.begin(), rus.end());
                for (int h = 0; h < rus.size(); h++)
                {
                    if (rus[h] == min)
                    {
                        addresses[h] = addr;
                        values[h] = val;
                        rus[h] = max + 1;
                        break;
                    }
                }
                TagForIns[set] = addresses;
                CacheForIns[set] = values;
                lfu[set] = rus;
            }
        }

        if (insrepl == 3)
        { // LFU
            if (instype == 1)
            { // fa
                // cout << "!";
                vector<int> addresses = TagForIns[0];
                vector<string> values = CacheForIns[0];
                vector<int> rus = lfu[0];
                int min = *min_element(rus.begin(), rus.end());
                int max = *max_element(rus.begin(), rus.end());
                // cout << min << max << endl;
                for (int h = 0; h < rus.size(); h++)
                {
                    if (rus[h] == min)
                    {
                        addresses[h] = addr;
                        values[h] = val;
                        rus[h] = 1;
                        break;
                    }
                }
                TagForIns[0] = addresses;
                CacheForIns[0] = values;
                lfu[0] = rus;
                // for (int u = 0; u < lfu.size(); u++)
                // {
                //     for (int v = 0; v < lfu[u].size(); v++)
                //     {
                //         cout << lfu[u][v] << " ";
                //     }
                //     cout << endl;
                // }
            }
            if (instype == 2)
            { // sa
                int set = addr % numSets;
                vector<int> addresses = TagForIns[set];
                vector<string> values = CacheForIns[set];
                vector<int> rus = lfu[set];
                int min = *min_element(rus.begin(), rus.end());
                int max = *max_element(rus.begin(), rus.end());
                for (int h = 0; h < rus.size(); h++)
                {
                    if (rus[h] == min)
                    {
                        addresses[h] = addr;
                        values[h] = val;
                        rus[h] = 1;
                        break;
                    }
                }
                TagForIns[set] = addresses;
                CacheForIns[set] = values;
                lfu[set] = rus;
            }
        }
    }

    string FindInCache(int addr, string val)
    {
        int flag = 0;
        vector<int> tempal = AlreadySetIns[addr % numSets];
        if (find(alreadyins.begin(), alreadyins.end(), addr) == alreadyins.end())
        {
            coldins++;
        }
        else if (find(tempal.begin(), tempal.end(), addr) == tempal.end())
        {
            capacityins++;
        }
        for (int u = 0; u < TagForIns.size(); u++)
        {
            for (int v = 0; v < TagForIns[u].size(); v++)
            {
                if (TagForIns[u][v] == addr)
                {
                    // cout << "_______________" << addr << endl;
                    flag++;
                    numhitsins++;
                    hitlatencyins++;
                    return CacheForIns[u][v];
                }
            }
        }
        if (flag == 0)
        {
            // cout << addr << "llll" << endl;
            TakeInstrxnToCache(addr, val);
            nummissins++;
            misslatencyins += 20;
        }
    }
};
InstrxnCache ic;

int datacachesize = 0;
int datablocksize = 0;
int datatype = 0;
int dataasso = 0;
int datarepl = 0;
int datasetsize = 0;
int colddata = 0;
int capacitydata = 0;
int dataset = 0;
class dataCache
{
public:
    int numSets = 0;
    int arrsize = 0;
    map<int, vector<int>> CacheFordata;
    map<int, vector<int>> TagFordata;
    map<int, vector<int>> AlreadySetData;
    map<int, vector<int>> lru;
    map<int, vector<int>> lfu;
    vector<int> alreadydata;
    void initCache()
    {
        cout << "Cache size for data? " << endl;
        cin >> datacachesize;
        cout << "Block size for data? " << endl;
        cin >> datablocksize;
        cout << "Type of mapping? 0 for DM, 1 for FA, 2 for SA? " << endl;
        cin >> datatype;
        if (datatype == 1)
        {
            cout << "What replacement policy for data? 0 for FIFO, 1 for RANDOM, 2 for LRU, 3 for LFU: ";
            cin >> datarepl;
        }
        if (datatype == 2)
        {
            cout << "What way set associative for data? ";
            cin >> dataasso;
            cout << "What replacement policy for data? 0 for FIFO, 1 for RANDOM, 2 for LRU, 3 for LFU: ";
            cin >> datarepl;
        }

        if (datatype == 1)
        {
            dataset = 1;
        }
        else if (datatype == 0)
        {
            dataset = datacachesize / datablocksize;
        }
        else if (datatype == 2)
        {
            dataset = datacachesize / (datablocksize * dataasso);
        }
        else
        {
            cout << "Please enter valid mapping" << endl;
        }
        numSets = dataset;
        arrsize = datacachesize / (datablocksize * dataset);
        // cout << numSets << endl;
        // cout << arrsize << endl;
        // int cache[numSets][arrsize]{-1};
        // int tag[numSets][arrsize]{-1};
        // for (int i = 0; i < numSets; i++)
        // {
        //     vector<int> temp;
        //     for (int j = 0; j < arrsize; j++)
        //     {
        //         temp.push_back("-1");
        //     }
        //     for (int k = 0; k < temp.size(); k++)
        //     {
        //         cout << temp[k] << " ";
        //     }
        //     cout << endl;
        //     CacheFordata.dataert({i, temp});
        // }
        // cout << "EE" << endl;

        // for(int i=0; i<numBlocks; i++){
        //     for(int j=0; j<arrsize; j++){
        // tag[i][j]=-1;
        // cache[i][j]=-1;
        // // cout<<cache[i][j];
        // CacheFordata.dataert({-1,{-1,-1}});
        //     }
        //     cout<<endl;
        // }

        // for (auto itr = CacheFordata.begin(); itr != CacheFordata.end(); ++itr)
        // {
        //     cout << itr->first << ": ";
        //     for (auto itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
        //     {
        //         cout << *itr2 << " ";
        //     }
        //     cout << endl;
        //     // cout << itr->first << itr->second << '\n';
        // }
    }

    int as = 0;
    void TakedatatrxnToCache(int addr, int val)
    {
        vector<int> tempal = AlreadySetData[addr % numSets];
        if (find(alreadydata.begin(), alreadydata.end(), addr) == alreadydata.end())
        {
            colddata++;
        }
        else if (find(tempal.begin(), tempal.end(), addr) == tempal.end())
        {
            capacitydata++;
        }
        if (datatype == 0)
        { // DM
            int check = 0;
            for (auto itr = TagFordata.begin(); itr != TagFordata.end(); ++itr)
            {
                int i = 0;
                // cout<<itr->first<<": ";
                for (auto itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
                {
                    // cout<<*itr2<<" ";
                    if (*itr2 == addr)
                    {
                        check = 1;
                        vector<int> temp = CacheFordata[itr->first];
                        temp[i] = val;
                        CacheFordata[itr->first] = temp;
                        vector<int> lfint = lfu[itr->first];
                        lfint[i] = lfint[i] + 1;
                    }
                    else
                    {
                        i++;
                    }
                }
                cout << endl;
                // cout << itr->first << itr->second << '\n';
            }
            if (check == 0)
            {
                alreadydata.push_back(addr);
                vector<int> tempal = AlreadySetData[addr % numSets];
                tempal.push_back(addr);
                AlreadySetData[addr % numSets] = tempal;
                if (TagFordata.size() < numSets)
                {
                    TagFordata.insert({TagFordata.size(), {addr}});
                    CacheFordata.insert({CacheFordata.size(), {val}});
                    lfu.insert({lfu.size(), {1}});
                }
                else
                {
                    ReplacePolicy(addr, val);
                }
            }
        }

        if (datatype == 1)
        { // FA
            // cout << "st1" << endl;
            // for (int u = 0; u < lfu.size(); u++)
            // {
            //     for (int v = 0; v < lfu[u].size(); v++)
            //     {
            //         cout << lfu[u][v] << " ";
            //     }
            //     cout << endl;
            // }
            int check = 0;
            vector<int> tagarr = TagFordata[0];
            int i = 0;
            // cout<<itr->first<<": ";
            for (auto itr2 = tagarr.begin(); itr2 != tagarr.end(); ++itr2)
            {
                // cout<<*itr2<<" ";
                if (*itr2 == addr)
                {
                    check = 1;
                    vector<int> temp = CacheFordata[0];
                    temp[i] = val;
                    CacheFordata[0] = temp;
                    vector<int> lfint = lfu[0];
                    // cout<<"---------------------"<<endl;
                    lfint[i] = lfint[i] + 1;
                }
                else
                {
                    i++;
                }
            }
            cout << endl;
            // cout << itr->first << itr->second << '\n';

            if (check == 0)
            {
                alreadydata.push_back(addr);
                vector<int> tempal = AlreadySetData[addr % numSets];
                tempal.push_back(addr);
                AlreadySetData[addr % numSets] = tempal;
                // cout << "Hi" << endl;
                if (CacheFordata[0].size() > 0)
                {
                    // cout << "j" << endl;
                    vector<int> addrs = TagFordata[0];
                    vector<int> lfii = lfu[0];
                    vector<int> temp = CacheFordata[0];
                    // cout<<addrs.size(<<endl;
                    // cout<<temp[0]<<endl;
                    if (temp.size() < arrsize && addrs.size() < arrsize)
                    {
                        // cout<<temp.size()<<endl;
                        // cout<<arrsize<<endl;
                        // temp[temp.size()] = val;
                        temp.push_back(val);
                        addrs.push_back(addr);
                        lfii.push_back(1);
                        CacheFordata[0] = temp;
                        TagFordata[0] = addrs;
                        lfu[0] = lfii;
                    }
                    else
                    {
                        // cout << "MM" << endl;
                        ReplacePolicy(addr, val);
                    }
                }
                else
                {
                    vector<int> temp;
                    vector<int> addrs;
                    vector<int> lfrii;
                    temp.push_back(val);
                    addrs.push_back(addr);
                    lfrii.push_back(1);
                    // cout<<arrsize<<" "<<lfrii.size();
                    // as++;
                    CacheFordata[0] = temp;
                    TagFordata[0] = addrs;
                    lfu[0] = lfrii;
                }
            }
        }
        if (datatype == 2)
        { // FA
            int set = addr % numSets;
            // cout << "st1" << endl;
            int check = 0;
            vector<int> tagarr = TagFordata[set];
            int i = 0;
            // cout<<itr->first<<": ";
            // for (int u = 0; u < lfu.size(); u++)
            // {
            //     for (int v = 0; v < lfu[u].size(); v++)
            //     {
            //         cout << lfu[u][v] << " ";
            //     }
            //     cout << endl;
            // }
            for (auto itr2 = tagarr.begin(); itr2 != tagarr.end(); ++itr2)
            {
                // cout<<*itr2<<" ";
                if (*itr2 == addr)
                {
                    check = 1;
                    vector<int> temp = CacheFordata[set];
                    temp[i] = val;
                    CacheFordata[set] = temp;
                    vector<int> lfint = lfu[set];
                    // cout<<"---------------------"<<endl;
                    lfint[i] = lfint[i] + 1;
                }
                else
                {
                    i++;
                }
            }
            cout << endl;
            // cout << itr->first << itr->second << '\n';

            if (check == 0)
            {
                alreadydata.push_back(addr);
                vector<int> tempal = AlreadySetData[addr % numSets];
                tempal.push_back(addr);
                AlreadySetData[addr % numSets] = tempal;
                // cout << "Hi" << endl;
                if (CacheFordata[set].size() > 0)
                {
                    // cout << "j" << endl;
                    vector<int> addrs = TagFordata[set];
                    vector<int> temp = CacheFordata[set];
                    vector<int> lfii = lfu[set];
                    // cout<<addrs.size(<<endl;
                    // cout<<temp[0]<<endl;
                    if (temp.size() < arrsize && addrs.size() < arrsize)
                    {
                        // cout<<temp.size()<<endl;
                        // cout<<arrsize<<endl;
                        // temp[temp.size()] = val;
                        temp.push_back(val);
                        addrs.push_back(addr);
                        CacheFordata[set] = temp;
                        TagFordata[set] = addrs;
                        lfii.push_back(1);
                        lfu[set] = lfii;
                    }
                    else
                    {

                        ReplacePolicy(addr, val);
                    }
                }
                else
                {
                    vector<int> temp;
                    vector<int> addrs;
                    temp.push_back(val);
                    addrs.push_back(addr);
                    CacheFordata[set] = temp;
                    TagFordata[set] = addrs;
                    vector<int> lfrii;
                    lfrii.push_back(1);
                    lfu[set] = lfrii;
                }
            }
        }
        cout << "DATA CACHE VALUES: " << endl;
        for (auto itr = CacheFordata.begin(); itr != CacheFordata.end(); ++itr)
        {
            cout << itr->first << ": ";
            for (auto itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
            {
                cout << *itr2 << " ";
            }
            cout << endl;
            // cout << itr->first << itr->second << '\n';
        }
        cout << "DATA CACHE ADDRESSES: " << endl;
        for (auto itr = TagFordata.begin(); itr != TagFordata.end(); ++itr)
        {
            cout << itr->first << ": ";
            for (auto itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2)
            {
                cout << *itr2 << " ";
            }
            cout << endl;
            // cout << itr->first << itr->second << '\n';
        }
    }

    void ReplacePolicy(int addr, int val)
    {
        if (datatype == 0)
        { // dm
            int set = addr % dataset;
            // cout << dataset << endl;
            vector<int> addresses = TagFordata[set];
            vector<int> values = CacheFordata[set];
            // cout << addresses.size() << " " << values.size() << endl;
            addresses[0] = addr;
            values[0] = val;
            TagFordata[set] = addresses;
            CacheFordata[set] = values;
        }
        if (datarepl == 0)
        { // FIFO
            if (datatype == 1)
            { // fa
                vector<int> addresses = TagFordata[0];
                vector<int> values = CacheFordata[0];
                for (int i = 0; i < addresses.size() - 1; i++)
                {
                    addresses[i] = addresses[i + 1];
                }
                addresses[addresses.size() - 1] = addr;
                for (int i = 0; i < values.size() - 1; i++)
                {
                    values[i] = values[i + 1];
                }
                values[values.size() - 1] = val;
                TagFordata[0] = addresses;
                CacheFordata[0] = values;
            }
            if (datatype == 2)
            { // fa
                int set = addr % numSets;
                vector<int> addresses = TagFordata[set];
                vector<int> values = CacheFordata[set];
                for (int i = 0; i < addresses.size() - 1; i++)
                {
                    addresses[i] = addresses[i + 1];
                }
                addresses[addresses.size() - 1] = addr;
                for (int i = 0; i < values.size() - 1; i++)
                {
                    values[i] = values[i + 1];
                }
                values[values.size() - 1] = val;
                TagFordata[set] = addresses;
                CacheFordata[set] = values;
            }
        }

        if (datarepl == 1)
        { // RANDOM uses fifo only
            if (datatype == 1)
            { // fa
                vector<int> addresses = TagFordata[0];
                vector<int> values = CacheFordata[0];
                for (int i = 0; i < addresses.size() - 1; i++)
                {
                    addresses[i] = addresses[i + 1];
                }
                addresses[addresses.size() - 1] = addr;
                for (int i = 0; i < values.size() - 1; i++)
                {
                    values[i] = values[i + 1];
                }
                values[values.size() - 1] = val;
                TagFordata[0] = addresses;
                CacheFordata[0] = values;
            }
            if (datatype == 2)
            { // fa
                int set = addr % numSets;
                vector<int> addresses = TagFordata[set];
                vector<int> values = CacheFordata[set];
                for (int i = 0; i < addresses.size() - 1; i++)
                {
                    addresses[i] = addresses[i + 1];
                }
                addresses[addresses.size() - 1] = addr;
                for (int i = 0; i < values.size() - 1; i++)
                {
                    values[i] = values[i + 1];
                }
                values[values.size() - 1] = val;
                TagFordata[set] = addresses;
                CacheFordata[set] = values;
            }
        }

        if (datarepl == 2)
        { // LRU
            if (datatype == 1)
            { // fa
                vector<int> addresses = TagFordata[0];
                vector<int> values = CacheFordata[0];
                vector<int> rus = lfu[0];
                int min = *min_element(rus.begin(), rus.end());
                int max = *max_element(rus.begin(), rus.end());
                for (int h = 0; h < rus.size(); h++)
                {
                    if (rus[h] == min)
                    {
                        addresses[h] = addr;
                        values[h] = val;
                        rus[h] = max + 1;
                        break;
                    }
                }
                TagFordata[0] = addresses;
                CacheFordata[0] = values;
                lfu[0] = rus;
            }
            if (datatype == 2)
            { // sa
                int set = addr % numSets;
                vector<int> addresses = TagFordata[set];
                vector<int> values = CacheFordata[set];
                vector<int> rus = lfu[set];
                int min = *min_element(rus.begin(), rus.end());
                int max = *max_element(rus.begin(), rus.end());
                for (int h = 0; h < rus.size(); h++)
                {
                    if (rus[h] == min)
                    {
                        addresses[h] = addr;
                        values[h] = val;
                        rus[h] = max + 1;
                        break;
                    }
                }
                TagFordata[set] = addresses;
                CacheFordata[set] = values;
                lfu[set] = rus;
            }
        }

        if (datarepl == 3)
        { // LFU
            if (datatype == 1)
            { // fa
                // cout << "!";
                vector<int> addresses = TagFordata[0];
                vector<int> values = CacheFordata[0];
                vector<int> rus = lfu[0];
                int min = *min_element(rus.begin(), rus.end());
                int max = *max_element(rus.begin(), rus.end());
                // cout << min << max << endl;
                for (int h = 0; h < rus.size(); h++)
                {
                    if (rus[h] == min)
                    {
                        addresses[h] = addr;
                        values[h] = val;
                        rus[h] = 1;
                        break;
                    }
                }
                TagFordata[0] = addresses;
                CacheFordata[0] = values;
                lfu[0] = rus;
                // for (int u = 0; u < lfu.size(); u++)
                // {
                //     for (int v = 0; v < lfu[u].size(); v++)
                //     {
                //         cout << lfu[u][v] << " ";
                //     }
                //     cout << endl;
                // }
            }
            if (datatype == 2)
            { // sa
                int set = addr % numSets;
                vector<int> addresses = TagFordata[set];
                vector<int> values = CacheFordata[set];
                vector<int> rus = lfu[set];
                int min = *min_element(rus.begin(), rus.end());
                int max = *max_element(rus.begin(), rus.end());
                for (int h = 0; h < rus.size(); h++)
                {
                    if (rus[h] == min)
                    {
                        addresses[h] = addr;
                        values[h] = val;
                        rus[h] = 1;
                        break;
                    }
                }
                TagFordata[set] = addresses;
                CacheFordata[set] = values;
                lfu[set] = rus;
            }
        }
    }

    int FindInCache(int addr, int val)
    {
        int flag = 0;
        for (int u = 0; u < TagFordata.size(); u++)
        {
            for (int v = 0; v < TagFordata[u].size(); v++)
            {
                if (TagFordata[u][v] == addr)
                {
                    // cout << "_______________" << addr << endl;
                    flag++;
                    numhitsdata++;
                    hitlatencydata++;
                    return CacheFordata[u][v];
                }
            }
        }
        if (flag == 0)
        {
            // cout << addr << "llll" << endl;
            TakedatatrxnToCache(addr, val);
            nummissdata++;
            misslatencydata += 20;
        }
    }
};
dataCache dc;

// class datatructions
// {
// public:
//     map<int, string> g;
//     vector<string> d;
//     map<int, int> dataMem;
//     int numdata = 0;
//     int numData = 0;

//     void TakeDataToMap()
//     {
//         dc.initCache();
//         fstream filedata;
//         // filedata.open("test1.mc", ios::in);
//         // filedata.open("fibonacci.mc", ios::in);
//         // filedata.open("tryStall.mc", ios::in);
//         filedata.open("loadstoretest.mc", ios::in);
//         // filedata.open("SumOfArray.mc", ios::in);
//         if (filedata.is_open())
//         {
//             string line;
//             while (getline(filedata, line))
//             {

//                 if (line == "end")
//                 {
//                     while (getline(filedata, line))
//                     {
//                         // cout << line << endl;
//                         d.push_back(line);
//                     }
//                 }
//             }
//         }

//         // cout<<d.size()<<endl;
//         d.pop_back();
//         for (string line : d)
//         {
//             // cout<<line<<endl;
//             numData += 1;
//             string temp = "";
//             string pc = "pc";
//             string data = "in";
//             int count = 0;
//             int i = 0;
//             for (char c : line)
//             {
//                 i++;
//                 if (c == ' ')
//                 {
//                     if (count == 0)
//                     {
//                         pc = temp;
//                         count++;
//                         temp = "";
//                     }
//                     else
//                     {
//                         count++;
//                     }
//                 }
//                 else if (c == '\n' || i == line.length())
//                 {
//                     temp = temp + c;
//                     data = temp;
//                 }
//                 else
//                 {
//                     temp = temp + c;
//                 }
//             }
//             string s1 = HexToBin(pc);
//             int intpc = binaryToDecimal(s1);
//             string s2 = HexToBin(data);
//             int intdata = binaryToDecimal(s2);
//             // cout<<intpc<<"c"<<endl;
//             // cout<<data<<"d"<<endl;
//             dataMem.insert({intpc, intdata});
//             dc.FindInCache(intpc, intdata);
//         }
//     }
//     void TakedatatructionsToMap()
//     {
//         ic.initCache();
//         fstream filedata;
//         // filedata.open("test1.mc", ios::in);
//         // filedata.open("fibonacci.mc", ios::in);
//         // filedata.open("tryStall.mc", ios::in);
//         filedata.open("loadstoretest.mc", ios::in);
//         // filedata.open("SumOfArray.mc", ios::in);
//         if (filedata.is_open())
//         {
//             string line;
//             while (getline(filedata, line))
//             {

//                 numdata += 1;
//                 string temp = "";
//                 string pc = "pc";
//                 string data = "in";
//                 int count = 0;
//                 int i = 0;
//                 if (line == "end")
//                 {
//                     ending = 1;
//                     // cout<<"Program Terminated";
//                     return;
//                 }
//                 else
//                 {
//                     for (char c : line)
//                     {
//                         i++;
//                         if (c == ' ')
//                         {
//                             if (count == 0)
//                             {
//                                 pc = temp;
//                                 count++;
//                                 temp = "";
//                             }
//                             else
//                             {
//                                 count++;
//                             }
//                         }
//                         else if (c == '\n' || i == line.length())
//                         {
//                             temp = temp + c;
//                             data = temp;
//                         }
//                         else
//                         {
//                             temp = temp + c;
//                         }
//                     }
//                 }
//                 string s1 = HexToBin(pc);
//                 int intpc = binaryToDecimal(s1);
//                 // cout<<intpc<<"c"<<endl;
//                 // cout<<data<<"d"<<endl;
//                 g.insert({intpc, data});
//                 // ic.TakedatatrxnToCache(intpc, data);
//             }
//             filedata.close();
//         }
//     }
//     void PrintMap()
//     {
//         cout << "dataTRUCTIONS HERE" << endl;
//         for (auto itr = g.begin(); itr != g.end(); ++itr)
//         {
//             cout << itr->first << '\t' << itr->second << '\n';
//         }
//         cout << "DATA HERE" << endl;
//         for (auto itr = dataMem.begin(); itr != dataMem.end(); ++itr)
//         {
//             cout << itr->first << '\t' << itr->second << '\n';
//         }
//     }
//     void PrintData()
//     {
//         for (auto itr = dataMem.begin(); itr != dataMem.end(); ++itr)
//         {
//             cout << itr->first << '\t' << itr->second << '\n';
//         }
//     }
// };

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
        dc.initCache();
        fstream fileIns;
        // fileIns.open("test1.mc", ios::in);
        fileIns.open("fibonacci.mc", ios::in);
        // fileIns.open("tryStall.mc", ios::in);
        // fileIns.open("loadstoretest.mc", ios::in);
        // fileIns.open("SumOfArray.mc", ios::in);
        if (fileIns.is_open())
        {
            string line;
            while (getline(fileIns, line))
            {

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
            string s1 = HexToBin(pc);
            int intpc = binaryToDecimal(s1);
            string s2 = HexToBin(ins);
            int intdata = binaryToDecimal(s2);
            // cout<<intpc<<"c"<<endl;
            // cout<<ins<<"d"<<endl;
            dataMem.insert({intpc, intdata});
            dc.FindInCache(intpc, intdata);
        }
    }
    void TakeInstructionsToMap()
    {
        ic.initCache();
        fstream fileIns;
        // fileIns.open("test1.mc", ios::in);
        fileIns.open("fibonacci.mc", ios::in);
        // fileIns.open("tryStall.mc", ios::in);
        // fileIns.open("loadstoretest.mc", ios::in);
        // fileIns.open("SumOfArray.mc", ios::in);
        if (fileIns.is_open())
        {
            string line;
            while (getline(fileIns, line))
            {

                numIns += 1;
                string temp = "";
                string pc = "pc";
                string ins = "in";
                int count = 0;
                int i = 0;
                if (line == "end")
                {
                    ending = 1;
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
                string s1 = HexToBin(pc);
                int intpc = binaryToDecimal(s1);
                // cout<<intpc<<"c"<<endl;
                // cout<<ins<<"d"<<endl;
                g.insert({intpc, ins});
                // ic.TakeInstrxnToCache(intpc, ins);
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
        else
        {
            cout << "DATA MEMORY NOT ACCESSED" << endl;
        }
    }
    int ReadFromMemory(int address)
    {
        cout << "READING FROM MEMORY LOCATION: " << address << endl;
        dc.FindInCache(address, i1.dataMem[address]);
        return i1.dataMem[address];
    }

    int WriteToMemory(int address, int value)
    {
        cout << "WRITING TO MEMORY LOCATION: " << address << endl;
        dc.FindInCache(address, value);
        i1.dataMem[address] = value;
    }
    int numIns = 0;
    int numInsF = 0;

    int IAG(int numInss, int immediate)
    {
        numIns = numInss;
        // cout<<"INIT "<<numIns<<endl;
        // cout<<" MUXINC "<<MuxINC_select<<" MuxPC "<<MuxPC_select<<endl;
        if (MuxPC_select == 1)
        {
            step.insert({immediate, numIns});
            numInsF = (immediate);
            // cout<<"1 "<<endl;
        }
        else
        {
            if (MuxINC_select == 0)
            {
                step.insert({numIns + 4, numIns});
                numInsF = numIns + 4;
                // cout << "2 " << endl;
            }
            else
            {
                step.insert({numIns + immediate, numIns});
                numInsF = numIns + (immediate);
                // cout << "immediate" << endl;
            }
        }
        // cout<<"Final "<<numIns<<endl;
        return numInsF;
    }
    map<int, vector<int>> btbTable;
    int instAddr = 0;
    int targetAddr = 0;
    int taken = 0;
    int checkBTB()
    {
        if (btbTable.find(instAddr) != btbTable.end())
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void btbInsert()
    {
        instAddr = numIns;
        targetAddr = numIns; // return vaali. change name here
        if (numInsF != numIns + 4)
        {
            taken = 1;
        }
        else
        {
            taken = 0;
        }
        btbTable.insert({instAddr, {targetAddr, taken}});
    }
};
int ls = 0;
int alu = 0;
int br = 0;

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
        string hexs = s;
        string full = HexToBin(hexs);
        // cout << full << endl;
        string opcodeString = full.substr(25, 7);
        int opcode = binaryToDecimal(opcodeString);
        // cout << opcodeString << " " << opcode << endl;

        if (opcode == 51)
        {
            alu++;
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
            alu++;
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
            ls++;
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
            ls++;
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
            br++;
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
            string immString = full[0] + imm2String + imm1String + "0";
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
            alu++;
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
            br++;
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

vector<vector<int>> ParaPast;
vector<int> Parameters{-1, -1, -1, -1, -1};
vector<int> PrevParameters{-1, -1, -1, -1, -1};
vector<int> PrevParameters3{-1, -1, -1, -1, -1};
vector<int> PrevParameters4{-1, -1, -1, -1, -1};
vector<int> PrevPrevParameters{-1, -1, -1, -1, -1};
int opcodePrev = -1;
int opcodePrevPrev = -1;
int numS = 0;
int numB = 0;
int dh = 0;
class Hazards
{
public:
    vector<vector<int>> InstrxnQueue = {{-1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1}};
    int opcode = Parameters[0];
    void UpdateIns()
    {
        vector<int> InstrxnPrev = PrevParameters;
        vector<int> InstrxnPrevPrev = PrevPrevParameters;
        // Parameters= ParaPast.back();
        InstrxnQueue[1] = InstrxnPrev;
        InstrxnQueue[0] = InstrxnPrevPrev;
        // cout<<"Prevs: "<<endl;
        // cout<<InstrxnPrev[0]<<endl;
        // cout<<InstrxnPrevPrev[0]<<endl;
        // cout << "Done" << endl;
    }

    void PrintQ()
    {
        for (auto para : InstrxnQueue)
        {
            for (auto elem : para)
            {
                cout << elem << " ";
            }
            cout << endl;
        }
    }

    vector<int> DataForwarding(int a, int b)
    {
        int fA = -1;
        int fB = -1;

        if (b == 7)
        {
            fB = 3;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Execute to Execute forwarding to both rs1 and rs2 with no stalls involved" << endl;
            return {fA, fB};
        }

        if (b == 6)
        {
            fB = 1;
            if (a == 5)
            {
                fA = 2;
                cout << "Memory to Execute forwarding to rs2 with 1 stall  of Execute" << endl;
            }
            if (a == 1)
            {
                fA = 4;
                cout << "Memory to Execute forwarding to rs2 with no stalls involved" << endl;
            }
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            return {fA, fB};
        }
        if (b == 5)
        {
            fB = 7;
            if (a == 6)
            {
                fA = 8;
                cout << "Memory to Execute forwarding to rs1 with 1 stall of Execute" << endl;
            }
            if (a == 2)
            {
                fA = 9;
                cout << "Memory to Execute forwarding to rs1 with no stalls involved" << endl;
            }
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            return {fA, fB};
        }
        if (b == 3)
        {
            fB = 10;
            cout << "FA " << fA << " ; fB " << fB << endl;
            cout << "Memory to Execute forwarding to both rs1 and rs2 with 1 stall of execute" << endl;
            return {fA, fB};
        }
        if (b == 2)
        {
            fB = 8;

            if (a == 5)
            {
                fA = 2;
                cout << "Memory to Execute forwarding to rs2 with 1 stall  of Execute" << endl;
            }

            if (a == 1)
            {
                fA = 4;
                cout << "Memory to Execute forwarding to rs2 with no stalls involved" << endl;
            }
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            return {fA, fB};
        }
        if (b == 1)
        {
            fB = 2;
            if (a == 6)
            {
                fA = 8;
                cout << "Memory to Execute forwarding to rs1 with 1 stall of Execute" << endl;
            }
            if (a == 2)
            {
                fA = 9;
                cout << "Memory to Execute forwarding to rs2 with no stalls involved" << endl;
            }
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            return {fA, fB};
        }
        if (b == 4)
        {
            fB = 8;
            cout << "Memory to Execute forwarding to rs1 with 1 stall of execute" << endl;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            return {fA, fB};
        }
        if (b == 12)
        {
            if (a == 12 || a == -1 || a == 15)
            {
                fB = 1;
                cout << "Execute to Execute forwarding to rs1 with no stall" << endl;
            }
            if (a == 11)
            {
                fA = 69;
                fB = -1;
                cout << "Decode operation is stalled one time" << endl;
            }
            if (a == 15)
            {
                fA = 69;
                fB = -1;
                cout << "Decode operation is stalled one time" << endl;
            }
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            return {fA, fB};
        }
        if (b == 11)
        {
            if (a == 11 || a == -1 || a == 14)
            {
                fB = 0;
                cout << " Memory to Memory forwarding to rs2 with no stall involved" << endl;
            }

            if (a == 12)
            {
                fA = -1;
                fB = 79;
                cout << "Decode operation is stalled two times" << endl;
            }
            if (a == 15)
            {
                fA = -1;
                fB = 79;
                cout << "Decode operation is stalled two times" << endl;
            }
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            return {fA, fB};
        }
        if (b == 13)
        {
            fA = -1;
            fB = 31;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Memory to Memory forwarding as well as Execute to Execute forwarding" << endl;
            return {fA, fB};
        }
        if (b == 15)
        {
            if (a == -1 or a == 12 or a == 15)
            {
                fB = 8;
                cout << "Memory to Execute forwarding to rs1 with 1 stall of Execute forwarding" << endl;
            }
            if (a == 11)
            {
                fB = -1;
                fA = 69;
                cout << "Decode operation is stalled one time" << endl;
            }
            if (a == 14)
            {
                fB = -1;
                fA = 69;
                cout << "Decode operation is stalled one time" << endl;
            }
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            return {fA, fB};
        }
        if (b == 14)
        {
            if (a == -1 or a == 11 or a == 14)
            {
                fB = 0;
                cout << "Memory to Memory forwarding to rs2 with no stall involved" << endl;
            }
            if (a == 12)
            {
                fB = -1;
                fA = 79;
                cout << "Decode operation is stalled two times" << endl;
            }
            if (a == 15)
            {
                fB = -1;
                fA = 79;
                cout << "Decode operation is stalled two times" << endl;
            }
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            return {fA, fB};
        }
        if (b == 16)
        {
            fA = -1;
            fB = 79;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            cout << "Decode operation is stalled two times" << endl;
            dh++;
            return {fA, fB};
        }

        if (a == 7)
        {
            fA = 16;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Memory to Execute forwarding to rs1 and rs2 with no stall involved" << endl;
            return {fA, fB};
        }
        if (a == 5)
        {
            fA = 4;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Memory to Execute forwarding to rs2 with no stalls involved" << endl;
            return {fA, fB};
        }
        if (a == 6)
        {
            fA = 17;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Memory to Execute forwarding to rs1 with no stall involved" << endl;
            return {fA, fB};
        }
        if (a == 3)
        {
            fA = 16;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Memory to Execute forwarding to rs1 and rs2 with no stall involved" << endl;
            return {fA, fB};
        }
        if (a == 1)
        {
            fA = 4;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Memory to Execute forwarding to rs2 with no stalls involved" << endl;
            return {fA, fB};
        }
        if (a == 2)
        {
            fA = 17;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Memory to Execute forwarding to rs1 and rs2 with no stall involved" << endl;
            return {fA, fB};
        }
        if (a == 4)
        {
            fA = 17;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Memory to Execute forwarding to rs1 and rs2 with no stall involved" << endl;
            return {fA, fB};
        }
        if (a == 12)
        {
            fB = -1;
            fA = 17;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Memory to Execute forwarding to rs1 and rs2 with no stall involved" << endl;
            return {fA, fB};
        }

        if (a == 11)
        {
            fB = -1;
            fA = 69;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Decode operation is stalled one time" << endl;
            return {fA, fB};
        }
        if (a == 13)
        {
            fB = -1;
            fA = 69;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Decode operation is stalled one time" << endl;
            return {fA, fB};
        }
        if (a == 15)
        {
            fB = -1;
            fA = 9;
            // cout << "FA " << fA << " ; fB " << fB << endl
            dh++;
            cout << "Memory to Execute forwarding to rs2 with no stalls involved" << endl;
            return {fA, fB};
        }
        if (a == 14)
        {
            fB = -1;
            fA = 69;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Decode operation is stalled one time" << endl;
            return {fA, fB};
        }
        if (a == 16)
        {
            fB = -1;
            fA = 69;
            // cout << "FA " << fA << " ; fB " << fB << endl;
            dh++;
            cout << "Decode operation is stalled one time" << endl;
            return {fA, fB};
        }
        // cout << "FA " << fA << " ; fB " << fB << endl;

        return {-1, -1};
    }

    int DataStalling(int a, int b)
    {
        int stall = -1;
        if (b == 7 || b == 5 || b == 6 || b == 1 || b == 2 || b == 3 || b == 4 || b == 11 || b == 12 || b == 13 || b == 14 || b == 15 || b == 16)
        {
            stall = 2;
            numB += 12;
            numS += 3;
            dh++;
            cout << "stall: " << stall << endl;
            return stall;
        }
        if (a == 5 || a == 6 || a == 7 || a == 1 || a == 2 || a == 3 || a == 4 || a == 11 || a == 12 || a == 13 || a == 14 || a == 15 || a == 16)
        {
            stall = 1;
            numB += 4;
            numS += 3;
            dh++;
            cout << "stall: " << stall << endl;
            return stall;
        }
        // cout<<"stall: "<<stall<<endl;
        return stall;
    }

    vector<int> Dependency()
    {
        UpdateIns();
        int p = -1;
        int pp = -1;
        opcodePrev = InstrxnQueue[1][0];
        opcode = Parameters[0];
        opcodePrevPrev = InstrxnQueue[0][0];
        // cout << " opcodes "<<opcode << " " << opcodePrev << " " << opcodePrevPrev << endl;
        // cout<<Parameters[0]<<endl;

        // R type after load
        if (opcodePrev == 3)
        {
            if (opcode == 51)
            {
                if (Parameters[3] == InstrxnQueue[1][1] && Parameters[4] == InstrxnQueue[1][1])
                {
                    p = 3;
                }
                else if (Parameters[3] == InstrxnQueue[1][1])
                {
                    p = 2;
                }
                else if (Parameters[4] == InstrxnQueue[1][1])
                {
                    p = 1;
                }
                // cout<<"---------------------"<<p<<"----------------------------"<<endl;
            }
        }

        // R after jal
        if (opcodePrev == -17)
        {
            if (opcode == 51)
            {
                if (Parameters[3] == InstrxnQueue[1][1] && Parameters[4] == InstrxnQueue[1][1])
                {
                    p = 3;
                }
                else if (Parameters[3] == InstrxnQueue[1][1])
                {
                    p = 2;
                }
                else if (Parameters[4] == InstrxnQueue[1][1])
                {
                    p = 1;
                }
                // cout<<"---------------------"<<p<<"----------------------------"<<endl;
            }
        }

        // R after after load
        if (opcodePrevPrev == 3)
        {
            // cout<<"HI"<<endl;
            if (opcode == 51)
            {
                // cout << "Tt" << endl;
                if (Parameters[3] == InstrxnQueue[0][1] && Parameters[4] == InstrxnQueue[0][1])
                {
                    pp = 3;
                }
                else if (Parameters[3] == InstrxnQueue[0][1])
                {
                    pp = 2;
                }
                else if (Parameters[4] == InstrxnQueue[0][1])
                {
                    pp = 1;
                }
                // cout<<"---------------------"<<pp<<"----------------------------"<<endl;
            }
        }

        // R after after jal

        if (opcodePrevPrev == -17)
        {
            // cout<<"HI"<<endl;
            if (opcode == 51)
            {
                // cout<<"Tt"<<endl;
                if (Parameters[3] == InstrxnQueue[0][1] && Parameters[4] == InstrxnQueue[0][1])
                {
                    pp = 3;
                }
                else if (Parameters[3] == InstrxnQueue[0][1])
                {
                    pp = 2;
                }
                else if (Parameters[4] == InstrxnQueue[0][1])
                {
                    pp = 1;
                }
                // cout<<"---------------------"<<pp<<"----------------------------"<<endl;
            }
        }

        // I type after load/ jal
        if (opcodePrev == 3 || opcodePrev == -17)
        {
            if (opcode == 19)
            {
                if (Parameters[3] == InstrxnQueue[1][1])
                {
                    p = 4;
                }

                // cout<<"---------------------"<<p<<"----------------------------"<<endl;
            }
        }

        // I type after after load/ jal
        if (opcodePrevPrev == 3 || opcodePrevPrev == -17)
        {
            if (opcode == 19)
            {
                if (Parameters[3] == InstrxnQueue[0][1])
                {
                    pp = 4;
                }
                // cout<<"---------------------"<<pp<<"----------------------------"<<endl;
            }
        }

        // R type after R or I
        if (opcodePrev == 51 || opcodePrev == 19)
        {
            if (opcode == 51)
            {
                if (Parameters[3] == InstrxnQueue[1][1] && Parameters[4] == InstrxnQueue[1][1])
                {
                    p = 7;
                }
                else if (Parameters[3] == InstrxnQueue[1][1])
                {
                    p = 6;
                }
                else if (Parameters[4] == InstrxnQueue[1][1])
                {
                    p = 5;
                }
                // cout<<"---------------------"<<p<<"----------------------------"<<endl;
            }
        }

        // R type after after R or I
        if (opcodePrevPrev == 51 || opcodePrevPrev == 19)
        {
            if (opcode == 51)
            {
                if (Parameters[3] == InstrxnQueue[0][1] && Parameters[4] == InstrxnQueue[0][1])
                {
                    pp = 7;
                }
                else if (Parameters[3] == InstrxnQueue[0][1])
                {
                    pp = 6;
                }
                else if (Parameters[4] == InstrxnQueue[0][1])
                {
                    pp = 5;
                }
                // cout<<"---------------------"<<pp<<"----------------------------"<<endl;
            }
        }

        // I type after R or I
        if (opcodePrev == 51 || opcodePrev == 19)
        {
            if (opcode == 19)
            {
                if (Parameters[3] == InstrxnQueue[1][1])
                {
                    p = 6;
                }
                // cout<<"---------------------"<<p<<"----------------------------"<<endl;
            }
        }

        // I type after after R or I
        if (opcodePrevPrev == 51 || opcodePrevPrev == 19)
        {
            if (opcode == 19)
            {
                if (Parameters[3] == InstrxnQueue[0][1])
                {
                    pp = 6;
                }
                // cout<<"---------------------"<<pp<<"----------------------------"<<endl;
            }
        }

        // SW after R or I
        if (opcodePrev == 51 || opcodePrev == 19)
        {
            if (opcode == 35)
            {
                if (Parameters[3] == InstrxnQueue[1][4] && Parameters[4] == InstrxnQueue[1][4])
                {
                    p = 13;
                }
                else if (Parameters[3] == InstrxnQueue[1][4])
                {
                    p = 12;
                }
                else if (Parameters[4] == InstrxnQueue[1][4])
                {
                    p = 11;
                }
                // cout<<"---------------------"<<p<<"----------------------------"<<endl;
            }
        }

        // SW type after after R or I
        if (opcodePrevPrev == 51 || opcodePrevPrev == 19)
        {
            if (opcode == 35)
            {
                if (Parameters[3] == InstrxnQueue[0][4] && Parameters[4] == InstrxnQueue[0][4])
                {
                    pp = 16;
                }
                else if (Parameters[3] == InstrxnQueue[0][4])
                {
                    pp = 15;
                }
                else if (Parameters[4] == InstrxnQueue[0][4])
                {
                    pp = 14;
                }
                // cout<<"---------------------"<<pp<<"----------------------------"<<endl;
            }
        }

        if (opcodePrev == 3 || opcodePrevPrev == -17)
        {
            if (opcode == 35)
            {
                if (Parameters[3] == InstrxnQueue[0][4] && Parameters[4] == InstrxnQueue[0][4])
                {
                    p = 16;
                }
                else if (Parameters[3] == InstrxnQueue[0][4])
                {
                    p = 15;
                }
                else if (Parameters[4] == InstrxnQueue[0][4])
                {
                    p = 14;
                }
                // cout<<"---------------------"<<pp<<"----------------------------"<<endl;
            }
        }

        if (opcodePrevPrev == 3 || opcodePrevPrev == -17)
        {
            if (opcode == 35)
            {
                if (Parameters[3] == InstrxnQueue[0][4] && Parameters[4] == InstrxnQueue[0][4])
                {
                    pp = 16;
                }
                else if (Parameters[3] == InstrxnQueue[0][4])
                {
                    pp = 15;
                }
                else if (Parameters[4] == InstrxnQueue[0][4])
                {
                    pp = 14;
                }
                // cout<<"---------------------"<<pp<<"----------------------------"<<endl;
            }
        }

        // LW after load/ jal
        if (opcodePrev == 3 || opcodePrev == -17)
        {
            if (opcode == 3)
            {
                if (Parameters[3] == InstrxnQueue[1][1])
                {
                    p = 14;
                }
                // cout<<"---------------------"<<p<<"----------------------------"<<endl;
            }
        }

        // LW after after load/ jal
        if (opcodePrevPrev == 3 || opcodePrevPrev == -17)
        {
            if (opcode == 3)
            {
                if (Parameters[3] == InstrxnQueue[0][1])
                {
                    pp = 14;
                }
                // cout<<"---------------------"<<pp<<"----------------------------"<<endl;
            }
        }

        return {pp, p};
    }

    int CheckCase(int check)
    {
        int s = 0;
        vector<int> dep = Dependency();
        if (check == 0)
        {
            s = DataStalling(dep[0], dep[1]);
        }
        else
        {
            DataForwarding(dep[0], dep[1]);
        }
        return s;
    }
};

int et = -1;
Hazards h;

// class PipelineControl
// {
//     int MemToExe = -1;
// queue<int> isFetching;
// queue<int> isDecoding;
// queue<int> isExecuting;
// queue<int> opcode;
// queue<int> function3;
// queue<int> function7;
// queue<int> executeOperations;
// queue<int> controls;
// queue<int> isMemAccess;
// queue<int> ReadfromMem;
// queue<int> WriteMem;
// queue<int> nBytes;
// queue<int> Mux_Y_Select;
// //queue<int> RM;
// //queue<int> RA;
// queue<int> ForwardOp;
// queue<int> isWriteBack;
// queue<int> rd;
// queue<int> WriteToRegisters;

// };

class Simulator
{
public:
    string prevIns = "-1";
    string prevPrevIns = "-1";
    string currIns = "-1";
    void Fetch()
    {

        // cout<<" ggggg "<<insNum<<endl;
        // i1.PrintMap();
        currIns = i1.g[insNum];
        ic.FindInCache(insNum, currIns);
        cout << "FETCHED INSTRUCTION: " << currIns << endl;
        int gian = 0;
        if (step.find(insNum) == step.end())
        {
        }
        else
        {
            gian = step[insNum];
            prevIns = i1.g[step[insNum]];
        }
        if (step.find(gian) == step.end())
        {
        }
        else
        {
            prevPrevIns = i1.g[step[step[insNum]]];
        }
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
            PrevPrevParameters = PrevParameters;
            PrevParameters = Parameters;
            Parameters = d.getParametersForInstructions(currIns);
            // for (auto elem : Parameters)
            // {
            //     cout << elem << " ";
            // }
            // cout << endl;
            // for (auto elem : PrevParameters)
            // {
            //     cout << elem << " ";
            // }
            // cout << endl;
            // for (auto elem : PrevPrevParameters)
            // {
            //     cout << elem << " ";
            // }
            // cout << "jjj" << endl;
            // for (auto para : ParaPast)
            // {
            //     for (auto elem : para)
            //     {
            //         cout << elem << " ";
            //     }
            //     cout<<endl;
            // }
            ParaPast.push_back(Parameters);
            cout << endl;
        }
    }
    Executer e;
    void Execute()
    {
        // h.UpdateIns();
        // h.PrintQ();
        // h.Dependency();
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
        // cout << "_______" << endl;
        // h.PrintQ();
        // cout<<e.immediate<<"ff"<<endl;
        insNum = m.IAG(insNum, e.immediate);
        // cout<<"ff "<<insNum<<endl;
        // m.InitMemory(i1.dataMem);
        if (insNum == (i1.numIns) * 4)
        {
            et = 0;
        }
    }
    void WriteBack()
    {
    }
};

int DFcheck = 0;
class SimulatorForward
{
public:
    string prevIns = "-1";
    string prevPrevIns = "-1";
    string currIns = "-1";
    void Fetch()
    {

        // cout<<" ggggg "<<insNum<<endl;
        // i1.PrintMap();

        currIns = i1.g[insNum];
        ic.FindInCache(insNum, currIns);
        int gian = 0;
        if (step.find(insNum) == step.end())
        {
        }
        else
        {
            gian = step[insNum];
            prevIns = i1.g[step[insNum]];
        }
        if (step.find(gian) == step.end())
        {
        }
        else
        {
            prevPrevIns = i1.g[step[step[insNum]]];
        }
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
            PrevPrevParameters = PrevParameters;
            PrevParameters = Parameters;
            Parameters = d.getParametersForInstructions(currIns);
            // for (auto elem : Parameters)
            // {
            //     cout << elem << " ";
            // }
            // cout << endl;
            // for (auto elem : PrevParameters)
            // {
            //     cout << elem << " ";
            // }
            // cout << endl;
            // for (auto elem : PrevPrevParameters)
            // {
            //     cout << elem << " ";
            // }
            // cout << "jjj" << endl;
            // for (auto para : ParaPast)
            // {
            //     for (auto elem : para)
            //     {
            //         cout << elem << " ";
            //     }
            //     cout<<endl;
            // }
            ParaPast.push_back(Parameters);
            // cout << endl;
        }
    }
    Executer e;
    void Execute()
    {

        // h.PrintQ();
        h.CheckCase(DFcheck);
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
        // cout << "_______" << endl;
        // h.PrintQ();
        // cout<<e.immediate<<"ff"<<endl;
        insNum = m.IAG(insNum, e.immediate);
        // cout<<"ff "<<insNum<<endl;
        // m.InitMemory(i1.dataMem);
        if (insNum == (i1.numIns) * 4)
        {
            et = 0;
        }
    }
    void WriteBack()
    {
    }
};

class StallRiscSim
{
public:
    queue<int> isFetching;
    queue<int> isDecoding;
    queue<int> isExecuting;
    queue<int> opcode;
    queue<int> function3;
    queue<int> function7;
    queue<int> executeOperations;
    queue<int> controls;
    queue<int> isMemAccess;
    queue<int> ReadfromMem;
    queue<int> WriteMem;
    queue<int> nBytes;
    queue<int> Mux_Y_Select;
    // queue<int> RM;
    // queue<int> RA;
    queue<int> ForwardOp;
    queue<int> isWriteBack;
    queue<int> rd;
    queue<int> WriteToRegisters;
    int func7Int, func3Int, rs1Int, rs2Int, rdInt, opcodeInt, immediateInt;
    /*void print(queue<int> q)
    {
        queue<int> g = q;
        while (!g.empty())
        {
            cout << '\t' << g.front();
            g.pop();
        }
        cout << '\n';
    }*/
    void GetParameters()
    {

        vector<int> TempParameters = Parameters;
        if (TempParameters.front() == 51)
        {
            func7Int = TempParameters.back();
            TempParameters.pop_back();
            rs2Int = TempParameters.back();
            TempParameters.pop_back();
            rs1Int = TempParameters.back();
            TempParameters.pop_back();
            func3Int = TempParameters.back();
            TempParameters.pop_back();
            rdInt = TempParameters.back();
            TempParameters.pop_back();
            opcodeInt = TempParameters.back();
            TempParameters.pop_back();
        }

        if (TempParameters.front() == 19)
        {
            immediateInt = TempParameters.back();
            TempParameters.pop_back();
            rs1Int = TempParameters.back();
            TempParameters.pop_back();
            func3Int = TempParameters.back();
            TempParameters.pop_back();
            rdInt = TempParameters.back();
            TempParameters.pop_back();
            opcodeInt = TempParameters.back();
            TempParameters.pop_back();
        }

        if (TempParameters.front() == 3)
        {
            immediateInt = TempParameters.back();
            TempParameters.pop_back();
            rs1Int = TempParameters.back();
            TempParameters.pop_back();
            func3Int = TempParameters.back();
            TempParameters.pop_back();
            rdInt = TempParameters.back();
            TempParameters.pop_back();
            opcodeInt = TempParameters.back();
            TempParameters.pop_back();
        }

        if (TempParameters.front() == 35)
        {
            rs2Int = TempParameters.back();
            TempParameters.pop_back();
            rs1Int = TempParameters.back();
            TempParameters.pop_back();
            func3Int = TempParameters.back();
            TempParameters.pop_back();
            immediateInt = TempParameters.back();
            TempParameters.pop_back();
            opcodeInt = TempParameters.back();
            TempParameters.pop_back();
        }

        if (TempParameters.front() == -29)
        {
            // cout << TempParameters[0] << endl;
            // cout << TempParameters[1] << endl;
            // cout << TempParameters[2] << endl;
            // cout << TempParameters[3] << endl;
            // cout << TempParameters[4] << endl;
            rs2Int = TempParameters.back();
            TempParameters.pop_back();
            rs1Int = TempParameters.back();
            TempParameters.pop_back();
            func3Int = TempParameters.back();
            TempParameters.pop_back();
            immediateInt = TempParameters.back();
            // cout << immediate << "   lkjj" << endl;
            TempParameters.pop_back();
            opcodeInt = TempParameters.back();
            TempParameters.pop_back();
            // cout << opcode << endl;
        }

        if (TempParameters.front() == 55)
        {
            immediateInt = TempParameters.back();
            TempParameters.pop_back();
            rdInt = TempParameters.back();
            TempParameters.pop_back();
            opcodeInt = TempParameters.back();
            TempParameters.pop_back();
        }

        if (TempParameters.front() == -17)
        {
            immediateInt = TempParameters.back();
            TempParameters.pop_back();
            rdInt = TempParameters.back();
            TempParameters.pop_back();
            opcodeInt = TempParameters.back();
            TempParameters.pop_back();
        }
        // cout << "srsmgetParameters" << opcodeInt << " " << func3Int << " " << rs1Int << " " << rs2Int << " " << func7Int << " " << immediateInt << " " << rdInt << endl;
    }
};

StallRiscSim srsm;

class SimulatorStall
{
public:
    string prevIns = "-1";
    string prevPrevIns = "-1";
    // string prevIns3="-1";
    // string prevIns4="-1";
    string currIns = "-1";
    string prevIns3 = "-1";
    string prevIns4 = "-1";
    int in = 0;
    int st = -1;

    void Fetch()
    {
        if (st == -1)
        {
            // cout << " ggggg " << insNum << endl;
            in++;
            cout << "CURRENTLY FETCHED INSTRUCTION: " << in << endl;

            // i1.PrintMap();

            currIns = i1.g[insNum];
            int gian = 0;
            ic.FindInCache(insNum, currIns);

            if (step.find(insNum) == step.end())
            {
            }
            else
            {
                gian = step[insNum];
                prevIns = i1.g[step[insNum]];
            }
            if (step.find(gian) == step.end())
            {
            }
            else
            {
                prevPrevIns = i1.g[step[step[insNum]]];
            }
            if (step.find(step[step[insNum]]) == step.end())
            {
            }
            else
            {
                prevIns3 = i1.g[step[step[step[insNum]]]];
            }
            if (step.find(step[step[step[insNum]]]) == step.end())
            {
            }
            else
            {
                prevIns4 = i1.g[step[step[step[step[insNum]]]]];
            }
            // cout << currIns << endl;

            // insNum += 4;
        }
        else
        {
            cout << "STILL FETCHED INSTRUCTION: " << in << endl;
        }
    }
    vector<int> ControlSig;
    vector<int> reqs;

    void Decode()
    {
        Decoder d;

        if (st == -1)
        {

            cout << "CURRENTLY DECODING INSTRUCTION" << endl;
            if (currIns != "-1")
            {
                PrevParameters4 = PrevParameters3;
                PrevParameters3 = PrevPrevParameters;
                PrevPrevParameters = PrevParameters;
                PrevParameters = Parameters;
                Parameters = d.getParametersForInstructions(currIns);
                srsm.GetParameters();
            }
            // cout << "PARAMETERS" << endl;
            // for (auto elem : Parameters)
            // {
            //     cout << elem << " ";
            // }
            // cout << endl;
            // cout << "PREV" << endl;
            // for (auto elem : PrevParameters)
            // {
            //     cout << elem << " ";
            // }
            // cout << endl;
            // cout << "PREV2" << endl;
            // for (auto elem : PrevPrevParameters)
            // {
            //     cout << elem << " ";
            // }
            // cout << endl;
            // cout << "PREV3" << endl;
            // for (auto elem : PrevParameters3)
            // {
            //     cout << elem << " ";
            // }
            // cout << endl;
            // cout << "PREV4" << endl;
            // for (auto elem : PrevParameters4)
            // {
            //     cout << elem << " ";
            // }
            // cout << endl;
            // cout << "jjj" << endl;
            // cout << endl;
            ParaPast.push_back(Parameters);

            cout << endl;
            st = h.CheckCase(DFcheck);
            // cout << "st: " << st << endl;
        }
        else
        {
            cout << "STILL DECODED INSTRUCTION" << endl;
            st--;
        }
    }

    Executer e;
    void Execute()
    {
        h.UpdateIns();
        // h.PrintQ();
        if (st == -1)
        {
            cout << "EXECUTING INSTRUCTION" << endl;
            // cout << "Here" << endl;
            // for (auto para : ParaPast)
            // {
            //     for (auto elem : para)
            //     {
            //         cout << elem << " ";
            //     }
            //     cout << endl;
            // }
            // cout<<"Done"<<endl;
            if (Parameters.size() != 0)
            {
                e.identifyParameters(Parameters);
                ControlSig = e.ALU_COntrol_Generator();
                reqs = e.GetRSPC();
                // cout << e.aout << endl;
            }
        }
        else
        {
            cout << "EXECUTE STALLED" << endl;
        }
    }
    void Memory()
    {
        // int aout, rs1, rs2, rd, immediate, numBytes, RA, PC, RB;
        // bool RF_Write = false, MuxB_select = false, MuxY_select = false, MuxMA_select = false, MuxINC_select = false, MuxPC_select = false, Mem_Read = false, Mem_Write = false;

        if (st == -1)
        {
            m.GetControls(ControlSig);
            // cout << "_______" << endl;
            // h.PrintQ();
            // cout<<e.immediate<<"ff"<<endl;
            insNum = m.IAG(insNum, e.immediate);
            // cout<<"ff "<<insNum<<endl;
            // m.InitMemory(i1.dataMem);
            if (insNum == (i1.numIns) * 4)
            {
                et = 0;
            }
            cout << "ACCESSING MEMORY IF REQUIRED" << endl;
        }
        else
        {
            cout << "MEMORY STALLED" << endl;
        }
    }
    void WriteBack()
    {
        if (st == -1)
        {
            cout << "WRITE BACK TO REGISTERS IF REQUIRED" << endl;
        }
        else
        {
            cout << "WRITEBACK STALLED" << endl;
        }
    }
};

SimulatorForward sf;
SimulatorStall ss;
int main()
{
    i1.TakeInstructionsToMap();
    i1.TakeDataToMap();
    i1.PrintMap();
    int PCheck = 0;
    cout << "Do you want to use pipelining?" << endl;
    cin >> PCheck;
    int RCheck = 0;
    cout << "Do you want to see register values at end of every cycle?" << endl;
    cin >> RCheck;
    if (PCheck == 0)
    {
        Simulator s;
        int i = 0;
        while (i < 160)
        {
            cout << endl;
            cout << "-----------------------------CLOCK " << i << "-------------------------------------" << endl;
            s.Fetch();
            cout << "-----------------------------CLOCK " << i + 1 << "-------------------------------------" << endl;
            s.Decode();
            cout << "INSTRUCTION DECODED" << endl;
            cout << "-----------------------------CLOCK " << i + 2 << "-------------------------------------" << endl;
            s.Execute();
            cout << "INSTRUCTION EXECUTED" << endl;
            cout << "-----------------------------CLOCK " << i + 3 << "-------------------------------------" << endl;
            s.Memory();
            cout << "CHECKING IF MEMORY ACCESS REQUIRED" << endl;
            cout << "-----------------------------CLOCK " << i + 4 << "-------------------------------------" << endl;
            s.WriteBack();
            cout << "WITING BACK TO REGISTER FILE REQUIRED" << endl;
            i += 5;
            cout << "-----------********* STATISTICS ************-------------------" << endl;

            cout << "Number of instructions: " << i1.g.size() << endl;
            cout << "Number of Data-transfer (load and store) instructions executed: " << ls << endl;
            cout << "Number of ALU instructions executed: " << alu << endl;
            cout << "Number of Control instructions executed: " << br << endl;
            cout << "Number of cycles: " << i << endl;
            cout << "CPI: " << (double)(i) / ParaPast.size() << endl;
            cout << "Number of stalls/ bubbles: " << numB << endl;
            cout << "Number of data hazards: " << dh << endl;
            // cout<<"Number of branch hazards: "<<bh<<endl;
            cout << "Number of stalls due to data hazards: " << numB << endl;
            cout << "Total number of accesses for instructions: " << numhitsins + nummissins << endl;
            cout << "Number of instruction hits: " << numhitsins << endl;
            cout << "Number of instruction misses: " << nummissins << endl;
            cout << "Total Hit latency for instruction: " << hitlatencyins << endl;
            cout << "Total Miss latency for instruction: " << misslatencyins << endl;
            cout << "Total number of data accesses: " << numhitsdata + nummissdata << endl;
            cout << "Number of data hits: " << numhitsdata << endl;
            cout << "Number of data misses: " << nummissdata << endl;
            cout << "Total data Hit latency: " << hitlatencydata << endl;
            cout << "Total data Miss latency: " << misslatencydata << endl;
            cout << "Number of cold data misses: " << colddata << endl;
            cout << "Number of cold instruction misses: " << coldins << endl;
            cout << "Number of conflict instruction misses: " << capacityins << endl;
            cout << "Number of conflict data misses: " << capacitydata << endl;
            cout << "Number of capacity instruction misses: " << nummissins - coldins - capacityins << endl;
            cout << "Number of capacity data misses: " << nummissdata - colddata - capacitydata << endl;

            cout << endl;
            if (RCheck == 1)
            {
                cout << "REGISTER VALUES-----------" << endl;
                r.PrintAllRegisters();
                cout << endl;
                cout << "DATA VALUES------------" << endl;
                i1.PrintData();
            }

            // for (auto itr = step.begin(); itr != step.end(); ++itr)
            // {
            //     cout << itr->first << '\t' << itr->second << '\n';
            // }
        }
    }
    else
    {
        cout << "Do you want to use forwarding?" << endl;
        cin >> DFcheck;
        // Simulator s;

        if (DFcheck == 1)
        {

            int i = 0;
            while (i < 160)
            {
                cout << endl;
                cout << "-----------------------------CLOCK " << i << "-------------------------------------" << endl;
                sf.Fetch();
                cout << "INSTRUCTION FETCHED: " << i << endl;
                // cout << "-----------------------------CLOCK " << i+1 << "-------------------------------------" << endl;
                sf.Decode();
                cout << "INSTRUCTION DECODED: " << endl;
                // cout << "-----------------------------CLOCK " << i+2 << "-------------------------------------" << endl;
                sf.Execute();
                cout << "INSTRUCTION EXECUTED: " << endl;
                // cout << "-----------------------------CLOCK " << i+3 << "-------------------------------------" << endl;
                sf.Memory();
                cout << "MEMORY ACCESSED IF NECESSARY " << endl;
                // cout << "-----------------------------CLOCK " << i+4 << "-------------------------------------" << endl;
                sf.WriteBack();
                cout << "WRITTEN BACK TO REGISTER IF NECESSARY" << endl;
                // cout<<"Number of instructions: "<<ParaPast.size()<<endl;
                cout << endl;
                if (RCheck == 1)
                {
                    cout << "REGISTER VALUES-----------" << endl;
                    r.PrintAllRegisters();
                    cout << endl;
                    cout << "DATA VALUES------------" << endl;
                    i1.PrintData();
                }

                i++;
                cout << "-----------********* STATISTICS ************-------------------" << endl;

                cout << "Number of instructions: " << i1.g.size() << endl;
                cout << "Number of Data-transfer (load and store) instructions executed: " << ls << endl;
                cout << "Number of ALU instructions executed: " << alu << endl;
                cout << "Number of Control instructions executed: " << br << endl;
                cout << "Number of cycles: " << ParaPast.size() + 3 << endl;
                cout << "CPI: " << (double)(ParaPast.size() + 3) / ParaPast.size() << endl;
                cout << "Number of stalls/ bubbles: " << numB << endl;
                cout << "Number of data hazards: " << dh << endl;
                cout << "Number of stalls due to data hazards: " << numB << endl;
                cout << "Total number of accesses of instruction: " << numhitsins + nummissins << endl;
                cout << "Number of hits of instruction: " << numhitsins << endl;
                cout << "Number of misses of instruction: " << nummissins << endl;
                cout << "Total Hit latency of instruction: " << hitlatencyins << endl;
                cout << "Total Miss latency of instruction: " << misslatencyins << endl;
                cout << "Total number of data accesses: " << numhitsdata + nummissdata << endl;
                cout << "Number of data hits: " << numhitsdata << endl;
                cout << "Number of data misses: " << nummissdata << endl;
                cout << "Total data Hit latency: " << hitlatencydata << endl;
                cout << "Total data Miss latency: " << misslatencydata << endl;
                cout << "Number of cold data misses: " << colddata << endl;
                cout << "Number of cold instruction misses: " << coldins << endl;
                cout << "Number of conflict instruction misses: " << capacityins << endl;
                cout << "Number of conflict data misses: " << capacitydata << endl;
                cout << "Number of capacity instruction misses: " << nummissins - coldins - capacityins << endl;
                cout << "Number of capacity data misses: " << nummissdata - colddata - capacitydata << endl;

                cout << endl;
                // for (auto itr = step.begin(); itr != step.end(); ++itr)
                // {
                //     cout << itr->first << '\t' << itr->second << '\n';
                // }
            }
        }

        else if (DFcheck == 0)
        {

            int i = 0;
            while (i < 160)
            {
                cout << endl;
                // cout<<ending<<endl;
                cout << "-----------------------------CLOCK " << i << "-------------------------------------" << endl;
                ss.Fetch();
                ss.Decode();
                ss.Execute();
                ss.Memory();
                ss.WriteBack();
                cout << "-----------********* STATISTICS ************-------------------" << endl;

                cout << "Number of instructions: " << i1.g.size() << endl;
                cout << "Number of Data-transfer (load and store) instructions executed: " << ls << endl;
                cout << "Number of ALU instructions executed: " << alu << endl;
                cout << "Number of Control instructions executed: " << br << endl;
                cout << "Number of cycles: " << i + 3 << endl;
                cout << "CPI: " << (double)(i + 3) / ParaPast.size() << endl;
                cout << "Number of stalls/ bubbles: " << numB << endl;
                cout << "Number of data hazards: " << dh << endl;
                cout << "Number of stalls due to data hazards: " << numB << endl;
                cout << "Total number of instruction accesses: " << numhitsins + nummissins << endl;
                cout << "Number of instruction hits: " << numhitsins << endl;
                cout << "Number of instruction misses: " << nummissins << endl;
                cout << "Total instruction Hit latency: " << hitlatencyins << endl;
                cout << "Total instruction Miss latency: " << misslatencyins << endl;
                cout << "Total number of data accesses: " << numhitsdata + nummissdata << endl;
                cout << "Number of data hits: " << numhitsdata << endl;
                cout << "Number of data misses: " << nummissdata << endl;
                cout << "Total data Hit latency: " << hitlatencydata << endl;
                cout << "Total data Miss latency: " << misslatencydata << endl;
                cout << "Number of cold data misses: " << colddata << endl;
                cout << "Number of cold instruction misses: " << coldins << endl;
                cout << "Number of conflict instruction misses: " << capacityins << endl;
                cout << "Number of conflict data misses: " << capacitydata << endl;
                cout << "Number of capacity instruction misses: " << nummissins - coldins - capacityins << endl;
                cout << "Number of capacity data misses: " << nummissdata - colddata - capacitydata << endl;

                cout << endl;
                if (RCheck == 1)
                {
                    cout << "REGISTER VALUES-----------" << endl;
                    r.PrintAllRegisters();
                    cout << endl;
                    cout << "DATA VALUES------------" << endl;
                    i1.PrintData();
                }

                i++;
                // for (auto itr = step.begin(); itr != step.end(); ++itr)
                // {
                //     cout << itr->first << '\t' << itr->second << '\n';
                // }
            }
        }
    }
}
