#include "types.h"
#include "stat.h"
#include "user.h"

extern void *mmap(int size);


int main(void) {
    int size =   4096*4; // Map 4 pages of memory
    char *add = (char *)mmap(size);

    if (add == 0) {
        printf(1, "mmap failed\n");
        exit();
    }

    printf(1, "mmap succeeded: starting address = %p\n", add);

    // Check virtual and physical page counts after mmap
    printf(1, "After mmap:\n");
    printf(1, "Number of virtual pages: %d\n", numvp());
    printf(1, "Number of physical pages: %d\n", numpp());
	char * addr=(char*)add;
    // Access the first page to trigger a page fault
    printf(1, "Accessing the first page...\n");
    addr[0] = 'A';
    printf(1, "First page accessed: %c\n", addr[0]);

    // Check page counts after accessing the first page
    printf(1, "After accessing the first page:\n");
    printf(1, "Number of virtual pages: %d\n", numvp());
    printf(1, "Number of physical pages: %d\n", numpp());

    // Access the third page to trigger another page fault
    printf(1, "Accessing the third page...\n");
    addr[4096 * 2] = 'B';
    printf(1, "Third page accessed: %c\n", addr[4096 * 2]);

    // Check page counts after accessing the third page
    printf(1, "After accessing the third page:\n");
    printf(1, "Number of virtual pages: %d\n", numvp());
    printf(1, "Number of physical pages: %d\n", numpp());

    // Access the last page to trigger another page fault
    printf(1, "Accessing the last page...\n");
    addr[4096 * 3] = 'C';
    printf(1, "Last page accessed: %c\n", addr[4096 * 3]);

    // Final page count verification
    printf(1, "After accessing all mapped pages:\n");
    printf(1, "Number of virtual pages: %d\n", numvp());
    printf(1, "Number of physical pages: %d\n", numpp());
    exit();
}
