#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

#define HEAP_SIZE 4096
#define SLOT_SIZE 8
#define HEAP_SLOTS HEAP_SIZE/SLOT_SIZE

uint64_t* HEAP_START = NULL;

void init_heap() {
  if(HEAP_START != NULL) { return; }
  uint64_t* heap = sbrk(HEAP_SIZE);
  HEAP_START = heap;
  *HEAP_START = (HEAP_SIZE - 8);
}

size_t block_size(uint64_t s) { return s & (~1); }
int block_busy(uint64_t s) { return s & 1; }
size_t round_size(size_t size) { return (size + 7) & ~7; }

void* allocate_at(uint64_t* start, size_t size) {
  size_t current_size = block_size(start[0]);
  if(current_size > size) {
    uint64_t remaining = current_size - size - SLOT_SIZE;
    int next_block_index = (size / SLOT_SIZE) + 1;
    start[next_block_index] = remaining; // even, free
  }
  start[0] = size | 1; // busy
  return &start[1];
}

void* malloc(size_t requested_size) {
  init_heap();
  int val_index = 0;
  size_t rounded = round_size(requested_size);
  while(val_index < HEAP_SLOTS) {
    uint64_t curr_slot = HEAP_START[val_index];
    int current_size = block_size(curr_slot);
    int current_busy = block_busy(curr_slot);
    if(!current_busy && (current_size >= rounded)) {
      return allocate_at(&HEAP_START[val_index], rounded);
    }
    else {
      val_index += (current_size / SLOT_SIZE) + 1;
      continue;
    }
  }
  return NULL;
}

void free(void* ptr) {
  uint64_t* slot_after_header = ptr;
  slot_after_header[-1] = slot_after_header[-1] - 1;
}

void show_heap() {
    int i = 0;
    while (i < HEAP_SLOTS) {
        uint64_t w = HEAP_START[i];
        int size = block_size(w);
        printf("[%3d] %-4s  %4d bytes\t%3d slots\n", i, (w & 1) ? "BUSY" : "free", size, size / SLOT_SIZE);
        i += size / SLOT_SIZE + 1;
    }
}

int main() {
  int* a = malloc(20);
  int* b = malloc(100);
  int* c = malloc(20);
  show_heap();
  printf("\n");
  free(b);
  show_heap();
  printf("\n");
  int* d = malloc(15);
  show_heap();
}
