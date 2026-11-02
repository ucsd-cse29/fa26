#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t length;
} String;

String string_new(char *str) {
    String s;
    s.length = 10; 
    s.str = malloc(10);

    if (s.str == NULL) {
      // DO SMART THINGS - FAIL NICELY
    }

    // s.str <- on the heap

    // Q1: Can I just strcat into newly malloc'ed heap?
    s.str[0] = 0;
    strcpy(s.str, str);
    return s;
}

void string_concat(String a, String b) {
    int catlen = strlen(a.str) + strlen(b.str);
    char* ptr;

    // Yay! Room in the varstr
    if (catlen < a.length) {
      strcat(a.str, b.str);
      return;
    }

    // TODO There is not enough room
    // in the String `a` to hold the concat str
    else {
      ptr = malloc(a.length * 2);
      ptr[0] = 0; // make 0 length string
      strcat(ptr, a.str);
      strcat(ptr, b.str);
    }
}

int main(void) {
    String hello = string_new("Hello, ");
    String world = string_new("world! Happy Halloween");
    string_concat(hello, world);

    printf("%s (length %zu)\n", hello.str, hello.length);

    //free(hello.str);
    //free(world.str);
    //free(message.str);
}
