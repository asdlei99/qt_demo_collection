#include <stdio.h>
#include <stdlib.h>
#include "cqueue.h"
void queue_init(queue *q)
{
	*q = (queue)malloc(sizeof(struct cqueue));
	if (*q)
	  (*q)->front = (*q)->rear = (*q)->data;
	else
	{
		puts("Out of Memory");
		exit(1);
	}
}
int queue_is_empty(queue q)
{
	return (q->front == q->rear);
}
int queue_is_full(queue q)
{
	ele_type *top = q->data + 99;
	ele_type *base = q->data;
	if (((top - q->front + 1) + (q->rear - base + 1)) % 100 == 0)
	  return 1;
	else return 0;
}
void en_queue(queue q,ele_type elet)
{
	if (!queue_is_full(q))
	{
		if ((q->rear == q->data + 99))
		{
			*(q->rear) = elet;
			q->rear = q->data;
		}
		else
		{
			*(q->rear) = elet;
			q->rear++;
		}
	}
	else
	{
		printf("Queue is full\n");
	}
}
ele_type out_queue(queue q)
{
	if (!queue_is_empty(q))
	{
		int temp = *(q->front);
		*(q->front) = 0;
		if (q->front != q->data + 99)
			q->front++;
		else
			q->front = q->data;
		return temp;
		
	}
	else 
	{
		puts("Queue is empty");
	}
}
void str_to_queue(char *str,queue q)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\n')
		{
			str++;
			continue;
		}
		else
          //push(q,*str++);
            en_queue(q, *str++);
	}
    //push(q,'\0');
    en_queue(q,'\0');
}

