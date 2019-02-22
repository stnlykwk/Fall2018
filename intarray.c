/* 
 * intarr.c
 *
 * Provides a bounds-checked, resizable array of integers with
 * random-access and stack interfaces, and several utility functions
 * that operate on them.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Structure type that encapsulates our safe int array. */
typedef struct {
  int* data;
  unsigned int len;
} intarr_t;

/* A type for returning status codes */
typedef enum {
  INTARR_OK,
  INTARR_BADARRAY,
  INTARR_BADINDEX,
  INTARR_BADALLOC,
  INTARR_NOTFOUND
} intarr_result_t;

/* LAB 5 TASK 1 */

// Create a new intarr_t with initial size len.  If successful
// (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated intarr_t.  If unsuccessful, returns a null pointer.
intarr_t* intarr_create( unsigned int len ){
    intarr_t *new = malloc(sizeof(intarr_t));
    new->len = len;
    if(new == NULL){
      return NULL;
    }

      // printf("t1created\n");

      int *array = calloc(len,sizeof(int));

      new->data = array;

      for(int i = 0; i < len; i++){
        new->data[i] = 0;

      }

      return new;
}

// frees all memory allocated for ia. If the pointer is null, do
// nothing. If the ia->data is null, do not attempt to free it.
void intarr_destroy( intarr_t* ia ){
    if((ia == NULL) || ia->data == NULL){

        return;
    } else {

        free(ia);
    }
}

/* LAB 5 TASK 2 */

// If index is valid, set the value at ia->data[index] to val and return
// INTARR_OK. Otherwise, leave the array unmodified and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_set( intarr_t* ia, 
			    unsigned int index, 
			    int val )
{
  if(ia == NULL){

    return INTARR_BADARRAY;
  }

  if(index < ia->len){
    ia->data[index] = val;
    return INTARR_OK;
  } 
  else{
    return INTARR_BADINDEX;
  }
}

// If index is valid and i is non-null, set *i to ia->data[index] and return
// INTARR_OK. Otherwise no not modify *i and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_get( const intarr_t* ia, 
			    unsigned int index, 
			    int* i )
{
  if(ia == NULL){
    return INTARR_BADARRAY;
  }

  if((index < ia->len) && (i != NULL)){
    *i = ia->data[index];
    return INTARR_OK;
  } else {
    return INTARR_BADINDEX;
  }
}

/* LAB 5 TASK 3 */

// Return a duplicate of ia, allocating new storage for the duplicate
// data (we call this a "deep copy"). If unsuccessful (i.e. memory
// allocation for the copy fails, or ia is null), return a null pointer. 
intarr_t* intarr_copy( const intarr_t* ia ){
    if(ia == NULL){
        return NULL;
    }
    
    intarr_t *ia_copy = intarr_create(ia->len);

    if(ia_copy != NULL){

      for(int i = 0; i < ia_copy->len; i++){
        intarr_set(ia_copy, i, ia->data[i]);
      }
      return ia_copy;
    } else{
      return NULL;
    }
}

/* LAB 5 TASK 4 */

// sort ia by value smallest-to-largest, so that data[i] < data[i+1]
// for all valid i, then return INTARR_OK. Works in-place: contents of
// ia are sorted on return. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_sort( intarr_t* ia ){
  if(ia == NULL){
    return INTARR_BADARRAY;
  }
  else
  {
    int temp = 999;

    //qsort
    int cmpfunc (const void * a, const void * b) {
      return ( *(int*)a - *(int*)b );
    }
    qsort(ia->data, ia->len, sizeof(int), cmpfunc);

    return INTARR_OK;
  }
}

/* LAB 5 TASK 5 */

// Find the first occurance of the target in the array, searching from
// index 0. If the target is found and i is non-null, set *i to the
// location index and return INTARR_OK. If target does not occur in
// the array, leave *i unmodified and return INTARR_NOTFOUND. If ia is
// null, return INTARR_BADARRAY.
intarr_result_t intarr_find( intarr_t* ia, int target, int* i ){
  if(ia == NULL){
    return INTARR_BADARRAY;
  }

  for(int j = 0; j < ia->len; j++){
    if(ia->data[j] == target){
      *i = j;
      return INTARR_OK;
    }
  }
  return INTARR_NOTFOUND;
}

/* LAB 5 TASK 6 */

// Append val to the end of ia (allocating space for it). If
// successful, return INTARR_OK, otherwise return
// INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_push( intarr_t* ia, int val ){
  if(ia == NULL){
    return INTARR_BADARRAY;
  }

  int *newarray = realloc(ia->data, (1+ia->len)*sizeof(int));
  if(newarray == NULL){
    return INTARR_BADALLOC;
  } else {
    ia->data = newarray;
    (ia->len)++;
    intarr_set(ia, (ia->len)-1, val);
  }
  return INTARR_OK;
}

// If the array is not empty, remove the value with the highest index
// from the array, and, if i is non-null, set *i to the removed value,
// then return INTARR_OK. If the array is empty, leave *i unmodified
// and return INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_pop( intarr_t* ia, int* i ){
  if(ia == NULL){

    return INTARR_BADARRAY;
  } else if(ia->len == 0)
	{
      return INTARR_BADINDEX;
	} else if(i != NULL){
      *i = ia->data[(ia->len)-1];
      
      int *removed = realloc(ia->data, ((ia->len)-1)*sizeof(int));
      (ia->len)--;
  }
    return INTARR_OK;
  
}

/* LAB 5 TASK 7 */

// Resize ia to contain newlen values. If newlen is less than the
// original array length, the end of the array is discarded. If newlen
// is greater than the original array length, intialize all the new
// integers to zero. If the allocation is successful, return
// INTARR_OK, otherwise return INTARR_BADALLOC. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_resize( intarr_t* ia, unsigned int newlen ){
  if(ia == NULL){
    return INTARR_BADARRAY;
  }

  if(newlen < ia->len){
    int *smcopy = realloc(ia->data, newlen * sizeof(int));
    if(smcopy != NULL){
      
      ia->len = newlen;

      return INTARR_OK;
    }
  } else if(newlen >= ia->len){
      int *lgcopy = realloc(ia->data, newlen * sizeof(int));

      if(lgcopy != NULL){

        ia->data = lgcopy;

        for(int j = ia->len; j < newlen; j++){
          intarr_set(ia, j, 0);
        }
        ia->len = newlen;
        }
        return INTARR_OK;
    } else {
      return INTARR_BADALLOC;
    }
  }

/* LAB 5 TASK 8 */

// Get a deep copy of a portion of ia from index first to index last
// inclusive. If successful, return a pointer to a newly-allocated
// intarr_t containing a copy of the specfied section. If an error
// occurs, i.e. ia is null, first or last are out of bounds, last <
// first, or memory allocation fails, return a null pointer.
intarr_t* intarr_copy_subarray( intarr_t* ia, 
				unsigned int first, 
				unsigned int last )
{
  if((ia == NULL) || (last < first) || (first < 0) || (last >= ia->len)){
    return NULL;
  }

  int newlen = last - first + 1;

  intarr_t *newintarr = intarr_create(newlen);
  newintarr->len = newlen;

  if(newintarr == NULL || newintarr->data == NULL){
    return NULL;
  }

  for(int i = first, j = 0; i <= last; i++, j++){
    newintarr->data[j] = ia->data[i];
  }
  return newintarr;

}
