#include <stdio.h>
#include "operators.h"
#include "operands.h"
#include "calc.h"

char expression[MAX_LENGTH];

struct opt_prior priortity[] = {{'+',1},{'-',1},{'*',3},{'/',3},{'%',3},{'\0',2},{'(',2}};
static int pos = 0;
static double power(int base,int exp)
{
	double value = 1;
	for (;exp--;)
	  value = value * base;
	return value;
}
int check(void)
{
	int i = 0;
	while (expression[i])
	{
		switch (expression[i])
		{
			case '(':
				opt_push(expression[i]);
				i++;
				break;
			case ')':
				if (opt_pop())
				  i++;
				else return 0;
				break;
			case '+':
			case '-':
			case '*':
			case '/':
            {
                double num = 0;
                sscanf(expression + i + 1, "%lf", &num);
                if (num == 0.0) return 0;
            }
			case '%':
			case '.':
			case ' ':
			case '\n':
				i++;
				continue;
			default :
				if (expression[i] >= '0' && expression[i] <= '9')
				{
					i++;
					continue;
				}
				else
				{
					return 0;
				}
		}
	}
	if (opt_stack_is_empty())
	  return 1;
	else 
	{
		opt_clear();
		return 0;
	}
}

/*float atof_from_queue(queue q)
{
	char ch;
	float value = 0.0;
	char *q_front_backup = q->front;
	ch = out_queue(q);
	while (ch)
	{
		if (ch <= '0' || ch >= '9')
		{
			q->front = q_front_backup;
			*(q->front) = ch;
			return temp;
		}
		else
		{
			value = value * 10 + ch -'0';
			q_front_backup = q->front;
			ch = out_queue(q);
		}
	}
}*/
int get_prior(char opt)
{
	int i = 0;
	int size = sizeof(priortity) / sizeof(struct opt_prior);
	for (;i < size;i++)
	{
		if (opt == priortity[i].opt)
			return priortity[i].prior;
	}
	return 0;
}
int cmp_prior(char opt1,char opt2)
{
	return (get_prior(opt1) - get_prior(opt2));
}

float get_double_from_str(void)
{
	int dot_width = 1;
    double value = 0.0;
	while (expression[pos])
	{
		if (expression[pos] >='0' && expression[pos] <= '9')
		{	  
			value = value * 10 + expression[pos] - '0';
			pos++;
		}

		else if (expression[pos] == '.')
		{
			pos++;
			while (expression[pos] >='0' && expression[pos] <= '9')
			{
				value = value + (expression[pos] - '0') / power(10,dot_width);
				dot_width++;
				pos++;
			}
		}
		else
		  break;
	} 
	return value;
}
double figure(double left_value, double right_value, char opt)
{
	switch (opt)
	{
		case '+':
			return (left_value + right_value);
		case '-':
			return (left_value - right_value);
		case '*':
			return (left_value * right_value);
		case '/':
			return (left_value / right_value);
		case '%':
			return ((int)left_value % (int)right_value);
	}
}
void parse(void)
{
    double value,left_value,right_value;
	char opt;
	opt = expression[pos];
	while (opt)
	{
		if (opt == '(')
		{
			opt_push(opt);
			pos++;
		}
		else if (opt >= '0' && opt <= '9')
		{
            value = get_double_from_str();
			opr_push(value);
		}
		else if (opt == ')')
		{
			while (opt_get_top() != '(')
			{
				right_value = opr_pop();
				left_value = opr_pop();
				opt = opt_pop();
				value = figure(left_value,right_value,opt);
				printf("%f\n",value);
				opr_push(value);
			}
			opt_pop();
			pos++;
		}
		else 
		{
			if (cmp_prior(opt,opt_get_top()) > 0)
			{
				pos++;
                right_value = get_double_from_str();
				left_value = opr_pop();
				value = figure(left_value,right_value,opt);
				printf("%f\n",value);
				opr_push(value);
			}
			else
			{
				opt_push(opt);
				pos++;
			}
		}
		opt = expression[pos];
	}
		opt = opt_pop();
	while (opt)
	{
		if (opt != '(')
		{
			right_value = opr_pop();
			left_value = opr_pop();
			value = figure(left_value,right_value,opt);
			printf("%f\n",value);
			opr_push(value);
		}
		  opt = opt_pop();
	}
	pos = 0;
}
void  get_expression(void)
{
	char ch;
	int i;
	for (i = 0;(ch = getchar()) != '\n';i++)
	{
		if (ch == ' ')
		{
			i--;
			continue;
		}
		else
		  expression[i] = ch;
	}
	expression[i] = '\0';
}
