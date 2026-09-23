#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double *data;
  int size;
} DoubleList;

typedef int (*Predicate)(double);

void list_append(DoubleList *list, double val);
void list_print(DoubleList *list);
DoubleList list_filter(DoubleList *list, Predicate pred);

int is_less_70(double val) { return val < 70.0; }
DoubleList filter_less_70(DoubleList *list) {
  DoubleList result = { NULL, 0 };
  for (int i = 0; i < list->size; i++) {
    if (is_less_70(list->data[i])) {
      list_append(&result, list->data[i]);
    }
  }
  return result;
}

int is_integer(double val) { return val == (int)val; }
DoubleList filter_is_integer(DoubleList *list) {
  DoubleList result = { NULL, 0 };
  for (int i = 0; i < list->size; i++) {
    if (is_integer(list->data[i])) {
      list_append(&result, list->data[i]);
    }
  }
  return result;
}

int is_unit(double val) { return val >= 0.0 && val <= 1.0; }
DoubleList filter_unit(DoubleList *list) {
  DoubleList result = { NULL, 0 };
  for (int i = 0; i < list->size; i++) {
    if (is_unit(list->data[i])) {
      list_append(&result, list->data[i]);
    }
  }
  return result;
}

void list_examples() {
  DoubleList d = { NULL, 0 };
  list_append(&d, 68.5);
  list_append(&d, 72.0);
  list_append(&d, 0.5);
  list_append(&d, 99.0);
  // How to call each filter function? What's the expected result for each?



}

void list_examples_pred() {
  DoubleList d = { NULL, 0 };
  list_append(&d, 68.5);
  list_append(&d, 72.0);
  list_append(&d, 0.5);
  list_append(&d, 99.0);
  // How to call list_filter for each? What's the expected result?



}

int main() {
  list_examples();
  list_examples_pred();
}

void list_append(DoubleList *list, double val) {
  list->data = realloc(list->data, (list->size + 1) * sizeof(double));
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

DoubleList list_filter(DoubleList *list, Predicate pred) {
  DoubleList result = { NULL, 0 };
  for (int i = 0; i < list->size; i++) {
    if (pred(list->data[i])) {
      list_append(&result, list->data[i]);
    }
  }
  return result;
}
