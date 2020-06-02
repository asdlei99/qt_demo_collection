#ifndef CALC_CQUEUE_H
#define CALC_CQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef char ele_type;
/**
 * 定义队列
 */
typedef struct cqueue
{
	ele_type data[100];
	ele_type *front,*rear;
}*queue;

void queue_init(queue *q);
int queue_is_empty(queue q);
int queue_is_full(queue q);
void en_queue(queue q,ele_type elet);
ele_type out_queue(queue q);
void str_to_queue(char *str,queue q);

#ifdef __cplusplus
}
#endif

#endif
