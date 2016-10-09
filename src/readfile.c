#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  FILE *f = fopen("/home/dsv/projects/mem_alloc_test/src/pages/contacts.html", "rb");
  fseek(f, 0, SEEK_END);
  long pos = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *bytes = malloc(pos);
  fread(bytes, pos, 1, f);
  fclose(f);

  printf("%s\n", bytes);
  return 0;
}
