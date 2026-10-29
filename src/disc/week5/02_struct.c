/* #include <sys/types.h>  // pid_t */
/* #include <unistd.h>     // fork(), getpid(), etc */
#include <stdio.h> // printf
#include <stdint.h> // uint32_t 

#define MAX_ARGS 5

// 9 bytes
// 16 bytes
//
typedef struct SimpleStruct {
    int y;     // 4 bytes
    char *ptr; // 8 bytes
    uint32_t x;// 4 bytes
} SimpleStruct;

// 24 bytes
// 28
// 21
// 53
typedef struct ComplexStruct {
    char *ptr; // 8 bytes
    char *args[MAX_ARGS]; // 8 * 5 = 40 bytes 
    uint32_t ret; // 4 bytes -> 8 bytes
    char some_char; // 1 bytes -> 8 bytes 
} ComplexStruct;
// 9 + 40 + 4 + 7 + 4 = 64


typedef struct __attribute__((packed)) {
    char some_char; // 1 bytes -> 8 bytes 
    char *ptr; // 8 bytes
    char *args[MAX_ARGS]; // 8 * 5 = 40 bytes 
    uint32_t ret; // 4 bytes -> 8 bytes
} PackedStruct;

typedef struct {
    char* str;
} StringStruct;

int main(){
    printf("sizeof(SimpleStruct) = %lu\n", sizeof(SimpleStruct));
    printf("sizeof(ComplexStruct) = %lu\n", sizeof(ComplexStruct));
    printf("sizeof(PackedStruct) = %lu\n", sizeof(PackedStruct));

    StringStruct x;
    x.str = "hello";
    // 8 b
    // 9
    // 53 again?
    // 
    printf("sizeof(StringStruct) = %lu\n", sizeof(StringStruct));
}

