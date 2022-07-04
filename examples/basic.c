#include <stdio.h>
#include <stdlib.h>
#include "../cfs.h"

int main() {
  char *path = fs_path_join(3, fs_cwd(), ".git", "hooks");
  printf("%s\n", path);
  fs_print_files_and_directories(path);
  free(path);
  fs_create_file("hello.txt");
  getchar();
  fs_remove_file("hello.txt");
  fs_write_file("world.txt", "Hello, world!\n");
  char *s = fs_read_file("cfs.h");
  printf("%s\n", s);
  fs_create_dir("hello");
  getchar();
  fs_remove_dir("hello");
  return 0;
}
