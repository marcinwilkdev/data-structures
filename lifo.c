#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"

Lifo new_lifo() {
  unsigned int capacity = 16;
  unsigned int size = 0;
  int *pointer = malloc(capacity * sizeof(int));
  int *begin = pointer;
  int *end = pointer;

  Lifo lifo = {
      .pointer = pointer,
      .begin = begin,
      .end = end,
      .size = size,
      .capacity = capacity,
  };

  return lifo;
}

void advance_lifo_begin(Lifo *lifo) {
  lifo->begin++;

  if (lifo->begin >= (lifo->pointer + lifo->capacity)) {
    lifo->begin = lifo->pointer;
  }
}

void advance_lifo_end(Lifo *lifo) {
  lifo->end++;

  if (lifo->end >= (lifo->pointer + lifo->capacity)) {
    lifo->end = lifo->pointer;
  }
}

void push_lifo(Lifo *lifo, int value) {
  if (lifo->size == lifo->capacity) {
    reallocate_lifo(lifo);
  }

  *lifo->end = value;
  lifo->size++;

  advance_lifo_end(lifo);
}

int pop_lifo(Lifo *lifo) {
  if (lifo->size == 0) {
    fprintf(stderr, "Can't pop of empty lifo. Quitting...");
    exit(-1);
  }

  int value = *lifo->begin;

  advance_lifo_begin(lifo);

  lifo->size--;

  return value;
}

void reallocate_lifo(Lifo *lifo) {
  int new_capacity = lifo->capacity * 2;

  int *new_pointer = malloc(new_capacity * sizeof(int));

  for (int i = 0; i < lifo->capacity; i++) {
    *(new_pointer + i) = pop_lifo(lifo);
  }

  free(lifo->pointer);

  lifo->pointer = new_pointer;
  lifo->begin = new_pointer;
  lifo->end = new_pointer + lifo->capacity;
  lifo->size = lifo->capacity;
  lifo->capacity = new_capacity;

  printf("REALLOCATING LIFO\n");
}

void present_lifo() {
  Lifo lifo = new_lifo();

  for (int i = 0; i < 100; i++) {
    push_lifo(&lifo, i);
  }

  for (int i = 0; i < 100; i++) {
    int value = pop_lifo(&lifo);

    printf("value: %d\n", value);
  }

  printf("\n");
}
