#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>

const int scale = 8;
const char * delim = " ,\n";

#define FLOAT_TO_FIXED(x) (x * (float)(1<<scale))
//#define INT_TO_FIXED(x) (x << scale) 
//#define FIXED_TO_INT(x) (x >> scale)
#define FIXED_TO_FLOAT(x) ((float)x / (float)(1<<scale))
#define SIZE_OUTPUT 3466
#define SIZE_OUTPUT_COL 2 

float string_to_float(const char * str);
void distance(int input_x_1, int input_x_2, int input_y_1, int input_y_2, int input_z_1, int input_z_2);
int float_index(float input);

double output[SIZE_OUTPUT][SIZE_OUTPUT_COL];

int jappba;

int main() {
  
  FILE * fcells;
  fcells = fopen("test_cells.txt", "r");
  
  char * cells = (char*) malloc(sizeof(char) * 50*1000000);
  //for(int i = 0; i < 6; ++i) {
    fread(cells, sizeof("+00.00"), 50*1000000, fcells);
    //}

  char * coordinates_strings = strtok(cells, delim);
  int * coordinates_fixed = (int *) malloc(sizeof(int) * 50*1000000);  
  
  int input[100000][3];
  int index = 0;

  while(coordinates_strings != NULL) {   
    // index / 3 signifies rows, index % 3 columns
    input[index / 3][index % 3] = FLOAT_TO_FIXED(string_to_float(coordinates_strings));
    //printf("%f \n", FIXED_TO_FLOAT(input[index / 3][index % 3]));

    index++;
    coordinates_strings = strtok(NULL, delim);
  }

  double a = 0;

  for (size_t ix = 0; ix < SIZE_OUTPUT; ++ix ){
        output[ix][0] = a;
        a = a+0.01;

        output[ix][1] = 0;
  }

  int n = (sizeof(input)/sizeof(int))/3;

  int count = 0;

#pragma omp parallel for reduction(+:output) num_threads(20)
  for (size_t i = 0; i < n-1; ++i){
    for(size_t j = i+1; j < n; ++j){
      //distance(input[i][0],input[j][0],input[i][1],input[j][1],input[i][2],input[j][2]);
  		float x_1 = FIXED_TO_FLOAT(input[i][0]);
  		float y_1 = FIXED_TO_FLOAT(input[i][1]);
  		float z_1 = FIXED_TO_FLOAT(input[i][2]);

  		float x_2 = FIXED_TO_FLOAT(input[j][0]);
  		float y_2 = FIXED_TO_FLOAT(input[j][1]);
  		float z_2 = FIXED_TO_FLOAT(input[j][2]);

  		int index; 
  		index = (int)((sqrt((x_2-x_1)*(x_2-x_1)+(y_2-y_1)*(y_2-y_1)+(z_2-z_1)*(z_2-z_1)) * 100)+1.5);

  		output[index][1] = output[index][1]+1;

    	}
  	}

  printf("%d\n", count);

  FILE * op;
  op = fopen("output.txt", "w");

  for ( size_t ix = 0; ix < SIZE_OUTPUT; ++ix ){
      fprintf(op, "%f %f\n", output[ix][0], output[ix][1]);
  }
  //printf("%d", jappba);

  return 0;
}

void distance(int input_x_1, int input_x_2, int input_y_1, int input_y_2, int input_z_1, int input_z_2) {
  float x_1 = FIXED_TO_FLOAT(input_x_1);
  float y_1 = FIXED_TO_FLOAT(input_y_1);
  float z_1 = FIXED_TO_FLOAT(input_z_1);

  float x_2 = FIXED_TO_FLOAT(input_x_2);
  float y_2 = FIXED_TO_FLOAT(input_y_2);
  float z_2 = FIXED_TO_FLOAT(input_z_2);

  int index; 
  index = (int)((sqrt((x_2-x_1)*(x_2-x_1)+(y_2-y_1)*(y_2-y_1)+(z_2-z_1)*(z_2-z_1)) * 100)+1.5);

  output[index][1] = output[index][1]+1;
}

float  string_to_float(const char * str) {
  // defining the float value itself and its sign
  float value = 0, sign = 1;
  
  // if first character in string is a dash, make float negative
  if (*str == '-') {
    str++;
    sign = -1;
  }  
  
  // loop searching for decimal point in string
  for (int dec_pt_found = 0; *str; str++){
    // confirm when it's found
    if (*str == '.') {
      dec_pt_found = 1;
      continue;
    }
    
    //assigning each digits position in float
    int d = *str - '0';
    if (d >= 0 && d <= 9) {
      // determining position of decimal point in float
      if(dec_pt_found == 1) {
	sign /= 10.0f;
      }
      value = value * 10.0f + (float)d;
    }
  }
  // NOTE TO SELF: check if you can return fewer decimals
  return value * sign;
}
