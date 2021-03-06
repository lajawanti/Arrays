#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;


/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array (int capacity) {
      // Allocate memory for the Array struct
      Array *arr = malloc(sizeof(Array));

      // Set initial values for capacity and count
      arr->capacity = capacity;
      arr->count = 0;

      // Allocate memory for elements
      arr->elements = calloc(capacity, sizeof(char *));
      return arr; //return type is Array struct...
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

      // Free all elements-- first
      for(int i = 0; i < arr->count; i++) {
            //arr->elements[i] = NULL;
            free(arr->elements[i]);
       }
      // Free array -- second
      free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

      // Create a new element storage with double capacity
      int capacity = 2 * arr->capacity;
      Array *new_arr = create_array(capacity);

      // Copy elements into the new storage
      for(int i = 0; i < arr->count; i++) {
            new_arr->elements[i] = arr->elements[i];
      }

      // Free the old elements array (but NOT the strings they point to)
      free(arr->elements);

      // Update the elements and capacity to new values
      arr->elements = new_arr->elements;
      arr->capacity = new_arr->capacity;
}



/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index) {

      // Throw an error if the index is greater than the current count
      if(index > arr->count) {
            printf("Error : Index is greater than the current count");
            exit(0);
      } else {
      // Otherwise, return the element at the given index
            return (arr->elements[index]);
      }
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {
      // printf("\n my function %s %d "  , element , index);
      // Throw an error if the index is greater than the current count
      if(index > arr->count) {
            printf("Error : Index is greater than the current count");
            exit(0);
      }
      // Resize the array if the number of elements is over capacity
      if(arr->count == arr->capacity){
            resize_array(arr);
      }
      // Move every element after the insert index to the right one position
      char *temp  = arr->elements[index];
      for( int i = index+1  ; i < arr->count+1 ; i++){
          char *temp2  =  arr->elements[i];     
          arr->elements[i] = temp;
          temp = temp2;
          printf(" \n Temp %s",  temp);
      }
      // Copy the element and add it to the array
      arr->elements[index] = element;
      // Increment count by 1
      arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

      // Resize the array if the number of elements is over capacity
      if(arr->count == arr->capacity){
            resize_array(arr);
      }
      // or throw an error if resize isn't implemented yet.

      // Copy the element and add it to the end of the array
      char *copy = element;
      arr->elements[arr->count] = copy;
      // Increment count by 1
      arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {
      printf("arr_remove  %s\n", element);
      int index_to_free = 0, flag = 0;

      // Search for the first occurence of the element and remove it.
      // Don't forget to free its memory!

      for(int i = 0; i < arr->count; i++) {
            printf("\narr->elements[%d]  : %s", i, arr->elements[i]);
            if(element == arr->elements[i]) { 
                index_to_free = i; 
                //free(arr->elements[i]);
                arr->elements[i] = NULL;
                flag = 1;
                printf("\nelement found at index  : %d", i);
            }  
            
            // Shift over every element after the removed element to the left one position
            if(flag == 1) {
                arr->elements[i] = arr->elements[i + 1]; 
            }
      }

      // Decrement count by 1
      if(flag == 1) {
            arr->count--;
      }
      else {
            printf("element not found...");
            exit(0);
      }
}


/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr) {
  printf("\n[");
  for (int i = 0 ; i < arr->count ; i++) {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1) {
      printf(",");
    }
  }
  printf("]\n");
}


#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
