#include "types.h"
#include "user.h"
#include "stat.h"
// #include <stdio.h>

void growStack(int count)
{
    int arr[1024];
    printf(1, "Number of user virtual pages = %d\n", numvp());
    printf(1, "Number of user physical pages = %d\n", numpp());
    if (count == 10)
    {
        return;
    }
    growStack(count + 1);
}
int main()
{
    // int pageCount, prevPageCount = 4;
    //growStack(0);
     printf(1, "Number of user virtual pages = %d\n", numvp());
     printf(1, "Number of user physical pages = %d\n", numpp());
     int *something = malloc(sizeof(int) * 4096);
     printf(1, "Number of user virtual pages = %d\n", numvp());
     printf(1, "Number of user physical pages = %d\n", numpp());
    exit();
}
