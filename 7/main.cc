#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <algorithm>

// From https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "usage: " << argv[0] << " <string>, where <string> is a list of tree nodes and their children" << std::endl;
        return 1;
    }
    
    /*
     * The solution is based around the idea that tha base node is the only
     * node that is never found in as a child of another node.
     * 
     * We simply collect an unordered set of nodes and another unordered set 
     * of child nodes. Then we look for a node that is not in the childrens 
     * list. This must be the base node.
     */
    
    std::istringstream allLines(argv[1]);
    std::string line;
    std::unordered_set<std::string> nodes, children;
    
    // Split argument into lines and extract nodes from each line
    while (std::getline(allLines, line, '\n'))
    {
        auto pos = line.find("->");                 // Split on "->", if found
        if (pos != std::string::npos)
        {
            std::string right = line.substr(pos+2); // Right side
            line = line.substr(0, pos);             // Left side
            
            while ((pos = right.find(",")) != std::string::npos)
            {
                std::string child = right.substr(0, pos);
                right.erase(0, pos+1);
                trim(child);
                children.insert(child);
            }
            
            // Don't forget the last child
            trim(right);
            children.insert(right);
        }
        
        line = line.substr(0, line.find("("));      // Remove (...
        trim(line);                                 // Trim away white space
        nodes.insert(line);
    }
    
    if (nodes.size() - children.size() != 1)
    {
        std::cout << "Unexpected input, no bottom program found" << std::endl;
        return 1;
    }
    
    auto node = nodes.begin();
    while (node != nodes.end())
    {
        if (children.find(*node) == children.end())
        {
            std::cout << "Bottom program: '" << *node << "'" << std::endl;
            return 0;
        }
        
        ++node;
    }
    
    std::cerr << "Unexpected input, no bottom program found in loop" << std::endl;
    return 1;
}
