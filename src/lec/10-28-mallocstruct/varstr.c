#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t length;
} String;

String string_new(char *str) {
    String s;
    s.length = strlen(str);
    s.str = malloc(s.length + 1);
    s.str[0] = '\0';
    strcat(s.str, str);
    return s;
}

String string_concat(String a, String b) {
    String result;
    result.length = a.length + b.length;
    result.str = malloc(result.length + 1);

    strcpy(result.str, a.str);
    strcat(result.str, b.str);
    return result;
}

int main(void) {
    String hello = string_new("Hello, ");
    String world = string_new("world!");
    String message = string_concat(hello, world);

    printf("%s (length %zu)\n", message.str, message.length);

    free(hello.str);
    free(world.str);
    free(message.str);
}
