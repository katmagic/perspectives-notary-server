#ifndef _FLEX_QUEUE_H_
#define _FLEX_QUEUE_H_

typedef struct {
  char *data, *first_elem, *last_elem;
  int max_elems;
  int elem_size;

} flex_queue;

flex_queue *queue_init(int start_count, int elem_size);
void queue_pushback(flex_queue *q, char *data_in);
int queue_size(flex_queue *q);
void queue_popfront(flex_queue *q, char *data_out);
void queue_free(flex_queue *q);


#endif
