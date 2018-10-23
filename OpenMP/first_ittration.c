#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

#define SIZE_OUTPUT 3467 
#define SIZE_OUTPUT_COL 2 

void distance(float x_1, float x_2, float y_1, float y_2, float z_1, float z_2);

float output[SIZE_OUTPUT][SIZE_OUTPUT_COL];

int main(){

  //Heap Allocation
	//int ** output = (int**) malloc(sizeof(int*) * SIZE_OUTPUT);
	//for (size_t ix = 0; ix < SIZE_OUTPUT; ++ix ){
  //		output[ix] = (int*) malloc(sizeof(int) * 2);
	//}

  //Stack Allocation
  //float output[SIZE_OUTPUT][SIZE_OUTPUT_COL];
  float input[10][3];
  float a = 0;

  input[0][0] = 4.105;
  input[0][1] = 0.883;
  input[0][2] = 6.158;

  input[1][0] = 2.355;
  input[1][1] = 2.489;
  input[1][2] = 7.404;

	for ( size_t ix = 0; ix < SIZE_OUTPUT; ++ix ){
  		for ( size_t jx = 0; jx < SIZE_OUTPUT_COL; ++jx ){
        if(jx == 0){
          output[ix][jx] = a;
          a = roundf((a +0.01)*100)/100;
        } else {
          output[ix][jx] = 0;
        }
  	 }
	}

  //Print out of the matrix
  for ( size_t ix = 0; ix < SIZE_OUTPUT; ++ix ){
    	printf("\n");
  	for ( size_t jx = 0; jx < SIZE_OUTPUT_COL; ++jx ){
  		printf("%f ", output[ix][jx]);
  	}
  }

  distance(input[0][0], input[1][0], input[0][1],input[1][1], input[0][2], input[1][2]);

  //free(output);

	return 0;
}

void distance(float x_1, float x_2, float y_1, float y_2, float z_1, float z_2) {
  //turn to float or use pacage for fixed point calucaltions
  int index; 

  //konverts value to index of matrix
  index = (int)(((roundf(sqrt((x_2-x_1)*(x_2-x_1)+(y_2-y_1)*(y_2-y_1)+(z_2-z_1)*(z_2-z_1)) * 100)/100)/ 0.01) +1);
  printf("%d\n", index);

  output[index][1] = output[index][1]+1;
}


