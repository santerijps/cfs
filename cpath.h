#ifndef CPATH_H

  #define CPATH_H

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

  _Bool path_exists(const char *path);
  char* path_join(int argc, ...);
  char* path_cwd(void);
  void path_print_files_and_directories(const char *path);

  _Bool path_exists(const char *path) {
    return access(path, F_OK) == 0;
  }

  char* path_join(int argc, ...) {
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

  char* path_cwd(void) {
    char *path = (char*) malloc(sizeof(char) * PATH_MAX_LEN);
    return getcwd(path, PATH_MAX_LEN);
  }

  void path_print_files_and_directories(const char *path) {
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

#endif