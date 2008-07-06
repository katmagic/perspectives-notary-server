
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flex_queue.h"

flex_queue *queue_init(int start_count, int elem_size) {
  flex_queue *q = (flex_queue*)malloc(sizeof(flex_queue));
  q->max_elems = start_count;
  q->elem_size = elem_size;
  q->data = (char*)malloc(start_count * elem_size);
  q->first_elem = q->last_elem = q->data;
  return q;
}

void queue_pushback(flex_queue *q, void *data_in) {
  char *array_back = q->data + (q->max_elems * q->elem_size);
  if(q->last_elem == array_back) {
    
    // preserve offsets in case realloc changes q->data
    int front_diff = q->first_elem - q->data; 
    int array_diff = q->last_elem - q->first_elem;
	q->max_elems *= 2;

    q->data = (char*)realloc(q->data,q->max_elems * q->elem_size); 
    q->first_elem = q->data + front_diff;
    q->last_elem = q->first_elem + array_diff;
  }
  memcpy(q->last_elem, data_in, q->elem_size);
  q->last_elem += q->elem_size; 
}


int queue_size(flex_queue *q) {
  return ((q->last_elem - q->first_elem) / q->elem_size);
}

// take a peek at data in a particular index 
void queue_peek(flex_queue *q, int index, void *data_out) {
  
  int offset, size = queue_size(q); 
  if(index < 0 || index >= size) { 
    printf("error: invalid index '%d' for queue of length '%d'\n", 
        index, size);
    return;
  }
 
  offset = index * q->elem_size;
  memcpy(data_out, q->first_elem + offset, q->elem_size); 
}

// should only be called if queue size is great than zero 
void queue_popfront(flex_queue *q, void *data_out) {
  int total_size, front_offset;
  float frac;
  if(queue_size(q) <= 0) { 
    printf("error: queue size is %d in 'get_front' \n", queue_size(q));
    return;
  }

  memcpy(data_out, q->first_elem, q->elem_size);
  q->first_elem += q->elem_size;

  total_size = q->max_elems * q->elem_size;
  front_offset = q->first_elem - q->data;  
  frac = ((float)front_offset) / ((float) total_size);
  if(front_offset > 10 && frac > 0.1) {
    // things are unbalanced enough, let's shift
    memmove(q->data, q->first_elem, q->last_elem - q->first_elem);
    q->first_elem -= front_offset;
    q->last_elem -= front_offset; 
  }
  
}

void queue_free(flex_queue *q) {
  free(q->data);
  free(q);
}

// just a wrapper to the standard qsort function
void queue_sort(flex_queue *q, int(*compar)(const void*, const void*)) {
  int num_members = queue_size(q); 
  qsort(q->first_elem, num_members, q->elem_size, compar);
}


/*  TEST MAIN - ignore 

int main(int argc, char** argv) {

  flex_queue *q = queue_init(1, sizeof(int));

  int i,j, result;
  for(i = 0; i < 100; i++) {
    queue_pushback(q, (char*)&i);
    printf("push: %d (size = %d) \n", i, queue_size(q));
    if(i % 10 == 0 && i != 0) {
      for(j = 0; j < 5; j++) {
        queue_popfront(q, (char*)&result);
        printf("pop: %d (size = %d )\n", result, queue_size(q));
      }
    }
  }
  
  while(queue_size(q) > 0) { 
        queue_popfront(q, (char*)&result);
        printf("pop: %d (size = %d )\n", result, queue_size(q));
  }
  queue_free(q);

  return 0;
}
*/

