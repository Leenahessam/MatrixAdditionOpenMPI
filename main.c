#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int **matAlloc (int row, int col)
{
    int* x;
    int** mat;
    int count = 0;
    x = malloc(sizeof(int)*row *col);
    mat = malloc(sizeof(int*)*row);
    for(count = 0; count<row; count++)
       mat[count] = &x[count * col];
return mat;
}


int main()
{
    int id, nthread, i, j, nrows, ncols, nrows2, ncols2;
    printf("enter your first matrix number of \nrows and cols respectively ");
    scanf("%d %d", &nrows, &ncols);
    printf("enter your second matrix number of \nrows and cols respectively ");
    scanf("%d %d", &nrows2, &ncols2);
    if (nrows != nrows2 || ncols != ncols2){
        printf("incompatible dimensions ");
        return;
    }
    int **a = matAlloc(nrows,ncols);
    int **b = matAlloc(nrows,ncols);
    int **c = matAlloc(nrows,ncols);
    printf("enter first matrix \n");
    for(i = 0; i < nrows; i++){
     for(j = 0 ; j < ncols; j++){
        int data;
        scanf("%d", &data);
        a[i][j] = data;
     }}
    printf("enter second matrix \n");
    for(i = 0; i < nrows; i++){
     for(j = 0 ; j < ncols; j++){
        int data;
        scanf("%d", &data);
        b[i][j] = data;
     }}
    #pragma omp parallel shared(a,b,c) private(i,j)
    {
        #pragma omp for schedule(static)
        for(i = 0 ; i < nrows ; i++)
        {
            for(j = 0 ; j < ncols; j++){
                c[i][j] = a[i][j]+b[i][j];
            }
        nthread = omp_get_num_threads();
        id = omp_get_thread_num();
        printf("thread number %d out of %d threads\n", id, nthread);
        }
    }
    printf("Result Matrix \n");
    for(i = 0 ; i < nrows ; i++)
    {
        for(j = 0 ; j < ncols ; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
}
