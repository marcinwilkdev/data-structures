#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers.h"

DoublyLinkedList new_doubly_linked_list() {
  DoublyLinkedList dll = {
      .head = NULL,
      .size = 0,
  };

  return dll;
}

void insert_last_dll(DoublyLinkedList *list, int value) {
  DLLNode *new_node_pointer = malloc(sizeof(DLLNode));

  if (list->head == NULL) {
    DLLNode new_node = {
        .value = value,
        .next = new_node_pointer,
        .before = new_node_pointer,
    };

    *new_node_pointer = new_node;

    list->head = new_node_pointer;
  } else {
    DLLNode *last_node_pointer = list->head->before;

    DLLNode new_node = {
        .value = value,
        .next = list->head,
        .before = last_node_pointer,
    };

    *new_node_pointer = new_node;

    last_node_pointer->next = new_node_pointer;

    list->head->before = new_node_pointer;
  }

  list->size++;
}

int get_value_dll(DoublyLinkedList *list, int index) {
  if (list->head == NULL) {
    fprintf(stderr, "Doubly linked list empty. Quitting...");
    exit(-1);
  }

  index %= list->size;

  DLLNode *node = list->head;

  if (index < list->size / 2) {
    for (int i = 0; i < index; i++) {
      node = node->next;
    }
  } else {
    for (int i = 0; i < list->size - index; i++) {
      node = node->before;
    }
  }

  return node->value;
}

void merge_dll(DoublyLinkedList *first_dll, DoublyLinkedList *second_dll) {
  first_dll->size += second_dll->size;

  if (first_dll->head == NULL) {
    first_dll->head = second_dll->head;
    return;
  }

  if (second_dll->head == NULL) {
    return;
  }

  DLLNode *first_dll_last_node = first_dll->head->before;
  DLLNode *second_dll_last_node = second_dll->head->before;

  first_dll->head->before = second_dll_last_node;
  first_dll_last_node->next = second_dll->head;

  second_dll->head->before = first_dll_last_node;
  second_dll_last_node->next = first_dll->head;
}

void benchmark_doubly_linked_list(DoublyLinkedList *dll) {
  double measurements[1000][3];

  for (int i = 0; i < 1000; i++) {
    clock_t start = clock();

    int value = get_value_dll(dll, 100);

    clock_t stop = clock();

    double measure_100 = ((double)stop - start) / CLOCKS_PER_SEC * 1000;

    start = clock();

    value = get_value_dll(dll, 500);

    stop = clock();

    double measure_500 = ((double)stop - start) / CLOCKS_PER_SEC * 1000;

    start = clock();

    value = get_value_dll(dll, 900);

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

  printf("\nDoubly linked list's 100th element access time: %.3fms",
         sum_100 / 1000);
  printf("\nDoubly linked list's 500th element access time: %.3fms",
         sum_500 / 1000);
  printf("\nDoubly linked list's 900th element access time: %.3fms",
         sum_900 / 1000);
}

void present_doubly_linked_list() {
  DoublyLinkedList dll = new_doubly_linked_list();

  for (int i = 0; i < 1000; i++) {
    insert_last_dll(&dll, i);
  }

  for (int i = 0; i < 1000; i++) {
    int value = get_value_dll(&dll, i);
    printf("Value index %d from doubly linked list is %d\n", i, value);
  }

  printf("\n");

  DoublyLinkedList first_dll = new_doubly_linked_list();

  for (int i = 0; i < 500; i++) {
    insert_last_dll(&first_dll, i);
  }

  DoublyLinkedList second_dll = new_doubly_linked_list();

  for (int i = 500; i < 1000; i++) {
    insert_last_dll(&second_dll, i);
  }

  printf("Merging doubly linked lists with values 0..500 and 500..1000\n");

  merge_dll(&first_dll, &second_dll);

  int value = get_value_dll(&first_dll, 100);
  printf("100th value from merged doubly linked lists is %d\n", value);

  value = get_value_dll(&first_dll, 500);
  printf("500th value from merged doubly linked lists is %d\n", value);

  value = get_value_dll(&first_dll, 900);
  printf("900th value from merged doubly linked lists is %d\n", value);

  benchmark_doubly_linked_list(&dll);
}
