/*
 * eight_queens_puzzle_bruteforce.c
 *
 * see: https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE_%D0%B2%D0%BE%D1%81%D1%8C%D0%BC%D0%B8_%D1%84%D0%B5%D1%80%D0%B7%D1%8F%D1%85#.D0.9E.D1.81.D0.BE.D0.B1.D0.B5.D0.BD.D0.BD.D0.BE.D1.81.D1.82.D0.B8_.D1.80.D0.B5.D1.88.D0.B5.D0.BD.D0.B8.D1.8F
 *
 * BUILD: gcc -std=c99 -I../.. -o eight_queens_puzzle_bruteforce eight_queens_puzzle_bruteforce.c
 *
 * RUN: ./eight_queens_puzzle_bruteforce
 *
 *
 * ATTENTION: it gives "Bus error: 10" 0n MAC OS X (!)
 */

#include <time.h>
#include <stdio.h>
#include <string.h>

// 8x8 шахматная доска
#define SIZE 8
 
int size,
    sol_num,
    a[SIZE];
 
struct _board {
    unsigned int a[SIZE];
} board[SIZE+1];


void dfs(register int ind)
{
    register int i, j;
 
    if (ind >= size)
    {
        ++sol_num;
        return;
    }
 
    for (a[ind] = 0; a[ind] < size; ++a[ind])
    {
        if (!(board[ind].a[ ind ] & (1<<a[ind])))
        {
            memcpy(board[ind+1].a, &board[ind].a , SIZE*sizeof(int));
 
            for (i = ind, j = a[ind]; i<size && j<size; ++i, ++j) {
                board[ind+1].a[i] |= (1<<j);
            }
 
            for (i = ind, j = a[ind]; i<size && j>=0; ++i, --j) {
                board[ind+1].a[i] |= (1<<j);
            }
 
            board[ind+1].a[ind] = 65535u;
 
            for (i = ind; i < size; ++i) {
                board[ind+1].a[i] |= 1<<a[ind];
            }
 
            dfs(ind+1);
        }
    }
}


int main()
{
    double start, end;
    int i;

    for (size = 1; size < 20; ++size)
    {
        start = clock();
 
        sol_num = 0;
        memset(a, 0, sizeof(int)*SIZE);
        for (i = 0; i < SIZE+1; ++i) {
            memset(board[i].a, 0, sizeof(int)*SIZE);
        }
 
        dfs(0);
        end = clock();
        printf("%20d%20d\ttime: %.2lf\n", size, sol_num, (end-start)/CLOCKS_PER_SEC);
    }
 
    return 0;
}
