#include <stdio.h>
#include <stdlib.h>

struct Elem {
    int linie;    
    int coloana;        
    struct Elem* next; 
};

typedef struct Elem ListNode;

struct Element {
    ListNode *head;         
    struct Element* next; 
};

typedef struct Element StackNode;

void push(StackNode **top, ListNode *head);
void afisare_stiva_invers(ListNode *head, FILE* scriere);
void afisare_stiva(StackNode *top, int *nrGen, FILE* scriere);
void deleteStack(StackNode **top);
void implementare_reguli_stiva(char **mat, int K, int N, int M, StackNode **top, FILE *scriere);
void adaugare_element_lista(ListNode **head, int linie, int coloana);