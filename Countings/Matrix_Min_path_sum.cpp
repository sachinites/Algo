#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define arr_get_macro(dtype)    \
    static inline dtype \
    arr_get_##dtype (dtype *arr, int r, int c, int col_max) {   \
    dtype *base_addr = (dtype *)arr;    \
    base_addr += (r * col_max) ;    \
    base_addr += c; \
    return *base_addr;  \
    }

#define arr_set_macro(dtype) \
    static inline void  \
    arr_set_##dtype(dtype *arr, int r, int c, int col_max, dtype elem) {  \
    dtype *base_addr = (dtype *)arr;    \
    base_addr += (r * col_max); \
    base_addr += c; \
    *base_addr = elem;  \
}

#define arr_create2D(dtype) \
    static inline dtype**   \
     arr_create2D_##dtype(int row, int col) { \
     int i; \
     dtype **l1 = (dtype **)calloc(row, sizeof(dtype *));   \
     for (i = 0; i < row; i++) {    \
         l1[i] = (dtype *)calloc (col, sizeof(dtype));  \
     }  \
    return l1;  \
    }

arr_get_macro(int);
arr_set_macro(int);
arr_create2D(int);

static void
printarray (int *arr, int row, int col) {

    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf ("%d  ", arr_get_int(arr, i, j, col));
        }
        printf ("\n");
    }
}

static void
_minPathSum(int *grid, int row, int col, int r, int c , uint32_t *S, uint32_t s) {

    if (r == row || c == col) return;

    if (r == (row - 1) && c == (col - 1)) {
        if (s < *S) *S = s; 
    }

    if ((r + 1) < row) _minPathSum(grid, row, col, r + 1 , c , S, 
        s + arr_get_int(grid, r + 1 , c , col));

    if ((c + 1) < col) _minPathSum(grid, row, col, r  , c + 1 , S,
        s + arr_get_int(grid, r , c + 1, col));
}

static uint32_t
minPathSum(int* grid, int row, int col){

    uint32_t S = UINT32_MAX;

    _minPathSum(grid, row, col, 0, 0, &S, arr_get_int(grid, 0 , 0, col));
    return S;
}


static void
printarray2 (int **arr, int row, int col) {

    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf ("%d  ", arr[i][j]);
        }
        printf ("\n");
    }
}

static void
_minPathSum2(int **grid, int row, int col, int r, int c , uint32_t *S, uint32_t s) {

    if (r == row || c == col) return;

    if (r == (row - 1) && c == (col - 1)) {
        if (s < *S) *S = s; 
    }

    if ((r + 1) < row) _minPathSum2(grid, row, col, r + 1 , c , S, 
        s + grid[r+1][c]);

    if ((c + 1) < col) _minPathSum2(grid, row, col, r  , c + 1 , S,
        s + grid[r][c+1]);
}

static uint32_t
minPathSum2(int** grid, int row, int col){

    uint32_t S = UINT32_MAX;

    _minPathSum2(grid, row, col, 0, 0, &S, grid[0][0]);
    return S;
}


int
main ( int argc, char **argv) {

    int *arr = (int *)calloc (3 * 3, sizeof(int));

    arr_set_int(arr, 0, 0, 3, 1);
    arr_set_int(arr, 0, 1, 3, 2);
    arr_set_int(arr, 0, 2, 3, 5);

    arr_set_int(arr, 1, 0, 3, 4);
    arr_set_int(arr, 1, 1, 3, 3);
    arr_set_int(arr, 1, 2, 3, 6);

    arr_set_int(arr, 2, 0, 3, 7);
    arr_set_int(arr, 2, 1, 3, 8);
    arr_set_int(arr, 2, 2, 3, 9);
    
    printarray (arr, 3, 3);

    printf ("minPathSum = %u\n", minPathSum(arr, 3, 3));

    free(arr);

    int **arr2 = arr_create2D_int(3, 3);

    arr2[0][0] = 1;
    arr2[0][1] = 2;
    arr2[0][2] = 3;

    arr2[1][0] = 4;
    arr2[1][1] = 5;
    arr2[1][2] = 6;

    arr2[2][0] = 7;
    arr2[2][1] = 8;
    arr2[2][2] = 9;

    printarray2 (arr2, 3, 3);

    printf ("minPathSum = %u\n", minPathSum2(arr2, 3, 3));

    return 0;
}