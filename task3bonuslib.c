#include "task1lib.h"
#include "task2lib.h"
#include "task3bonuslib.h"

void populare_stiva(StackNode **top, int K, FILE *f){
    /*FILE *f=fopen("task3bonus.txt", "rt");
    if(f==NULL){
        printf("Eroare la deschiderea fisierului.");
        exit(1);
    }*/
    int linie, coloana;
    ListNode *head=NULL;
    for(int i=0; i<K; i++){
        fscanf(f, "%d", &linie);
        fscanf(f, "%d", &coloana);

        adaugare_element_lista(&head, linie, coloana);
    }
    push(top, head);
    fclose(f);
}

void reverse_modificari(char **mat, int N, int M, ListNode *head){
    ListNode *aux=head;
    if(aux==NULL) return;

    while(aux){
        if (aux->linie>=0 && aux->linie<N && aux->coloana>=0 && aux->coloana<M) {
            if (mat[aux->linie][aux->coloana] == 'X') {
                mat[aux->linie][aux->coloana] = '+';
            } else {
                mat[aux->linie][aux->coloana] = 'X';
            }
        }
        aux=aux->next;
    }
}

void reconstructie_matrice(StackNode *top, char **mat, int N, int M){
    StackNode *aux=top;
    while(top){
        reverse_modificari(mat, N, M, aux->head);
        aux=aux->next;
    }
}