#include "task1lib.h"
#include "task2lib.h"
#include "task3lib.h"

void implementare_reguli_B(char **mat, int K, int N, int M, ListNode **head){
    int nrVii;
    char **temp = (char**)malloc(N * sizeof(char*));
    char **temp2 = (char**)malloc(N * sizeof(char*));
    
    if(temp == NULL || temp2 == NULL) {
        printf("Eroare la alocare dinamica.");
        exit(1);
    }
    
    for(int i = 0; i < N; i++){
        temp[i] = (char*)malloc(M * sizeof(char));
        temp2[i] = (char*)malloc(M * sizeof(char));
        if(temp[i] == NULL || temp2[i] == NULL){
            printf("Eroare la alocare dinamica.");
            exit(1);
        }
    }
    
    for(int j = 0; j < N; j++){
        for(int k = 0; k < M; k++){
            temp2[j][k] = mat[j][k];
            temp[j][k] = mat[j][k];
        }
    }
        
    //aplicam regula pt B
    for(int j = 0; j < N; j++){
        for(int k = 0; k < M; k++){
            vecini_vii(mat, N, M, &nrVii, j, k);
                
            if(mat[j][k]=='+' && nrVii==2){
                temp[j][k]='X';
            } else if(mat[j][k]=='X'){
                temp[j][k]='X';
            } else{
                temp[j][k]='+';
            }
        }
    }
        
    //cream lista cu nodurile care s-au schimbat
    for(int j = 0; j < N; j++){
        for(int k = 0; k < M; k++){
            if(temp2[j][k] != temp[j][k]){
                adaugare_element_lista(head, j, k);
            }
        }
    }
        
    
    for(int j = 0; j < N; j++){
        for(int k = 0; k < M; k++){
            mat[j][k] = temp[j][k];
        }
    }
    
    for(int i = 0; i < N; i++){
        free(temp[i]);
        free(temp2[i]);
    }
    free(temp);
    free(temp2);
}

void eliberare_arbore(TreeNode *root) { //functie eliberare
    if(root == NULL) return;

    eliberare_arbore(root->left);
    eliberare_arbore(root->right);
    
    if(root->lista != NULL) {
        ListNode *current = root->lista;
        while(current != NULL) {
            ListNode *temp = current;
            current = current->next;
            free(temp);
        }
        free(root->lista);
    }
    
    free(root);
}

void implementare_reguli_init(char **mat, int K, int N, int M, ListNode **head){ // functia folosita la task 2 doar ca este implementata cu o singura lista
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

    for(int j=0; j<N; j++){
        for(int k=0; k<M; k++){
            if(temp2[j][k]!=temp[j][k]){
                adaugare_element_lista(head, j, k);
            }
        }
    }
    for(int j=0; j<N; j++){
        for(int k=0; k<M; k++){
            mat[j][k]=temp[j][k];
        }
    }
    
    for(int i=0; i<N; i++){
        free(temp[i]);
        free(temp2[i]);
    }
    free(temp);
    free(temp2);
}

TreeNode* construieste_arbore(char **mat, int count, int K, int N, int M, FILE *scriere) {
    //count este nivelul
    if (count > K) return NULL; //daca count e mai mare decat generatia iese

    //creez nodul pentru arbore
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("Eroare la alocare dinamica pentru nod arbore!\n");
        exit(1);
    }
    node->left = node->right = NULL;
    node->lista = NULL;

   //afisam matricea curenta
    scriere_matrice(mat, N, M, scriere);
    fprintf(scriere, "\n");

    //daca este radacina
    if (count == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (mat[i][j] == 'X') {
                    adaugare_element_lista(&node->lista, i, j);
                }
            }
        }
    }

    //cand s-a ajuns la generatia finala iese
    if (count == K) return node;

    //cele 2 matrici pt fii stanga/dreapta
    char **mat_stanga =(char**)malloc(N*sizeof(char*));
    char **mat_dreapta =(char**)malloc(N*sizeof(char*));
    for (int i = 0; i < N; i++) {
        mat_stanga[i] =(char*)malloc(M*sizeof(char));
        mat_dreapta[i] =(char*)malloc(M*sizeof(char));
        if(mat_dreapta[i]==NULL){
            printf("Eroare la alocare dinamica!");
            exit(1);
        }
        if(mat_stanga[i]==NULL){
            printf("Eroare la alocare dinamica!");
            exit(1);
        }
        for (int j = 0; j < M; j++) { //copiem matricile pentru a aplica regulile pt fiecare copil
            mat_stanga[i][j] = mat[i][j];
            mat_dreapta[i][j] = mat[i][j];
        }
    }

    //cream listele de modificari
    ListNode *stanga = NULL;
    ListNode *dreapta = NULL;
    implementare_reguli_B(mat_stanga, 1, N, M, &stanga);
    implementare_reguli_init(mat_dreapta, 1, N, M, &dreapta);

    //construim in preordine arborele
    node->left = construieste_arbore(mat_stanga, count + 1, K, N, M, scriere);
    node->right = construieste_arbore(mat_dreapta, count + 1, K, N, M, scriere);

    //salvam modificarile
    if (node->left) node->left->lista = stanga;
    if (node->right) node->right->lista = dreapta;

    // Eliberăm matricile temporare
    for (int i = 0; i < N; i++) {
        free(mat_stanga[i]);
        free(mat_dreapta[i]);
    }
    free(mat_stanga);
    free(mat_dreapta);

    return node;
}





