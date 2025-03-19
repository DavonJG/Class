#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <immintrin.h>
#include <x86intrin.h>

#define ALIGN __attribute__ ((aligned (32)))

double ALIGN a[1024 * 1024];
double ALIGN b[1024 * 1024];
double ALIGN c[1024 * 1024];
double ALIGN c1[1024 * 1024];


void dgemm(int n)
{
	int i,j,k;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			double cij = 0;
			for(k=0; k<n; k++)
				cij = cij + a[i*n+k] * b[k*n+j];
			c1[i*n+j] = cij;
		}
	}
}

void dgemm_intrin(int n)
{
	int i,j,k;
	for(i=0; i<n; i+=1)
	{
		for(j=0; j<n; j+=4)
		{
			__m256d c4  = _mm256_load_pd(&c[i * n+j]);
			for(k=0; k<n; k++)
			{
				__m256d a4 = _mm256_broadcast_sd(&a[i*n+k]);
				__m256d b4 = _mm256_load_pd(&b[k*n+j]);
				c4 = _mm256_add_pd(c4, _mm256_mul_pd(a4, b4));
			}
			_mm256_store_pd(&c[i*n+j], c4);
		}
	}
}


void dgemm_unrolling(int n)
{
	int i,j,k;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			double cij = 0;
			
			for(k=0; k<n; k+=4)
			{
				double s1 = a[i*n+k] * b[k*n+j];
				double s2 = a[i*n+(k+1)] * b[(k+1)*n+j];
				double s3 = a[i*n+(k+2)] * b[(k+2)*n+j];
				double s4 = a[i*n+(k+3)] * b[(k+3)*n+j];
				cij += s1 + s2 + s3 + s4;
			}
			c[i*n+j] = cij;
		}
	}
}


#define BLOCK_SIZE 4

void do_block(int n, int si, int sj, int sk, double *a, double *b, double *c)
{
  int i, j, k;
  for (i=si; i<si+BLOCK_SIZE; i++)
    for (j=sj; j<sj+BLOCK_SIZE; j+=1024) {
             /*double cij = c[i*n+j];*/
            __m256d c4  = _mm256_load_pd(&c[i * n+j]);
      	    for (k=sk; k<sk+BLOCK_SIZE; k+=1024){
            	c4 = (_mm256_add_pd(c4, _mm256_mul_pd(_mm256_broadcast_sd(&a[i*n+k]), _mm256_load_pd(&b[k*n+j]))));
            	c4 = (_mm256_add_pd(c4, _mm256_mul_pd(_mm256_broadcast_sd(&a[i*n+(k+1)]), _mm256_load_pd(&b[(k+1)*n+j]))));
            	c4 = (_mm256_add_pd(c4, _mm256_mul_pd(_mm256_broadcast_sd(&a[i*n+(k+2)]), _mm256_load_pd(&b[(k+2)*n+j]))));
            	c4 = (_mm256_add_pd(c4, _mm256_mul_pd(_mm256_broadcast_sd(&a[i*n+(k+3)]), _mm256_load_pd(&b[(k+3)*n+j]))));
     	    }

      _mm256_store_pd(&c[i*n+j],c4);
     //c[i*n+j] = cij;
    }
}

void dgemm_blocking(int n)
{
  int i, j, k;
  for(i=0; i<n; i+=BLOCK_SIZE) 
    for(j=0; j<n; j+=BLOCK_SIZE) {
       c[i*n+j] = 0;
       for(k=0; k<n; k+=BLOCK_SIZE){
          do_block(n, i, j, k, a, b, c);
	}
    }
}

/* Implement this function with multiple optimization techniques. */
void optimized_dgemm(int n)
{
  dgemm_blocking(n);
  //dgemm_unrolling(n);
  //dgemm_intrin(n);
}

int main(int argc, char** argv)
{
	int i, j;
	time_t t;
	struct timeval start, end;
	double elapsed_time;

	int check_correctness = 0;
	int correct = 1;

	if(argc > 1)
	{
		if(strcmp(argv[1], "corr") == 0)
		{
			check_correctness = 1;
		}
	}

	/* Initialize random number generator */
	srand((unsigned) time(&t));

	/* Populate the arrays with random values */
	for(i=0; i<1024; i++)
	{
		for(j=0; j<1024; j++)
		{
			a[i*1024+j] = (double)rand() / (RAND_MAX + 1.0);
			b[i*1024+j] = (double)rand() / (RAND_MAX + 1.0);
			c[i*1024+j] = 0.0;
			c1[i*1024+j] = 0.0;
		}
	}
	

	gettimeofday(&start, NULL);

	/* Call you optimized function optimized_dgemm */
	optimized_dgemm(1024);

	gettimeofday(&end, NULL);

	/* For TA use only */
	
	if(check_correctness)
	{
		dgemm(1024);
		for(i=0; (i<1024) && correct ; i++)
		{
			for(j=0; (j<1024) && correct; j++)
			{
				if(fabs(c[i*1024+j]-c1[i*1024+j]) >= 0.0000001)
				{
					printf("%f != %f\n", c[i*1024+j], c1[i*1024+j]);
					correct = 0;
				}
			}
		}
		
		if(correct)
			printf("Result is correct!\n");
		else
			printf("Result is incorrect!\n");
	}
	
	elapsed_time = (end.tv_sec - start.tv_sec) * 1000.0;
	elapsed_time += (end.tv_usec - start.tv_usec) / 1000.0;

	printf("dgemm finished in %f milliseconds.\n", elapsed_time);
}
