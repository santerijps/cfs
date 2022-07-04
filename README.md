# cfs

`cfs` is a file system utility library for the C programming language.

**NOTE!** This library cannot be build with `tcc`. Use `gcc` or `clang` instead.

## Functions

```c
_Bool path_exists(const char *path);
char* path_join(int argc, ...);
char* path_cwd(void);
void path_print_files_and_directories(const char *path);
```
