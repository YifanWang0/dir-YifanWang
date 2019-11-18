#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>


int main() {

  DIR *d;
  d = opendir(".");
  if (d == NULL){
    printf("%s\n", strerror(errno));
    return 0;
  }

  printf("Statistics for directory: .\n");
  struct dirent *entry = readdir(d);
  int size = 0;
  while (entry != NULL){
    struct stat file_stats;
    if (stat(entry->d_name, &file_stats) == -1){
      printf("%s\n", strerror(errno));
      return 0;
    }
    size += file_stats.st_size;
    entry = readdir(d);
  }
  printf("Total Directory Size: %d Bytes\n", size);

  printf("Directories:\n");
  rewinddir(d);
  while (entry != NULL){
    if (entry->d_type == DT_DIR){
      printf("HIIIIIIIII\n");
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(d);
  }
  rewinddir(d);
  printf("Regular files:\n");
  while (entry != NULL){
    if (entry->d_type == DT_REG){
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(d);
  }

  return 0;
}