#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

std::string banksToString(const std::vector<int> &banks)
{
    std::string res;
    
    for (int i=0; i<banks.size(); ++i)
        res += std::to_string(banks[i]) + std::string((i==banks.size()-1)?"":"-");
    
    return res;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "usage: " << argv[0] << " <v1> <v2> ... <vN>, where <vX> is a list memory banks with a block count" << std::endl;
        return 1;
    }
 
    std::unordered_set<std::string> knownBanks;
    std::vector<int> banks;
 
    for (int i=1; i<argc; ++i)
        banks.push_back(std::stoi(argv[i]));
    
    int count = 1;
    knownBanks.insert(banksToString(banks));
    while(true)
    {
        int max = *std::max_element(std::begin(banks), std::end(banks));
        int pos = 0;
        
        // Locate first instance of pos
        while(banks[pos] != max)
            ++pos;
        
        banks[pos] = 0;
        while(max)
        {
            ++pos;
            if (pos == banks.size())
                pos = 0;
            ++banks[pos];
            --max;
        }
        
        std::string bankString = banksToString(banks);
        if (knownBanks.find(bankString) != knownBanks.end())
            break;
        else
            knownBanks.insert(bankString);
        
        ++count;
    }
    
    std::cout << "Cycles: " << count << std::endl;
    
    return 0;
}
