#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "point_array.h"

/* ALL THESE FUNCTIONS REQUIRE A VALID POINT_ARRAY_T POINTER AS THEIR
   FIRST PARAMETER. THEY SHOULD FAIL ON ASSERTION IF THIS POINTER IS
   NULL */

/* TASK 1 */

// Safely initalize an empty array structure.
void point_array_init( point_array_t* pa ) {
  assert(pa);

    pa->points = NULL;
    pa->len = 0;
    pa->reserved = 0;
  
}

/* TASK 2 */

// Resets the array to be empty, freeing any memory allocated if
// necessary.
void point_array_reset( point_array_t* pa ) {
  assert(pa);

  if(pa->points != NULL) {
    free(pa->points);
  }

//set pa->points to NULL and change pa->len to 0
  pa->points = NULL;
  pa->len = 0;
}

/* TASK 3 */

// Append a point to the end of an array. If successful, return 0,
// else return 1;
int point_array_append( point_array_t* pa, point_t* p ) {
  assert(pa);
  assert(p);

  //realloc memory to add p
    point_t *new = realloc(pa->points, (pa->len + 1) * sizeof(point_t));
    if(new == NULL) {
      return 1;
    }
  //point to new location of array
    pa->points = new; 

  //append p and increase length by one
    pa->points[pa->len] = *p;
    pa->len += 1;
    
    return 0;   
}

/* TASK 4 */

// Remove the point at index i from the array, reducing the size of
// the array by one. The order of points in the array may change.
int point_array_remove( point_array_t* pa, unsigned int i ) {
  assert(pa);

  if(i >= pa->len || i < 0) {
    return 1;
  } else {
  //copy last element into removed element's place, free, reduce len
    pa->points[i] = pa->points[pa->len-1];
    pa->len -= 1;

    return 0;
  }


}

