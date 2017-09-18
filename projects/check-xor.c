/*
 * XOR-based checksum over two files
*/

#include <stdio.h>

char checksum(FILE *fp);

int
main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <filename1> <filename2>\n", argv[0]);
    return 1;
  }

  FILE *fp1, *fp2;

  fp1 = fopen(argv[1], "r");
  fp2 = fopen(argv[2], "r");

  if (fp1 == NULL || fp2 == NULL) {
    fprintf(stderr, "Unable to open file.");
    return 1;
  }
  
  if (checksum(fp1) != checksum(fp2)) {
    printf("Checksum failed. File has been modified.\n");
    fclose(fp1);
    fclose(fp2);
    return 1;
  }
  else {
    printf("Checksum success.\n");
    fclose(fp1);
    fclose(fp2);
    return 0;
  }
}

char checksum(FILE *fp) {
  char initial = 'a';
  char buffer;

  while (fread(&buffer, 1, 1, fp) != 0) {
    initial ^= buffer; 
  }

  return initial;
}
