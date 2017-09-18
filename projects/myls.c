/**
 * Simple implementation of `ls`
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>
#include <limits.h>
#include <fcntl.h>

/*
   struct dirent {
    char            d_name[256]; // Filename
    ino_t           d_ino; // Inode number
    off_t           d_off; // Offset to next dirent
    unsigned short  d_reclen; // Length of this record
    unsigned char   d_type; // Type of file
   }
*/

/* 
   struct stat {
    ...
    ino_t           st_ino; // inode number
    uid_t           st_uid; // user-id of owner
    off_t           st_size; // file size, in bytes
    ...
   }
*/

int
main(int argc, char *argv[])
{
  DIR *dp; 

  if (argc == 3) {
    dp = opendir(argv[2]);
    assert(dp != NULL);
  }
  else {
    dp = opendir(".");
    assert(dp != NULL);
  }

  struct dirent *d;

  while ((d = readdir(dp)) != NULL) {

    struct stat stat_buf;

    if (argc >= 2 && (strcmp(argv[1], "-l") == 0)) {

      int fd = openat(dirfd(dp), d->d_name, O_RDONLY);

      assert(fd >= 0);

      fstat(fd, &stat_buf);
      printf("UID: %u, size: %llu, name: %s\n", stat_buf.st_uid, stat_buf.st_size, d->d_name);

      close(fd);
    }
    else {
      printf("%lu %s\n", (unsigned long) d->d_ino, d->d_name);
    }
  }
  closedir(dp);
  return 0;
}
