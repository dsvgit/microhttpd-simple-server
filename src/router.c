#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "router.h"

char * get_page(const char * url) {
  char * page = NULL;

  if (0 == strcmp(url, "/") || 0 == strcmp(url, "/home")) {
    page = get_template("/home.html");
  } else if (0 == strcmp(url, "/contacts")) {
    page = get_template("/contacts.html");
  }

  if (page == NULL) page = get_template("/forbidden.html");

  return page;
}

char * get_template(char * url) {
  printf("asdf\n");
  char result_url[256] = "/home/dsv/projects/mem_alloc_test/src/templates";
  FILE *f = fopen(strcat(result_url, url), "rb");
  fseek(f, 0, SEEK_END);
  long pos = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *bytes = malloc(pos);
  fread(bytes, pos, 1, f);
  fclose(f);

  printf("%s\n", bytes);
  return bytes;
}
