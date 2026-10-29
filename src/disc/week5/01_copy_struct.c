#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ArrayStruct {
    char data[20]; 
};

struct PointerStruct {
    char *data;
};

int main() {
    printf("PART 1:\n");
    struct ArrayStruct A1; // memory = address 0000

    strcpy(A1.data, "Original");
    
    struct ArrayStruct A2 = A1; // address 1000
    
    strcpy(A2.data, "Modified"); 
    printf("A1 contains: %s\n", A1.data);
    printf("A2 contains: %s\n\n", A2.data);

    //---------------

    printf("PART 2:\n");
    struct PointerStruct P1; // address 0000
    P1.data = malloc(20 * sizeof(char));
    strcpy(P1.data, "Original");
    
    struct PointerStruct P2 = P1; // 1000
    
    strcpy(P2.data, "Modified"); 
    
    printf("P1 contains: %s\n", P1.data);
    printf("P2 contains: %s\n", P2.data);

    free(P1.data); 

    return 0;
}
