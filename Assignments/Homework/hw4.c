//Brandon Truong

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 10000

void transpose(int *dst, int *src, int dim)
{
    int i, j;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[j*dim + i] = src[i*dim + j];
}

void newTranspose(int *dst, int *src, int dim)
{
    int i, j, ii, jj;
	int bsize = 32;
    for (i = 0; i < dim; i += bsize) {
		for (j = 0; j < dim; j += bsize) {
			for (ii = i; ii < i + bsize && ii < dim; ii++) {
				for (jj = j; jj < j + bsize && jj < dim; jj++) {
					dst[jj * dim + ii] = src[ii * dim + jj];
				}
			}
		}
	}
}

void testNew(void)
{
	int i, j;
	int *dst = (int *) malloc(NUM * NUM * sizeof(int));
	int *src = (int *) malloc(NUM * NUM * sizeof(int));
	for (i = 0; i < NUM; i++)
    {
		for (j = 0; j < NUM; j++)
        {
            int num = i * NUM + j;
			src[num] = num;
        }
	}
	clock_t start;
	clock_t end;
	start = clock();
	newTranspose(dst, src, NUM);
	end = clock();
	printf("New ran for %lf\n", difftime(end, start)/CLOCKS_PER_SEC);
	free(dst);
	free(src);
}

void testOld(void)
{
    int i, j;
	int *dst = (int *) malloc(NUM * NUM * sizeof(int));
	int *src = (int *) malloc(NUM * NUM * sizeof(int));
	for (i = 0; i < NUM; i++)
    {
		for (j = 0; j < NUM; j++)
        {
            int num = i * NUM + j;
			src[num] = num;
        }
	}
	clock_t start;
	clock_t end;
	start = clock();
	transpose(dst, src, NUM);
	end = clock();
	printf("Old ran for %lf\n", difftime(end, start)/CLOCKS_PER_SEC);
	free(dst);
	free(src);
}

int main(void)
{
	testOld();
    testNew();
	return 0;
}