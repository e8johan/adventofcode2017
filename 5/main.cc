#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "usage: " << argv[0] << " <values>, where <values> is a list of jump offsets" << std::endl;
        return 1;
    }

    std::vector<int> values;        // Holds the jump table
    
    // Populate the jump table
    std::istringstream lines(argv[1]);
    while (lines)
    {
        std::string value;
        lines >> value;
        if (value.empty())
            break;
        values.push_back(std::stoi(value));
    }

    // Current position and step counter
    int pos = 0;
    int count = 0;
    
    // Run jump algorithm
    while (pos >= 0 && pos < values.size())
    {
        ++values[pos];              // Increase current position
        pos += values[pos]-1;       // Make the jump, based on the unincreased value

        ++count;
    }
    std::cout << "Steps: " << count << std::endl;
    return 0;
}
