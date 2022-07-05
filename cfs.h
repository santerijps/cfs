#ifndef CFS_H

  #define CFS_H

  #ifndef _INC_STDIO
    #include <stdio.h>
  #endif

  #ifndef _INC_STDLIB
    #include <stdlib.h>
  #endif

  #ifndef _INC_STRING
    #include <string.h>
  #endif

  #ifndef _DIRENT_H_
    #include <dirent.h>
  #endif

  #ifndef _STDBOOL_H
    #include <stdbool.h>
  #endif

  #ifndef _UNISTD_H
    #include <unistd.h>
  #endif

  #ifndef _STDARG_H
    #include <stdarg.h>
  #endif

  #define PATH_MAX_LEN 100

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

  _Bool fs_path_exists(const char *path) {
    return access(path, F_OK) == 0;
  }

  char* fs_path_join(int argc, ...) {
    va_list vl;
    char *arg, *path;
    int i, len;

    path = NULL;
    len = 0;
    va_start(vl, argc);

    for (i = 0; i < argc; i++) {
      arg = va_arg(vl, char*);
      len += strlen(arg);

      if (path == NULL)  {
        path = (char*) malloc(sizeof(char) * len);
        memset(path, 0, len);
        strcat(path, arg);
      }

      else {
        len += 1;
        path = (char*) realloc(path, len);
        #ifdef _WIN32
          strcat(path, "\\");
        #else
          strcat(path, "/");
        #endif
        strcat(path, arg);
      }

    }

    va_end(vl);
    return path;
  }

  char* fs_cwd(void) {
    char *path = (char*) malloc(sizeof(char) * PATH_MAX_LEN);
    return getcwd(path, PATH_MAX_LEN);
  }

  char* fs_home_dir(void) {
    #ifdef _WIN32
      return getenv("USERPROFILE");
    #else
      return getenv("HOME");
    #endif
  }

  void fs_print_files_and_directories(const char *path) {
    DIR *dir;
    struct dirent *de;
    dir = opendir(path);
    while (dir) {
      de = readdir(dir);
      if (de == NULL) return;
      printf("%s\n", de->d_name);
    }
    closedir(dir);
  }

  _Bool fs_create_file(const char *path) {
    FILE *f;
    f = fopen(path, "w");
    if (f != NULL) {
      fclose(f);
      return true;
    }
    else {
      return false;
    }
  }

  _Bool fs_remove_file(const char *path) {
    return remove(path) == 0;
  }

  _Bool fs_write_file(const char *path, const char *data) {
    FILE *f;
    f = fopen(path, "w");
    if (f != NULL) {
      fwrite(data, sizeof(char), strlen(data), f);
      fclose(f);
      return true;
    }
    else {
      return false;
    }
  }

  char* fs_read_file(const char *path) {
    FILE *f = fopen(path, "r");
    size_t bytes_read, cap = BUFSIZ * 4, len = 0;
    char *data = NULL, buf[BUFSIZ];

    if (f != NULL) {

      while (!feof(f)) {
        memset(buf, 0, BUFSIZ);
        bytes_read = fread(buf, sizeof(char), BUFSIZ, f);

        if (data == NULL) {
          data = (char*) malloc(sizeof(char) * cap);
          memset(data, 0, cap);
        }

        len += bytes_read;

        if (len >= cap) {
          cap *= 2;
          data = (char*) realloc(data, cap);
        }

        strcat(data, buf);
      }

      fclose(f);
    }
    return data;
  }

  int fs_create_dir(const char *path) {
    return mkdir(path) == 0;
  }

  int fs_remove_dir(const char *path) {
    return rmdir(path) == 0;
  }

#endif