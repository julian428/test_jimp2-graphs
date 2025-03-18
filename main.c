#include <stdio.h>

#include "lib/file-check.h"

int main(int argc, char **argv) {
  printf("Testowanie programu 'jimp2-graphs'.\n");
  int file_parity = checkFileParity("test.txt", 3, 3);
  printf("File parity sum: %d", file_parity);
}
