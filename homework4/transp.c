#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

//Printing utility function for debugging matrix transposition
void matrixPrint(int input_width, float* matrix)
{
   printf("Matrix:\n");
    for (int count = 0; count < input_width*input_width; count++)
    {
        printf("%f ",matrix[count]);
    }
}

int main (int argc, char* argv[])
{
    int input_width = atoi(argv[1]);
    int block_width = atoi(argv[2]);
    struct timeval start, end;
    
    float* input_matrix = (float*)malloc(input_width*input_width * sizeof(float));
    float* output_matrix = (float*)malloc(input_width*input_width * sizeof(float));

    //Populate the input matrix with random float values
    srand(time(NULL));
    for (int count = 0; count < input_width*input_width; count++)
    {
        input_matrix[count] = rand();
    }

    //Begin timing of transposition
    gettimeofday(&start, NULL);
    for (int i = 0; i < input_width; i+=block_width){
        for (int j = 0; j < input_width; j+=block_width){
            for (int k = 0; k < i + block_width; ++k){
                for (int l = 0; l < j + block_width; ++l){
                    output_matrix[k+l*input_width] = input_matrix[l+k*input_width];
                }
            }
        }
    }
    gettimeofday(&end, NULL);
    //End timing of transposition

    printf("Transposition time: %ld\n",((end.tv_sec * 1000000 + end.tv_usec)-(start.tv_sec * 1000000 + start.tv_usec)));

    //Return arrays to the heap
    free(input_matrix);
    free(output_matrix);

    return 0;
}