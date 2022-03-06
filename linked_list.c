#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers.h"

LinkedList new_linked_list() {
  LinkedList linked_list = {
      .head = NULL,
      .tail = NULL,
  };

  return linked_list;
}

void push_linked_list(LinkedList *linked_list, int value) {
  LLNode *new_node_pointer = malloc(sizeof(LLNode));

  LLNode new_node = {
      .value = value,
      .next = NULL,
  };

  *new_node_pointer = new_node;

  if (linked_list->head == NULL) {
    linked_list->head = new_node_pointer;
  } else {
    LLNode *last_node = linked_list->tail;

    last_node->next = new_node_pointer;
  }

  linked_list->tail = new_node_pointer;
}

int get_linked_list(LinkedList *linked_list, int index) {
  LLNode *node = linked_list->head;

  if (node == NULL) {
    fprintf(stderr, "Linked list empty. Quitting...");
    exit(-1);
  }

  for (int i = 0; i < index; i++) {
    if (node == NULL) {
      fprintf(stderr, "Index greater than linked list size. Quitting...");
      exit(-1);
    }

    node = node->next;
  }

  return node->value;
}

void merge_linked_list(LinkedList *first_ll, LinkedList *second_ll) {
  LLNode *last_node = first_ll->head;

  while (last_node->next != NULL) {
    last_node = last_node->next;
  }

  last_node->next = second_ll->head;
}

void bechmark_linked_list(LinkedList *linked_list) {
  double measurements[1000][3];

  for (int i = 0; i < 1000; i++) {
    clock_t start = clock();

    int value = get_linked_list(linked_list, 100);

    clock_t stop = clock();

    double measure_100 = ((double)stop - start) / CLOCKS_PER_SEC * 1000;

    start = clock();

    value = get_linked_list(linked_list, 500);

    stop = clock();

    double measure_500 = ((double)stop - start) / CLOCKS_PER_SEC * 1000;

    start = clock();

    value = get_linked_list(linked_list, 900);

    stop = clock();

    double measure_900 = ((double)stop - start) / CLOCKS_PER_SEC * 1000;

    measurements[i][0] = measure_100;
    measurements[i][1] = measure_500;
    measurements[i][2] = measure_900;
  }

  double sum_100 = 0.0;
  double sum_500 = 0.0;
  double sum_900 = 0.0;

  for (int i = 0; i < 1000; i++) {
    sum_100 += measurements[i][0];
    sum_500 += measurements[i][1];
    sum_900 += measurements[i][2];
  }

  printf("\nLinked list's 100th element access time: %.3fms", sum_100 / 1000);
  printf("\nLinked list's 500th element access time: %.3fms", sum_500 / 1000);
  printf("\nLinked list's 900th element access time: %.3fms", sum_900 / 1000);
}

void present_linked_list() {
  LinkedList linked_list = new_linked_list();

  for (int i = 0; i < 1000; i++) {
    push_linked_list(&linked_list, i);
  }

  for (int i = 0; i < 1000; i++) {
    int value = get_linked_list(&linked_list, i);
    printf("Value index %d from linked list is %d\n", i, value);
  }

  printf("\n");

  LinkedList first_linked_list = new_linked_list();

  for (int i = 0; i < 500; i++) {
    push_linked_list(&first_linked_list, i);
  }

  LinkedList second_linked_list = new_linked_list();

  for (int i = 500; i < 1000; i++) {
    push_linked_list(&second_linked_list, i);
  }

  printf("Merging linked lists with values 0..500 and 500..1000\n");

  merge_linked_list(&first_linked_list, &second_linked_list);

  int value = get_linked_list(&first_linked_list, 100);
  printf("100th value from merged linked lists is %d\n", value);

  value = get_linked_list(&first_linked_list, 500);
  printf("500th value from merged linked lists is %d\n", value);

  value = get_linked_list(&first_linked_list, 900);
  printf("900th value from merged linked lists is %d\n", value);

  bechmark_linked_list(&linked_list);
}
