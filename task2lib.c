#include "task1lib.h"
#include "task2lib.h"

void push(StackNode **top, ListNode *head){
    StackNode *newItem=(StackNode*)malloc(sizeof(StackNode));
    if(newItem==NULL){
        printf("Eroare la alocare dinamica!");
        exit(1);
    }
    newItem->head=head;
    newItem->next=*top;
    *top=newItem;
}

void adaugare_element_lista(ListNode **head, int linie, int coloana){
    ListNode* newNode=(ListNode*)malloc(sizeof(ListNode));
    if(newNode==NULL){
        printf("Eroare la alocare dinamica!");
        exit(1);
    }
    newNode->linie=linie;
    newNode->coloana=coloana;
    newNode->next=*head;
    *head=newNode;
}

void afisare_stiva_invers(ListNode *head, FILE* scriere){
    if(head == NULL)
        return;
    afisare_stiva_invers(head->next, scriere);

    fprintf(scriere, " %d %d", head->linie, head->coloana);
}

void afisare_stiva(StackNode *top, int *nrGen, FILE* scriere){
    if(top==NULL)
        return;
    afisare_stiva(top->next, nrGen, scriere);

    fprintf(scriere, "%d", *nrGen);
    //ListNode *temp=top->head;
    /*while(temp!=NULL){
        fprintf(scriere, " %d %d", temp->linie, temp->coloana);
        temp=temp->next;
    }*/
    afisare_stiva_invers(top->head, scriere);
    fprintf(scriere, "\n");
    (*nrGen)++;
}

void deleteStack(StackNode **top){
    while(*top!=NULL){
        ListNode *temp=(*top)->head;
        while(temp!=NULL){
            ListNode *temp2=temp;
            temp=temp2->next;
            free(temp2);
        }
        StackNode *tempStack=*top;
        *top=(*top)->next;
        free(tempStack);
    }
}

void implementare_reguli_stiva(char **mat, int K, int N, int M, StackNode **top, FILE *scriere){
    int nrVii;
    //alocam dinamic o matrice temporara pentru a salva modificarile
    char **temp=(char**)malloc(N*sizeof(char*));
    char **temp2=(char**)malloc(N*sizeof(char*));
    for(int i=0; i<N; i++){
        temp[i]=(char*)malloc(M*sizeof(char));
        if(temp[i]==NULL){
            printf("Eroare la alocare dinamica.");
            exit(1);
        }
    }
    for(int i=0; i<N; i++){
        temp2[i]=(char*)malloc(M*sizeof(char));
        if(temp2[i]==NULL){
            printf("Eroare la alocare dinamica.");
            exit(1);
        }
    }
    for(int nrGen=0; nrGen<K; nrGen++){//iteram pentru a crea primele K generatii
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                temp2[j][k]=mat[j][k];
            }
        }
        
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                vecini_vii(mat, N, M, &nrVii, j, k);

                if(mat[j][k]=='X'){
                    if(nrVii<2 || nrVii>3)
                        temp[j][k]='+';
                    else
                        temp[j][k]='X';
                } else{
                    if(nrVii==3)
                        temp[j][k]='X';
                    else
                        temp[j][k]='+';
                }
            }
        }
        ListNode *head=NULL; //initializam capul listei pt aceasta generatie
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                if(temp2[j][k]!=temp[j][k]){
                    adaugare_element_lista(&head, j, k);
                }
            }
        }
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                mat[j][k]=temp[j][k];
            }
        }
        push(top, head);
    }
    for(int i=0; i<N; i++){
        free(temp[i]);
        free(temp2[i]);
    }
    free(temp);
    free(temp2);
}

