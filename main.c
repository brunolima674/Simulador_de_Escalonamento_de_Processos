#include <stdio.h>
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

// funcao para simular o escalonamento de processos
void simulate(list_t *l) {
    // criacao de nohs apontando para o inicio da lista
    node_t *node = l->beginning; // noh de controle do elemento a ser processado
    node_t *aux = l->beginning; // noh de controle da prioridade
    node_t *aux1 = l->beginning; // noh auxiliar para verificar a prioridade

    // inicializando a variavel tempo = 1
    int time = 1;
    // enquanto houver elementos na lista
    while (l->size > 0) {
        do {
            // se o tempo de entrada de um processo for igual ao tempo atual
            if (aux->initial_entry_time == time) {
                // enquanto a prioridade do noh auxiliar 1 for maior que a prioridade
                // do noh auxiliar, avanca o noh aux1 para o proximo
                while (aux1->priority > aux->priority) {
                    aux1 = aux1->next;
                }
                // se o noh aux tiver maior prioridade
                if (aux->priority > aux1->priority) {
                    // remove ele da posicao atual
                    node_t *temp = remove_node(l, aux->code);
                    // se o noh aux1 continua no comeco da lista, entao a posicao
                    // correta para inserir o noh de maior prioridade eh antes do aux1
                    // consequentemente no inicio da lista
                    if (aux1 == l->beginning) {
                        insert_at_beginning(l, temp->code, temp->initial_entry_time, temp->quantum_needed, temp->priority);
                    } else {
                        // caso contrario, insere ele antes da posicao do aux1
                        insert_before_elem(l, temp, aux1);
                    }
                    // volta para o comeco da lista para continuar o processamento
                    // do elemento de maior prioridade
                    node = l->beginning;
                }
            }
            // avanca aux
            aux = aux->next;
            // seta aux1 para o comeco da lista para auxiliar na proxima comparacao de prioridade
            aux1 = l->beginning;
        } while (aux->next != l->beginning);

        // se a tempo de entrada do processo for menor ou igual ao tempo de controle
        if (node->initial_entry_time <= time) {
            // diminui 1 quantum daquele processo
            node->quantum_needed--;
        } else {
            // caso contrario, enquanto o tempo de entrada do processo for maior
            // que o tempo de controle, avanca para o proximo processo
            while (node->initial_entry_time > time) {
                node = node->next;
            }
            // quando encontrada o processo com o tempo de entrada adequado
            // diminui em 1 o quantum desse processo
            node->quantum_needed--;
        }

        // se a qtd de quantum de um processo chegar a zero
        if (node->quantum_needed == 0) {
            // imprime o processo e o tempo necessario para conclui-lo
            printf("%d %d\n", node->code, time);
            // e remove o processo da lista
            remove_node(l, node->code);
        }

        // avanca p noh para o proximo
        node = node->next;
        // aumenta o tempo de controle
        time++;
    }

}

int main() {
    // cria uma lista encadeada circular
    list_t *l = create();

    char c; // char de controle de leitura dos inputs
    int code, initial_time, quantum, priority;
    // enquando nao for lido o caracter EOF
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);

        // le os dados do input
        scanf("%d", &code);
        scanf("%d", &initial_time);
        scanf("%d", &quantum);
        scanf("%d", &priority);

        // insere as informacoes de forma ordenada de acordo
        // com a prioridade e o tempo de entrada do processo
        insert_ordered(l, code, initial_time, quantum, priority);
    }

    // faz a simulacao do escalonamento de processo para a lista l
    simulate(l);

    return 0;
}
