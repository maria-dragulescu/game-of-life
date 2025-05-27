#include "task1lib.h"
#include "task2lib.h"
#include "task3lib.h"

int main(int argc, char **argv){
    FILE *citire=fopen(argv[1],"rt");
    if(citire==NULL){
        printf("Nu s-a putut deschide fisierul pentru citire.");
        exit(1);
    }
    FILE *scriere=fopen(argv[2], "wt");
    if(scriere==NULL){
        printf("Nu s-a putut deschide fisierul pentru scriere.");
        exit(1);
    }

    int T, N, M, K, nrGen=1;
    StackNode *top=NULL;

    fscanf(citire, "%d", &T);

    /*//alocarea dinamica a matricei
    char **mat=(char**)malloc(N*sizeof(char*));
    for(int i=0; i<N; i++){
        mat[i]=(char*)malloc(M*sizeof(char));
        if(mat[i]==NULL){
            printf("Eroare la alocare dinamica.");
            exit(1);
        }
    }*/

    if(T==1){
        fscanf(citire, "%d", &N);
        fscanf(citire, "%d", &M);
        fscanf(citire, "%d", &K);
        char **mat1=(char**)malloc(N*sizeof(char*));
        for(int i=0; i<N; i++){
            mat1[i]=(char*)malloc(M*sizeof(char));
        if(mat1[i]==NULL){
            printf("Eroare la alocare dinamica.");
            exit(1);
        }
    }
        citire_matrice(mat1, N, M, citire);
        scriere_matrice(mat1, N, M, scriere);
        fprintf(scriere, "\n");
        implementare_reguli(mat1, K, N, M, scriere);
        fprintf(scriere, "\n");
        for(int i=0; i<N; i++){
            free(mat1[i]);
        }
        free(mat1);
    }
    if(T==2){
        fscanf(citire, "%d", &N);
        fscanf(citire, "%d", &M);
        fscanf(citire, "%d", &K);
        char **mat2=(char**)malloc(N*sizeof(char*));
        for(int i=0; i<N; i++){
            mat2[i]=(char*)malloc(M*sizeof(char));
        if(mat2[i]==NULL){
            printf("Eroare la alocare dinamica.");
            exit(1);
        }
    }
        citire_matrice(mat2, N, M, citire);
        implementare_reguli_stiva(mat2, K, N, M, &top, scriere);
        afisare_stiva(top, &nrGen, scriere);
        for(int i=0; i<N; i++){
            free(mat2[i]);
        }
        free(mat2);
    }
    if (T == 3) {
        fscanf(citire, "%d", &N);
        fscanf(citire, "%d", &M);
        fscanf(citire, "%d", &K);
        char **mat3=(char**)malloc(N*sizeof(char*));
        for(int i=0; i<N; i++){
            mat3[i]=(char*)malloc(M*sizeof(char));
        if(mat3[i]==NULL){
            printf("Eroare la alocare dinamica.");
            exit(1);
        }
    }   
        citire_matrice(mat3, N, M, citire);
        TreeNode *root = construieste_arbore(mat3, 0, K, N, M, scriere);
        eliberare_arbore(root);
        for(int i=0; i<N; i++){
            free(mat3[i]);
        }
        free(mat3);
    }


    deleteStack(&top);
    fclose(citire);
    fclose(scriere);

    return 0;
}