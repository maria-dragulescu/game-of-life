#include "task1lib.h"
#include "task2lib.h"
#include "task3lib.h"
#include "task4lib3.h"

char** cloneaza_matrice(char **mat, int N, int M) { //functie folosita pentru copierea matricilor
    char **copie = malloc(N * sizeof(char*));
    if (!copie) {
        printf("Eroare la alocare dinamica!\n");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        copie[i] = malloc(M + 1);
        if (!copie[i]) {
        printf("Eroare la alocare dinamica!\n");
        exit(1);
        }
        strcpy(copie[i], mat[i]);
    }
    return copie;
}

/*void aplicare_modificari(char **mat, int N, int M, ListNode *head){ // aplicam modificarile asupra generatiilor anterioare
    while (head) {
        if (head->linie >= 0 && head->linie < N && head->coloana >= 0 && head->coloana < M) {
            mat[head->linie][head->coloana] =
                (mat[head->linie][head->coloana] == 'X') ? '+' : 'X';
        }
        head = head->next;
    }
}*/

int numara_vii(char **mat, int N, int M) { //numaram elementele vii
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (mat[i][j] == 'X')
                count++;
    return count;
}

Graph* construieste_mat_adiacenta(char **mat, int N, int M, int ***pozitii) {
    Graph *g = malloc(sizeof(Graph));
    if (!g) exit(1);
    
    g->V = numara_vii(mat, N, M);
    g->E = 0;
    g->a = NULL;
    *pozitii = NULL;

    if (g->V == 0) return g;

    // alocam matricea de adiacenta
    g->a = calloc(g->V, sizeof(int*));
    for (int i = 0; i < g->V; i++) {
        g->a[i] = calloc(g->V, sizeof(int));
    }

    //alocam matricea in care vor fi stocate pozitiile elementelor vii
    *pozitii = malloc(g->V * sizeof(int*));
    int index = 0;
    
    // scriem pozitiile celulelor vii
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (mat[i][j] == 'X') {
                (*pozitii)[index] = malloc(2 * sizeof(int));
                (*pozitii)[index][0] = i;
                (*pozitii)[index][1] = j;
                index++;
            }
        }
    }

    // construim matricea de adiacenta
    for (int i = 0; i < g->V; i++) {
        for (int j = i + 1; j < g->V; j++) {
            int dx = abs((*pozitii)[i][0] - (*pozitii)[j][0]);
            int dy = abs((*pozitii)[i][1] - (*pozitii)[j][1]);
            
            if (dx <= 1 && dy <= 1) {
                g->a[i][j] = g->a[j][i] = 1;
                g->E++;
            }
        }
    }

    return g;
}


void implementare_reguli_B1(char **mat, int N, int M, ListNode **head) { //implementarea regulilor locala
    int nrVii;
    char **temp = cloneaza_matrice(mat, N, M);
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < M; k++) {
            vecini_vii(mat, N, M, &nrVii, j, k);
            if (mat[j][k] == '+' && nrVii == 2)
                temp[j][k] = 'X';
            else if (mat[j][k] == 'X')
                temp[j][k] = 'X';
            else
                temp[j][k] = '+';
        }
    }
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < M; k++) {
            if (mat[j][k] != temp[j][k])
                adaugare_element_lista(head, j, k);
            mat[j][k] = temp[j][k];
        }
        free(temp[j]);
    }
    free(temp);
}

void implementare_reguli_init1(char **mat, int N, int M, ListNode **head) { //implementarea regulilor locala
    int nrVii;
    char **temp = cloneaza_matrice(mat, N, M);
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < M; k++) {
            vecini_vii(mat, N, M, &nrVii, j, k);
            if (mat[j][k] == 'X') {
                if (nrVii < 2 || nrVii > 3)
                    temp[j][k] = '+';
                else
                    temp[j][k] = 'X';
            } else {
                if (nrVii == 3)
                    temp[j][k] = 'X';
                else
                    temp[j][k] = '+';
            }
        }
    }
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < M; k++) {
            if (mat[j][k] != temp[j][k])
                adaugare_element_lista(head, j, k);
            mat[j][k] = temp[j][k];
        }
        free(temp[j]);
    }
    free(temp);
}

void dfs(int node, int **adiacenta, int *vizitat, ConnectedGroup* group, int nrnoduri) {
    vizitat[node] = 1;
    group->vertices[group->count++] = node;
    for (int i = 0; i < nrnoduri; i++) {
        if (adiacenta[node][i] && !vizitat[i]) {
            dfs(i, adiacenta, vizitat, group, nrnoduri);
        }
    }
}

ConnectedGroup* find_all_components(Graph *graph, int *nrcomponente) {
    if (graph->V == 0) {
        *nrcomponente = 0;
        return NULL;
    }
    
    int *marked = calloc(graph->V, sizeof(int));
    ConnectedGroup* groups = malloc(graph->V * sizeof(ConnectedGroup));
    *nrcomponente = 0;
    
    for (int i = 0; i < graph->V; i++) {
        if (!marked[i]) {
            groups[*nrcomponente].vertices = malloc(graph->V * sizeof(int));
            groups[*nrcomponente].count = 0;
            dfs(i, graph->a, marked, &groups[*nrcomponente], graph->V);
            (*nrcomponente)++;
        }
    }
    
    free(marked);
    return groups;
}

bool cauta_lant_hamiltonian(int nodcurent, int **adiacenta, int *vizitat, int *cale_curenta, int adancime, ConnectedGroup* group, HamiltonianData* hamiltonian_info, int **pozitii) {
    
    // aplicam conditia sa treaca prin varfurile
    //lungimea sa fie egala cu numarul de noduri din comp conexa
    if (adancime == group->count) {
        hamiltonian_info->longest_length = adancime;
        hamiltonian_info->path_exists = true;
        hamiltonian_info->is_complete = true;
        
        // stocam calea cea buna
        for (int i = 0; i < adancime; i++) {
            hamiltonian_info->optimal_path[i] = cale_curenta[i];
        }
        return true; 
    }
    
    // determinam toti vecinii nevizitati care sunt conectati la nodul curent
    int *next = malloc(group->count * sizeof(int));
    int next_count = 0;
    
    for (int i = 0; i < group->count; i++) {
        int aux = group->vertices[i];
        if (!vizitat[aux] && adiacenta[nodcurent][aux]) {
            next[next_count++] = aux;
        }
    }
    
    // sortam vecinii lexicografic (intai dupa linii apoi pe coloane)
    for (int i = 0; i < next_count - 1; i++) {
        for (int j = i + 1; j < next_count; j++) {
            int node_i = next[i];
            int node_j = next[j];
            
            int x1 = pozitii[node_i][0], y1 = pozitii[node_i][1];
            int x2 = pozitii[node_j][0], y2 = pozitii[node_j][1];
            
            if (x2 < x1 || (x2 == x1 && y2 < y1)) {
                int temp = next[i];
                next[i] = next[j];
                next[j] = temp;
            }
        }
    }
    
    // incercam sa extindem calea
    //exploram fiecare vecin
    for (int i = 0; i < next_count; i++) {
        int next_node = next[i];
        
        vizitat[next_node] = 1;
        cale_curenta[adancime] = next_node;
        
        if (cauta_lant_hamiltonian(next_node, adiacenta, vizitat, cale_curenta, adancime + 1, group, hamiltonian_info, pozitii)) {
            free(next);
            return true; //s-a gasit un lant complet
        }
        
        vizitat[next_node] = 0; // resetam modificarile (backtracking)
    }
    
    free(next);
    return false; 
}

TreeNode* construieste_arbore_fara_afisare(char **mat, int count, int K, int N, int M) {
    TreeNode *node = malloc(sizeof(TreeNode));
    if (!node) {
        printf("Memory allocation failed for TreeNode!\n");
        exit(1);
    }
    node->left = NULL;
    node->right = NULL;
    node->lista = NULL;

    if (count == K) {
        return node;
    }

    char **mat_st = cloneaza_matrice(mat, N, M);
    char **mat_dr = cloneaza_matrice(mat, N, M);

    ListNode *ls = NULL, *ld = NULL;
    implementare_reguli_B1(mat_st, N, M, &ls);
    implementare_reguli_init1(mat_dr, N, M, &ld);

    if (ls == NULL && ld == NULL) {
        for (int i = 0; i < N; i++) {
            free(mat_st[i]);
            free(mat_dr[i]);
        }
        free(mat_st);
        free(mat_dr);
        return node;
    }

    node->left = construieste_arbore_fara_afisare(mat_st, count + 1, K, N, M);
    node->right = construieste_arbore_fara_afisare(mat_dr, count + 1, K, N, M);

    if (node->left) node->left->lista = ls;
    if (node->right) node->right->lista = ld;

    for (int i = 0; i < N; i++) {
        free(mat_st[i]);
        free(mat_dr[i]);
    }
    free(mat_st);
    free(mat_dr);

    return node;
}

//cauta lant hamiltonian in componenta
int gaseste_hamiltonian_in_componenta(Graph *graph, ConnectedGroup* group, HamiltonianData* hamiltonian_info, int **pozitii) {
    // initializam pentru cautare
    hamiltonian_info->longest_length = 0;
    hamiltonian_info->is_complete = false;
    hamiltonian_info->path_exists = false;
    memset(hamiltonian_info->optimal_path, -1, graph->V * sizeof(int));
    
    if (group->count == 0) {
        return -1;
    }
    
    if (group->count == 1) {
        hamiltonian_info->longest_length = 1;
        hamiltonian_info->optimal_path[0] = group->vertices[0];
        hamiltonian_info->is_complete = true;
        hamiltonian_info->path_exists = true;
        return 1;
    }
    
    int *vizitat = calloc(graph->V, sizeof(int));
    int *cale_curenta = malloc(graph->V * sizeof(int));
    
    // sortam varfurile componentelor dupa coordonate
    for (int i = 0; i < group->count - 1; i++) {
        for (int j = i + 1; j < group->count; j++) {
            int node_i = group->vertices[i];
            int node_j = group->vertices[j];
            
            int pos1_x = pozitii[node_i][0], pos1_y = pozitii[node_i][1];
            int pos2_x = pozitii[node_j][0], pos2_y = pozitii[node_j][1];
            
            if (pos2_x < pos1_x || (pos2_x == pos1_x && pos2_y < pos1_y)) {
                int temp = group->vertices[i];
                group->vertices[i] = group->vertices[j];
                group->vertices[j] = temp;
            }
        }
    }
    
    // incercam fiecare nod ca punct de plecare si incepem cautarea
    for (int start_idx = 0; start_idx < group->count && !hamiltonian_info->is_complete; start_idx++) {
        int nod_inceput = group->vertices[start_idx];
        
        //apoi resetam
        memset(vizitat, 0, graph->V * sizeof(int));
        memset(cale_curenta, -1, graph->V * sizeof(int));
        vizitat[nod_inceput] = 1;
        cale_curenta[0] = nod_inceput;
        
        if (cauta_lant_hamiltonian(nod_inceput, graph->a, vizitat, cale_curenta, 1, group, hamiltonian_info, pozitii)) {
            break; 
        }
    }

    free(vizitat);
    free(cale_curenta);

    //returnam lungimea daca lantul este valid
    return hamiltonian_info->path_exists && hamiltonian_info->is_complete ? hamiltonian_info->longest_length : -1;
}

int cauta_cel_mai_lung_lant(Graph *graph, HamiltonianData* hamiltonian_info, int **pozitii) {
    //initializam datele pentru cautare
    hamiltonian_info->longest_length = 0;
    hamiltonian_info->is_complete = false;
    hamiltonian_info->path_exists = false;
    
    if (graph->V == 0) {
        return -1;
    }
    
    if (graph->V == 1) {
        hamiltonian_info->longest_length = 1;
        hamiltonian_info->optimal_path[0] = 0;
        hamiltonian_info->is_complete = true;
        hamiltonian_info->path_exists = true;
        return 1;
    }
    
    // cautam toate componentele
    int total;
    ConnectedGroup* all_groups = find_all_components(graph, &total);
    
    if (total == 0) {
        return -1;
    }
    
    int best = -1;
    HamiltonianData best_result = {0, NULL, false, false};
    best_result.optimal_path = malloc(graph->V * sizeof(int));
    memset(best_result.optimal_path, -1, graph->V * sizeof(int));
    
    // ne uitam la fiecare componenta pentru a gasi lant
    for (int i = 0; i < total; i++) {
        HamiltonianData temp_result = {0, NULL, false, false};
        temp_result.optimal_path = malloc(graph->V * sizeof(int));
        
        int component_path_length = gaseste_hamiltonian_in_componenta(graph, &all_groups[i], &temp_result, pozitii);
        
        // acceptam doar lanturi complete
        if (component_path_length > 0 && temp_result.path_exists && temp_result.is_complete && temp_result.longest_length == all_groups[i].count && temp_result.longest_length > best) {
            
            best = temp_result.longest_length;
            
            //stocam cel mai bun rezultat
            best_result.longest_length = temp_result.longest_length;
            best_result.is_complete = temp_result.is_complete;
            best_result.path_exists = temp_result.path_exists;
            
            // copiem calea
            memset(best_result.optimal_path, -1, graph->V * sizeof(int));
            for (int j = 0; j < temp_result.longest_length; j++) {
                best_result.optimal_path[j] = temp_result.optimal_path[j];
            }
        }
        
        free(temp_result.optimal_path);
    }
    
    // copiem datele daca s a gasit cale valida
    if (best > 0 && best_result.path_exists && best_result.is_complete) {
        hamiltonian_info->longest_length = best_result.longest_length;
        hamiltonian_info->is_complete = best_result.is_complete;
        hamiltonian_info->path_exists = best_result.path_exists;
        
        memset(hamiltonian_info->optimal_path, -1, graph->V * sizeof(int));
        for (int i = 0; i < best_result.longest_length; i++) {
            hamiltonian_info->optimal_path[i] = best_result.optimal_path[i];
        }
    }
    
    //eliberare de memorie
    free(best_result.optimal_path);
    for (int i = 0; i < total; i++) {
        free(all_groups[i].vertices);
    }
    free(all_groups);
    
    return best > 0 ? best : -1;
}

void traverse_and_solve(TreeNode* root, char** mat, int N, int M, HamiltonianData* hamiltonian_info, FILE *scriere) {
    if (root == NULL) return;

    // aplicam modificarile pe generatia curenta
    ListNode* aux = root->lista;
    while (aux != NULL) {
        int i = aux->linie;
        int j = aux->coloana;
        mat[i][j] = (mat[i][j] == '+') ? 'X' : '+';
        aux = aux->next;
    }

    // construim graful
    int **pozitii;
    Graph *graph =construieste_mat_adiacenta(mat, N, M, &pozitii);

    // initializam datele
    hamiltonian_info->longest_length = 0;
    hamiltonian_info->is_complete = false;
    hamiltonian_info->path_exists = false;
    memset(hamiltonian_info->optimal_path, -1, N * M * sizeof(int));

    if (graph != NULL && graph->V > 0) {
        int path_length = cauta_cel_mai_lung_lant(graph, hamiltonian_info, pozitii);

        // facem validarea pt lanturile hamiltoniene
        bool valid_complete_hamiltonian = false;
        
        if (path_length > 0 && hamiltonian_info->path_exists && hamiltonian_info->is_complete && 
            hamiltonian_info->longest_length > 0) {
            
            //verificam daca sunt conexe
            bool connectivity_valid = true;
            
            // verificam daca exista in cale
            for (int i = 0; i < hamiltonian_info->longest_length - 1; i++) {
                int node_a = hamiltonian_info->optimal_path[i];
                int node_b = hamiltonian_info->optimal_path[i + 1];

                if (node_a < 0 || node_b < 0 || node_a >= graph->V || node_b >= graph->V || !graph->a[node_a][node_b]) {
                    connectivity_valid = false;
                    break;
                }
            }
            
            // verificam daca calea trece exact o singura data
            if (connectivity_valid) {
                int component_count;
                ConnectedGroup* components = find_all_components(graph, &component_count);
                
                bool component_match = false;
                for (int i = 0; i < component_count && !component_match; i++) {
                    if (components[i].count == hamiltonian_info->longest_length) {
                        // Verify path vertices match component
                        bool perfect_match = true;
                        for (int j = 0; j < hamiltonian_info->longest_length; j++) {
                            bool vertex_found = false;
                            for (int k = 0; k < components[i].count; k++) {
                                if (components[i].vertices[k] == hamiltonian_info->optimal_path[j]) {
                                    vertex_found = true;
                                    break;
                                }
                            }
                            if (!vertex_found) {
                                perfect_match = false;
                                break;
                            }
                        }
                        if (perfect_match) {
                            component_match = true;
                        }
                    }
                }
                
                valid_complete_hamiltonian = component_match;
                
                // eliberare de memorie
                for (int i = 0; i < component_count; i++) {
                    free(components[i].vertices);
                }
                free(components);
            }
        }

        // scrierea in fisier
        if (!valid_complete_hamiltonian) {
            fprintf(scriere,"-1\n");
        } else {
            fprintf(scriere,"%d\n", hamiltonian_info->longest_length - 1);
            int vertex_idx = hamiltonian_info->optimal_path[0];
            fprintf(scriere,"(%d,%d)", pozitii[vertex_idx][0], pozitii[vertex_idx][1]);
            
            for (int i = 1; i < hamiltonian_info->longest_length; i++) {
                vertex_idx = hamiltonian_info->optimal_path[i];
                if (vertex_idx >= 0 && vertex_idx < graph->V)
                    fprintf(scriere," (%d,%d)", pozitii[vertex_idx][0], pozitii[vertex_idx][1]);
            }
            fprintf(scriere,"\n");
        }

        //eliberam graful
        if (graph->a) {
            for (int i = 0; i < graph->V; i++) {
                free(graph->a[i]);
                if (pozitii && pozitii[i]) free(pozitii[i]);
            }
            free(graph->a);
        }
        if (pozitii) free(pozitii);
    } else {
        printf("-1\n");
    }

    if (graph) free(graph);

    // continuam parcurgerea arborelui in preordine
    traverse_and_solve(root->left, mat, N, M, hamiltonian_info, scriere);
    traverse_and_solve(root->right, mat, N, M, hamiltonian_info, scriere);

    // intoarcem modificarile
    aux = root->lista;
    while (aux != NULL) {
        int i = aux->linie;
        int j = aux->coloana;
        mat[i][j] = (mat[i][j] == '+') ? 'X' : '+';
        aux = aux->next;
    }
}