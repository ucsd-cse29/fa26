#include <stdio.h>
#include <stdint.h>

// int main(int argc, char* argv[]){
int main(int argc, char** argv){
    printf("sizeof(uint32_t) = %d\n",(int) sizeof(uint32_t));
    
    uint32_t var = 0; 
    printf("sizeof(var) = %d\n",(int) sizeof(var));

    uint32_t* ptr;
    printf("sizeof(ptr) = %d\n",(int) sizeof(ptr));

    uint32_t arr[5];
    printf("sizeof(arr) = %d\n",(int) sizeof(arr));
    
    printf("length of arr = %d\n", (int) (sizeof(arr) / sizeof(*arr)));

    return 0;
}
