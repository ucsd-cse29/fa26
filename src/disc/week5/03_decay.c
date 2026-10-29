#include <stdio.h>

struct NetworkData {
    int id;
    char buffer[1024];
};

void process_data(char data_array[1024]) {
    printf("Function size: %zu\n", sizeof(data_array));
}

void process_data2(struct NetworkData x) {
    printf("Function size: %zu\n", sizeof(x.buffer));
}


int main() {
    struct NetworkData net;
    printf("Struct size: %zu\n", sizeof(net.buffer));
    process_data(net.buffer);  // 8
    process_data2(net);// 1024
}
