int main() {
  char a[] = "abc";
  return a[1] / 0;
  for(int i = 0; i < 10000000; i += 1) {
    a[i] = 'z';
  }
  return 37;
}
