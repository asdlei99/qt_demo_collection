#include "operands.h"

float operands[128];
int opr_top = 0;

void opr_push(double opr)
{
	operands[opr_top++] = opr;
}
double opr_pop(void)
{
	float temp;
	temp = operands[--opr_top];
	operands[opr_top] = 0.0;
	return temp;
}
void opr_clear(void)
{
	while (!opr_stack_is_empty())
	  opr_pop();
}
