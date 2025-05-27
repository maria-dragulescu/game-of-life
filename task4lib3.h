#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int V;  //nr varfuri
    int E;  //nr muchii
    int **a;
}Graph;

typedef struct {
    int longest_length;
    int *optimal_path;
    bool is_complete;
    bool path_exists;
} HamiltonianData;

typedef struct ConnectedGroup{
    int* vertices;
    int count;
} ConnectedGroup;

char** cloneaza_matrice(char **mat, int N, int M);
void aplicare_modificari(char **mat, int N, int M, ListNode *head);
int numara_vii(char **mat, int N, int M);
Graph* construieste_mat_adiacenta(char **mat, int N, int M, int ***pozitii);
void implementare_reguli_B1(char **mat, int N, int M, ListNode **head);
void implementare_reguli_init1(char **mat, int N, int M, ListNode **head);
void dfs(int node, int **adiacenta, int *vizitat, ConnectedGroup* group, int nrnoduri);
ConnectedGroup* find_all_components(Graph *graph, int *nrcomponente);
bool cauta_lant_hamiltonian(int nodcurent, int **adiacenta, int *vizitat, int *cale_curenta, int adancime, ConnectedGroup* group, HamiltonianData* hamiltonian_info, int **pozitii);
TreeNode* construieste_arbore_fara_afisare(char **mat, int count, int K, int N, int M);
int gaseste_hamiltonian_in_componenta(Graph *graph, ConnectedGroup* group, HamiltonianData* hamiltonian_info, int **pozitii);
int cauta_cel_mai_lung_lant(Graph *graph, HamiltonianData* hamiltonian_info, int **pozitii);
void traverse_and_solve(TreeNode* root, char** mat, int N, int M, HamiltonianData* hamiltonian_info, FILE *scriere);

