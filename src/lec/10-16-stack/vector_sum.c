#include <stdio.h>

// vector_sum: takes two same-length vectors (double[])
// adds them together component-wise in a new array
// vector_sum({ 1.2, 3.4 }, {-1.0, 3.6 }) => { 0.2, 7.0 }
// Assume the vectors have the same length

// Q: What happens if double[] is used as a return type?
// double[] vector_sum(double vec1[], double vec2[]);

// Q: What about using double* as return type?
// double* vector_sum(double vec1[], double vec2[])

// Pass in length as an argument. Maybe now we've got it!
double* vector_sum(double* v1, double* v2, int len) {
  double res[len];
  printf("v1@%p : %p\tv2@%p : %p\tres: %p\n",
            &v1,  v1,   &v2,  v2,     res);
  for(int i = 0; i < len; i += 1) { res[i] = v1[i] + v2[i]; }
  return res;
}
int main() {
  double vec1[] = { 1.3, 4.2 }, vec2[] = { 1.5, -1 };
  double* res1 = vector_sum(vec1, vec2, 2);

  double vec3[] = { 333, 222 }, vec4[] = { 9000, 1000 };
  double* res2 = vector_sum(vec3, vec4, 2);

  printf("res1[0]: %f\t res2[0]: %f\n", res1[0], res2[0]);

  printf("vec1: %p\n", vec1);
  printf("vec2: %p\n", vec2);
  printf("vec3: %p\n", vec3);
  printf("vec4: %p\n", vec4);
  printf("res1: %p\n", res1);
  printf("res2: %p\n", res1);
}
