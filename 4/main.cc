#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "usage: " << argv[0] << " <string>, where <string> is a string with words" << std::endl;
        return 1;
    }
    
    std::istringstream allLines(argv[1]);
    std::string line;
    int count = 0;
    
    // Split argument into lines and work on each line
    while (std::getline(allLines, line, '\n'))
    {
        /*
         * Keep an unordered set of known words
         * If a given word is in the set, the line is not valid
         * Add new words to the set, until the line ends
         */
        std::unordered_set<std::string> knownWords;
        std::istringstream words(line);
        bool valid = true;

        do 
        {
            std::string word;
            words >> word;
            
            if (word.empty())
                break;
            
            if (knownWords.find(word) != knownWords.end())
            {
                valid = false;
                break;
            }
            
            knownWords.insert(word);
        } while (words);
        
        if (valid)
            ++ count;
    }
    
    std::cout << "Count: " << count << std::endl;
    return 0;
}
