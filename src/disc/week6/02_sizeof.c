#include <stdio.h>

void print_size(int arr[]) {
    printf("  inside function: sizeof(arr) = %zu\n", sizeof(arr));
}

int main(void) {
    int small[3];
    int big[100];

    printf("in main: sizeof(small) = %zu\n", sizeof(small));
    print_size(small);

    printf("in main: sizeof(big)   = %zu\n", sizeof(big));
    print_size(big);

    return 0;
}
