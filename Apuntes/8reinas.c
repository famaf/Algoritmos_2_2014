#include <stdio.h>

#define N 8
#define bool int
#define true 1
#define false 0

int count = 0;

void display(int * solution) {
    int i, j;

    for (i = 1; i <= N; i++) {
        for (j = 1; j < solution[i]; j++) printf(".");
        printf("Q");
        for (j = solution[i]+1; j <= N; j++) printf(".");
        printf("\n");
    }

    printf("\n");
    count++;
}

int down(int i, int j) {
    return j-i+N-1;
}

int up(int i, int j) {
    return i+j-1;
}

void unmark(int i, int j, bool * cols, bool * downs, bool * ups) {
    int d, u;

    d = down(i,j);
    u = up(i,j);

    if (j != 0) {
        cols[j] = false;
        downs[d] = false;
        ups[u] = false;
    }
}

void next(int i, int * sol, bool * cols, bool * downs, bool * ups) {
    int c, d, u;

    c = sol[i];
    d = down(i,c);
    u = up(i,c);

    do {
        c++;
        d++;
        u++;
    } while (c <= N && (cols[c] || downs[d] || ups[u]));

      sol[i] = c;
}

int mark(int i, int * sol, bool * cols, bool * downs, bool * ups) {
    int c, d, u;

    c = sol[i];
    d = down(i,c);
    u = up(i,c);

    if (c <= N) {
        cols[c] = true;
        downs[d] = true;
        ups[u] = true;
        i++;
        sol[i] = 0;
    }

    return i;
}

void main() {
    int sol[N+2];
    bool cols[N+1], downs[2*N], ups[2*N];
    int i;

    for (i = 0; i <= N; i++) {
        cols[i] = false;
    }

    for (i = 0; i < 2*N; i++) {
        downs[i] = false;
        ups[i] = false;
    }

    i = 1;
    sol[1] = 0;

    while (sol[1] <= N) {
        if (i > N) {
            display(sol);
            i--;
        }
        else if (sol[i] <= N) {
            unmark(i,sol[i],cols,downs,ups);
            next(i,sol,cols,downs,ups);
            /*printf("i = %d; j = %d\n",i,sol[i]);*/
            i = mark(i,sol,cols,downs,ups);
        }
        else {
            i--;
        }
    }

    printf("Número de soluciones: %d\n", count);
}
