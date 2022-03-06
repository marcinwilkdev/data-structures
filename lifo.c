#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"

Lifo new_lifo() {
  unsigned int capacity = 16;
  int *pointer = malloc(capacity * sizeof(int));

  Lifo lifo = {
      .pointer = pointer,
      .capacity = capacity,
  };

  return lifo;
}

void reallocate_lifo(Lifo *lifo) {
  unsigned int new_capacity = lifo->capacity * 2;
  int *new_pointer = malloc(new_capacity * sizeof(int));

  memcpy(new_pointer, lifo->pointer, lifo->size * sizeof(int));
  free(lifo->pointer);

  lifo->pointer = new_pointer;
  lifo->capacity = new_capacity;
}

void push_lifo(Lifo *lifo, int value) {
  if (lifo->size == lifo->capacity) {
    reallocate_lifo(lifo);
  }

  *(lifo->pointer + lifo->size) = value;
  lifo->size++;
}

int pop_lifo(Lifo *lifo) {
  if (lifo->size > 0) {
    int value = *(lifo->pointer + lifo->size - 1);
    lifo->size--;
    return value;
  } else {
    fprintf(stderr, "Trying to pop of empty lifo! Quitting...");
    exit(-1);
  }
}

void present_lifo() {
  Lifo lifo = new_lifo();

  for (int i = 0; i < 100; i++) {
    printf("Adding %d to lifo.\n", i);
    push_lifo(&lifo, i);
  }

  for (int i = 0; i < 100; i++) {
    int value = pop_lifo(&lifo);
    printf("Popped %d from lifo\n", value);
  }

  printf("\n");
}
