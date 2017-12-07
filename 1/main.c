#include <stdio.h>
#include <stdbool.h>

bool isDigit(char c)
{
    if (c >= '0' && c <='9')
        return true;
    else
        return false;
}

int countDigits(char *str)
{
    int digits = 0;
    
    while(*str != '\0')
    {
        if (isDigit(*str))
            digits ++;

        str ++;
    }
    
    return digits;
}

int nextDigit(char *str, int pos)
{
    while(!isDigit(str[pos]))
    {
        if (str[pos] == '\0')
            pos = 0;
        else
            pos ++;
    }
        
    return pos;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s <string>, where <string> is a string where consecutive digits are counted\n", argv[0]);
        return 1;
    }
    
    int sum = 0;
    if (countDigits(argv[1]) > 1)
    {
        int current, firstDigit;
        firstDigit = current = nextDigit(argv[1], 0);
        do {
            int next = nextDigit(argv[1], current+1);
            if (argv[1][current] == argv[1][next])
                sum += argv[1][current] - '0';
            current = next;
        } while (current != firstDigit);
    }
    
    printf("Sum: %d\n", sum);
    return 0;
}
