#include "operators.h"

char operators[128];

int opt_top = 0;

void opt_push(char ch)
{
	operators[opt_top] = ch;
	opt_top++;
}
char opt_pop(void)
{
	char temp;
	if (!opt_stack_is_empty())
	{
		temp = operators[--opt_top];
		operators[opt_top] = '\0';
		return temp;
	}
	else return '\0';
}
void opt_clear(void)
{
	while (!opt_stack_is_empty())
		opt_pop();
}
