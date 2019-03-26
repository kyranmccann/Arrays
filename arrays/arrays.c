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
  Array *array = malloc(sizeof(Array));

  // Set initial values for capacity and count
  array -> capacity = capacity;
  array -> count = 0;

  // Allocate memory for elements
  array -> elements = calloc(capacity, sizeof(char *));

  return array;

}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  for (int i = 0; i < arr -> count; i++)
  {
    if (arr -> elements[i] != NULL)
    {
      free(arr -> elements[i]);
    }
    else
    {
      break;
    }
  }

  if (arr -> elements != NULL)
  {
    free(arr -> elements);
  }
  // Free array
  if (arr != NULL)
  {
    free(arr);
  }

}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {

  // Create a new element storage with double capacity
  char **double_arr = malloc(2 * (arr -> capacity) * sizeof(char *));
  // Copy elements into the new storage
  memcpy(double_arr, arr -> elements, (arr -> capacity) * sizeof(char *));

  // Free the old elements array (but NOT the strings they point to)
  free(arr -> elements);

  // Update the elements and capacity to new values
  arr -> elements = double_arr;
  arr -> capacity = arr -> capacity * 2;

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
  if (index >= arr -> count)
  {
    printf("ERROR: Index out of bounds.\n");
    return NULL;
  }
  // Otherwise, return the element at the given index
  else
  {
    return arr -> elements[index];
  }
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if (index >= arr -> count && arr -> count != 0)
  {
    printf("ERROR: Index out of bounds.\n");
    return NULL;
  }

  // Resize the array if the number of elements is over capacity
  if (arr -> count == arr -> capacity)
  {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  for (int i = arr -> count - 1; i >= index; i--)
  {
    arr -> elements[i + 1] = arr -> elements[i];
  }

  // Copy the element and add it to the array
  arr -> elements[index] = strdup(element);

  // Increment count by 1
  arr -> count++;

}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr -> count == arr -> capacity)
  {
    resize_array(arr);
  }

  // Copy the element and add it to the end of the array
  arr -> elements[arr -> count] = strdup(element);
  // Increment count by 1
  arr -> count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  int tries = 0;
  while(strcmp(arr -> elements[tries], element) != 0 && tries < arr -> count)
  {
    tries++;
  }

  if (tries >= arr -> count)
  {
    printf("ERROR: Not found.\n");
    return NULL;
  }
  else
  {
    free(arr -> elements[tries]);
  }

  // Shift over every element after the removed element to the left one position
  for (int i = tries; i < arr -> count; i++ )
  {
    arr -> elements[i] = arr -> elements[i + 1];
  }

  // Decrement count by 1
  arr -> count--;

}


/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr) {
  printf("[");
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
