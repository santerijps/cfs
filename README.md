# cfs

`cfs` is a file system utility library for the C programming language. The purpose of this library is to provide functions for common file system operations, such as reading and writing to files.

**NOTE!** This library cannot be build with `tcc`. Use `gcc` or `clang` instead.

## Functions

```c
  /**
   * Checks if a file or directory exists.
  */
  _Bool fs_path_exists(const char *path);

  /**
   * Joins all strings together with a / or a \ depending on the OS.
  */
  char* fs_path_join(int argc, ...);

  /**
   * Returns the absolute path to the current working directory.
  */
  char* fs_cwd(void);

  /**
   * Returns the absolute path to the user's home directory.
  */
  char* fs_home_dir(void);

  /**
   * Prints all files and directories in the given path.
  */
  void fs_print_files_and_directories(const char *path);

  /**
   * Creates a file. Returns 1 if successful.
  */
  _Bool fs_create_file(const char *path);

  /**
   * Removes a file. Returns 1 if successful.
  */
  _Bool fs_remove_file(const char *path);

  /**
   * Writes to a file. Creates a file if it doesn't exist.
  */
  _Bool fs_write_file(const char *path, const char *data);

  /**
   * Reads the contents of a file.
  */
  char* fs_read_file(const char *path);

  /**
   * Creates a directory.
  */
  int fs_create_dir(const char *path);

  /**
   * Removes a directory.
  */
  int fs_remove_dir(const char *path);
```
