#include <stdio.h>
#include <stdbool.h>

bool isDigit(char c)
{
    if (c >= '0' && c <='9')
        return true;
    else
        return false;
}

char *getNextInt(char *ptr, int *v)
{
    int sum = 0;
    
    // Skip anything that is not a digit until we hit EOL or a digit
    while(*ptr != '\0' && !isDigit(*ptr))
        ++ptr;
    
    // If there is no integer, return NULL
    if (*ptr == '\0')
        return NULL;
    
    // Otherwise, calculate the value
    while(*ptr != '\0' && isDigit(*ptr))
    {
        sum = sum*10 + *ptr - '0';
        ++ptr;
    }
    
    // Return the sum and the pointer to the rest of the string
    *v = sum;
    return ptr;
}

int lineSum(char *line)
{
    int v, min = 0, max = 0;
    int ii = 0;
    
    while (line = getNextInt(line, &v))
    {
        // First time around, min and max are the value
        if (ii == 0)
            min = max = v;
        else
        // Later we update min and max by comparison with the value
        {
            min = (v<min)?v:min;
            max = (v>max)?v:max;
        }
        
        ++ii;
    }
    
    return max - min;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s <string>, where <string> is a spreadsheet of integers\n", argv[0]);
        return 1;
    }

    char *ptr = argv[1];
    int sum = 0;
    bool done = false;
    
    // Splitting the input into lines and processing them one by one
    while (!done)
    {
        char *line = ptr;
        
        while (*ptr != '\n' && *ptr != '\0')
            ++ptr;
        
        if (*ptr == '\0')
            done = true;
        
        *ptr = '\0';
        sum += lineSum(line);
        ++ptr;
    }
        
    printf("Sum: %d\n", sum);
    return 0;
}
