#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"

Fifo new_fifo() {
  unsigned int capacity = 16;
  int *pointer = malloc(capacity * sizeof(int));
  int *curr = pointer;
  unsigned int size = 0;

  Fifo fifo = {
      .pointer = pointer,
      .curr = curr,
      .size = size,
      .capacity = capacity,
  };

  return fifo;
}

void reallocate_fifo(Fifo *fifo) {
  unsigned int new_capacity = fifo->capacity * 2;
  int *new_pointer = malloc(new_capacity * sizeof(int));

  memcpy(new_pointer, fifo->pointer, fifo->size * sizeof(int));
  free(fifo->pointer);

  long curr_placement = fifo->curr - fifo->pointer;

  fifo->pointer = new_pointer;
  fifo->capacity = new_capacity;
  fifo->curr = fifo->pointer + curr_placement;
}

void push_fifo(Fifo *fifo, int value) {
  if (fifo->size == fifo->capacity) {
    reallocate_fifo(fifo);
  }

  *(fifo->pointer + fifo->size) = value;
  fifo->size++;
}

int pop_fifo(Fifo *fifo) {
  if (fifo->curr - fifo->size < fifo->pointer) {
    int value = *fifo->curr;
    fifo->curr++;
    return value;
  } else {
    fprintf(stderr, "Trying to pop of empty fifo! Quitting...");
    exit(-1);
  }
}

void present_fifo() {
  Fifo fifo = new_fifo();

  for (int i = 0; i < 100; i++) {
    printf("Adding %d to fifo.\n", i);
    push_fifo(&fifo, i);
  }

  for (int i = 0; i < 100; i++) {
    int value = pop_fifo(&fifo);

    printf("Popped %d from fifo\n", value);
  }

  printf("\n");
}
