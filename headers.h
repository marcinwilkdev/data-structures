typedef struct Fifo {
  int *pointer;
  int *curr;
  unsigned int size;
  unsigned int capacity;
} Fifo;

typedef struct Lifo {
  int *pointer;
  int *begin;
  int *end;
  unsigned int size;
  unsigned int capacity;
} Lifo;

typedef struct LinkedList {
  struct LLNode *head;
  struct LLNode *tail;
} LinkedList;

typedef struct LLNode {
  int value;
  struct LLNode *next;
} LLNode;

typedef struct DoublyLinkedList {
  struct DLLNode *head;
  unsigned int size;
} DoublyLinkedList;

typedef struct DLLNode {
  int value;
  struct DLLNode *next;
  struct DLLNode *before;
} DLLNode;

Fifo new_fifo();
void reallocate_fifo(Fifo *fifo);
void push_fifo(Fifo *fifo, int value);
int pop_fifo(Fifo *fifo);
void present_fifo();

Lifo new_lifo();
void reallocate_lifo(Lifo *lifo);
void push_lifo(Lifo *lifo, int value);
int pop_lifo(Lifo *lifo);
void present_lifo();

LinkedList new_linked_list();
void push_linked_list(LinkedList *linked_list, int value);
int get_linked_list(LinkedList *linked_list, int index);
void merge_linked_list(LinkedList *first_ll, LinkedList *second_ll);
void present_linked_list();

DoublyLinkedList new_doubly_linked_list();
void insert_last_dll(DoublyLinkedList *list, int value);
int get_value_dll(DoublyLinkedList *list, int index);
void merge_dll(DoublyLinkedList *first_dll, DoublyLinkedList *second_dll);
void present_doubly_linked_list();
