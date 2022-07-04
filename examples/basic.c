#include <stdio.h>
#include <stdlib.h>
#include "../pathutil.h"

int main() {
  char *path = path_join(3, path_cwd(), ".git", "hooks");
  printf("%s\n", path);
  path_print_files_and_directories(path);
  free(path);
  return 0;
}
