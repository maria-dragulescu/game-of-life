# gameoflife.c

> Conway's Game of Life – Modular implementation in C.

## Features

- Structură modulară: fiecare task este separat (task1–4).
- Suport pentru:
  - Simulări clasice cu reguli Game of Life.
  - Stive și liste pentru modificări între generații.
  - Arbore binar de evoluție.
  - Reprezentare grafuri și analiză Hamiltoniană.
- Optimizat pentru performanță și scalabilitate.
- Suport complet pentru C.

---

## Example

```c
#include <stdio.h>
#include "task1lib.h"
#include "task2lib.h"

int main() {
    int N = 4, M = 5, K = 3;
    char **mat = alocare_matrice(N, M);

    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    citire_matrice(mat, N, M, in);
    implementare_reguli(mat, K, N, M, out);

    fclose(in);
    fclose(out);
    eliberare_matrice(mat, N);
    return 0;
}
````


## Functions

#Basic 
citire_matrice	  Citește matricea din fișier.
scriere_matrice	  Scrie matricea în fișier.
vecini_vii	  Calculează vecini vii pt o celulă.
implementare_reguli	  Aplică regulile Game of Life.

#Stack (task2)
push	  Adaugă o generație în stivă.
afisare_stiva	  Afișează stiva în ordine inversă.
deleteStack	  Eliberează întreaga stivă.
implementare_reguli_stiva	  Salvează modificări.

#Tree (task3)
construieste_arbore	Creează arborele generațiilor folosind cele două reguli.
eliberare_arbore	Eliberează memoria alocată arborelui.

#Graph & Hamiltonian (task4)
construieste_mat_adiacenta	  Creează graful celulelor vii.
cauta_cel_mai_lung_lant	  Caută cel mai lung lanț Hamiltonian.
traverse_and_solve	  Parcurge arborele și verifică soluții.

## Notes
O celulă vie este reprezentată prin X, iar una moartă prin +.

Matricea este alocată dinamic: char **mat.

Listele și stivele sunt implementate folosind structuri personalizate (ListNode, StackNode).

Arborele binar are la fiecare nod o listă cu modificările efectuate la acea generație.

Grafurile sunt neorientate și conectează celulele vii învecinate.

## Build and run
Compile
make

Clean
make clean

Run
./a.out input.txt output.txt
