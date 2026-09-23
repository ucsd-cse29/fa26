#include <stdio.h>

int NUM = 1000;
char HI[] = "Hi!";

int static_counter_fun() {
  static int ctr = 0; // Only happens on the first call!
  ctr += 1;
  printf("ctr:\t%d\n", ctr);
  printf("&ctr:\t%p\n", &ctr);
  return ctr;
}

int main(int argc, char** argv) {
  char hello[] = "hello everyone";
  char* ptr = hello;// could also write &hello
  char* hiptr = HI; // could also write &HI
  int* numptr = &NUM; // could NOT also write NUM
  printf("&main:\t%p\n", &main);
  printf("&main:\t%p\n", &main);
  printf("&NUM:\t%p\n", &NUM);
  printf("numptr:\t%p\n", numptr);
  printf("&HI:\t%p\n", &HI);
  printf("hiptr:\t%p\n", hiptr);
  printf("stdin:\t%p\n", &stdin);
  static_counter_fun();
  static_counter_fun();
  printf("&argv:\t%p\n", &argv);
  printf("ptr:\t%p\n", ptr);
  printf("&ptr:\t%p\n", &ptr);
  printf("&hiptr:\t%p\n", &hiptr);
  printf("hello:\t%p\n", hello);
  printf("argv:\t%p\n", argv);
  printf("argv[0]:%p\n", argv[0]);
}
