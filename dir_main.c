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


int main(int argc, char *argv[]) {
  DIR *d;
  if (argc > 1) {
    d = opendir(argv[1]);
  } else{
    printf("Enter a directory: \n");
    char buffer[1000];
    fgets(buffer, 1000, stdin);
    buffer[strlen(buffer)-1]= 0;
    d = opendir(buffer);
  }

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
  entry = readdir(d);
  while (entry != NULL){
    if (entry->d_type == DT_DIR){
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(d);
  }
  rewinddir(d);
  entry = readdir(d);
  printf("Regular files:\n");
  while (entry != NULL){
    if (entry->d_type == DT_REG){
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(d);
  }

  closedir(d);
  return 0;
}
