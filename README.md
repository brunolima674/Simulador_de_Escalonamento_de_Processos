### Simulador_de_Escalonamento_de_Processos
# Entrada:

Os dados do arquivo de entrada definem a lista de processos a ser executada pelo simulador. Dada uma lista L de processos, cada linha de L deve conter o código **p**i de um processo, seu tempo inicial de entrada no simulador **t0**i, o volume de quantum necessário para ser completamente executado **tf**i, e o nível de prioridade do processo **r**i.

   Exemplo:
   
   (int)**p**0 (int)**t0**0 (int)**tf**0 (int)**r**0
              
# Saída:

O simulador exibe, como saída, o tempo **tf**i em que o processo **p**i tem sua execução finalizada.

   Exemplo:

   (int)**p**i (int)**tf**i
   
O algoritmo utilizado para simular o escalonador de processos é similar ao *Round Robin*, que utiliza uma lista encadeada circular para ir atualizando o quantum de cada processo.
