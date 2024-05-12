/**
 * @defgroup   SAXPY saxpy
 *
 * @brief      This file implements an iterative saxpy operation
 *
 * @param[in] <-p> {vector size}
 * @param[in] <-s> {seed}
 * @param[in] <-n> {number of threads to create}
 * @param[in] <-i> {maximum itertions}
 *
 * @author     Danny Munera
 * @date       2020
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <pthread.h>
#include<stdbool.h>// Booleanos
#include <math.h>

// Variables to obtain command line parameters
unsigned int seed = 1;
int p = 10000000;
int n_threads = 2;
int max_iters = 1000;
// Variables to perform SAXPY operation
double *X;
double a;
double *Y;
double *Y_avgs;
int i, it;


//-------------------------------------------------------------------
struct ThreadArgs {
    bool esPrimeraParte; // Para indicar si es la primera parte de X y Y
    int limit;   // Indica hasta donde parar de hacer la operacion
};




//-------------------------------------------------------------------
void calculate(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;

	if(p >= 2){

		if(args->esPrimeraParte == true){
			i = 0;
		}else{
			i = args->limit +1;
			args->limit = p-1;
		}

		for (i = i; i <= args->limit; i++)
		{
			Y[i] = Y[i] + a * X[i];
			Y_avgs[it] += Y[i];
		}
	}else{
		printf("P < 2\n");
	}
}




//-------------------------------------------------------------------
int main(int argc, char *argv[])
{

	// Variables to get execution time
	struct timeval t_start, t_end;
	double exec_time;

	// Getting input values
	int opt;
	while ((opt = getopt(argc, argv, ":p:s:n:i:")) != -1)
	{
		switch (opt)
		{
		case 'p':
			printf("vector size: %s\n", optarg);
			p = strtol(optarg, NULL, 10);
			assert(p > 0 && p <= 2147483647);
			break;

		case 's':
			printf("seed: %s\n", optarg);
			seed = strtol(optarg, NULL, 10);
			break;

		case 'n':
			printf("threads number: %s\n", optarg);
			n_threads = strtol(optarg, NULL, 10);
			break;

		case 'i':
			printf("max. iterations: %s\n", optarg);
			max_iters = strtol(optarg, NULL, 10);
			break;

		case ':':
			printf("option -%c needs a value\n", optopt);
			break;

		case '?':
			fprintf(stderr, "Usage: %s [-p <vector size>] [-s <seed>] [-n <threads number>] [-i <maximum itertions>]\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	srand(seed);

	printf("\np = %d, seed = %d, n_threads = %d, max_iters = %d\n",
		   p, seed, n_threads, max_iters);

	// initializing data
	fill_vectors();


#ifdef DEBUG
	
	print_vector(); // Imprime todos los valores

#endif
	/*
	 *	Function to parallelize
	 */
	gettimeofday(&t_start, NULL);
	funtion_saxpy();
	gettimeofday(&t_end, NULL);

#ifdef DEBUG
	print_y_final(); // Imprime el valor final de Y_avgs
#endif

	// Computing execution time
	exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;	 // sec to ms
	exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
	printf("Execution time: %f ms \n", exec_time);
	printf("Last 3 values of Y: %f, %f, %f \n", Y[p - 3], Y[p - 2], Y[p - 1]);
	printf("Last 3 values of Y_avgs: %f, %f, %f \n", Y_avgs[max_iters - 3], Y_avgs[max_iters - 2], Y_avgs[max_iters - 1]);
	return 0;
}
//-------------------------------------------------------------------




void print_vector()
{
	printf("\na= %f \n", a);

	printf("vector X= [ ");
	for (i = 0; i < p - 1; i++)
	{
		printf("%f, ", X[i]);
	}
	printf("%f ]\n", X[p - 1]);

	printf("vector Y= [ ");
	for (i = 0; i < p - 1; i++)
	{
		printf("%f, ", Y[i]);
	}
	printf("%f ]\n", Y[p - 1]);
}




//-------------------------------------------------------------------
void print_y_final(){
	printf("RES: final vector Y= [ ");
	for (i = 0; i < p - 1; i++)
	{
		printf("%f, ", Y[i]);
	}
	printf("%f ]\n\n", Y[p - 1]);
}




//-------------------------------------------------------------------
void funtion_saxpy(){
	// SAXPY iterative SAXPY mfunction
	bool esPrimeraParte = false;
	pthread_t hilo1, hilo2;

	for (it = 0; it < max_iters; it++)
	{
		int division_entera = floor(p/2); // Mitad de los arreglos X y Y

        struct ThreadArgs *args1 = malloc(sizeof(struct ThreadArgs));
        args1->esPrimeraParte = true;
        args1->limit = division_entera;

        struct ThreadArgs *args2 = malloc(sizeof(struct ThreadArgs));
        args2->esPrimeraParte = false;
        args2->limit = division_entera;

		pthread_create(&hilo1, NULL, calculate, (void *)args1);
		pthread_create(&hilo2, NULL, calculate, (void *)args2);

		pthread_join(hilo1, NULL);
		pthread_join(hilo2, NULL);
		Y_avgs[it] = Y_avgs[it] / p;
	}
}




//-------------------------------------------------------------------
void fill_vectors(){

	// initializing data
	X = (double *)malloc(sizeof(double) * p);
	Y = (double *)malloc(sizeof(double) * p);
	Y_avgs = (double *)malloc(sizeof(double) * max_iters);

	for (i = 0; i < p; i++)
	{
		(X)[i] = (double)rand() / RAND_MAX;
		(Y)[i] = (double)rand() / RAND_MAX;
	}
	for (i = 0; i < max_iters; i++)
	{

		(Y_avgs)[i] = 0.0;
	}

	a = (double)rand() / RAND_MAX;	
}