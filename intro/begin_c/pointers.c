#include <stdio.h>

int main() {
    int x,y;
    int *ptr_p;

    x = 5;
    ptr_p = &x; // Address of integer "x" - ptr_p now assigned address of "x"
    printf("ptr_p is assigned address of x: %p\n", ptr_p);
    y = *ptr_p; // Dereference the pointer
                // Access the value of the integer being pointed to
    printf("y is assigned to \"x\" via dereferencing the pointer: %d\n", y);
    // We can also change the integer by dereferencing the pointer on assignment:
    y = 3;
    printf("reassigning y=3: %d\n", y);
    printf("What is x? %d\n", x);

    *ptr_p = 10;
    printf("Reassign x by dereferencing pointer and assigning to 10, %d\n", x);
    return 0;
}
