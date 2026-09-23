#include <stdio.h>

typedef struct Grade {
  char name[20];
  int pts;
  int max_pts;
} Grade;

Grade lab(int wk, int pts) {
  Grade g = { "", pts, 4 };
  snprintf(g.name, 20, "Week %d Lab", wk);
  return g;
}

void example1() {
  Grade wk1_lab = lab(1, 4);
  Grade wk2_lab = lab(2, 4);
  Grade wk3_lab = lab(3, 1);
}


typedef struct Len32String {
  char contents[32];
} Len32String;

Len32String return_struct() {
  Len32String str_struct = { "some string content" };
  return str_struct;
}

char* return_array() {
  char str[] = "some string content";
  return str;
}

void example2() {
  char* from_array1 = return_array();
  printf("from_array1:\t%p\n", from_array1);
  char* from_array2 = return_array();
  printf("from_array2:\t%p\n", from_array2);

  Len32String from_struct1 = return_struct();
  printf("from_struct1:\t%p\n", from_struct1.contents);
  Len32String from_struct2 = return_struct();
  printf("from_struct2:\t%p\n", from_struct2.contents);
}

int main() {
  example1(); example2();
}
