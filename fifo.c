#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"

Fifo new_fifo() {
  unsigned int capacity = 16;
  unsigned int size = 0;
  int *pointer = malloc(capacity * sizeof(int));
  int *begin = pointer;
  int *end = pointer;

  Fifo fifo = {
      .pointer = pointer,
      .begin = begin,
      .end = end,
      .size = size,
      .capacity = capacity,
  };

  return fifo;
}

void advance_fifo_begin(Fifo *fifo) {
  fifo->begin++;

  if (fifo->begin >= (fifo->pointer + fifo->capacity)) {
    fifo->begin = fifo->pointer;
  }
}

void advance_fifo_end(Fifo *fifo) {
  fifo->end++;

  if (fifo->end >= (fifo->pointer + fifo->capacity)) {
    fifo->end = fifo->pointer;
  }
}

void push_fifo(Fifo *fifo, int value) {
  if (fifo->size == fifo->capacity) {
    reallocate_fifo(fifo);
  }

  *fifo->end = value;
  fifo->size++;

  advance_fifo_end(fifo);
}

int pop_fifo(Fifo *fifo) {
  if (fifo->size == 0) {
    fprintf(stderr, "Can't pop of empty lifo. Quitting...");
    exit(-1);
  }

  int value = *fifo->begin;

  advance_fifo_begin(fifo);

  fifo->size--;

  return value;
}

void reallocate_fifo(Fifo *fifo) {
  int new_capacity = fifo->capacity * 2;

  int *new_pointer = malloc(new_capacity * sizeof(int));

  for (int i = 0; i < fifo->capacity; i++) {
    *(new_pointer + i) = pop_fifo(fifo);
  }

  free(fifo->pointer);

  fifo->pointer = new_pointer;
  fifo->begin = new_pointer;
  fifo->end = new_pointer + fifo->capacity;
  fifo->size = fifo->capacity;
  fifo->capacity = new_capacity;
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
