#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

class Parser 
{
public:
    Parser(std::istringstream &stream);
    
    enum Token {
        StartOfGroup,
        EndOfGroup,
        EndOfStream
    };
    
    Token getNextToken();
    
    int garbageCount;
    
private:
    std::istringstream &m_stream;
};

Parser::Parser(std::istringstream &stream) 
    : m_stream(stream)
    , garbageCount(0)
{
}

Parser::Token Parser::getNextToken()
{
    bool inGarbage = false;
    bool isEscaped = false;
    
    char c = m_stream.get();
    do 
    {
        if (c == -1)
            return EndOfStream;

        if (inGarbage)
        {
            if (!isEscaped)
            {
                if (c == '>')
                    inGarbage = false;  // Garbage is not nested
                else if (c == '!')
                    isEscaped = true;   // The next character is escaped
                else
                    ++garbageCount;
            }
            else
                isEscaped = false;      // The escaped char has been ignored
        }
        else
        {
            if (c == '{')               // A new group begins
                return StartOfGroup;
            else if (c == '}')          // A group ends
                return EndOfGroup;
            else if (c == '<')          // Garbage begins
                inGarbage = true;
        }
        
        c = m_stream.get();
    } while (m_stream);

    return EndOfStream;                 // No more input
}

int calculateGroupScore(Parser &parser, int level=1)
{
    Parser::Token token;
    int sum = 0;
    
    do
    {
        token = parser.getNextToken();
        
        if (token == Parser::StartOfGroup)
            sum += level + calculateGroupScore(parser, level+1);
        
    } while(token != Parser::EndOfGroup && token != Parser::EndOfStream);
    
    return sum;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "usage: " << argv[0] << " <string>, where <string> is a character stream" << std::endl;
        return 1;
    }
    
    /*
     * The solution is built around a parser returning the following tokens:
     * 
     * - start-of-group
     * - end-of-group
     * - end-of-stream
     * 
     * The parser has to know if it is inside garbage or not.
     * If inside of garbage, it automatically handles the escape character "!"
     * In all cases, the non-important characters are skipped
     * 
     * The output of the parser is fed to a recursive function calculating the
     * score of each group it encounters and returning the needed sum
     */
    
    std::istringstream stream(argv[1]);
    Parser parser(stream);
    
    std::cout << "Sum: " << calculateGroupScore(parser) << std::endl;
    std::cout << "Garbage count: " << parser.garbageCount << std::endl;
    
    return 0;
}
