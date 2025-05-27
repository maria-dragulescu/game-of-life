#include "task1lib.h"

void citire_matrice(char **mat, int N, int M, FILE *citire){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            fscanf(citire, " %c", &mat[i][j]);
        }
    }
}
void scriere_matrice(char **mat, int N, int M, FILE *scriere){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            fprintf(scriere, "%c", mat[i][j]);
        }
        fprintf(scriere, "\n");
    }
}

void vecini_vii(char **mat, int N, int M, int *nrVii, int j, int k){
    (*nrVii)=0;
    for(int pozLinie=j-1; pozLinie<=j+1; pozLinie++){
        for(int pozCol=k-1; pozCol<=k+1; pozCol++){
            if(pozLinie>=0 && pozLinie<N && pozCol>=0 && pozCol<M && mat[pozLinie][pozCol]=='X' && !(pozCol==k && pozLinie==j)){
                    (*nrVii)++;
            }
        }
    }
}

void implementare_reguli(char **mat, int K, int N, int M, FILE *scriere){
    int nrVii;
    //alocam dinamic o matrice temporara pentru a salva modificarile
    char **temp=(char**)malloc(N*sizeof(char*));
    for(int i=0; i<N; i++){
        temp[i]=(char*)malloc(M*sizeof(char));
        if(temp[i]==NULL){
            printf("Eroare la alocare dinamica.");
            exit(1);
        }
    }
    for(int nrGen=0; nrGen<K; nrGen++){//iteram pentru a crea primele K generatii
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
                mat[j][k]=temp[j][k];
            }
        }
        scriere_matrice(mat, N, M, scriere);
        if(nrGen<K-1)
            fprintf(scriere, "\n");
    }
    for(int i=0; i<N; i++){
        free(temp[i]);
    }
    free(temp);
}