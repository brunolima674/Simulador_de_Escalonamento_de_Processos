#ifndef SIMULADOR_DE_ESCALONAMENTO_DE_PROCESSOS_CIRCULAR_LINKED_LIST_H
#define SIMULADOR_DE_ESCALONAMENTO_DE_PROCESSOS_CIRCULAR_LINKED_LIST_H

typedef struct list list_t;
typedef struct node node_t;

list_t *create();

int insert_at_beginning(list_t *list, int value, int initial_time, int quantum, int priority);

int insert_at_end(list_t *list, int value, int initial_time, int quantum, int priority);

int insert_ordered(list_t *list, int value, int initial_time, int quantum, int priority);

int insert_before_elem(list_t *l, node_t *node, node_t *next_node);

node_t *remove_node(list_t *list, int value);

int search(list_t *list, int value);

#endif //SIMULADOR_DE_ESCALONAMENTO_DE_PROCESSOS_CIRCULAR_LINKED_LIST_H
