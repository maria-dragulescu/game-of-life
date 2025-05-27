#include <stdio.h>
#include <stdlib.h>

struct El{
    ListNode* lista;
    struct El *left, *right;
};
typedef struct El TreeNode;

void implementare_reguli_B(char **mat, int K, int N, int M, ListNode **head);
void eliberare_arbore(TreeNode *root);
void implementare_reguli_init(char **mat, int K, int N, int M, ListNode **head);
TreeNode* construieste_arbore(char** mat, int count, int K, int N, int M, FILE *scriere);
