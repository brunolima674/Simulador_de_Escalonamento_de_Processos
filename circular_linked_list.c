#include <stdio.h>
#include <stdlib.h>
#include "circular_linked_list.h"

typedef struct node node_t;

struct node {
    int code;
    int initial_entry_time;
    int quantum_needed;
    int priority;
    node_t *next;
};

struct list {
    node_t *beginning;
    node_t *end;
    int size;
};

// funcao que cria uma lista
list_t *create() {
    list_t *l = (list_t *) malloc(sizeof(list_t));

    if (l != NULL) {
        l->beginning = NULL;
        l->end = NULL;
        l->size = 0;
    }

    return l;
}

// funcao que insere um elemento no comeco da lista
int insert_at_beginning(list_t *list, int value, int initial_time, int quantum, int priority) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    // se o noh criado for diferente de nulo
    if (new_node != NULL) {
        // copia todas as informacoes para o noh
        new_node->code = value;
        new_node->initial_entry_time = initial_time;
        new_node->quantum_needed = quantum;
        new_node->priority = priority;

        // o próximo aponta para o início da lista
        new_node->next = list->beginning;
        // new_node se torna o início da lista
        list->beginning = new_node;
        // se o final da lista for nulo (list vazia), end aponta para new_node
        if(list->end == NULL) {
            list->end = new_node;
        }
        // end aponta para início
        list->end->next = list->beginning;
        // atualiza o tamanho da lista
        list->size++;

        return 1;
    }

    return 0;
}

// funcao que insere um elemento no final da lista
int insert_at_end(list_t *list, int value, int initial_time, int quantum, int priority) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    // se o noh criado for diferente de nulo
    if (new_node != NULL) {
        // copia todas as informacoes para o noh
        new_node->code = value;
        new_node->initial_entry_time = initial_time;
        new_node->quantum_needed = quantum;
        new_node->priority = priority;

        // se a lista estiver vazia
        if (list->beginning == NULL) {
            // noh inicial recebe o novo noh
            list->beginning = new_node;
            // noh final que eh igual o inicial recebe o novo noh
            list->end = new_node;
            // o proximo do ultimo noh aponta para o comeco
            list->end->next = list->beginning;
        } else {
            // se a lista nao estiver vazia
            // o proximo noh do ultimo recebe o novo noh
            list->end->next = new_node;
            // atualiza o final para o novo noh
            list->end = new_node;
            // o proximo noh do ultimo aponta para o comeco
            list->end->next = list->beginning;
        }
        // atualiza o tamanho da lista
        list->size++;

        return 1;
    }

    return 0;
}

// funcao que insere um elemento anteriormente a outro, passado no parametro (next_node)
int insert_before_elem(list_t *l, node_t *node, node_t *next_node) {
    // cria um noh auxiliar apontando para o comeco da lista
    node_t *aux = l->beginning;
    // o proximo noh da onde deve ser inserido o noh desejado
    // nao for o primeiro da lista
    if (next_node != l->beginning) {
        // enquanto o proximo do aux nao encontrar o next_node
        while (aux->next != next_node) {
            // avanca aux
            aux = aux->next;
        }
        // atualiza o proximo de aux para o noh desejado
        aux->next = node;
        // e atualiza o proximo do noh inserido para o next_node
        node->next = next_node;
        // atualiza o tamanho da lista
        l->size++;

        return 1;
    } else if (next_node == l->beginning) {
        // caso contrario, se deseja inserir um elemento anteriormente ao primeiro
        // entao insere esse elemento na primeira posicao
        insert_at_beginning(l, node->code, node->initial_entry_time, node->quantum_needed, node->priority);
        return 0;
    }

    return -1;
}

// funcao que insere um elemento de forma ordenada
int insert_ordered(list_t *list, int value, int initial_time, int quantum, int priority) {
    // aloca espaco para o noh a ser inserido
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    // criacao de nohs auxiliares
    node_t *aux, *tmp = list->beginning;

    // se o noh criado for diferente de nulo
    if (new_node != NULL) {
        // enquanto for encontrado um codigo na lista igual ao que
        // sera inserido, vai aumentando o valor do codigo a ser inserido
        while (search(list, value) == 1) {
            value++;
        }
        // copia as informacoes para o noh a ser inserido
        new_node->code = value;
        new_node->initial_entry_time = initial_time;
        new_node->quantum_needed = quantum;
        new_node->priority = priority;

        // se a lista estiver vazia ou o tempo de entrada do novo noh
        // for menor que o tempo de entrada do primeiro noh da lista
        if (list->beginning == NULL || new_node->initial_entry_time < list->beginning->initial_entry_time) {
            // insere o novo noh no comeco da lista
            insert_at_beginning(list, value, initial_time, quantum, priority);
            return 1;

        } else {
            // caso contrario
            // aux aponta para o comeco da lista
            aux = list->beginning;

            // enquanto o proximo de aux for diferente do comeco da lista e o tempo de entrada do novo noh for
            // maior ou igual ao tempo de entrada de aux e a prioridade do novo noh for menor que a prioridade de aux
            while (aux->next != list->beginning && new_node->initial_entry_time >= aux->initial_entry_time && new_node->priority < aux->priority) {
                // avanca aux
                aux = aux->next;
            }

            // se o tempo de entrada do novo noh for maior ou igual a tempo de entrada onde o aux parou
            // e a prioridade do novo noh for menor que a prioridade de aux
            if (new_node->initial_entry_time >= aux->initial_entry_time && new_node->priority < aux->priority) {
                // insere o elemento no final da lista
                insert_at_end(list, value, initial_time, quantum, priority);
                return 1;

            // se o tempo de entrada do novo noh for maior ou igual a tempo de entrada onde o aux parou
            // e a prioridade do novo noh for maior ou igual a prioridade de aux
            } else if (new_node->initial_entry_time >= aux->initial_entry_time && new_node->priority >= aux->priority) {
                // se as prioridade sao iguais
                if (new_node->priority == aux->priority) {
                    // entao, compara os codigos, se o codigo do novo noh for menor
                    if (new_node->code < aux->code) {
                        // insere o novo noh anteriormente a aux
                        insert_before_elem(list, new_node, aux);
                        return 1;
                    } else {
                        // caso contrario avanca aux
                        aux = aux->next;
                        // e insere o elemento anteriormente a aux
                        insert_before_elem(list, new_node, aux);
                        return 1;
                    }
                } else {
                    // se a prioridade do novo noh for maior
                    // insere ele anteriormente a aux
                    insert_before_elem(list, new_node, aux);
                    return 1;
                }

            } else {
                // insere o novo noh anteriormente a aux
                insert_before_elem(list, new_node, aux);
                return 1;
            }
        }
    }

    return 0;
}

// funcao para remover um noh (processo)
node_t *remove_node(list_t *list, int value) {
    // noh auxiliar e o noh que sera retornado que foi removido
    node_t *aux, *remove = NULL;

    // se a lista nao estiver vazia
    if (list->beginning != NULL) {
        // se a lista possuir somente um elemento e o codigo
        // do processo a ser removido for o desejado
        if (list->beginning == list->end && list->beginning->code == value) {
            // noh removido sera igual ao primeiro elemento da lista
            remove = list->beginning;
            // comeco e final da lista aponta para null
            list->beginning = NULL;
            list->end = NULL;
            // reduz em 1 o tamanho da lista
            list->size--;
        } else if (list->beginning->code == value) {
            // caso a lista tenha mais de 1 processo
            // e o processo a ser removido eh o primeiro
              // o elemento a ser removido eh o primeiro da lista
              remove =  list->beginning;
              // o primeiro elemento da lista passa a ser o
              // proximo do que foi removida
              list->beginning = remove->next;
              // como a lista eh circular, o proximo do ultimo elemento
              // eh atualizado para o primeiro
              list->end->next = list->beginning;
              // atualiza o tamanho da lista
              list->size--;
        } else {
            // caso contrario, inicializa a variavel aux no inicio da lista
            aux = list->beginning;
            // enquanto o proximo noh de aux for diferente do comeco da lista e
            // o proximo noh nao eh o processo a ser removido
            while (aux->next != list->beginning && aux->next->code != value) {
                // avanca aux
                aux = aux->next;
            }
            // se encontrou no proximo noh de aux o processo a ser removido
            if (aux->next->code == value) {
                // se o noh a ser removido for o ultimo
                if (list->end == aux->next) {
                    // atualiza o noh que sera retornado que eh o elemento removido
                    remove = aux->next;
                    // atualiza o noh que sera removida para o proximo dele
                    aux->next = remove->next;
                    // atualiza o final da lista para o noh anterior do que foi removido
                    list->end = aux;
                } else {
                    // caso contrario
                    remove = aux->next;
                    aux->next = remove->next;
                }
                // atualiza o tamanho da lista
                list->size--;
            }
        }
    }

    // retorna o noh removido
    return remove;
}

// funcao para fazer a busca de um processo
int search(list_t *list, int value) {
    // cria um noh auxiliar apontando para o inicio da lista
    node_t *aux = list->beginning;

    // se aux for diferente de nulo
    if (aux != NULL) {
        // enquanto aux for diferente do comeco da lista
        do {
            // se encontrou o codigo desejado retorna
            if (aux->code == value) {
                return 1;
            }
            // avanca o aux
            aux = aux->next;
        } while (aux != list->beginning);
    }

    // se nao encontrou o codigo desejado retorna 0
    return 0;
}
