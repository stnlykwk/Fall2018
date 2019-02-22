#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "intarr.h"


/* LAB 6 TASK 2 */

/*
  Save the entire array ia into a file called 'filename' in a JSON
  text file array file format that can be loaded by
  intarr_load_json(). Returns zero on success, or a non-zero error
  code on failure. Arrays of length 0 should produce an output file
  containing an empty array.
  
  The JSON output should be human-readable.

  Examples:

  The following line is a valid JSON array:
  [ 100, 200, 300 ]
  
  The following lines are a valid JSON array:
  [ 
   100, 
   200, 
   300 
  ]
*/
int intarr_save_json( intarr_t* ia, const char* filename ) 
{
//make sure input is not NULL
    if(ia == NULL) {
        puts("null input");
        return 1;
    }

//create file and check
    FILE *fp = fopen(filename, "w");

    if(fp == NULL) {
        puts("could not open file for writing");
        return 1;
    }
    else {
        puts("file opened");
    }

//write data
    int len = ia->len;

    fprintf(fp, "%c ", '[');

    if(len > 0) {
        for(int j = 1, i = 0; j < len; i++, j++) {
            fprintf(fp, "%i, ", ia->data[i]);
        }
        fprintf(fp, "%i ", ia->data[len-1]);
    }
    
    fprintf(fp, "%c", ']');
    
//close file
    puts("closing file");
    fclose(fp);
    puts("file closed");
    
    return 0;
}

/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save(). The file may contain an array
  of length 0. Returns a pointer to a newly-allocated intarr_t on
  success (even if that array has length 0), or NULL on failure.
*/
intarr_t* intarr_load_json( const char* filename ) {
    
    FILE *fp = fopen(filename, "r");
    
    if(fp == NULL) {
        puts("b could not open file\n");
        return NULL;
    }

    if(filename == NULL) {
        puts("b null filename\n");
        return NULL;
    }

    char c;
    int val, count = 0;

//get rid of '['
    fscanf(fp, "%c", &c);
    printf("c = %c\n", c);

    intarr_t* new_intarr = intarr_create(0);

//push elements to new_intarr until ']'
    while(fscanf(fp, "%i,", &val) == 1) {
        // if(val != ']') {
            intarr_push(new_intarr, val);
            count++;
        // }
        // if(val == ']') {
        //     printf("] the end\n");        
        // }
        printf("pushing %i\n", val);
    }
    //for last element
    // if(fscanf(fp, "%i", &val) == 1) {
    //     intarr_push(new_intarr, val);
    //     count++;
    // }
    printf("count: %i\n", count);
    printf("len: %i\n", new_intarr->len);

    fclose(fp);

    return new_intarr;
}