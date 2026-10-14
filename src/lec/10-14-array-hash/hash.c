#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void print_sha256(const void *data, size_t length)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(data, length, hash);

    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }

    putchar('\n');
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40};
    const char text[] = "funkyfish";

    print_sha256(numbers, sizeof(numbers));
    print_sha256(text, strlen(text));

    return 0;
}
