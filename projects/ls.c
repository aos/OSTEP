#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>

/*
   struct dirent {
    char            d_name[256]; // Filename
    ino_t           d_ino; // Inode number
    off_t           d_off; // Offset to next dirent
    unsigned short  d_reclen; // Length of this record
    unsigned char   d_type; // Type of file
   }
*/

int
main(int argc, char *argv[])
{
  DIR *dp = opendir(".");
  assert(dp != NULL);

  struct dirent *d;
  struct stat buf;

  while ((d = readdir(dp)) != NULL) {

    if (argc == 2 && (strcmp(argv[1], "l") == 0)) {
      int fd = dirfd(dp);
      assert(fd != -1);

      fstat(fd, &buf);
      printf("UID: %lu, size: %lu, name: %s\n", (unsigned long) buf.st_uid, (unsigned long) buf.st_size, d->d_name);
    }
    else {
      printf("%lu %s\n", (unsigned long) d->d_ino, d->d_name);
    }
  }
  closedir(dp);
  return 0;
}
