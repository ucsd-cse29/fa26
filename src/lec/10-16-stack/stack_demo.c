#include <stdint.h>
#include <stdio.h>

#define N 16

static void show_frame(
    const char *name,
    volatile int variables[N],
    const void *marker,
    const void *caller_marker
) {
    uintptr_t current = (uintptr_t)marker;
    uintptr_t caller  = (uintptr_t)caller_marker;
    uintptr_t distance =
        current > caller ? current - caller : caller - current;

    printf("%s\n", name);
    printf("  frame marker:    %p\n", marker);
    printf("  variables start: %p\n", (void *)&variables[0]);
    printf("  variables end:   %p\n", (void *)&variables[N - 1]);
    printf("  local array size: %zu bytes\n", N * sizeof(int));
    printf("  distance from caller's marker: %zu bytes\n\n",
           (size_t)distance);
}

static void level2(const void *level1_marker) {
    volatile int variables[N];
    volatile int marker = 2;

    for (int i = 0; i < N; i++) {
        variables[i] = 200 + i;
    }

    show_frame("LEVEL 2", variables, (const void *)&marker,
               level1_marker);
}

static void level1(const void *main_marker, int call_level2) {
    volatile int variables[N];
    volatile int marker = 1;

    for (int i = 0; i < N; i++) {
        variables[i] = 100 + i;
    }

    show_frame("LEVEL 1", variables, (const void *)&marker,
               main_marker);

    if (call_level2) {
        level2((const void *)&marker);
    }

    /* Use the array after level2 returns to discourage optimization. */
    printf("LEVEL 1 is finishing; variables[0] = %d\n\n",
           variables[0]);
}

int main(void) {
    volatile int marker = 0;

    printf("MAIN\n");
    printf("  frame marker: %p\n\n", (void *)&marker);

    printf("=== Calling one function ===\n\n");
    level1((const void *)&marker, 0);

    printf("=== Calling two nested functions ===\n\n");
    level1((const void *)&marker, 1);

    return 0;
}
