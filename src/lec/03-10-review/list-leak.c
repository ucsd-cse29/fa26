#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double *data;
  int size;
} DoubleList;

void list_append(DoubleList *list, double val);
void list_print(DoubleList *list);

int main() {
  DoubleList temps = { NULL, 0 };

  list_append(&temps, 68.5);
  list_append(&temps, 72.0);
  list_append(&temps, 65.3);

  list_print(&temps);

  free(temps.data);
}

void list_append(DoubleList *list, double val) {
  double *new_data = malloc((list->size + 1) * sizeof(double));
  memcpy(new_data, list->data, list->size * sizeof(double));
  list->data = new_data;
  list->data[list->size] = val;
  list->size++;
}

void list_print(DoubleList *list) {
  printf("[");
  for (int i = 0; i < list->size; i++) {
    if (i > 0) printf(", ");
    printf("%.1f", list->data[i]);
  }
  printf("]\n");
}
