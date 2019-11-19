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
    char cwd[1000];
    if (argc > 1) {
        strcpy(cwd, argv[1]);
    } else{
        printf("Enter a directory: \n");
        fgets(cwd, 1000, stdin);
        cwd[strlen(cwd)-1]= 0;
    }

    DIR *d;
    d = opendir(cwd);
    if (d == NULL){
        printf("%s\n", strerror(errno));
        return errno;
    }

    printf("Statistics for directory:\n");
    struct dirent *entry = readdir(d);
    int size = 0;
    while (entry != NULL) {
        struct stat file_stats;
        char directory[1000];
        strcpy(directory, cwd);
        strcpy(directory, "/");
        strcpy(directory, entry->d_name);
        if (stat(cwd, &file_stats) == -1){
            printf("errno: %s\n", strerror(errno));
            return errno;
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
