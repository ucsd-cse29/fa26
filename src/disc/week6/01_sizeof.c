#include <stdio.h>

int main(void) {
    printf("=================\n");
    
    // 1. will this compile? 
    size_t size = sizeof(double); 
    printf("Double size = %ld\n", size);
    printf("=================\n");

    // 2. what will this print?
    int i = 10;
    size_t s = sizeof(i++); 
    printf("Size: %zu\n", s);
    printf("i: %d\n", i); 
    printf("=================\n");
                         
    // 3. will this compile? 
    void *p1 = (void *)&printf; 
    printf("p1 = %p\n", p1);
    void *p2 = &sizeof; 
    printf("p2 = %p\n", p2);
    printf("=================\n");

    // 4. will this compile? what does it print?
    int x = 42;
    size_t s2 = sizeof(x);  
    size_t s1 = sizeof x;   
    printf("s1 = %ld, s2 = %ld\n", s1, s2);
    
    return 0;
}
