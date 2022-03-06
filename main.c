#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "You have to specify program mode (fifo, lifo, "
                    "linked_list, doubly_linked_list).");
    exit(-1);
  }

  char *mode = argv[1];

  if (strcmp(mode, "lifo") == 0) {
    present_lifo();
  } else if (strcmp(mode, "fifo") == 0) {
    present_fifo();
  } else if (strcmp(mode, "linked_list") == 0) {
    present_linked_list();
  } else if (strcmp(mode, "doubly_linked_list") == 0) {
    present_doubly_linked_list();
  } else {
    fprintf(stderr, "Wrong program mode. Available ones are (fifo, lifo, "
                    "linked_list, doubly_linked_list).");
    exit(-1);
  }

  return 0;
}
