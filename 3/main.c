#include <stdio.h>
#include <stdlib.h>

int countStepsRecursive(int v, int l)
{
    int side = l*2-1;               // length of a side for level l
    
    int circumference = 1;           // special case for first level
    if (l > 1)
        circumference = side*4-4;    // length of the circumference
    else if (v == 1)                 // special case for the first node
        return 0;

    /* 
     * If the value is inside the circumference of the current level, calculate
     * how far from the center.
     * 
     * We do this in three stages:
     * 
     * (1) Calculate the position along each edge using the modulus operation.
     *     This gives us a value, 0 - (side-1). As the first value is 1, the
     *     order is shifted so that the first value is in the right position,
     *     second from the bottom
     * 
     * (2) Subtract the value, so that zero is the middle of the edge
     * 
     * (3) Get the absolute value.
     * 
     * The result is the distance from the center (calculated above, plus the 
     * number of steps from the middle, given by the level argument, l.
     */
    if (v <= circumference)
    {
        v = v % (side-1); // (1)
        v = v - l + 1;    // (2)
        if (v < 0)        // (3)
            v = -v;
        return v+l-1;
    }
    else
    {
        return countStepsRecursive(v-circumference, l+1);
    }
}

int countSteps(int v)
{
    return countStepsRecursive(v, 1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s <n>, where <n> is an integer and >0\n", argv[0]);
        return 1;
    }
    
    int v = atoi(argv[1]);
    
    if (v <= 0 )
    {
        printf("The value argument must be >0\n");
        return 1;
    }
    
    printf("Data from square %d is carried %d steps\n", v, countSteps(v));
    
    return 0;
}
